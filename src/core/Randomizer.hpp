#pragma once
#include <filesystem>
#include <thread>
#include <unordered_map>
#include <random>
#include <type_traits>
#include <string>
#include <vector>
#include <cstdint>
#include "Data.hpp"
#include "BytesHelper.hpp"

struct randomizer_t
{
private:
  std::mt19937 rng;
  std::unordered_map<int, enemy_data_t*> enemy_data;
  std::vector<field_data_t*> field_data;
  std::vector<shop_data_t*> item_shop_data;
  std::vector<shop_data_t*> gear_shop_data;
  std::vector<gear_data_t*> buki_data;
  std::vector<gear_data_t*> weapon_data;
  std::vector<gear_data_t*> arms_shop_data;
  std::vector<item_rate_t*> item_rate_data;
  std::vector<character_stats_t*> character_stats_data;
  std::vector<aeon_scaling_data_t*> aeon_scaling_data;
  std::vector<aeon_stat_data_t*> aeon_stat_data;

  std::unordered_map<int, item_t*> all_items;
  std::unordered_map<int, item_t*> all_non_key_items;
  std::unordered_map<int, item_t*> all_key_items;
  std::vector<gear_data_t*> all_armor;
  std::vector<gear_data_t*> all_weapons;
  std::vector<uint16_t> abilities;
  std::vector<uint8_t> def_pool;
  std::vector<uint8_t> mdef_pool;
  std::vector<uint8_t> eva_pool;

  bool randomize_enemy_drops;
  bool randomize_enemy_steals;
  bool randomize_enemy_bribes;
  bool randomize_enemy_gear_drops;
  bool randomize_enemy_stats_normal;
  bool randomize_enemy_stats_defensive_normalized;
  bool randomize_enemy_stats_shuffle;
  bool randomize_enemy_elemental_affinities;
  bool randomize_shops;
  bool randomize_shop_prices;
  bool randomize_field_items;
  bool randomize_gear_abilities;
  bool randomize_player_stats;
  bool randomize_aeon_stat_scaling;
  bool randomize_aeon_base_stats;
  bool shuffle_player_stats;
  bool shuffle_aeon_stat_scaling;
  bool shuffle_aeon_base_stats;
  bool randomize_starting_overdrive_mode;

  bool poison_is_deadly;

  bool randomize_key_items;
  bool keep_things_sane;

  std::vector<character_stats_t*> shuffled_player_stats_data;
  std::vector<aeon_scaling_data_t*> shuffled_aeon_data;
  std::vector<aeon_stat_data_t*> shuffled_aeon_stat_data;

public:
  randomizer_t( int32_t seed,
                std::unordered_map<int, enemy_data_t*> enemy_data,
                std::vector<field_data_t*> field_data,
                std::vector< shop_data_t*> item_shop_data,
                std::vector< shop_data_t*> gear_shop_data,
                std::vector< gear_data_t*> buki_data,
                std::vector< gear_data_t*> weapon_data,
                std::vector< gear_data_t*> arms_shop_data,
                std::vector<item_rate_t*> item_rate_data,
                std::vector<character_stats_t*> player_stats_data,
                std::vector<aeon_scaling_data_t*> aeon_scaling_data,
                std::vector<aeon_stat_data_t*> aeon_stat_data,
                bool randomize_enemy_drops,
                bool randomize_enemy_steals,
                bool randomize_enemy_bribes,
                bool randomize_enemy_gear_drops,
                bool randomize_enemy_stats,
                bool randomize_enemy_stats_defensive_normalized,
                bool randomize_enemy_stats_shuffle,
                bool randomize_enemy_elemental_affinities,
                bool randomize_shops,
                bool randomize_shop_prices,
                bool randomize_field_items,
                bool randomize_gear_abilities,
                bool randomize_player_stats,
                bool randomize_aeon_stat_scaling,
                bool randomize_aeon_base_stats,
                bool shuffle_player_stats,
                bool shuffle_aeon_stat_scaling,
                bool shuffle_aeon_base_stats,
                bool poison_is_deadly,
                bool randomize_starting_overdrive_mode,
                bool randomize_key_items,
                bool keep_things_sane
  )
    :
  enemy_data( enemy_data ),
    field_data( field_data ),
    item_shop_data( item_shop_data ),
    gear_shop_data( gear_shop_data ),
    buki_data( buki_data ),
    weapon_data( weapon_data ),
    arms_shop_data( arms_shop_data ),
    item_rate_data( item_rate_data ),
    character_stats_data( player_stats_data ),
    aeon_scaling_data( aeon_scaling_data ),
    aeon_stat_data( aeon_stat_data ), // End of Data input
    randomize_enemy_drops( randomize_enemy_drops ),
    randomize_enemy_gear_drops( randomize_enemy_gear_drops ),
    randomize_enemy_steals( randomize_enemy_steals ),
    randomize_enemy_bribes( randomize_enemy_bribes ),
    randomize_enemy_stats_normal( randomize_enemy_stats ),
    randomize_enemy_stats_defensive_normalized( randomize_enemy_stats_defensive_normalized ),
    randomize_enemy_stats_shuffle( randomize_enemy_stats_shuffle ),
    randomize_enemy_elemental_affinities( randomize_enemy_elemental_affinities ),
    randomize_shops( randomize_shops ),
    randomize_shop_prices( randomize_shop_prices ),
    randomize_field_items( randomize_field_items ),
    randomize_gear_abilities( randomize_gear_abilities ),
    randomize_player_stats( randomize_player_stats ),
    randomize_aeon_stat_scaling( randomize_aeon_stat_scaling ),
    randomize_aeon_base_stats( randomize_aeon_base_stats ),
    shuffle_player_stats( shuffle_player_stats ),
    shuffle_aeon_stat_scaling( shuffle_aeon_stat_scaling ),
    shuffle_aeon_base_stats( shuffle_aeon_base_stats ),
    poison_is_deadly( poison_is_deadly ),
    randomize_starting_overdrive_mode( randomize_starting_overdrive_mode ),
    randomize_key_items( randomize_key_items ),
    keep_things_sane( keep_things_sane )
  {
    rng.seed( seed );
    getFieldItems();
    getShopItems();
    getMonsterItems();
    poplateGearLists();
    populateAbilityData();
    randomize();
  }

  template <typename T>
  T uniform( T min, T max ) {
    static_assert( std::is_integral<T>::value, "Only integral types are supported" );

    using DistType = typename std::conditional<
      sizeof( T ) <= 2, uint32_t, T
    >::type;

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

  // TODO: Clean up this mess of repetitive code
  void reconstructBukiData()
  {
    std::vector<char> reconstructed_buki_data;
    std::string path = INPUT_FOLDER + BATTLE_KERNEL_FOLDER + "buki_get.bin";
    std::vector<char> bytes = bytes_mapper_t::fileToBytes( path );
    bytes = std::vector<char>( bytes.begin(), bytes.begin() + 20 );
    reconstructed_buki_data.insert( reconstructed_buki_data.end(), bytes.begin(), bytes.end() );
    for (auto& gear : buki_data)
    {
      std::vector<char> gear_bytes = gear->bytes;
      reconstructed_buki_data.insert( reconstructed_buki_data.end(), gear_bytes.begin(), gear_bytes.end() );
    }

    std::string output_path = OUTPUT_FOLDER + BATTLE_KERNEL_FOLDER;
    std::filesystem::create_directories( output_path );
    std::string file = output_path + "buki_get.bin";
    bytes_mapper_t::writeBytesToNewFile( reconstructed_buki_data, file );
  }

  void reconstructWeaponData()
  {
    std::vector<char> reconstructed_weapon_data;
    std::string path = INPUT_FOLDER + BATTLE_KERNEL_FOLDER + "weapon.bin";
    std::vector<char> bytes = bytes_mapper_t::fileToBytes( path );
    bytes = std::vector<char>( bytes.begin(), bytes.begin() + 20 );
    reconstructed_weapon_data.insert( reconstructed_weapon_data.end(), bytes.begin(), bytes.end() );
    for (auto& gear : weapon_data)
    {
      std::vector<char> gear_bytes = gear->bytes;
      reconstructed_weapon_data.insert( reconstructed_weapon_data.end(), gear_bytes.begin(), gear_bytes.end() );
    }

    std::string output_path = OUTPUT_FOLDER + BATTLE_KERNEL_FOLDER;
    std::filesystem::create_directories( output_path );
    std::string file = output_path + "weapon.bin";
    bytes_mapper_t::writeBytesToNewFile( reconstructed_weapon_data, file );
  }

  void reconstructShopArmsData()
  {
    std::vector<char> reconstructed_shop_arms_data;
    std::string path = INPUT_FOLDER + BATTLE_KERNEL_FOLDER + "shop_arms.bin";
    std::vector<char> bytes = bytes_mapper_t::fileToBytes( path );
    bytes = std::vector<char>( bytes.begin(), bytes.begin() + 20 );
    reconstructed_shop_arms_data.insert( reconstructed_shop_arms_data.end(), bytes.begin(), bytes.end() );
    for (auto& gear : arms_shop_data)
    {
      std::vector<char> gear_bytes = gear->bytes;
      reconstructed_shop_arms_data.insert( reconstructed_shop_arms_data.end(), gear_bytes.begin(), gear_bytes.end() );
    }
    std::string output_path = OUTPUT_FOLDER + BATTLE_KERNEL_FOLDER;
    std::filesystem::create_directories( output_path );
    std::string file = output_path + "shop_arms.bin";
    bytes_mapper_t::writeBytesToNewFile( reconstructed_shop_arms_data, file );
  }

  void reconstructTakaraData()
  {
    std::vector<char> reconstructed_takara_data;
    std::string path = INPUT_FOLDER + BATTLE_KERNEL_FOLDER + "takara.bin";
    std::vector<char> bytes = bytes_mapper_t::fileToBytes( path );
    bytes = std::vector<char>( bytes.begin(), bytes.begin() + 20 );
    reconstructed_takara_data.insert( reconstructed_takara_data.end(), bytes.begin(), bytes.end() );
    for (auto& gear : field_data)
    {
      std::vector<char> gear_bytes = gear->bytes;
      reconstructed_takara_data.insert( reconstructed_takara_data.end(), gear_bytes.begin(), gear_bytes.end() );
    }
    std::string output_path = OUTPUT_FOLDER + BATTLE_KERNEL_FOLDER;
    std::filesystem::create_directories( output_path );
    std::string file = output_path + "takara.bin";
    bytes_mapper_t::writeBytesToNewFile( reconstructed_takara_data, file );
  }

  void reconstructItemShopData()
  {
    std::vector<char> reconstructed_item_shop_data;
    std::string path = INPUT_FOLDER + BATTLE_KERNEL_FOLDER + "item_shop.bin";
    std::vector<char> bytes = bytes_mapper_t::fileToBytes( path );
    bytes = std::vector<char>( bytes.begin(), bytes.begin() + 20 );
    reconstructed_item_shop_data.insert( reconstructed_item_shop_data.end(), bytes.begin(), bytes.end() );
    for (auto& gear : item_shop_data)
    {
      std::vector<char> gear_bytes = gear->bytes;
      reconstructed_item_shop_data.insert( reconstructed_item_shop_data.end(), gear_bytes.begin(), gear_bytes.end() );
    }
    std::string output_path = OUTPUT_FOLDER + BATTLE_KERNEL_FOLDER;
    std::filesystem::create_directories( output_path );
    std::string file = output_path + "item_shop.bin";
    bytes_mapper_t::writeBytesToNewFile( reconstructed_item_shop_data, file );
  }

  void reconstructArmsShopData()
  {
    std::vector<char> reconstructed_arms_shop_data;
    std::string path = INPUT_FOLDER + BATTLE_KERNEL_FOLDER + "arms_shop.bin";
    std::vector<char> bytes = bytes_mapper_t::fileToBytes( path );
    bytes = std::vector<char>( bytes.begin(), bytes.begin() + 20 );
    reconstructed_arms_shop_data.insert( reconstructed_arms_shop_data.end(), bytes.begin(), bytes.end() );
    for (auto& gear : gear_shop_data)
    {
      std::vector<char> gear_bytes = gear->bytes;
      reconstructed_arms_shop_data.insert( reconstructed_arms_shop_data.end(), gear_bytes.begin(), gear_bytes.end() );
    }
    std::string output_path = OUTPUT_FOLDER + BATTLE_KERNEL_FOLDER;
    std::filesystem::create_directories( output_path );
    std::string file = output_path + "arms_shop.bin";
    bytes_mapper_t::writeBytesToNewFile( reconstructed_arms_shop_data, file );
  }

  void reconstructItemRateData()
  {
    std::vector<char> reconstructed_item_rate_data;
    std::string path = INPUT_FOLDER + BATTLE_KERNEL_FOLDER + "item_rate.bin";
    std::vector<char> bytes = bytes_mapper_t::fileToBytes( path );
    bytes = std::vector<char>( bytes.begin(), bytes.begin() + 20 );
    reconstructed_item_rate_data.insert( reconstructed_item_rate_data.end(), bytes.begin(), bytes.end() );
    for (auto& item_rate : item_rate_data)
    {
      std::vector<char> item_rate_bytes = item_rate->bytes;
      reconstructed_item_rate_data.insert( reconstructed_item_rate_data.end(), item_rate_bytes.begin(), item_rate_bytes.end() );
    }
    std::string output_path = OUTPUT_FOLDER + BATTLE_KERNEL_FOLDER;
    std::filesystem::create_directories( output_path );
    std::string file = output_path + "item_rate.bin";
    bytes_mapper_t::writeBytesToNewFile( reconstructed_item_rate_data, file );
  }

  void reconstructPlayerStatsData()
  {
    for (auto& locale : LOCALIZATIONS)
    {
      std::string path = INPUT_FOLDER + locale.second + "ply_save.bin";
      std::vector<char> original_bytes = bytes_mapper_t::fileToBytes( path );
      for (int j = 0; j < character_stats_data.size(); j++)
      {
        character_stats_t* player_stats = character_stats_data[ j ];
        std::vector<char> player_stats_bytes = player_stats->bytes;
        for (int i = 0; i < player_stats_bytes.size(); i++)
        {
          original_bytes[ 20 + player_stats->index * 148 + i ] = player_stats_bytes[ i ];
        }
      }
      std::string output_path = OUTPUT_FOLDER + locale.second;
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
      int initial_offset = 20 + 44 * 8;
      for (int j = 0; j < aeon_scaling_data.size(); j++)
      {
        aeon_scaling_data_t* aeon_scaling = aeon_scaling_data[ j ];
        std::vector<char> aeon_scaling_bytes = aeon_scaling->bytes;
        for (int i = 0; i < aeon_scaling_bytes.size(); i++)
        {
          original_bytes[ initial_offset + j * 44 + i ] = aeon_scaling_bytes[ i ];
        }
      }
      std::string output_path = OUTPUT_FOLDER + locale.second;
      std::filesystem::create_directories( output_path );
      std::string file = output_path + "ply_rom.bin";
      bytes_mapper_t::writeBytesToNewFile( original_bytes, file );
    }
  }

  void reconstructAeonStatData()
  {
    std::string path = INPUT_FOLDER + BATTLE_KERNEL_FOLDER + "sum_assure.bin";
    std::vector<char> original_bytes = bytes_mapper_t::fileToBytes( path );
    for (int j = 0; j < shuffled_aeon_data.size(); j++)
    {
      aeon_scaling_data_t* aeon_scaling = shuffled_aeon_data[ j ];
      std::vector<char> aeon_scaling_bytes = aeon_scaling->bytes;
      for (int i = 0; i < aeon_scaling_bytes.size(); i++)
      {
        original_bytes[ 20 + j * 120 + i ] = aeon_scaling_bytes[ i ];
      }
    }
    std::string output_path = OUTPUT_FOLDER + BATTLE_KERNEL_FOLDER;
    std::filesystem::create_directories( output_path );
    std::string file = output_path + "sum_assure.bin";
    bytes_mapper_t::writeBytesToNewFile( original_bytes, file );
  }

  void checkItemList( uint16_t& id, uint8_t& quantity, bool key = false )
  {
    if (id == 0)
      return;
    if (quantity == 0)
      quantity = 1;
    if (id > 9000)
      key = true;

    std::unordered_map<int, item_t*>::iterator it = all_items.find( id );

    bool found = it != all_items.end();
    if (!found)
    {
      item_t* item = new item_t( id, quantity, quantity );
      all_items.insert( { id , item } );
      if (!key)
        all_non_key_items.insert( { id , item } );
      if (key)
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
    for (auto& item : field_data)
    {
      field_data_t& field = *item;
      if (field.flag == 2 || field.flag == 10)
        checkItemList( field.type, field.quantity, field.flag == 10 );
    }
  }

  void getMonsterItems()
  {
    for (auto& enemy : enemy_data)
    {
      enemy_loot_data_t& loot = *enemy.second->loot_data;
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
    for (auto& shop : item_shop_data)
    {
      shop_data_t& item_shop = *shop;
      for (auto& item : item_shop.item_indexes)
      {
        checkItemList( item, quantity );
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
    if (keep_things_sane)
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
    if (keep_things_sane)
    {
      if (loot.gil > 0)
        loot.gil = normal<uint16_t>( loot.gil, loot.gil, 0, UINT16_MAX );
      if (loot.ap > 0)
        loot.ap = normal<uint16_t>( loot.ap, loot.ap, 0, UINT16_MAX );
      if (loot.ap_overkill > 0)
        loot.ap_overkill = normal<uint16_t>( loot.ap_overkill, loot.ap_overkill, 0, UINT16_MAX );
    }
    else
    {
      loot.gil = uniform<uint16_t>( 0, UINT16_MAX );
      loot.ap = uniform<uint16_t>( 0, UINT16_MAX );
      loot.ap_overkill = uniform<uint16_t>( 0, UINT16_MAX );
    }
    item_t* normal_drop = getRandomItemFromMap( randomize_key_items ? all_items : all_non_key_items );
    int normal_drop_quantity = getRandomItemQuantity( normal_drop );
    item_t* rare_drop = getRandomItemFromMap( randomize_key_items ? all_items : all_non_key_items );
    int rare_drop_quantity = getRandomItemQuantity( rare_drop );
    item_t* secondary_normal_drop = getRandomItemFromMap( randomize_key_items ? all_items : all_non_key_items );
    int secondary_normal_drop_quantity = getRandomItemQuantity( secondary_normal_drop );
    item_t* secondary_rare_drop = getRandomItemFromMap( randomize_key_items ? all_items : all_non_key_items );
    int secondary_rare_drop_quantity = getRandomItemQuantity( secondary_rare_drop );
    item_t* normal_overkill_drop = getRandomItemFromMap( randomize_key_items ? all_items : all_non_key_items );
    int normal_overkill_drop_quantity = getRandomItemQuantity( normal_overkill_drop );
    item_t* rare_overkill_drop = getRandomItemFromMap( randomize_key_items ? all_items : all_non_key_items );
    int rare_overkill_drop_quantity = getRandomItemQuantity( rare_overkill_drop );
    item_t* secondary_overkill_drop = getRandomItemFromMap( randomize_key_items ? all_items : all_non_key_items );
    int secondary_overkill_drop_quantity = getRandomItemQuantity( secondary_overkill_drop );
    item_t* secondary_rare_overkill_drop = getRandomItemFromMap( randomize_key_items ? all_items : all_non_key_items );
    int secondary_rare_overkill_drop_quantity = getRandomItemQuantity( secondary_rare_overkill_drop );
    loot.primary_normal_drop = normal_drop->id;
    loot.primary_normal_drop_rare = rare_drop->id;
    loot.primary_drop_chance = uniform<int>( 0, 255 );
    loot.secondary_normal_drop = secondary_normal_drop->id;
    loot.secondary_normal_drop_rare = secondary_rare_drop->id;
    loot.secondary_drop_chance = uniform<int>( 0, 255 );
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
    loot.writeToBytes();
    enemy->loot_data = &loot;
    enemy->writeLootData( loot );
  };

  void randomizeEnemySteal( enemy_data_t* enemy )
  {
    enemy_loot_data_t& loot = *enemy->loot_data;
    item_t* steal_item = getRandomItemFromMap( randomize_key_items ? all_items : all_non_key_items );
    int steal_item_quantity = getRandomItemQuantity( steal_item );
    item_t* rare_steal_item = getRandomItemFromMap( randomize_key_items ? all_items : all_non_key_items );
    int rare_steal_item_quantity = getRandomItemQuantity( rare_steal_item );
    loot.steal_chance = uniform<int>( 0, 255 );
    loot.steal_item = steal_item->id;
    loot.steal_item_rare = rare_steal_item->id;
    loot.n_steal_item = steal_item_quantity;
    loot.n_steal_item_rare = rare_steal_item_quantity;
    if (loot.n_gil_steal > 0)
      loot.n_gil_steal = normal<uint16_t>( loot.n_gil_steal, loot.n_gil_steal, 0, UINT16_MAX );
    loot.writeToBytes();
    enemy->loot_data = &loot;
    enemy->writeLootData( loot );
  }

  void randomizeEnemyBribe( enemy_data_t* enemy )
  {
    enemy_loot_data_t& loot = *enemy->loot_data;
    item_t* bribe_item = getRandomItemFromMap( randomize_key_items ? all_items : all_non_key_items );
    int bribe_item_quantity = getRandomItemQuantity( bribe_item );
    loot.bribe_item = bribe_item->id;
    loot.n_bribe_item = bribe_item_quantity;
    loot.writeToBytes();
    enemy->loot_data = &loot;
    enemy->writeLootData( loot );
  }

  void randomizeEnemyStatsNormal( enemy_data_t* enemy )
  {
    enemy_stat_data_t& stats = *enemy->stats_data;
    stats.hp = normal<uint32_t>( stats.hp, stats.hp / 2, 50, UINT32_MAX );
    stats.mp = normal<uint32_t>( stats.mp, stats.mp / 2, 1, 999 );
    stats.overkill_threshold = normal<uint32_t>( stats.overkill_threshold / 2, stats.overkill_threshold, 1, UINT32_MAX );
    stats.str = normal<uint8_t>( stats.str, stats.str / 2, 0, UINT8_MAX );
    stats.def = normal<uint8_t>( stats.def, stats.def / 2, 0, UINT8_MAX );
    stats.mag = normal<uint8_t>( stats.mag, stats.mag / 2, 0, UINT8_MAX );
    stats.mdef = normal<uint8_t>( stats.mdef, stats.mdef / 2, 0, UINT8_MAX );
    stats.agi = normal<uint8_t>( stats.agi, stats.agi / 2, 0, UINT8_MAX );
    stats.acc = normal<uint8_t>( stats.acc, stats.acc / 2, 0, UINT8_MAX );
    stats.flags1.armored = rand() % 4 == 0;
    stats.writeToBytes();
    enemy->stats_data = &stats;
    enemy->writeStatsData( stats );
  }

  void addEnemyDefenses( enemy_data_t* enemy )
  {
    enemy_stat_data_t& stats = *enemy->stats_data;
    def_pool.push_back( stats.def );
    mdef_pool.push_back( stats.mdef );
    eva_pool.push_back( stats.eva );
  }

  void randomizeEnemyStatsDefensiveNormalization( enemy_data_t* enemy )
  {
    enemy_stat_data_t& stats = *enemy->stats_data;
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

    double defensive_factor = ( def_factor + mdef_factor + evasion_factor );
    if (defensive_factor < 0.33)
      stats.flags1.armored = 0;
    else
      stats.flags1.armored = rand() % 4 == 0;

    uint32_t base_hp = stats.hp * defensive_factor;
    if (base_hp == 0)
      base_hp = 1;
    uint32_t hp = normal<uint32_t>( base_hp, base_hp / 2, 50, UINT32_MAX );
    stats.hp = hp;
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
    enemy_stat_data_t& stats = *enemy->stats_data;
    // Pick a random index to pull the stats from
    std::uniform_int_distribution<size_t> dist( 0, enemy_data.size() - 1 );
    int index = dist( rng );
    stats.hp = normal<uint32_t>( stats.hp, stats.hp / 2, 50, UINT32_MAX );
    stats.mp = normal<uint32_t>( stats.mp, stats.mp / 2, 1, UINT32_MAX );
    stats.overkill_threshold = normal<uint32_t>( stats.overkill_threshold / 2, stats.overkill_threshold, 1, UINT32_MAX );
    stats.str = normal<uint8_t>( stats.str, stats.str / 2, 0, UINT8_MAX );
    stats.def = def_pool[ index ];
    stats.mdef = mdef_pool[ index ];
    stats.eva = eva_pool[ index ];
    stats.flags1.armored = rand() % 4 == 0;
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

    int fire_roll = uniform<int>( 0, 69 );
    int ice_roll = uniform<int>( 0, 69 );
    int lightning_roll = uniform<int>( 0, 69 );
    int water_roll = uniform<int>( 0, 69 );
    int holy_roll = uniform<int>( 0, 69 );

    stats.element_weakness_flags.fire = fire_roll < 20;
    stats.element_weakness_flags.ice = ice_roll < 20;
    stats.element_weakness_flags.lightning = lightning_roll < 20;
    stats.element_weakness_flags.water = water_roll < 20;
    stats.element_weakness_flags.holy = holy_roll < 20;

    stats.element_resist_flags.fire = fire_roll < 25 && fire_roll >= 20;
    stats.element_resist_flags.ice = ice_roll < 25 && ice_roll >= 20;
    stats.element_resist_flags.lightning = lightning_roll < 25 && lightning_roll >= 20;
    stats.element_resist_flags.water = water_roll < 25 && water_roll >= 20;
    stats.element_resist_flags.holy = holy_roll < 25 && holy_roll >= 20;

    stats.element_immune_flags.fire = fire_roll < 30 && fire_roll >= 25;
    stats.element_immune_flags.ice = ice_roll < 30 && ice_roll >= 25;
    stats.element_immune_flags.lightning = lightning_roll < 30 && lightning_roll >= 25;
    stats.element_immune_flags.water = water_roll < 30 && water_roll >= 25;
    stats.element_immune_flags.holy = holy_roll < 30 && holy_roll >= 25;

    stats.element_absorb_flags.fire = fire_roll < 35 && fire_roll >= 30;
    stats.element_absorb_flags.ice = ice_roll < 35 && ice_roll >= 30;
    stats.element_absorb_flags.lightning = lightning_roll < 35 && lightning_roll >= 30;
    stats.element_absorb_flags.water = water_roll < 35 && water_roll >= 30;
    stats.element_absorb_flags.holy = holy_roll < 35 && holy_roll >= 30;

    stats.writeToBytes();
    enemy->stats_data = &stats;
    enemy->writeStatsData( stats );
  }

  void poplateGearLists()
  {
    for (auto& gear : buki_data)
    {
      gear_data_t* armor = gear;
      if (armor->is_armor)
        all_armor.push_back( armor );
      else
        all_weapons.push_back( armor );
    }
    for (auto& gear : weapon_data)
    {
      gear_data_t* armor = gear;
      if (armor->is_armor)
        all_armor.push_back( armor );
      else
        all_weapons.push_back( armor );
    }
    for (auto& gear : arms_shop_data)
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
    for (auto& enemy : enemy_data)
    {
      enemy_data_t* enemy_data = enemy.second;
      enemy_loot_data_t& loot = *enemy_data->loot_data;
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
    for (auto& shop : item_shop_data)
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
    std::uniform_int_distribution<size_t> dist( 0, arms_shop_data.size() - 1 );
    return dist( rng );
  }

  void randomizeGearShops()
  {
    for (auto& shop : gear_shop_data)
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

  void writeGearData( gear_data_t* gear )
  {
    if (gear->is_celestial || gear->is_brotherhood)
      return;

    int n_abilities = uniform<int>( 0, 3 );

    std::vector<uint16_t> abilities;

    for (int i = 0; i < 4; i++)
    {
      if (i >= n_abilities)
      {
        abilities.push_back( 255 );
        continue;
      }
      abilities.push_back( getRandomAbility() );
    }

    gear->ability_slot1 = abilities.at( 0 );
    gear->ability_slot2 = abilities.at( 1 );
    gear->ability_slot3 = abilities.at( 2 );
    gear->ability_slot4 = abilities.at( 3 );

    gear->writeToBytes();
  }

  void randomizeShopArmsAbilities()
  {
    for (auto& gear : arms_shop_data)
    {
      gear_data_t* gear_data = gear;
      writeGearData( gear_data );
    }
  }

  void randomizeBukiAbilities()
  {
    for (auto& gear : buki_data)
    {
      gear_data_t* gear_data = gear;
      writeGearData( gear_data );
    }
  }

  void randomizeWeaponsAbilities()
  {
    for (auto& gear : weapon_data)
    {
      gear_data_t* gear_data = gear;
      writeGearData( gear_data );
    }
  }

  void randomizeFieldItems()
  {
    std::vector<int> blacklist = { 177, 203 };
    for (auto& field : field_data)
    {
      field_data_t& field_data = *field;
      if (std::find( blacklist.begin(), blacklist.end(), field_data.index ) != blacklist.end())
        continue;

      if (field_data.flag != 10 || randomize_key_items)
      {
        int max = randomize_key_items ? 3 : 2;
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
            field_data.flag = 0x02;
            field_data.type = item->id;
            field_data.quantity = getRandomItemQuantity( item, false );
            field_data.writeToBytes();
            break;
          case 2:
            field_data.flag = 5;
            field_data.quantity = 1;
            field_data.type = uniform<uint16_t>( 0, buki_data.size() - 1 );
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
    for (auto& price : item_rate_data)
    {
      item_rate_t* item_rate = price;
      if (item_rate->item_rate > 1 && item_rate->item_rate != 2 && keep_things_sane)
        item_rate->item_rate = normal<uint32_t>( item_rate->item_rate, item_rate->item_rate, 0, UINT32_MAX );
      else
        item_rate->item_rate = uniform<uint32_t>( 1, UINT16_MAX );
      item_rate->writeToBytes();
    }
  }

  void randomizePlayerStats()
  {
    for (int i = 0; i < 7; i++)
    {
      character_stats_t& stats = *character_stats_data.at( i );
      stats.base_hp = normal<uint32_t>( stats.base_hp, stats.base_hp / 2, 50, 9999 );
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
    for (auto& aeon : aeon_scaling_data)
    {
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
    for (auto& aeon : aeon_stat_data)
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
      character_stats_t& stats = *character_stats_data.at( i );
      character_stats_t& new_stats = *shuffled_player_stats_data.at( i );
      stats.base_hp = new_stats.base_hp;
      stats.base_mp = new_stats.base_mp;
      if ( (i == 0 || i == 2 ) && new_stats.base_str < 14)
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
    for (int i = 0; i < aeon_scaling_data.size(); i++)
    {
      aeon_scaling_data_t& aeon = *aeon_scaling_data.at( i );
      aeon_scaling_data_t& shuffled_aeon = *aeon_scaling_data.at( i );
      aeon.bytes = shuffled_aeon.bytes;
    }
  }

  void shuffleAeonBaseStats()
  {
    std::shuffle( aeon_stat_data.begin(), aeon_stat_data.end(), rng );
    for (int i = 0; i < aeon_stat_data.size(); i++)
    {
      aeon_stat_data_t& aeon = *aeon_stat_data.at( i );
      aeon_stat_data_t& shuffled_aeon = *aeon_stat_data.at( i );
      aeon.bytes = shuffled_aeon.bytes;
    }
  }

  void doEnemyRandomization()
  {
    if (!randomize_enemy_drops && !randomize_enemy_steals && !randomize_enemy_bribes && !randomize_enemy_gear_drops &&
         !randomize_enemy_stats_normal && !randomize_enemy_stats_defensive_normalized && !randomize_enemy_stats_shuffle &&
         !randomize_enemy_elemental_affinities )
      return;

    if (randomize_enemy_drops)
    {
      printf( "Randomizing Enemy Drops...\n" );
      for (auto& enemy : enemy_data)
      {
        enemy_data_t* enemy_data = enemy.second;
        randomizeEnemyDrops( enemy.second );
      }
    }

    if (randomize_enemy_steals)
    {
      printf( "Randomizing Enemy Steals...\n" );
      for (auto& enemy : enemy_data)
      {
        enemy_data_t* enemy_data = enemy.second;
        randomizeEnemySteal( enemy.second );
      }
    }

    if (randomize_enemy_bribes)
    {
      printf( "Randomizing Enemy Bribes...\n" );
      for (auto& enemy : enemy_data)
      {
        enemy_data_t* enemy_data = enemy.second;
        randomizeEnemyBribe( enemy.second );
      }
    }

    if (randomize_enemy_gear_drops)
    {
      printf( "Randomizing Enemy Gear Drops...\n" );
      for (auto& enemy : enemy_data)
      {
        enemy_data_t* enemy_data = enemy.second;
        randomizeEnemyGearDrops( enemy.second );
      }
    }

    if (randomize_enemy_stats_normal)
    {
      printf( "Randomizing Enemy Stats...\n" );
      for (auto& enemy : enemy_data)
      {
        enemy_data_t* enemy_data = enemy.second;
        randomizeEnemyStatsNormal( enemy.second );
      }
    }

    if (randomize_enemy_stats_defensive_normalized)
    {
      printf( "Randomizing Enemy Defensive Stats...\n" );
      for (auto& enemy : enemy_data)
      {
        enemy_data_t* enemy_data = enemy.second;
        addEnemyDefenses( enemy.second );
      }
      for (auto& enemy : enemy_data)
      {
        enemy_data_t* enemy_data = enemy.second;
        randomizeEnemyStatsDefensiveNormalization( enemy.second );
      }
    }

    if (randomize_enemy_stats_shuffle)
    {
      printf( "Shuffling Enemy Stats...\n" );
      for (auto& enemy : enemy_data)
      {
        enemy_data_t* enemy_data = enemy.second;
        addEnemyDefenses( enemy.second );
      }
      for (auto& enemy : enemy_data)
      {
        enemy_data_t* enemy_data = enemy.second;
        shuffleEnemyStats( enemy.second );
      }
    }

    if (randomize_enemy_elemental_affinities)
    {
      printf( "Randomizing Enemy Elemental Affinities...\n" );
      for (auto& enemy : enemy_data)
      {
        enemy_data_t* enemy_data = enemy.second;
        randomizeEnemyElementalAffinities( enemy.second );
      }
    }

    printf( "Reconstructing Enemy Files...\n" );
    for (auto& enemy : enemy_data)
    {
      enemy_data_t* enemy_data = enemy.second;
      std::string pathstr = OUTPUT_FOLDER + MONSTER_FOLDER + "_m" + enemy_data->monster_id;
      std::filesystem::path path = pathstr;
      std::filesystem::create_directories( path );
      std::string filepath = pathstr + "/m" + enemy_data->monster_id + ".bin";
      enemy_data->writeBytesToNewFile( enemy_data->bytes, filepath );
    }
  }

  void doShopRandomization()
  {
    if (!randomize_shops)
      return;

    printf( "Randomizing Item Shops...\n" );
    std::thread item_thread( &randomizer_t::randomizeItemShops, this );
    printf( "Randomizing Gear Shops...\n" );
    std::thread gear_thread( &randomizer_t::randomizeGearShops, this );

    item_thread.join();
    gear_thread.join();

    printf( "Reconstructing item_shop.bin...\n" );
    std::thread item_shop_thread( &randomizer_t::reconstructItemShopData, this );
    printf( "Reconstructing arms_shop.bin...\n" );
    std::thread arms_shop_thread( &randomizer_t::reconstructArmsShopData, this );

    item_shop_thread.join();
    arms_shop_thread.join();
  }

  void doPriceRandomization()
  {
    if (!randomize_shop_prices)
      return;

    printf( "Randomizing Item Prices...\n" );
    randomizeItemPrices();
    printf( "Reconstructing item_rate.bin...\n" );
    reconstructItemRateData();
  }

  void doFieldRandomization()
  {
    if (!randomize_field_items)
      return;

    printf( "Randomizing Field Items...\n" );
    randomizeFieldItems();
    printf( "Reconstructing takara.bin...\n" );
    reconstructTakaraData();
  }

  void doAbilityRandomization()
  {
    if (!randomize_gear_abilities)
      return;

    printf( "Randomizing shop_arms.bin Abilities...\n" );
    std::thread shop_arms_thread( &randomizer_t::randomizeShopArmsAbilities, this );
    printf( "Randomizing buki_get.bin Abilities...\n" );
    std::thread buki_thread( &randomizer_t::randomizeBukiAbilities, this );
    printf( "Randomizing weapon.bin Abilities...\n" );
    std::thread weapon_thread( &randomizer_t::randomizeWeaponsAbilities, this );

    shop_arms_thread.join();
    buki_thread.join();
    weapon_thread.join();

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
    if (!randomize_player_stats && !randomize_aeon_stat_scaling && !shuffle_player_stats && !shuffle_aeon_stat_scaling && !poison_is_deadly && !randomize_starting_overdrive_mode)
      return;

    if (randomize_player_stats)
    {
      printf( "Randomizing Party Stats...\n" );
      randomizePlayerStats();
    }

    if (randomize_aeon_stat_scaling)
    {
      printf( "Randomizing Aeon Stat Scaling...\n" );
      randomizeAeonStatScaling();
    }

    if (randomize_aeon_base_stats)
    {
      printf( "Randomizing Aeon Base Stats...\n" );
      randomizeAeonBaseStats();
    }

    if (shuffle_player_stats)
    {
      for (int i = 0; i < 7; i++)
      {
        character_stats_t* stats = character_stats_data.at( i );
        shuffled_player_stats_data.push_back( stats );
      }
      std::shuffle( shuffled_player_stats_data.begin(), shuffled_player_stats_data.end(), rng );
      printf( "Shuffling Party Stats...\n" );
      shuffleCharacterStats();
    }

    if (shuffle_aeon_stat_scaling)
    {
      printf( "Shuffling Aeon Stat Scaling...\n" );
      for (auto& aeon_scaling_data : aeon_scaling_data)
      {
        shuffled_aeon_data.push_back( aeon_scaling_data );
        std::shuffle( shuffled_aeon_data.begin(), shuffled_aeon_data.end(), rng );
      }
      shuffleAeonStatScaling();
    }

    if (shuffle_aeon_base_stats)
    {
      printf( "Shuffling Aeon Base Stats...\n" );
      shuffleAeonBaseStats();
    }

    if (poison_is_deadly)
    {
      printf( "Making Poison Deadly...\n" );
      for (auto& stats : character_stats_data)
      {
        stats->poison_damage = 50;
        stats->writeToBytes();
      }
    }

    if (randomize_starting_overdrive_mode)
    {
      printf( "Randomizing Starting Overdrive Mode...\n" );
      for (int i = 0; i < 7; i++)
      {
        character_stats_t& stats = *character_stats_data.at( i );
        uint8_t overdrive_mode = uniform<uint8_t>( 0, 17 );
        stats.overdrive_current = overdrive_mode;
        stats.overdrive_mode = overdrive_mode;
        stats.writeToBytes();
      }
    }

    printf( "Reconstructing ply_save.bin...\n" );
    reconstructPlayerStatsData();

    if (randomize_aeon_stat_scaling || shuffle_aeon_stat_scaling)
    {
      printf( "Reconstructing ply_rom.bin...\n" );
      reconstructAeonScalingData();
    }

    if (randomize_aeon_base_stats || shuffle_aeon_base_stats)
    {
      printf( "Reconstructing sum_assure.bin...\n" );
      reconstructAeonStatData();
    }
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
    std::thread ability_thread( &randomizer_t::doAbilityRandomization, this );
    std::thread player_thread( &randomizer_t::doPlayerStatRandomization, this );


    enemy_thread.join();
    shop_thread.join();
    price_thread.join();
    field_thread.join();
    ability_thread.join();
    player_thread.join();
  }
};