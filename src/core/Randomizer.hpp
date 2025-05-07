#pragma once
#include "BytesHelper.hpp"
#include "Data.hpp"
#include "json.hpp"
#include <Windows.h>
#include <cstdint>
#include <filesystem>
#include <random>
#include <string>
#include <thread>
#include <algorithm>
#include <type_traits>
#include <unordered_map>
#include <vector>

using json = nlohmann::json;

struct randomizer_t
{
private:
  std::mt19937 rng;

  // Static data
  data_pack_t& data_pack;
  options_pack_t& options_pack;

  // Dynamically populated data
  std::unordered_map<int, item_t*> all_items;
  std::unordered_map<int, item_t*> all_non_key_items;
  std::unordered_map<int, item_t*> all_key_items;
  std::vector<gear_data_t*> all_armor;
  std::vector<gear_data_t*> all_weapons;
  std::vector<uint16_t> abilities;
  std::vector<uint8_t> weapon_formulas;
  std::vector<uint8_t> def_pool;
  std::vector<uint8_t> mdef_pool;
  std::vector<uint8_t> eva_pool;
  std::vector<uint16_t> original_sphere_grid_node_ids;
  std::vector<uint16_t> standard_sphere_grid_node_ids;
  std::vector<uint16_t> expert_sphere_grid_node_ids;

  // Shuffled vectors
  std::vector<character_stats_t*> shuffled_player_stats_data;
  std::vector<aeon_scaling_data_t*> shuffled_aeon_scaling_data;
  std::vector<aeon_stat_data_t*> shuffled_aeon_stat_data;
  std::vector<uint16_t> shuffled_original_sphere_grid_node_ids;
  std::vector<uint16_t> shuffled_standard_sphere_grid_node_ids;
  std::vector<uint16_t> shuffled_expert_sphere_grid_node_ids;

public:
  std::string prefix;
  std::string btl_kernel_input;
  std::string btl_kernel_output;

  json json_data;

  randomizer_t( options_pack_t& options_pack,
                data_pack_t& data_pack )
    :
    data_pack( data_pack ),
    options_pack( options_pack ),
    all_items(),
    all_non_key_items(),
    all_key_items(),
    all_armor(),
    all_weapons(),
    abilities(),
    def_pool(),
    mdef_pool(),
    eva_pool(),
    original_sphere_grid_node_ids(),
    standard_sphere_grid_node_ids(),
    expert_sphere_grid_node_ids(),
    shuffled_player_stats_data(),
    shuffled_aeon_scaling_data(),
    shuffled_aeon_stat_data(),
    shuffled_original_sphere_grid_node_ids(),
    shuffled_standard_sphere_grid_node_ids(),
    shuffled_expert_sphere_grid_node_ids(),
    prefix( options_pack.fahrenheit ? FAHRENHEIT_PREFIX : "" ),
    btl_kernel_input( INPUT_FOLDER + BATTLE_KERNEL_FOLDER ),
    btl_kernel_output( OUTPUT_FOLDER + prefix + BATTLE_KERNEL_FOLDER ),
    json_data()
  {
    rng.seed( options_pack.seed );

    json_data = {
      { "Name", NAME },
      { "Desc", DESCRIPTION },
      { "Authors", AUTHOR },
      { "Link", "https://github.com/nyterage/FFXRando" },
      { "DllList", json::array() },
      { "Dependencies", json::array() },
      { "LoadAfter", json::array() },
      { "Version", VERSION },
      { "Seed", options_pack.seed_text }
    };

    getFieldItems();
    getShopItems();
    getMonsterItems();

    if (options_pack.shuffle_sphere_grid)
      getSphereGridNodeIds();

    poplateGearLists();
    populateAbilityData();
    populateWeaponFormulas();
    randomize();
  }

  template <typename T>
  T uniform( T min, T max ) {
    static_assert( std::is_integral<T>::value, "Only integral types are supported" );

    using DistType = typename std::conditional<sizeof( T ) <= 2, uint32_t, T>::type;

    std::uniform_int_distribution<DistType> dist( min, max );
    return static_cast< T >( dist( rng ) );
  }

  template <typename T>
  T normal( T mean, T stddev, T min, T max ) {
    static_assert( std::is_integral<T>::value, "Only integral types are supported" );
    if (mean == 0)
      return 0;

    if (stddev == 0)
      return mean;

    std::normal_distribution<double> dist( static_cast< double >( mean ), static_cast< double >( stddev ) );
    T number;
    do
    {
      double sampled = dist( rng );
      number = static_cast< T >( std::round( sampled ) );
    }
    while (number < min || number > max);

    return number;
  }

  void writeJson( json& j )
  {
    if (!options_pack.fahrenheit)
      return;

    std::cout << std::setw( 4 ) << j << std::endl;
    std::ofstream file( OUTPUT_FOLDER + "FFXRando/FFXRando.manifest.json" );
    file.write( j.dump( 4 ).c_str(), j.dump( 4 ).size() );
  }

  template <typename T>
  void genericReconstructor( const std::string& input_path, const std::string& output_path, const std::string& filename, std::vector<T*>& vector, bool has_header = false )
  {
    std::vector<char> reconstructed_bytes;
    std::string full_path = input_path + filename;
    std::vector<char> bytes = bytes_mapper_t::fileToBytes( full_path );

    if (has_header)
      bytes = std::vector<char>( bytes.begin(), bytes.begin() + 20 );

    reconstructed_bytes.insert( reconstructed_bytes.end(), bytes.begin(), bytes.end() );

    for (auto& element : vector)
    {
      std::vector<char> element_bytes = element->bytes;
      reconstructed_bytes.insert( reconstructed_bytes.end(), element_bytes.begin(), element_bytes.end() );
    }

    std::filesystem::create_directories( output_path );
    std::string file = output_path + filename;
    bytes_mapper_t::writeBytesToNewFile( reconstructed_bytes, file );
  }

  // TODO: Clean up this mess of repetitive code
  void reconstructBukiData()
  {
    std::string name = "buki_get.bin";
    genericReconstructor( btl_kernel_input, btl_kernel_output, name, data_pack.buki_data, true );
  }

  void reconstructWeaponData()
  {
    std::string name = "weapon.bin";
    genericReconstructor( btl_kernel_input, btl_kernel_output, name, data_pack.weapon_data, true );
  }

  void reconstructShopArmsData()
  {
    std::string name = "shop_arms.bin";
    genericReconstructor( btl_kernel_input, btl_kernel_output, name, data_pack.shop_arms_data, true );
  }

  void reconstructTakaraData()
  {
    std::string name = "takara.bin";
    genericReconstructor( btl_kernel_input, btl_kernel_output, name, data_pack.field_data, true );
  }

  void reconstructItemShopData()
  {
    std::string name = "item_shop.bin";
    genericReconstructor( btl_kernel_input, btl_kernel_output, name, data_pack.item_shop_data, true );
  }

  void reconstructArmsShopData()
  {
    std::string name = "arms_shop.bin";
    genericReconstructor( btl_kernel_input, btl_kernel_output, name, data_pack.gear_shop_data, true );
  }

  void reconstructItemRateData()
  {
    std::string name = "item_rate.bin";
    genericReconstructor( btl_kernel_input, btl_kernel_output, name, data_pack.item_rate_data, true );
  }

  void reconstructArmsRateData()
  {
    std::string name = "arms_rate.bin";
    genericReconstructor( btl_kernel_input, btl_kernel_output, name, data_pack.arms_rate_data, true );
  }

  void reconstructPlayerStatsData()
  {
    for (auto& locale : LOCALIZATIONS)
    {
      std::string path = INPUT_FOLDER + locale.second + "ply_save.bin";
      std::vector<char> original_bytes = bytes_mapper_t::fileToBytes( path );
      for (size_t j = 0; j < data_pack.player_stats_data.size(); j++)
      {
        character_stats_t& player_stats = *data_pack.player_stats_data[ j ];
        std::vector<char> player_stats_bytes = player_stats.bytes;
        for (size_t i = 0; i < player_stats_bytes.size(); i++)
        {
          original_bytes[ 20 + j * player_stats_bytes.size() + i ] = player_stats_bytes[ i ];
        }
      }
      std::string output_path = OUTPUT_FOLDER + prefix + locale.second;
      std::filesystem::create_directories( output_path );
      std::string file = output_path + "ply_save.bin";
      bytes_mapper_t::writeBytesToNewFile( original_bytes, file );
    }
  }

  void reconstructAeonScalingData()
  {
    for (auto& locale : LOCALIZATIONS)
    {
      std::string path = INPUT_FOLDER + locale.second + "ply_rom.bin";
      std::vector<char> original_bytes = bytes_mapper_t::fileToBytes( path );
      for (size_t j = 0; j < data_pack.aeon_scaling_data.size(); j++)
      {
        aeon_scaling_data_t& aeon_scaling = *data_pack.aeon_scaling_data[ j ];
        std::vector<char> aeon_scaling_bytes = aeon_scaling.bytes;
        for (size_t i = 0; i < aeon_scaling_bytes.size(); i++)
        {
          original_bytes[ 20 + j * aeon_scaling_bytes.size() + i ] = aeon_scaling_bytes[ i ];
        }
      }
      std::string output_path = OUTPUT_FOLDER + prefix + locale.second;
      std::filesystem::create_directories( output_path );
      std::string file = output_path + "ply_rom.bin";
      bytes_mapper_t::writeBytesToNewFile( original_bytes, file );
    }
  }

  void reconstructAeonStatData()
  {
    std::string path = INPUT_FOLDER + BATTLE_KERNEL_FOLDER + "sum_assure.bin";
    std::vector<char> original_bytes = bytes_mapper_t::fileToBytes( path );
    for (size_t j = 0; j < data_pack.aeon_stat_data.size(); j++)
    {
      aeon_stat_data_t& aeon_stats = *data_pack.aeon_stat_data[ j ];
      std::vector<char> aeon_stat_bytes = aeon_stats.bytes;
      for (size_t i = 0; i < aeon_stat_bytes.size(); i++)
      {
        original_bytes[ 20 + j * aeon_stat_bytes.size() + i ] = aeon_stat_bytes[ i ];
      }
    }
    std::string output_path = OUTPUT_FOLDER + prefix + BATTLE_KERNEL_FOLDER;
    std::filesystem::create_directories( output_path );
    std::string file = output_path + "sum_assure.bin";
    bytes_mapper_t::writeBytesToNewFile( original_bytes, file );
  }

  void reconstructSphereGridData()
  {
    for (auto& grid : data_pack.sphere_grid_data)
    {
      //std::string name = "dat0" + std::to_string( grid->type + 1 ) + ".dat";
      //std::string string = "Reconstructing " + name + "...";
      //std::cout << string << std::endl;
      //std::string path = INPUT_FOLDER + ABMAP_FOLDER + name;
      std::string output_path = OUTPUT_FOLDER + prefix + ABMAP_FOLDER;
      std::filesystem::create_directories( output_path );
      //std::string file = output_path + name;
      //bytes_mapper_t::writeBytesToNewFile( grid->bytes, file );

      std::string content_name;

      switch (grid->type)
      {
        case SPHERE_GRID_ORIGINAL:
          content_name = "dat09.dat";
          break;
        case SPHERE_GRID_STANDARD:
          content_name = "dat10.dat";
          break;
        case SPHERE_GRID_EXPERT:
          content_name = "dat11.dat";
          break;
        default:
          break;
      }
      std::string content_string = "Reconstructing " + content_name + "...";
      std::cout << content_string << std::endl;
      std::string content_path = INPUT_FOLDER + ABMAP_FOLDER + content_name;
      std::vector<char> content_bytes;
      content_bytes.insert( content_bytes.end(), grid->full_content_bytes.begin(), grid->full_content_bytes.end() );
      std::string content_file = output_path + content_name;
      bytes_mapper_t::writeBytesToNewFile( content_bytes, content_file );
    }
  }

  void checkItemList( uint16_t& id, uint8_t& quantity, bool key = false )
  {
    bool key_item = key;
    if (id == 0)
      return;
    if (quantity == 0)
      quantity = 1;
    if (id > 9000)
      key_item = true;

    std::unordered_map<int, item_t*>::iterator it = all_items.find( id );

    bool found = it != all_items.end();
    if (!found)
    {
      item_t* item = new item_t( id, quantity, quantity );
      all_items.insert( { id , item } );
      if (!key_item)
        all_non_key_items.insert( { id , item } );
      if (key_item)
        all_key_items.insert( { id , item } );
    }
    else
    {
      item_t& item = *all_items.at( id );
      if (item.getMinQuantity() > quantity)
        item.setMinQuantity( quantity );
      if (item.getMaxQuantity() < quantity)
        item.setMaxQuantity( quantity );
    }
  }

  void getFieldItems()
  {
    for (auto& item : data_pack.field_data)
    {
      field_data_t& field = *item;
      if (field.flag == 2 || field.flag == 10)
        checkItemList( field.type, field.quantity, field.flag == 10 );
    }
  }

  void getMonsterItems()
  {
    for (auto& enemy : data_pack.enemy_data)
    {
      enemy_loot_data_t& loot = *enemy->loot_data;
      checkItemList( loot.primary_normal_drop, loot.n_primary_normal_drop );
      checkItemList( loot.primary_normal_drop_rare, loot.n_primary_normal_drop_rare );
      checkItemList( loot.secondary_normal_drop, loot.n_secondary_normal_drop );
      checkItemList( loot.secondary_normal_drop_rare, loot.n_secondary_normal_drop_rare );
      checkItemList( loot.primary_normal_drop_overkill, loot.n_primary_normal_drop_overkill );
      checkItemList( loot.primary_normal_drop_overkill_rare, loot.n_primary_normal_drop_overkill_rare );
      checkItemList( loot.secondary_normal_drop_overkill, loot.n_secondary_normal_drop_overkill );
      checkItemList( loot.secondary_normal_drop_overkill_rare, loot.n_secondary_normal_drop_overkill_rare );
      checkItemList( loot.steal_item, loot.n_steal_item );
      checkItemList( loot.steal_item_rare, loot.n_steal_item_rare );
      checkItemList( loot.bribe_item, loot.n_bribe_item );
    }
  }

  void getShopItems()
  {
    uint8_t quantity = 1;
    for (auto& shop : data_pack.item_shop_data)
    {
      shop_data_t& item_shop = *shop;
      for (auto& item : item_shop.item_indexes)
      {
        checkItemList( item, quantity );
      }
    }
  }

  void getSphereGridNodeIds()
  {
    for (auto& grid : data_pack.sphere_grid_data)
    {
      for (auto& node : grid->nodes)
      {
        switch (grid->type)
        {
          case SPHERE_GRID_ORIGINAL:
            original_sphere_grid_node_ids.push_back( node->original_content );
            break;
          case SPHERE_GRID_STANDARD:
            standard_sphere_grid_node_ids.push_back( node->original_content );
            break;
          case SPHERE_GRID_EXPERT:
            expert_sphere_grid_node_ids.push_back( node->original_content );
            break;
          default:
            std::cerr << "Unknown sphere grid type: " << grid->type << std::endl;
            break;
        }
      }
    }
  }

  item_t* getRandomItemFromMap( std::unordered_map<int, item_t*>& map )
  {
    std::vector<item_t*> items;
    for (auto& item : map)
      items.push_back( item.second );

    std::uniform_int_distribution<size_t> dist( 0, items.size() - 1 );
    int index = dist( rng );
    return items[ index ];
  }

  int getRandomItemQuantity( item_t* item, bool is_monster = true )
  {
    if (options_pack.keep_things_sane)
    {
      if (is_monster)
        return uniform<uint8_t>( 1, 4 );
      if (item->getAverageQuantity() > 2 && item->getMaxQuantity() > item->getMinQuantity() + 1)
        return normal<uint8_t>( item->getAverageQuantity(), item->getStandardDeviation(), item->getMinQuantity(), item->getMaxQuantity() );
      else if (item->getMaxQuantity() > item->getMinQuantity())
        return uniform<uint8_t>( item->getMinQuantity(), item->getMaxQuantity() );
      else
        return item->getMinQuantity();
    }

    return uniform<uint8_t>( 0, 99 );
  }

  void randomizeEnemyDrops( enemy_data_t* enemy )
  {
    enemy_loot_data_t& loot = *enemy->loot_data;
    if (options_pack.keep_things_sane)
    {
      if (loot.gil > 0)
        loot.gil = normal<uint16_t>( loot.gil, loot.gil / 2, loot.gil * 0.05, static_cast< uint16_t >( std::min<double>( loot.gil * 3, UINT16_MAX ) ) );
      else
        loot.gil = 0;
      if (loot.ap > 0)
        loot.ap = normal<uint16_t>( loot.ap, loot.ap / 2, loot.ap * 0.05, static_cast< uint16_t >( std::min<double>( loot.ap * 3, UINT16_MAX ) ) );
      else
        loot.ap = 0;
      if (loot.ap_overkill > 0)
        loot.ap_overkill = normal<uint16_t>( loot.ap_overkill, loot.ap_overkill / 2, loot.ap_overkill * 0.05, static_cast<uint16_t>( std::min<double>( loot.ap_overkill * 3, UINT16_MAX ) ) );
      else
        loot.ap_overkill = 0;
    }
    else
    {
      loot.gil = uniform<uint16_t>( 1, UINT16_MAX );
      loot.ap = uniform<uint16_t>( 1, UINT16_MAX );
      loot.ap_overkill = uniform<uint16_t>( 1, UINT16_MAX );
    }
    item_t* normal_drop = getRandomItemFromMap( options_pack.randomize_key_items ? all_items : all_non_key_items );
    int normal_drop_quantity = getRandomItemQuantity( normal_drop );
    item_t* rare_drop = getRandomItemFromMap( options_pack.randomize_key_items ? all_items : all_non_key_items );
    int rare_drop_quantity = getRandomItemQuantity( rare_drop );
    item_t* secondary_normal_drop = getRandomItemFromMap( options_pack.randomize_key_items ? all_items : all_non_key_items );
    int secondary_normal_drop_quantity = getRandomItemQuantity( secondary_normal_drop );
    item_t* secondary_rare_drop = getRandomItemFromMap( options_pack.randomize_key_items ? all_items : all_non_key_items );
    int secondary_rare_drop_quantity = getRandomItemQuantity( secondary_rare_drop );
    item_t* normal_overkill_drop = getRandomItemFromMap( options_pack.randomize_key_items ? all_items : all_non_key_items );
    int normal_overkill_drop_quantity = getRandomItemQuantity( normal_overkill_drop );
    item_t* rare_overkill_drop = getRandomItemFromMap( options_pack.randomize_key_items ? all_items : all_non_key_items );
    int rare_overkill_drop_quantity = getRandomItemQuantity( rare_overkill_drop );
    item_t* secondary_overkill_drop = getRandomItemFromMap( options_pack.randomize_key_items ? all_items : all_non_key_items );
    int secondary_overkill_drop_quantity = getRandomItemQuantity( secondary_overkill_drop );
    item_t* secondary_rare_overkill_drop = getRandomItemFromMap( options_pack.randomize_key_items ? all_items : all_non_key_items );
    int secondary_rare_overkill_drop_quantity = getRandomItemQuantity( secondary_rare_overkill_drop );
    loot.primary_normal_drop = normal_drop->id;
    loot.primary_normal_drop_rare = rare_drop->id;
    if (options_pack.keep_things_sane && loot.primary_drop_chance > 0 )
      loot.primary_drop_chance = normal<uint8_t>( loot.primary_drop_chance, loot.primary_drop_chance / 2, 0, 255 );
    else
      loot.primary_drop_chance = uniform<uint8_t>( 0, 255 );
    loot.secondary_normal_drop = secondary_normal_drop->id;
    loot.secondary_normal_drop_rare = secondary_rare_drop->id;
    if (options_pack.keep_things_sane && loot.secondary_drop_chance > 0)
      loot.secondary_drop_chance = normal<uint8_t>( loot.secondary_drop_chance, loot.secondary_drop_chance / 2, 0, 255 );
    else
      loot.secondary_drop_chance = uniform<uint8_t>( 0, 255 );
    loot.primary_normal_drop_overkill = normal_overkill_drop->id;
    loot.primary_normal_drop_overkill_rare = rare_overkill_drop->id;
    loot.secondary_normal_drop_overkill = secondary_overkill_drop->id;
    loot.secondary_normal_drop_overkill_rare = secondary_rare_overkill_drop->id;
    loot.n_primary_normal_drop = normal_drop_quantity;
    loot.n_primary_normal_drop_rare = rare_drop_quantity;
    loot.n_secondary_normal_drop = secondary_normal_drop_quantity;
    loot.n_secondary_normal_drop_rare = secondary_rare_drop_quantity;
    loot.n_primary_normal_drop_overkill = normal_overkill_drop_quantity;
    loot.n_primary_normal_drop_overkill_rare = rare_overkill_drop_quantity;
    loot.n_secondary_normal_drop_overkill = secondary_overkill_drop_quantity;
    loot.n_secondary_normal_drop_overkill_rare = secondary_rare_overkill_drop_quantity;
    if (options_pack.randomize_weapon_attack_power && loot.gear_attack_power > 0 )
    {
      if (options_pack.keep_things_sane)
        loot.gear_attack_power = normal<uint8_t>( loot.gear_attack_power, loot.gear_attack_power / 2, 1, 24 );
      else
        loot.gear_attack_power = uniform<uint8_t>( 1, 100 );
    }
    if (options_pack.randomize_weapon_crit && loot.gear_crit_bonus > 0 )
    {
      if (options_pack.keep_things_sane)
        loot.gear_crit_bonus = normal<uint8_t>( loot.gear_crit_bonus, loot.gear_crit_bonus / 2, 0, 100 );
      else
        loot.gear_crit_bonus = uniform<uint8_t>( 1, 100 );
    }
    if (options_pack.randomize_weapon_damage_formula && loot.gear_damage_calc > 0 )
    {
      loot.gear_damage_calc = getRandomFormula();
    }
    loot.writeToBytes();
    enemy->loot_data = &loot;
    enemy->writeLootData( loot );
  };

  void randomizeEnemySteal( enemy_data_t* enemy )
  {
    enemy_loot_data_t& loot = *enemy->loot_data;
    item_t* steal_item = getRandomItemFromMap( options_pack.randomize_key_items ? all_items : all_non_key_items );
    int steal_item_quantity = getRandomItemQuantity( steal_item );
    item_t* rare_steal_item = getRandomItemFromMap( options_pack.randomize_key_items ? all_items : all_non_key_items );
    int rare_steal_item_quantity = getRandomItemQuantity( rare_steal_item );
    if (options_pack.keep_things_sane && loot.steal_chance > 0 )
      loot.steal_chance = normal<uint8_t>( loot.steal_chance, loot.steal_chance / 2, 0, 255 );
    else
      loot.steal_chance = uniform<int>( 0, 255 );
    loot.steal_item = steal_item->id;
    loot.steal_item_rare = rare_steal_item->id;
    loot.n_steal_item = steal_item_quantity;
    loot.n_steal_item_rare = rare_steal_item_quantity;
    if (loot.n_gil_steal > 0)
    {
      if (options_pack.keep_things_sane )
        loot.n_gil_steal = normal<uint16_t>( loot.n_gil_steal, loot.n_gil_steal / 2, 1, UINT16_MAX );
      else
        loot.n_gil_steal = uniform<uint16_t>( 1, UINT16_MAX );
    }
    loot.writeToBytes();
    enemy->loot_data = &loot;
    enemy->writeLootData( loot );
  }

  void randomizeEnemyBribe( enemy_data_t* enemy )
  {
    enemy_loot_data_t& loot = *enemy->loot_data;
    item_t* bribe_item = getRandomItemFromMap( options_pack.randomize_key_items ? all_items : all_non_key_items );
    int bribe_item_quantity = getRandomItemQuantity( bribe_item );
    loot.bribe_item = bribe_item->id;
    loot.n_bribe_item = bribe_item_quantity;
    loot.writeToBytes();
    enemy->loot_data = &loot;
    enemy->writeLootData( loot );
  }

  void randomizeEnemyStatsNormal( enemy_data_t* enemy )
  {
    if (enemy->monster_id == "211" || enemy->monster_id == "237")
      return;
    enemy_stat_data_t& stats = *enemy->stats_data;
    if (stats.hp <= 1)
      return;
    if (stats.hp > 1)
      stats.hp = normal<uint32_t>( stats.hp, stats.hp / 2, 50, UINT32_MAX );
    if (stats.hp < 50)
      stats.hp = 50;
    stats.mp = normal<uint32_t>( stats.mp, stats.mp / 2, 1, 999 );
    stats.overkill_threshold = normal<uint32_t>( stats.overkill_threshold / 2, stats.overkill_threshold, 1, UINT32_MAX );
    stats.str = normal<uint8_t>( stats.str, stats.str / 2, 0, UINT8_MAX );
    stats.def = normal<uint8_t>( stats.def, stats.def / 2, 0, UINT8_MAX );
    stats.mag = normal<uint8_t>( stats.mag, stats.mag / 2, 0, UINT8_MAX );
    stats.mdef = normal<uint8_t>( stats.mdef, stats.mdef / 2, 0, UINT8_MAX );
    stats.agi = normal<uint8_t>( stats.agi, stats.agi / 2, 0, UINT8_MAX );
    stats.acc = normal<uint8_t>( stats.acc, stats.acc / 2, 0, UINT8_MAX );
    stats.flags1.bits.armored = rand() % 4 == 0;
    stats.writeToBytes();
    enemy->stats_data = &stats;
    enemy->writeStatsData( stats );
  }

  void addEnemyDefenses( enemy_data_t* enemy )
  {
    enemy_stat_data_t& stats = *enemy->stats_data;
    if (stats.hp <= 1)
      return;
    def_pool.push_back( stats.def );
    mdef_pool.push_back( stats.mdef );
    eva_pool.push_back( stats.eva );
  }

  void randomizeEnemyStatsDefensiveNormalization( enemy_data_t* enemy )
  {
    if (enemy->monster_id == "211" || enemy->monster_id == "237")
      return;
    enemy_stat_data_t& stats = *enemy->stats_data;
    if (stats.hp <= 1)
      return;

    if (stats.mp > 0)
      stats.mp = normal<uint32_t>( stats.mp, stats.mp / 2, 1, 999 );

    stats.overkill_threshold = normal<uint32_t>( stats.overkill_threshold, stats.overkill_threshold / 2, 1, UINT32_MAX );
    stats.str = normal<uint8_t>( stats.str, stats.str / 2, 0, UINT8_MAX );

    std::uniform_int_distribution<size_t> dist( 0, def_pool.size() - 1 );
    uint8_t def = def_pool[ dist( rng ) ];
    stats.def = def;
    double def_factor = 1;
    if (def != 0)
      def_factor = ( 1.0 - ( def / 255.0 ) / 3 );

    std::uniform_int_distribution<size_t> dist2( 0, mdef_pool.size() - 1 );
    uint8_t mdef = mdef_pool[ dist2( rng ) ];
    stats.mdef = mdef;
    double mdef_factor = 1;
    if (mdef != 0)
      mdef_factor = ( 1.0 - ( mdef / 255.0 ) / 3 );

    std::uniform_int_distribution<size_t> dist3( 0, eva_pool.size() - 1 );
    uint8_t eva = eva_pool[ dist3( rng ) ];
    stats.eva = eva;
    double evasion_factor = 1;
    if (eva != 0)
      evasion_factor = ( 1.0 - ( eva / 255.0 ) / 3 );

    double defensive_factor = ( def_factor + mdef_factor + evasion_factor ) * 2;
    if (defensive_factor < 0.33)
      stats.flags1.bits.armored = 0;
    else
      stats.flags1.bits.armored = rand() % 4 == 0;

    uint32_t base_hp = 1;
    if (stats.hp > 1)
      base_hp = stats.hp * defensive_factor;
    if (base_hp <= 1)
      base_hp = 50;
    uint32_t hp = normal<uint32_t>( base_hp, base_hp / 2, 50, UINT32_MAX );
    stats.hp = hp;
    if (stats.hp < 50)
      stats.hp = 50;
    stats.mag = normal<uint8_t>( stats.mag, stats.mag / 2, 0, UINT8_MAX );
    stats.agi = normal<uint8_t>( stats.agi, stats.agi / 2, 0, UINT8_MAX );
    stats.acc = normal<uint8_t>( stats.acc, stats.acc / 2, 0, UINT8_MAX );
    enemy->loot_data->gil /= defensive_factor;
    enemy->loot_data->ap /= defensive_factor;
    stats.writeToBytes();
    enemy->stats_data = &stats;
    enemy->writeStatsData( stats );
  }

  void shuffleEnemyStats( enemy_data_t* enemy )
  {
    if (enemy->monster_id == "211" || enemy->monster_id == "237")
      return;
    enemy_stat_data_t& stats = *enemy->stats_data;
    if (stats.hp <= 1)
      return;
    // Pick a random index to pull the stats from
    std::uniform_int_distribution<size_t> dist( 0, data_pack.enemy_data.size() - 1 );
    int index = dist( rng );
    if (stats.hp > 1)
      stats.hp = normal<uint32_t>( stats.hp, stats.hp / 2, 50, UINT32_MAX );
    if (stats.hp < 50)
      stats.hp = 50;
    stats.mp = normal<uint32_t>( stats.mp, stats.mp / 2, 1, UINT32_MAX );
    stats.overkill_threshold = normal<uint32_t>( stats.overkill_threshold / 2, stats.overkill_threshold, 1, UINT32_MAX );
    stats.str = normal<uint8_t>( stats.str, stats.str / 2, 0, UINT8_MAX );
    stats.def = def_pool[ index ];
    stats.mdef = mdef_pool[ index ];
    stats.eva = eva_pool[ index ];
    stats.flags1.bits.armored = rand() % 4 == 0;
    stats.agi = normal<uint8_t>( stats.agi, stats.agi / 2, 0, UINT8_MAX );
    stats.luck = normal<uint8_t>( stats.luck, stats.luck / 2, 0, UINT8_MAX );
    stats.acc = normal<uint8_t>( stats.acc, stats.acc / 2, 0, UINT8_MAX );
    stats.writeToBytes();
    enemy->stats_data = &stats;
    enemy->writeStatsData( stats );
  }

  void randomizeEnemyElementalAffinities( enemy_data_t* enemy )
  {
    enemy_stat_data_t& stats = *enemy->stats_data;
    if (stats.hp <= 1)
      return;

    int fire_roll = uniform<int>( 0, 69 );
    int ice_roll = uniform<int>( 0, 69 );
    int lightning_roll = uniform<int>( 0, 69 );
    int water_roll = uniform<int>( 0, 69 );
    int holy_roll = uniform<int>( 0, 69 );

    stats.element_weakness_flags.bits.fire = fire_roll < 20;
    stats.element_weakness_flags.bits.ice = ice_roll < 20;
    stats.element_weakness_flags.bits.lightning = lightning_roll < 20;
    stats.element_weakness_flags.bits.water = water_roll < 20;
    stats.element_weakness_flags.bits.holy = holy_roll < 20;

    stats.element_resist_flags.bits.fire = fire_roll < 25 && fire_roll >= 20;
    stats.element_resist_flags.bits.ice = ice_roll < 25 && ice_roll >= 20;
    stats.element_resist_flags.bits.lightning = lightning_roll < 25 && lightning_roll >= 20;
    stats.element_resist_flags.bits.water = water_roll < 25 && water_roll >= 20;
    stats.element_resist_flags.bits.holy = holy_roll < 25 && holy_roll >= 20;

    stats.element_immune_flags.bits.fire = fire_roll < 30 && fire_roll >= 25;
    stats.element_immune_flags.bits.ice = ice_roll < 30 && ice_roll >= 25;
    stats.element_immune_flags.bits.lightning = lightning_roll < 30 && lightning_roll >= 25;
    stats.element_immune_flags.bits.water = water_roll < 30 && water_roll >= 25;
    stats.element_immune_flags.bits.holy = holy_roll < 30 && holy_roll >= 25;

    stats.element_absorb_flags.bits.fire = fire_roll < 35 && fire_roll >= 30;
    stats.element_absorb_flags.bits.ice = ice_roll < 35 && ice_roll >= 30;
    stats.element_absorb_flags.bits.lightning = lightning_roll < 35 && lightning_roll >= 30;
    stats.element_absorb_flags.bits.water = water_roll < 35 && water_roll >= 30;
    stats.element_absorb_flags.bits.holy = holy_roll < 35 && holy_roll >= 30;

    stats.writeToBytes();
    enemy->stats_data = &stats;
    enemy->writeStatsData( stats );
  }

  void poplateGearLists()
  {
    for (auto& gear : data_pack.buki_data)
    {
      gear_data_t* armor = gear;
      if (armor->is_armor)
        all_armor.push_back( armor );
      else
        all_weapons.push_back( armor );
    }
    for (auto& gear : data_pack.weapon_data)
    {
      gear_data_t* armor = gear;
      if (armor->is_armor)
        all_armor.push_back( armor );
      else
        all_weapons.push_back( armor );
    }
    for (auto& gear : data_pack.shop_arms_data)
    {
      gear_data_t* armor = gear;
      if (armor->is_armor)
        all_armor.push_back( armor );
      else
        all_weapons.push_back( armor );
    }
  }

  uint16_t getRandomAbility()
  {
    std::uniform_int_distribution<size_t> dist( 0, abilities.size() - 1 );
    return abilities[ dist( rng ) ];
  }

  void populateAbilityData()
  {
    for (auto& gear : all_armor)
    {
      gear_data_t* armor = gear;
      armor->mapAbilities( abilities );
    }
    for (auto& gear : all_weapons)
    {
      gear_data_t* weapon = gear;
      weapon->mapAbilities( abilities );
    }
    for (auto& enemy : data_pack.enemy_data)
    {
      enemy_loot_data_t& loot = *enemy->loot_data;
      for (int chr = 0; chr < 7; chr++)
      {
        for (int i = 0; i < 8; i++)
        {
          bool found = std::find( abilities.begin(), abilities.end(), loot.weapon_abilities_by_char.at( chr ) ) != abilities.end();
          if (!found && loot.weapon_abilities_by_char.at( chr ) != 255)
            abilities.push_back( loot.weapon_abilities_by_char.at( chr ) );
        }
      }
      for (int chr = 0; chr < 7; chr++)
      {
        for (int i = 0; i < 8; i++)
        {
          bool found = std::find( abilities.begin(), abilities.end(), loot.gear_abilities_by_char.at( chr ) ) != abilities.end();
          if (!found && loot.gear_abilities_by_char.at( chr ) != 255)
            abilities.push_back( loot.gear_abilities_by_char.at( chr ) );
        }
      }
    }
  }

  uint8_t getRandomFormula()
  {
    std::uniform_int_distribution<size_t> dist( 0, weapon_formulas.size() - 1 );
    return weapon_formulas[ dist( rng ) ];
  }

  void populateWeaponFormulas()
  {
    for (auto& gear : all_weapons)
    {
      gear_data_t& weapon = *gear;
      weapon.mapFormulas( weapon_formulas );
    }
    for (auto& enemy : data_pack.enemy_data)
    {
      enemy_loot_data_t& loot = *enemy->loot_data;
      bool found = std::find( weapon_formulas.begin(), weapon_formulas.end(), loot.gear_damage_calc ) != weapon_formulas.end();
      if (!found)
        weapon_formulas.push_back( loot.gear_damage_calc );
    }
  }

  void randomizeEnemyGearDrops( enemy_data_t* enemy )
  {
    enemy_loot_data_t& loot = *enemy->loot_data;
    loot.gear_drop_chance = uniform<int>( -1, 254 );

    for (int chr = 0; chr < 7; chr++)
    {
      for (int i = 0; i < 8; i++)
      {
        loot.weapon_abilities_by_char.at( chr ) = getRandomAbility();
      }
    }

    for (int chr = 0; chr < 7; chr++)
    {
      for (int i = 0; i < 8; i++)
      {
        loot.gear_abilities_by_char.at( chr ) = getRandomAbility();
      }
    }

    loot.writeToBytes();
    enemy->loot_data = &loot;
    enemy->writeLootData( loot );
  }

  void randomizeItemShops()
  {
    for (auto& shop : data_pack.item_shop_data)
    {
      shop_data_t* item_shop = shop;
      int n_items = uniform<int>( 1, 16 );
      for (int i = 0; i < 16; i++)
      {
        if (i >= n_items)
        {
          item_shop->item_indexes.at( i ) = 0;
          continue;
        }

        bool found = true;
        item_t* potential_item;
        do
          potential_item = getRandomItemFromMap( all_non_key_items );
        while (found = std::find( item_shop->item_indexes.begin(), item_shop->item_indexes.end(), potential_item->id ) != item_shop->item_indexes.end() && potential_item->id < 10000);

        item_shop->item_indexes.at( i ) = potential_item->id;
      }
      item_shop->writeToBytes();
    }
  }

  int getRandomShopArmsIndex()
  {
    std::uniform_int_distribution<size_t> dist( 0, data_pack.shop_arms_data.size() - 1 );
    return dist( rng );
  }

  void randomizeGearShops()
  {
    for (auto& shop : data_pack.gear_shop_data)
    {
      shop_data_t* gear_shop = shop;
      int n_items = uniform<int>( 1, 16 );
      for (int i = 0; i < 16; i++)
      {
        if (i >= n_items)
        {
          gear_shop->item_indexes.at( i ) = 0;
          continue;
        }
        gear_shop->item_indexes.at( i ) = getRandomShopArmsIndex();
      }
      gear_shop->writeToBytes();
    }
  }

  void writeGearData( gear_data_t& gear )
  {
    if (( gear.is_celestial && !options_pack.randomize_celestials ) || ( gear.is_brotherhood && !options_pack.randomize_brotherhood ))
      return;

    uint8_t n_abilities = uniform<uint8_t>( 0, 3 );

    std::vector<uint16_t> abilities;

    for (uint8_t i = 0; i < 4; i++)
    {
      if (i >= n_abilities)
      {
        abilities.push_back( 255 );
        continue;
      }
      abilities.push_back( getRandomAbility() );
    }

    gear.slots = n_abilities;
    gear.ability_slot1 = abilities.at( 0 );
    gear.ability_slot2 = abilities.at( 1 );
    gear.ability_slot3 = abilities.at( 2 );
    gear.ability_slot4 = abilities.at( 3 );

    gear.writeToBytes();
  }

  void randomizeShopArmsAbilities()
  {
    for (auto& gear : data_pack.shop_arms_data)
    {
      gear_data_t& gear_data = *gear;
      writeGearData( gear_data );
    }
  }

  void randomizeBukiAbilities()
  {
    for (auto& gear : data_pack.buki_data)
    {
      gear_data_t& gear_data = *gear;
      writeGearData( gear_data );
    }
  }

  void randomizeWeaponsAbilities()
  {
    for (auto& gear : data_pack.weapon_data)
    {
      gear_data_t& gear_data = *gear;
      writeGearData( gear_data );
    }
  }

  void randomizeWeaponCrit()
  {
    for (auto& gear : data_pack.shop_arms_data)
    {
      gear_data_t& gear_data = *gear;
      if (gear_data.is_armor || ( gear_data.is_celestial && !options_pack.randomize_celestials ) || ( gear_data.is_brotherhood && !options_pack.randomize_brotherhood ))
        continue;
      if (options_pack.keep_things_sane)
        gear_data.crit_bonus = normal<uint8_t>( gear_data.crit_bonus, gear_data.crit_bonus / 2, 1, 100 );
      else
        gear_data.crit_bonus = uniform<uint8_t>( 0, 100 );
      gear_data.writeToBytes();
    }
    for (auto& gear : data_pack.buki_data)
    {
      gear_data_t& gear_data = *gear;
      if (gear_data.is_armor || ( gear_data.is_celestial && !options_pack.randomize_celestials ) || ( gear_data.is_brotherhood && !options_pack.randomize_brotherhood ))
        continue;
      if (options_pack.keep_things_sane)
        gear_data.crit_bonus = normal<uint8_t>( gear_data.crit_bonus, gear_data.crit_bonus / 2, 1, 100 );
      else
        gear_data.crit_bonus = uniform<uint8_t>( 0, 100 );
      gear_data.writeToBytes();
    }
    for (auto& gear : data_pack.weapon_data)
    {
      gear_data_t& gear_data = *gear;
      if (gear_data.is_armor || ( gear_data.is_celestial && !options_pack.randomize_celestials ) || ( gear_data.is_brotherhood && !options_pack.randomize_brotherhood ))
        continue;
      if (options_pack.keep_things_sane)
        gear_data.crit_bonus = normal<uint8_t>( gear_data.crit_bonus, gear_data.crit_bonus / 2, 1, 100 );
      else
        gear_data.crit_bonus = uniform<uint8_t>( 0, 100 );
      gear_data.writeToBytes();
    }
  }

  void randomizeWeaponAttackPower()
  {
    for (auto& gear : data_pack.shop_arms_data)
    {
      gear_data_t& gear_data = *gear;
      if (gear_data.is_armor || ( gear_data.is_celestial && !options_pack.randomize_celestials ) || ( gear_data.is_brotherhood && !options_pack.randomize_brotherhood ))
        continue;
      if (options_pack.keep_things_sane)
        gear_data.attack_power = normal<uint8_t>( gear_data.attack_power, gear_data.attack_power / 2, 1, 24 );
      else
        gear_data.attack_power = uniform<uint8_t>( 0, 100 );

      gear_data.writeToBytes();
    }
    for (auto& gear : data_pack.buki_data)
    {
      gear_data_t& gear_data = *gear;
      if (gear_data.is_armor || ( gear_data.is_celestial && !options_pack.randomize_celestials ) || ( gear_data.is_brotherhood && !options_pack.randomize_brotherhood ))
        continue;
      if (options_pack.keep_things_sane)
        gear_data.attack_power = normal<uint8_t>( gear_data.attack_power, gear_data.attack_power / 2, 1, 24 );
      else
        gear_data.attack_power = uniform<uint8_t>( 0, 100 );
      gear_data.writeToBytes();
    }
    for (auto& gear : data_pack.weapon_data)
    {
      gear_data_t& gear_data = *gear;
      if (gear_data.is_armor || ( gear_data.is_celestial && !options_pack.randomize_celestials ) || ( gear_data.is_brotherhood && !options_pack.randomize_brotherhood ))
        continue;
      if (options_pack.keep_things_sane)
        gear_data.attack_power = normal<uint8_t>( gear_data.attack_power, gear_data.attack_power / 2, 1, 24 );
      else
        gear_data.attack_power = uniform<uint8_t>( 0, 100 );
      gear_data.writeToBytes();
    }
  }

  void randomizeWeaponDamageFormula()
  {
    for (auto& gear : data_pack.shop_arms_data)
    {
      gear_data_t& gear_data = *gear;
      if (gear_data.is_armor || ( gear_data.is_celestial && !options_pack.randomize_celestials ) || ( gear_data.is_brotherhood && !options_pack.randomize_brotherhood ))
        continue;

      gear_data.damage_calc = getRandomFormula();
      gear_data.writeToBytes();
    }
    for (auto& gear : data_pack.buki_data)
    {
      gear_data_t& gear_data = *gear;
      if (gear_data.is_armor || ( gear_data.is_celestial && !options_pack.randomize_celestials ) || ( gear_data.is_brotherhood && !options_pack.randomize_brotherhood ))
        continue;

      gear_data.damage_calc = getRandomFormula();
      gear_data.writeToBytes();
    }
    for (auto& gear : data_pack.weapon_data)
    {
      gear_data_t& gear_data = *gear;
      if (gear_data.is_armor || ( gear_data.is_celestial && !options_pack.randomize_celestials ) || ( gear_data.is_brotherhood && !options_pack.randomize_brotherhood ))
        continue;

      gear_data.damage_calc = getRandomFormula();
      gear_data.writeToBytes();
    }
  }

  void randomizeFieldItems()
  {
    std::vector<int> blacklist = { 177, 203 };
    for (auto& field : data_pack.field_data)
    {
      field_data_t& field_data = *field;
      if (std::find( blacklist.begin(), blacklist.end(), field_data.index ) != blacklist.end())
        continue;

      if (field_data.flag != 10 || options_pack.randomize_key_items)
      {
        int max = options_pack.randomize_key_items ? 3 : 2;
        int rolled_type = uniform<int>( 0, max );
        item_t* item = getRandomItemFromMap( all_non_key_items );
        item_t* key_item = getRandomItemFromMap( all_key_items );
        switch (rolled_type)
        {
          case 0:
            field_data.flag = 0;
            field_data.quantity = uniform<uint8_t>( 1, UINT8_MAX );
            field_data.writeToBytes();
            break;
          case 1:
            field_data.flag = 2;
            field_data.type = item->id;
            field_data.quantity = getRandomItemQuantity( item, false );
            field_data.writeToBytes();
            break;
          case 2:
            field_data.flag = 5;
            field_data.quantity = 1;
            field_data.type = uniform<uint16_t>( 0, data_pack.buki_data.size() - 1 );
            field_data.writeToBytes();
            break;
          case 3:
            field_data.flag = 10;
            field_data.type = key_item->id;
            field_data.quantity = getRandomItemQuantity( key_item, false );
            field_data.writeToBytes();
            break;
          default:
            break;
        }
      }
    }
  }

  void randomizeItemPrices()
  {
    for (auto& price : data_pack.item_rate_data)
    {
      item_rate_t& item_rate = *price;
      if (item_rate.rate > 1 && item_rate.rate != 2 && options_pack.keep_things_sane)
        item_rate.rate = normal<uint32_t>( item_rate.rate, item_rate.rate, 1, UINT32_MAX );
      else if (item_rate.rate == 2 && options_pack.keep_things_sane)
        // Spheres normally cost 2 gil in data, since they are never sold by vendors. 
        // Since this can happen with randomization, bump the price to something more reasonable. 
        item_rate.rate = normal<uint32_t>( 500, 250, 1, UINT32_MAX );
      else
        item_rate.rate = uniform<uint32_t>( 1, UINT32_MAX );
      item_rate.writeToBytes();
    }
  }

  void randomizeArmsPrices()
  {
    for (auto& price : data_pack.arms_rate_data)
    {
      arms_rate_t& arms_rate = *price;
      if (arms_rate.rate > 1 && options_pack.keep_things_sane)
        arms_rate.rate = normal<uint32_t>( arms_rate.rate, arms_rate.rate, 1, UINT32_MAX );
      else
        arms_rate.rate = uniform<uint32_t>( 1, UINT32_MAX );
      arms_rate.writeToBytes();
    }
  }

  void randomizePlayerStats()
  {
    for (int i = 0; i < 7; i++)
    {
      character_stats_t& stats = *data_pack.player_stats_data[ i ];
      stats.base_hp = normal<uint32_t>( stats.base_hp, stats.base_hp / 2, 50, 9999 );
      if (stats.base_hp < 50)
        stats.base_hp = 50;
      stats.base_mp = normal<uint32_t>( stats.base_mp, stats.base_mp / 2, 1, 999 );
      bool tidus_or_auron = i == 0 || i == 2;
      stats.base_str = normal<uint8_t>( stats.base_str, stats.base_str / 2, tidus_or_auron ? 14 : 0, UINT8_MAX );
      stats.base_def = normal<uint8_t>( stats.base_def, stats.base_def / 2, 0, UINT8_MAX );
      stats.base_mag = normal<uint8_t>( stats.base_mag, stats.base_mag / 2, 0, UINT8_MAX );
      stats.base_mdef = normal<uint8_t>( stats.base_mdef, stats.base_mdef / 2, 0, UINT8_MAX );
      stats.base_agi = normal<uint8_t>( stats.base_agi, stats.base_agi / 2, 0, UINT8_MAX );
      stats.base_acc = normal<uint8_t>( stats.base_acc, stats.base_acc / 2, 0, UINT8_MAX );
      stats.base_luck = normal<uint8_t>( stats.base_luck, stats.base_luck / 2, 0, UINT8_MAX );
      stats.current_ap = normal<uint16_t>( stats.current_ap, stats.current_ap / 2, 0, UINT16_MAX );
      stats.current_hp = normal<uint32_t>( stats.current_hp, stats.current_hp / 2, 1, UINT32_MAX );
      stats.current_mp = normal<uint32_t>( stats.current_mp, stats.current_mp / 2, 1, UINT32_MAX );
      stats.max_hp = normal<uint32_t>( stats.max_hp, stats.max_hp / 2, 1, UINT32_MAX );
      stats.max_mp = normal<uint32_t>( stats.max_mp, stats.max_mp / 2, 1, UINT32_MAX );
      stats.str = normal<uint8_t>( stats.str, stats.str / 2, 0, UINT8_MAX );
      stats.def = normal<uint8_t>( stats.def, stats.def / 2, 0, UINT8_MAX );
      stats.mag = normal<uint8_t>( stats.mag, stats.mag / 2, 0, UINT8_MAX );
      stats.mdef = normal<uint8_t>( stats.mdef, stats.mdef / 2, 0, UINT8_MAX );
      stats.agi = normal<uint8_t>( stats.agi, stats.agi / 2, 0, UINT8_MAX );
      stats.acc = normal<uint8_t>( stats.acc, stats.acc / 2, 0, UINT8_MAX );
      stats.luck = normal<uint8_t>( stats.luck, stats.luck / 2, 0, UINT8_MAX );
      stats.writeToBytes();
    }
  }

  void randomizeAeonStatScaling()
  {
    for (auto& aeon : data_pack.aeon_scaling_data)
    {
      if (!aeon->is_yuna_summon)
        continue;
      aeon->ap_req_coef1 = normal<uint16_t>( aeon->ap_req_coef1, aeon->ap_req_coef1 / 2, 0, UINT16_MAX );
      aeon->ap_req_coef2 = normal<uint16_t>( aeon->ap_req_coef2, aeon->ap_req_coef2 / 2, 0, UINT16_MAX );
      aeon->ap_req_coef3 = normal<uint16_t>( aeon->ap_req_coef3, aeon->ap_req_coef3 / 2, 0, UINT16_MAX );
      aeon->ap_req_max = normal<uint16_t>( aeon->ap_req_max, aeon->ap_req_max / 2, 0, UINT16_MAX );
      aeon->hp_coef1 = normal<uint16_t>( aeon->hp_coef1, aeon->hp_coef1 / 2, 0, UINT16_MAX );
      aeon->hp_coef2 = normal<uint16_t>( aeon->hp_coef2, aeon->hp_coef2 / 2, 0, UINT16_MAX );
      aeon->mp_coef1 = normal<uint16_t>( aeon->mp_coef1, aeon->mp_coef1 / 2, 0, UINT16_MAX );
      aeon->mp_coef2 = normal<uint16_t>( aeon->mp_coef2, aeon->mp_coef2 / 2, 0, UINT16_MAX );
      aeon->str_coef1 = normal<uint16_t>( aeon->str_coef1, aeon->str_coef1 / 2, 0, UINT16_MAX );
      aeon->str_coef2 = normal<uint16_t>( aeon->str_coef2, aeon->str_coef2 / 2, 0, UINT16_MAX );
      aeon->def_coef1 = normal<uint16_t>( aeon->def_coef1, aeon->def_coef1 / 2, 0, UINT16_MAX );
      aeon->def_coef2 = normal<uint16_t>( aeon->def_coef2, aeon->def_coef2 / 2, 0, UINT16_MAX );
      aeon->mag_coef1 = normal<uint16_t>( aeon->mag_coef1, aeon->mag_coef1 / 2, 0, UINT16_MAX );
      aeon->mag_coef2 = normal<uint16_t>( aeon->mag_coef2, aeon->mag_coef2 / 2, 0, UINT16_MAX );
      aeon->mdef_coef1 = normal<uint16_t>( aeon->mdef_coef1, aeon->mdef_coef1 / 2, 0, UINT16_MAX );
      aeon->mdef_coef2 = normal<uint16_t>( aeon->mdef_coef2, aeon->mdef_coef2 / 2, 0, UINT16_MAX );
      aeon->agi_coef1 = normal<uint16_t>( aeon->agi_coef1, aeon->agi_coef1 / 2, 0, UINT16_MAX );
      aeon->agi_coef2 = normal<uint16_t>( aeon->agi_coef2, aeon->agi_coef2 / 2, 0, UINT16_MAX );
      aeon->acc_coef1 = normal<uint16_t>( aeon->acc_coef1, aeon->acc_coef1 / 2, 0, UINT16_MAX );
      aeon->acc_coef2 = normal<uint16_t>( aeon->acc_coef2, aeon->acc_coef2 / 2, 0, UINT16_MAX );
      aeon->writeToBytes();
    }
  }

  void randomizeAeonBaseStats()
  {
    for (auto& aeon : data_pack.aeon_stat_data)
    {
      aeon->hp = normal<uint32_t>( aeon->hp, aeon->hp / 2, 50, UINT32_MAX );
      aeon->mp = normal<uint32_t>( aeon->mp, aeon->mp / 2, 1, UINT32_MAX );
      aeon->str = normal<uint8_t>( aeon->str, aeon->str / 2, 0, UINT8_MAX );
      aeon->def = normal<uint8_t>( aeon->def, aeon->def / 2, 0, UINT8_MAX );
      aeon->mag = normal<uint8_t>( aeon->mag, aeon->mag / 2, 0, UINT8_MAX );
      aeon->mdef = normal<uint8_t>( aeon->mdef, aeon->mdef / 2, 0, UINT8_MAX );
      aeon->agi = normal<uint8_t>( aeon->agi, aeon->agi / 2, 0, UINT8_MAX );
      aeon->acc = normal<uint8_t>( aeon->acc, aeon->acc / 2, 0, UINT8_MAX );
      aeon->writeToBytes();
    }
  }

  void shuffleCharacterStats()
  {
    for (int i = 0; i < 7; i++)
    {
      character_stats_t& stats = *data_pack.player_stats_data[ i ];
      character_stats_t& new_stats = *shuffled_player_stats_data[ i ];
      stats.base_hp = new_stats.base_hp;
      stats.base_mp = new_stats.base_mp;
      if (( i == 0 || i == 2 ) && new_stats.base_str < 14)
        new_stats.base_str = 14;
      stats.base_str = new_stats.base_str;
      stats.base_def = new_stats.base_def;
      stats.base_mag = new_stats.base_mag;
      stats.base_mdef = new_stats.base_mdef;
      stats.base_agi = new_stats.base_agi;
      stats.base_acc = new_stats.base_acc;
      stats.base_luck = new_stats.base_luck;
      stats.current_ap = new_stats.current_ap;
      stats.current_hp = new_stats.current_hp;
      stats.current_mp = new_stats.current_mp;
      stats.max_hp = new_stats.max_hp;
      stats.max_mp = new_stats.max_mp;
      stats.str = new_stats.str;
      stats.def = new_stats.def;
      stats.mag = new_stats.mag;
      stats.mdef = new_stats.mdef;
      stats.agi = new_stats.agi;
      stats.acc = new_stats.acc;
      stats.luck = new_stats.luck;
      stats.writeToBytes();
    }
  }

  void shuffleAeonStatScaling()
  {
    int idx = 0;
    for (auto& aeon_sd : data_pack.aeon_scaling_data)
    {
      aeon_scaling_data_t& aeon = *aeon_sd;
      if (!aeon.is_yuna_summon)
        continue;
      aeon_scaling_data_t& shuffled_aeon = *shuffled_aeon_scaling_data[ idx ];
      idx++;
      aeon.bytes = shuffled_aeon.bytes;
    }
  }

  void shuffleAeonBaseStats()
  {
    std::shuffle( data_pack.aeon_stat_data.begin(), data_pack.aeon_stat_data.end(), rng );
    for (size_t i = 0; i < data_pack.aeon_stat_data.size(); i++)
    {
      aeon_stat_data_t& aeon = *data_pack.aeon_stat_data[ i ];
      aeon_stat_data_t& shuffled_aeon = *data_pack.aeon_stat_data[ i ];
      aeon.bytes = shuffled_aeon.bytes;
    }
  }

  void shuffleSphereGridNodes()
  {
    // Force Lancet and Use to be on Riku and Kimari to prevent softlocks
    character_stats_t& riku_stats = *data_pack.player_stats_data[ 6 ];
    riku_stats.ability_flags1.bits.use = 1;
    riku_stats.writeToBytes();

    character_stats_t& kimari_stats = *data_pack.player_stats_data[ 3 ];
    kimari_stats.ability_flags2.bits.lancet = 1;
    kimari_stats.writeToBytes();

    for (auto& grid : data_pack.sphere_grid_data)
    {
      switch (grid->type)
      {
        case SPHERE_GRID_ORIGINAL:
          shuffled_original_sphere_grid_node_ids = original_sphere_grid_node_ids;
          std::shuffle( shuffled_original_sphere_grid_node_ids.begin(), shuffled_original_sphere_grid_node_ids.end(), rng );
          break;
        case SPHERE_GRID_STANDARD:
          shuffled_standard_sphere_grid_node_ids = standard_sphere_grid_node_ids;
          std::shuffle( shuffled_standard_sphere_grid_node_ids.begin(), shuffled_standard_sphere_grid_node_ids.end(), rng );
          break;
        case SPHERE_GRID_EXPERT:
          shuffled_expert_sphere_grid_node_ids = expert_sphere_grid_node_ids;
          std::shuffle( shuffled_expert_sphere_grid_node_ids.begin(), shuffled_expert_sphere_grid_node_ids.end(), rng );
          break;
        default:
          break;
      }

      for (size_t i = 0; i < grid->nodes.size(); i++)
      {
        sphere_grid_node_data_t& node = *grid->nodes[ i ];
        switch (grid->type)
        {
          case SPHERE_GRID_ORIGINAL:
            node.content = shuffled_original_sphere_grid_node_ids[ i ];
            node.writeToBytes();
            break;
          case SPHERE_GRID_STANDARD:
            node.content = shuffled_standard_sphere_grid_node_ids[ i ];
            node.writeToBytes();
            break;
          case SPHERE_GRID_EXPERT:
            node.content = shuffled_expert_sphere_grid_node_ids[ i ];
            node.writeToBytes();
            break;
          default:
            break;
        }
      }

      grid->writeToBytes();
    }
  }

  void randomizeSphereGrid()
  {
    // Force Lancet and Use to be on Riku and Kimari to prevent softlocks
    character_stats_t& riku_stats = *data_pack.player_stats_data[ 6 ];
    riku_stats.ability_flags1.bits.use = 1;
    riku_stats.writeToBytes();

    character_stats_t& kimari_stats = *data_pack.player_stats_data[ 3 ];
    kimari_stats.ability_flags2.bits.lancet = 1;
    kimari_stats.writeToBytes();

    for (auto& grid : data_pack.sphere_grid_data)
    {
      sphere_grid_data_t& sphere_grid = *grid;
      for (auto& node_data : sphere_grid.nodes)
      {
        sphere_grid_node_data_t& node = *node_data;
        std::vector<uint16_t> blacklist = { 0x3B, 0xFF };
        uint8_t new_content = uniform<uint8_t>( 0, 0x7F );
        node.content = new_content;
        node.writeToBytes();
      }
      sphere_grid.writeToBytes();
    }
  }

  void emptySphereGrid()
  {
    for (auto& grid : data_pack.sphere_grid_data)
    {
      sphere_grid_data_t& sphere_grid = *grid;
      for (auto& node_data : sphere_grid.nodes)
      {
        sphere_grid_node_data_t& node = *node_data;
        std::vector<uint16_t> blacklist = { 0x3B, 0xFF };
        if (std::find( blacklist.begin(), blacklist.end(), node.original_content ) != blacklist.end())
          continue;
        if (node.content <= 0x29)
          node.content = 0x01;
        node.writeToBytes();
      }
      sphere_grid.writeToBytes();
    }
  }

  void fillSphereGrid()
  {
    for (auto& grid : data_pack.sphere_grid_data)
    {
      sphere_grid_data_t& sphere_grid = *grid;
      for (auto& node_data : sphere_grid.nodes)
      {
        sphere_grid_node_data_t& node = *node_data;
        if (node.content != 0x01)
          continue;
        uint8_t new_content = uniform<uint8_t>( 1, 0x26 );
        node.content = new_content;
        node.writeToBytes();
      }
      sphere_grid.writeToBytes();
    }
  }

  void removeSphereGridLocks()
  {
    for (auto& grid : data_pack.sphere_grid_data)
    {
      sphere_grid_data_t& sphere_grid = *grid;
      for (auto& node_data : sphere_grid.nodes)
      {
        sphere_grid_node_data_t& node = *node_data;
        std::vector<uint16_t> whitelist = { 0x00, 0x27, 0x28, 0x29 };
        if (std::find( whitelist.begin(), whitelist.end(), node.content ) != whitelist.end())
          node.content = 0x01;
        node.writeToBytes();
      }
      sphere_grid.writeToBytes();
    }
  }

  void doEnemyRandomization()
  {
    if (!options_pack.randomize_enemy_drops && !options_pack.randomize_enemy_steals && !options_pack.randomize_enemy_bribes && !options_pack.randomize_enemy_gear_drops &&
         !options_pack.randomize_enemy_stats && !options_pack.randomize_enemy_stats_defensive && !options_pack.randomize_enemy_stats_shuffle &&
         !options_pack.randomize_enemy_elemental_affinities)
      return;

    // Generate the enemy defensive stats pool before going into the main loop
    if (options_pack.randomize_enemy_stats_defensive || options_pack.randomize_enemy_stats_shuffle)
      for (auto& enemy : data_pack.enemy_data)
        addEnemyDefenses( enemy );

    for (auto& enemy : data_pack.enemy_data)
    {
      if (options_pack.randomize_enemy_drops)
      {
        printf( "Randomizing Enemy Drops for monster %s\n", enemy->monster_id.c_str() );
        randomizeEnemyDrops( enemy );
      }
      if (options_pack.randomize_enemy_steals)
      {
        printf( "Randomizing Enemy Steals for monster %s\n", enemy->monster_id.c_str() );
        randomizeEnemySteal( enemy );
      }
      if (options_pack.randomize_enemy_bribes)
      {
        printf( "Randomizing Enemy Bribes for monster %s\n", enemy->monster_id.c_str() );
        randomizeEnemyBribe( enemy );
      }
      if (options_pack.randomize_enemy_gear_drops)
      {
        printf( "Randomizing Enemy Gear Drops for monster %s\n", enemy->monster_id.c_str() );
        randomizeEnemyGearDrops( enemy );
      }
      if (options_pack.randomize_enemy_stats)
      {
        printf( "Randomizing Enemy Stats for monster %s\n", enemy->monster_id.c_str() );
        randomizeEnemyStatsNormal( enemy );
      }
      if (options_pack.randomize_enemy_stats_defensive)
      {
        printf( "Randomizing Enemy Defensive for monster %s\n", enemy->monster_id.c_str() );
        randomizeEnemyStatsDefensiveNormalization( enemy );
      }
      if (options_pack.randomize_enemy_stats_shuffle)
      {
        printf( "Shuffling Enemy Stats for monster %s\n", enemy->monster_id.c_str() );
        shuffleEnemyStats( enemy );
      }
      if (options_pack.randomize_enemy_elemental_affinities)
      {
        printf( "Randomizing Enemy Elemental Affinities for monster %s\n", enemy->monster_id.c_str() );
        randomizeEnemyElementalAffinities( enemy );
      }

      printf( "Reconstructing files for for monster %s\n", enemy->monster_id.c_str() );
      std::string pathstr = OUTPUT_FOLDER + prefix + MONSTER_FOLDER + "_m" + enemy->monster_id;
      std::filesystem::path path = pathstr;
      std::filesystem::create_directories( path );
      std::string filepath = pathstr + "/m" + enemy->monster_id + ".bin";
      enemy->writeBytesToNewFile( enemy->bytes, filepath );
    }
  }

  void doShopRandomization()
  {
    if (!options_pack.randomize_item_shops && !options_pack.randomize_gear_shops)
      return;

    if (options_pack.randomize_item_shops)
    {
      printf( "Randomizing Item Shops...\n" );
      randomizeItemShops();
      reconstructItemShopData();
    }

    if (options_pack.randomize_gear_shops)
    {
      printf( "Randomizing Gear Shops...\n" );
      randomizeGearShops();
      reconstructArmsShopData();
    }
  }

  void doPriceRandomization()
  {
    if (!options_pack.randomize_item_shop_prices && !options_pack.randomize_gear_shop_prices)
      return;

    if (options_pack.randomize_item_shop_prices)
    {
      printf( "Randomizing Item Prices...\n" );
      randomizeItemPrices();
      printf( "Reconstructing item_rate.bin...\n" );
      reconstructItemRateData();
    }

    if (options_pack.randomize_gear_shop_prices)
    {
      printf( "Randomizing Gear Prices...\n" );
      randomizeArmsPrices();
      printf( "Reconstructing arms_rate.bin...\n" );
      reconstructArmsRateData();
    }
  }

  void doFieldRandomization()
  {
    if (!options_pack.randomize_field_items)
      return;

    printf( "Randomizing Field Items...\n" );
    randomizeFieldItems();
    printf( "Reconstructing takara.bin...\n" );
    reconstructTakaraData();
  }

  void doGearRandomization()
  {
    if (!options_pack.randomize_gear_abilities && !options_pack.randomize_weapon_attack_power && !options_pack.randomize_weapon_crit &&
         !options_pack.randomize_weapon_damage_formula)
      return;

    if (options_pack.randomize_gear_abilities)
    {
      printf( "Randomizing shop_arms.bin Abilities...\n" );
      std::thread shop_arms_thread( &randomizer_t::randomizeShopArmsAbilities, this );
      printf( "Randomizing buki_get.bin Abilities...\n" );
      std::thread buki_thread( &randomizer_t::randomizeBukiAbilities, this );
      printf( "Randomizing weapon.bin Abilities...\n" );
      std::thread weapon_thread( &randomizer_t::randomizeWeaponsAbilities, this );

      shop_arms_thread.join();
      buki_thread.join();
      weapon_thread.join();
    }

    if (options_pack.randomize_weapon_attack_power)
    {
      printf( "Randomizing weapon.bin Attack Power...\n" );
      randomizeWeaponAttackPower();
    }

    if (options_pack.randomize_weapon_crit)
    {
      printf( "Randomizing weapon.bin Crit Chance...\n" );
      randomizeWeaponCrit();
    }

    if (options_pack.randomize_weapon_damage_formula)
    {
      printf( "Randomizing weapon.bin Damage Formula...\n" );
      randomizeWeaponDamageFormula();
    }

    printf( "Reconstructing shop_arms.bin...\n" );
    std::thread shop_arms_data_thread( &randomizer_t::reconstructShopArmsData, this );
    printf( "Reconstructing buki_get.bin...\n" );
    std::thread buki_data_thread( &randomizer_t::reconstructBukiData, this );
    printf( "Reconstructing weapon.bin...\n" );
    std::thread weapon_data_thread( &randomizer_t::reconstructWeaponData, this );

    shop_arms_data_thread.join();
    buki_data_thread.join();
    weapon_data_thread.join();
  }

  void doPlayerStatRandomization()
  {
    if (!options_pack.randomize_player_stats && !options_pack.randomize_aeon_stat_scaling && !options_pack.shuffle_player_stats &&
         !options_pack.shuffle_aeon_stat_scaling && !options_pack.poison_is_deadly && !options_pack.randomize_starting_overdrive_mode &&
         !options_pack.shuffle_sphere_grid && !options_pack.randomize_sphere_grid)
      return;

    if (options_pack.randomize_player_stats)
    {
      printf( "Randomizing Party Stats...\n" );
      randomizePlayerStats();
    }

    if (options_pack.randomize_aeon_stat_scaling)
    {
      printf( "Randomizing Aeon Stat Scaling...\n" );
      randomizeAeonStatScaling();
    }

    if (options_pack.randomize_aeon_base_stats)
    {
      printf( "Randomizing Aeon Base Stats...\n" );
      randomizeAeonBaseStats();
    }

    if (options_pack.shuffle_player_stats)
    {
      for (int i = 0; i < 7; i++)
      {
        character_stats_t* stats = data_pack.player_stats_data[ i ];
        shuffled_player_stats_data.push_back( stats );
      }
      std::shuffle( shuffled_player_stats_data.begin(), shuffled_player_stats_data.end(), rng );
      printf( "Shuffling Party Stats...\n" );
      shuffleCharacterStats();
    }

    if (options_pack.shuffle_aeon_stat_scaling)
    {
      printf( "Shuffling Aeon Stat Scaling...\n" );
      for (auto& aeon_scaling_data : data_pack.aeon_scaling_data)
      {
        if (!aeon_scaling_data->is_yuna_summon)
          continue;
        shuffled_aeon_scaling_data.push_back( aeon_scaling_data );
        std::shuffle( shuffled_aeon_scaling_data.begin(), shuffled_aeon_scaling_data.end(), rng );
      }
      shuffleAeonStatScaling();
    }

    if (options_pack.shuffle_aeon_base_stats)
    {
      printf( "Shuffling Aeon Base Stats...\n" );
      shuffleAeonBaseStats();
    }

    if (options_pack.poison_is_deadly)
    {
      printf( "Making Poison Deadly...\n" );
      for (auto& stats : data_pack.player_stats_data)
      {
        stats->poison_damage = 50;
        stats->writeToBytes();
      }
    }

    if (options_pack.randomize_starting_overdrive_mode)
    {
      printf( "Randomizing Starting Overdrive Mode...\n" );
      for (int i = 0; i < 7; i++)
      {
        character_stats_t& stats = *data_pack.player_stats_data.at( i );
        uint8_t overdrive_mode = uniform<uint8_t>( 0, 16 );
        stats.overdrive_current = overdrive_mode;
        stats.overdrive_mode = overdrive_mode;
        if (overdrive_mode != 2)
          stats.overdrive.bits.stoic = 0;

        switch (overdrive_mode)
        {
          case 0:
            stats.overdrive.bits.warrior = 1;
            break;
          case 1:
            stats.overdrive.bits.comrade = 1;
            break;
          case 2:
            stats.overdrive.bits.stoic = 1;
            break;
          case 3:
            stats.overdrive.bits.healer = 1;
            break;
          case 4:
            stats.overdrive.bits.tactician = 1;
            break;
          case 5:
            stats.overdrive.bits.victim = 1;
            break;
          case 6:
            stats.overdrive.bits.dancer = 1;
            break;
          case 7:
            stats.overdrive.bits.avenger = 1;
            break;
          case 8:
            stats.overdrive.bits.slayer = 1;
            break;
          case 9:
            stats.overdrive.bits.hero = 1;
            break;
          case 10:
            stats.overdrive.bits.rook = 1;
            break;
          case 11:
            stats.overdrive.bits.victor = 1;
            break;
          case 12:
            stats.overdrive.bits.coward = 1;
            break;
          case 13:
            stats.overdrive.bits.ally = 1;
            break;
          case 14:
            stats.overdrive.bits.sufferer = 1;
            break;
          case 15:
            stats.overdrive.bits.daredevil = 1;
            break;
          case 16:
            stats.overdrive.bits.loner = 1;
            break;
        }
        stats.writeToBytes();
        // stats.test();
      }
    }

    printf( "Reconstructing ply_save.bin...\n" );
    reconstructPlayerStatsData();

    if (options_pack.randomize_aeon_stat_scaling || options_pack.shuffle_aeon_stat_scaling)
    {
      printf( "Reconstructing ply_rom.bin...\n" );
      reconstructAeonScalingData();
    }

    if (options_pack.randomize_aeon_base_stats || options_pack.shuffle_aeon_base_stats)
    {
      printf( "Reconstructing sum_assure.bin...\n" );
      reconstructAeonStatData();
    }
  }

  void upgradeSphereGridNodes()
  {
    for (auto& grid : data_pack.sphere_grid_data)
    {
      sphere_grid_data_t& grid_data = *grid;
      for (auto& grid_node : grid_data.nodes)
      {
        sphere_grid_node_data_t& node = *grid_node;
        switch (node.content)
        {
          case 0x02:
          case 0x03:
          case 0x04:
            node.content = 0x05;
            break;
          case 0x06:
          case 0x07:
          case 0x08:
            node.content = 0x09;
            break;
          case 0x0A:
          case 0x0B:
          case 0x0C:
            node.content = 0x0D;
            break;
          case 0x0E:
          case 0x0F:
          case 0x10:
            node.content = 0x11;
            break;
          case 0x12:
          case 0x13:
          case 0x14:
            node.content = 0x15;
            break;
          case 0x16:
          case 0x17:
          case 0x18:
            node.content = 0x19;
            break;
          case 0x1A:
          case 0x1B:
          case 0x1C:
            node.content = 0x1D;
            break;
          case 0x1E:
          case 0x1F:
          case 0x20:
            node.content = 0x21;
            break;
          case 0x22:
            node.content = 0x23;
            break;
          case 0x25:
          case 0x26:
            node.content = 0x24;
            break;
          default:
            break;
        }
        node.writeToBytes();
      }
      grid_data.writeToBytes();
    }
  }

  void downgradeSphereGridNodes()
  {
    for (auto& grid : data_pack.sphere_grid_data)
    {
      sphere_grid_data_t& grid_data = *grid;
      for (auto& grid_node : grid_data.nodes)
      {
        sphere_grid_node_data_t& node = *grid_node;
        switch (node.content)
        {
          case 0x03:
          case 0x04:
          case 0x05:
            node.content = 0x02;
            break;
          case 0x07:
          case 0x08:
          case 0x09:
            node.content = 0x06;
            break;
          case 0x0B:
          case 0x0C:
          case 0x0D:
            node.content = 0x0A;
            break;
          case 0x0F:
          case 0x10:
          case 0x11:
            node.content = 0x0E;
            break;
          case 0x13:
          case 0x14:
          case 0x15:
            node.content = 0x12;
            break;
          case 0x17:
          case 0x18:
          case 0x19:
            node.content = 0x16;
            break;
          case 0x1B:
          case 0x1C:
          case 0x1D:
            node.content = 0x1A;
            break;
          case 0x1F:
          case 0x20:
          case 0x21:
            node.content = 0x1E;
            break;
          case 0x23:
            node.content = 0x22;
            break;
          case 0x24:
          case 0x25:
            node.content = 0x26;
            break;
          default:
            break;
        }
        node.writeToBytes();
      }
      grid_data.writeToBytes();
    }
  }

  void doSphereGridRandomization()
  {
    if (!options_pack.shuffle_sphere_grid && !options_pack.randomize_sphere_grid && !options_pack.empty_sphere_grid &&
         !options_pack.fill_sphere_grid && !options_pack.upgrade_sphere_nodes && !options_pack.downgrade_sphere_nodes &&
         !options_pack.remove_sphere_grid_locks)
      return;

    if (options_pack.shuffle_sphere_grid)
    {
      printf( "Randomizing Sphere Grid...\n" );
      shuffleSphereGridNodes();
    }

    if (options_pack.randomize_sphere_grid)
    {
      printf( "Randomizing Sphere Grid...\n" );
      randomizeSphereGrid();
    }

    if (options_pack.remove_sphere_grid_locks)
    {
      printf( "Removing Sphere Grid Locks...\n" );
      removeSphereGridLocks();
    }

    if (options_pack.empty_sphere_grid)
    {
      printf( "Emptying Sphere Grid...\n" );
      emptySphereGrid();
    }

    if (options_pack.fill_sphere_grid)
    {
      printf( "Filling Sphere Grid...\n" );
      fillSphereGrid();
    }

    if (options_pack.upgrade_sphere_nodes)
    {
      printf( "Upgrading Sphere Grid Nodes...\n" );
      upgradeSphereGridNodes();
    }

    if (options_pack.downgrade_sphere_nodes)
    {
      printf( "Downgrading Sphere Grid Nodes...\n" );
      downgradeSphereGridNodes();
    }

    reconstructSphereGridData();
  }

  void randomize()
  {
    printf( "Starting Randomizer...\n" );

    // Clean the output folder to prevent any issues
    std::filesystem::remove_all( OUTPUT_FOLDER );

    std::thread enemy_thread( &randomizer_t::doEnemyRandomization, this );
    std::thread shop_thread( &randomizer_t::doShopRandomization, this );
    std::thread price_thread( &randomizer_t::doPriceRandomization, this );
    std::thread field_thread( &randomizer_t::doFieldRandomization, this );
    std::thread gear_thread( &randomizer_t::doGearRandomization, this );
    // Dont Thread these to prevent a race condition.
    // TODO: Refactor so the race condition isnt possible
    // Since Player stats write the data to the file, make sure sphere grid is randomized first
    // as this sets the flags for Use and Lancet on Khimari and Riku if necessaray.
    doSphereGridRandomization();
    doPlayerStatRandomization();

    enemy_thread.join();
    shop_thread.join();
    price_thread.join();
    field_thread.join();
    gear_thread.join();

    writeJson( json_data );
  }
};