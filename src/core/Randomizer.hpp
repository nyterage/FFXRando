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
  std::unordered_map<int, field_data_t*> field_data;
  std::unordered_map<int, shop_data_t*> item_shop_data;
  std::unordered_map<int, shop_data_t*> gear_shop_data;
  std::unordered_map<int, gear_data_t*> buki_data;
  std::unordered_map<int, gear_data_t*> weapon_data;
  std::unordered_map<int, gear_data_t*> arms_shop_data;
  std::vector<item_rate_t*> item_rate_data;
  std::unordered_map<int, item_t*> all_items;
  std::unordered_map<int, item_t*> all_non_key_items;
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
  bool randomize_enemy_resists;
  bool randomize_shops;
  bool randomize_shop_prices;
  bool randomize_field_items;
  bool randomize_gear_abilities;
  bool randomize_key_items;
  bool keep_things_sane;

public:
  randomizer_t( int64_t seed,
                std::unordered_map<int, enemy_data_t*> enemy_data,
                std::unordered_map<int, field_data_t*> field_data,
                std::unordered_map<int, shop_data_t*> item_shop_data,
                std::unordered_map<int, shop_data_t*> gear_shop_data,
                std::unordered_map<int, gear_data_t*> buki_data,
                std::unordered_map<int, gear_data_t*> weapon_data,
                std::unordered_map<int, gear_data_t*> arms_shop_data,
                std::vector<item_rate_t*> item_rate_data,
                bool randomize_enemy_drops,
                bool randomize_enemy_steals,
                bool randomize_enemy_bribes,
                bool randomize_enemy_gear_drops,
                bool randomize_enemy_stats,
                bool randomize_enemy_stats_defensive_normalized,
                bool randomize_enemy_stats_shuffle,
                bool randomize_shops,
                bool randomize_shop_prices,
                bool randomize_field_items,
                bool randomize_gear_abilities,
                bool randomize_key_items,
                bool keep_things_sane
  )
    : rng( seed ),
    enemy_data( enemy_data ),
    field_data( field_data ),
    item_shop_data( item_shop_data ),
    gear_shop_data( gear_shop_data ),
    buki_data( buki_data ),
    weapon_data( weapon_data ),
    arms_shop_data( arms_shop_data ),
    item_rate_data( item_rate_data ),
    randomize_enemy_drops( randomize_enemy_drops ),
    randomize_enemy_gear_drops( randomize_enemy_gear_drops ),
    randomize_enemy_steals( randomize_enemy_steals ),
    randomize_enemy_bribes( randomize_enemy_bribes ),
    randomize_enemy_stats_normal( randomize_enemy_stats ),
    randomize_enemy_stats_defensive_normalized( randomize_enemy_stats_defensive_normalized ),
    randomize_enemy_stats_shuffle( randomize_enemy_stats_shuffle ),
    randomize_enemy_resists( false ),
    randomize_shops( randomize_shops ),
    randomize_shop_prices( randomize_shop_prices ),
    randomize_field_items( randomize_field_items ),
    randomize_gear_abilities( randomize_gear_abilities ),
    randomize_key_items( randomize_key_items ),
    keep_things_sane( keep_things_sane )
  {
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
      std::vector<char> gear_bytes = gear.second->bytes;
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
      std::vector<char> gear_bytes = gear.second->bytes;
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
      std::vector<char> gear_bytes = gear.second->bytes;
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
      std::vector<char> gear_bytes = gear.second->bytes;
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
      std::vector<char> gear_bytes = gear.second->bytes;
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
      std::vector<char> gear_bytes = gear.second->bytes;
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

  void checkItemList( uint16_t& id, uint8_t& quantity, bool key = false )
  {
    bool found = all_items.find( id ) != all_items.end();
    if (!found)
    {
      item_t* item = new item_t( id, quantity, quantity );
      all_items.insert( { id , item } );
      if (!key && ( id > 2100 && id < 2000 ) || id == 2064)
      {
        all_non_key_items.insert( { id , item } );
      }
    }
    else
    {
      item_t& it = *all_items.at( id );
      if (it.getMinQuantity() > quantity)
        it.setMinQuantity( quantity );
      if (it.getMaxQuantity() < quantity)
        it.setMaxQuantity( quantity );
    }
  }

  void getFieldItems()
  {
    for (int i = 0; i < field_data.size(); i++)
    {
      field_data_t& field = *field_data.at( i );
      if (field.flag == 10 || field.flag == 2)
        checkItemList( field.type, field.quantity, field.flag == 10 );
    }
  }

  void getMonsterItems()
  {
    for (auto& enemy : enemy_data)
    {
      enemy_loot_data_t* loot = enemy.second->loot_data;
      checkItemList( loot->primary_normal_drop, loot->n_primary_normal_drop );
      checkItemList( loot->primary_normal_drop_rare, loot->n_primary_normal_drop_rare );
      checkItemList( loot->secondary_normal_drop, loot->n_secondary_normal_drop );
      checkItemList( loot->secondary_normal_drop_rare, loot->n_secondary_normal_drop_rare );
      checkItemList( loot->primary_normal_drop_overkill, loot->n_primary_normal_drop_overkill );
      checkItemList( loot->primary_normal_drop_overkill_rare, loot->n_primary_normal_drop_overkill_rare );
      checkItemList( loot->secondary_normal_drop_overkill, loot->n_secondary_normal_drop_overkill );
      checkItemList( loot->secondary_normal_drop_overkill_rare, loot->n_secondary_normal_drop_overkill_rare );
      checkItemList( loot->steal_item, loot->n_steal_item );
      checkItemList( loot->steal_item_rare, loot->n_steal_item_rare );
      checkItemList( loot->bribe_item, loot->n_bribe_item );
    }
  }

  void getShopItems()
  {
    uint8_t quantity = 1;
    for (uint16_t i = 0; i < item_shop_data.size(); i++)
    {
      shop_data_t& shop = *item_shop_data.at( i );
      for (uint16_t j = 0; j < shop.item_indexes.size(); j++)
      {
        checkItemList( shop.item_indexes[ j ], quantity );
      }
    }
  }

  item_t* getRandomItemFromMap( std::unordered_map<int, item_t*>& map )
  {
    std::uniform_int_distribution<size_t> dist( 0, map.size() - 1 );
    int index = dist( rng );
    auto it = map.begin();
    std::advance( it, index );
    return it->second;
  }

  int getRandomItemQuantity( item_t* item )
  {
    if (keep_things_sane)
    {
      if (item->getAverageQuantity() > 2 && item->getMaxQuantity() > item->getMinQuantity() + 1)
        return normal<int>( item->getAverageQuantity(), item->getStandardDeviation(), item->getMinQuantity(), item->getMaxQuantity() );
      else if (item->getMaxQuantity() > item->getMinQuantity())
        return uniform<int>( item->getMinQuantity(), item->getMaxQuantity() );
      else
        return item->getMinQuantity();
    }

    return uniform<int>( 0, 99 );
  }

  void randomizeEnemyDrops( enemy_data_t* enemy, std::unordered_map<int, item_t*> map )
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
    item_t* normal_drop = getRandomItemFromMap( map );
    int normal_drop_quantity = getRandomItemQuantity( normal_drop );
    item_t* rare_drop = getRandomItemFromMap( map );
    int rare_drop_quantity = getRandomItemQuantity( rare_drop );
    item_t* secondary_normal_drop = getRandomItemFromMap( map );
    int secondary_normal_drop_quantity = getRandomItemQuantity( secondary_normal_drop );
    item_t* secondary_rare_drop = getRandomItemFromMap( map );
    int secondary_rare_drop_quantity = getRandomItemQuantity( secondary_rare_drop );
    item_t* normal_overkill_drop = getRandomItemFromMap( map );
    int normal_overkill_drop_quantity = getRandomItemQuantity( normal_overkill_drop );
    item_t* rare_overkill_drop = getRandomItemFromMap( map );
    int rare_overkill_drop_quantity = getRandomItemQuantity( rare_overkill_drop );
    item_t* secondary_overkill_drop = getRandomItemFromMap( map );
    int secondary_overkill_drop_quantity = getRandomItemQuantity( secondary_overkill_drop );
    item_t* secondary_rare_overkill_drop = getRandomItemFromMap( map );
    int secondary_rare_overkill_drop_quantity = getRandomItemQuantity( secondary_rare_overkill_drop );
    loot.primary_normal_drop = normal_drop->id;
    loot.primary_normal_drop_rare = rare_drop->id;
    loot.primary_drop_chance = uniform<int>( -1, 254 );
    loot.secondary_normal_drop = secondary_normal_drop->id;
    loot.secondary_normal_drop_rare = secondary_rare_drop->id;
    loot.secondary_drop_chance = uniform<int>( -1, 254 );
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

  void randomizeEnemySteal( enemy_data_t* enemy, std::unordered_map<int, item_t*> map )
  {
    enemy_loot_data_t& loot = *enemy->loot_data;
    item_t* steal_item = getRandomItemFromMap( map );
    int steal_item_quantity = getRandomItemQuantity( steal_item );
    item_t* rare_steal_item = getRandomItemFromMap( map );
    int rare_steal_item_quantity = getRandomItemQuantity( rare_steal_item );
    loot.steal_chance = uniform<int>( -1, 254 );
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

  void randomizeEnemyBribe( enemy_data_t* enemy, std::unordered_map<int, item_t*> map )
  {
    enemy_loot_data_t& loot = *enemy->loot_data;
    item_t* bribe_item = getRandomItemFromMap( map );
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
    stats.hp = normal<uint32_t>( stats.hp, stats.hp, 1, UINT32_MAX );
    stats.mp = normal<uint32_t>( stats.mp, stats.mp, 1, UINT32_MAX );
    stats.overkill_threshold = normal<uint32_t>( stats.overkill_threshold, stats.overkill_threshold, 1, UINT32_MAX );
    stats.str = normal<uint8_t>( stats.str, stats.str, 0, UINT8_MAX );
    stats.def = normal<uint8_t>( stats.def, stats.def, 0, UINT8_MAX );
    stats.mag = normal<uint8_t>( stats.mag, stats.mag, 0, UINT8_MAX );
    stats.mdef = normal<uint8_t>( stats.mdef, stats.mdef, 0, UINT8_MAX );
    stats.agi = normal<uint8_t>( stats.agi, stats.agi, 0, UINT8_MAX );
    stats.acc = normal<uint8_t>( stats.acc, stats.acc, 0, UINT8_MAX );
    stats.flags.armored = rand() % 4 == 0;
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
    stats.mp = normal<uint32_t>( stats.mp, stats.mp, 1, UINT32_MAX );
    stats.overkill_threshold = normal<uint32_t>( stats.overkill_threshold, stats.overkill_threshold, 1, UINT32_MAX );
    stats.str = normal<uint8_t>( stats.str, stats.str, 0, UINT8_MAX );

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
    if( eva != 0 )
      evasion_factor = ( 1.0 - ( eva / 255.0 ) / 3 );

    double defensive_factor = ( def_factor + mdef_factor + evasion_factor );
    if (defensive_factor < 0.33)
      stats.flags.armored = 0;
    else
      stats.flags.armored = rand() % 4 == 0;

    uint32_t base_hp = std::min( 1, static_cast< int >( std::ceil( stats.hp * defensive_factor ) ) );
    uint32_t hp = normal<uint32_t>( base_hp, base_hp, 1, UINT32_MAX );
    stats.mag = normal<uint8_t>( stats.mag, stats.mag, 0, UINT8_MAX );
    stats.agi = normal<uint8_t>( stats.agi, stats.agi, 0, UINT8_MAX );
    stats.acc = normal<uint8_t>( stats.acc, stats.acc, 0, UINT8_MAX );
    stats.writeToBytes();
    enemy->stats_data = &stats;
    enemy->writeStatsData( stats );
  }

  void shuffleStats( enemy_data_t* enemy )
  {
    enemy_stat_data_t& stats = *enemy->stats_data;
    // Pick a random index to pull the stats from
    std::uniform_int_distribution<size_t> dist( 0, enemy_data.size() - 1 );
    int index = dist( rng );
    stats.hp = normal<uint32_t>( stats.hp, stats.hp, 1, UINT32_MAX );
    stats.mp = normal<uint32_t>( stats.mp, stats.mp, 1, UINT32_MAX );
    stats.overkill_threshold = normal<uint32_t>( stats.overkill_threshold, stats.overkill_threshold, 1, UINT32_MAX );
    stats.str = normal<uint8_t>( stats.str, stats.str, 0, UINT8_MAX );
    stats.def = def_pool[ index ];
    stats.mdef = mdef_pool[ index ];
    stats.eva = eva_pool[ index ];
    stats.flags.armored = rand() % 4 == 0;
    stats.agi = normal<uint8_t>( stats.agi, stats.agi, 0, UINT8_MAX );
    stats.luck = normal<uint8_t>( stats.luck, stats.luck, 0, UINT8_MAX );
    stats.acc = normal<uint8_t>( stats.acc, stats.acc, 0, UINT8_MAX );
  }

  void poplateGearLists()
  {
    for (auto& gear : buki_data)
    {
      gear_data_t* armor = gear.second;
      if (armor->is_armor)
        all_armor.push_back( armor );
      else
        all_weapons.push_back( armor );
    }
    for (auto& gear : weapon_data)
    {
      gear_data_t* armor = gear.second;
      if (armor->is_armor)
        all_armor.push_back( armor );
      else
        all_weapons.push_back( armor );
    }
    for (auto& gear : arms_shop_data)
    {
      gear_data_t* armor = gear.second;
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
      shop_data_t* item_shop = shop.second;
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
        while (found = std::find( item_shop->item_indexes.begin(), item_shop->item_indexes.end(), potential_item->id ) != item_shop->item_indexes.end());

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
      shop_data_t* gear_shop = shop.second;
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

    bool ability_in_slot_1 = uniform<int>( 0, 1 );
    bool ability_in_slot_2 = uniform<int>( 0, 1 );
    bool ability_in_slot_3 = uniform<int>( 0, 1 );
    bool ability_in_slot_4 = uniform<int>( 0, 1 );

    int n_abilities = ability_in_slot_1 + ability_in_slot_2 + ability_in_slot_3 + ability_in_slot_4;

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
      gear_data_t* gear_data = gear.second;
      writeGearData( gear_data );
    }
  }

  void randomizeBukiAbilities()
  {
    for (auto& gear : buki_data)
    {
      gear_data_t* gear_data = gear.second;
      writeGearData( gear_data );
    }
  }

  void randomizeWeaponsAbilities()
  {
    for (auto& gear : weapon_data)
    {
      gear_data_t* gear_data = gear.second;
      writeGearData( gear_data );
    }
  }

  void randomizeFieldItems()
  {
    for (auto& field : field_data)
    {
      field_data_t* field_data = field.second;
      // Dont randomize key items for now
      if (field_data->flag == 2)
      {
        item_t* item = getRandomItemFromMap( all_non_key_items );
        field_data->type = item->id;
        field_data->quantity = getRandomItemQuantity( item );
        field_data->writeToBytes();
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

  void doEnemyRandomization()
  {
    if (!randomize_enemy_drops && !randomize_enemy_steals && !randomize_enemy_bribes && !randomize_enemy_gear_drops && 
         !randomize_enemy_stats_normal && !randomize_enemy_stats_defensive_normalized && !randomize_enemy_stats_shuffle )
      return;

    if (randomize_enemy_drops)
    {
      printf( "Randomizing Enemy Drops\n" );
      for (auto& enemy : enemy_data)
      {
        enemy_data_t* enemy_data = enemy.second;
        std::unordered_map<int, item_t*> map = randomize_key_items ? all_items : all_non_key_items;
        randomizeEnemyDrops( enemy.second, map );
      }
    }

    if (randomize_enemy_steals)
    {
      printf( "Randomizing Enemy Steals\n" );
      for (auto& enemy : enemy_data)
      {
        enemy_data_t* enemy_data = enemy.second;
        std::unordered_map<int, item_t*> map = randomize_key_items ? all_items : all_non_key_items;
        randomizeEnemySteal( enemy.second, map );
      }
    }

    if (randomize_enemy_bribes)
    {
      printf( "Randomizing Enemy Bribes\n" );
      for (auto& enemy : enemy_data)
      {
        enemy_data_t* enemy_data = enemy.second;
        std::unordered_map<int, item_t*> map = randomize_key_items ? all_items : all_non_key_items;
        randomizeEnemyBribe( enemy.second, map );
      }
    }

    if (randomize_enemy_gear_drops)
    {
      printf( "Randomizing Enemy Gear Drops\n" );
      for (auto& enemy : enemy_data)
      {
        enemy_data_t* enemy_data = enemy.second;
        randomizeEnemyGearDrops( enemy.second );
      }
    }

    if (randomize_enemy_stats_normal)
    {
      printf( "Randomizing Enemy Stats\n" );
      for (auto& enemy : enemy_data)
      {
        enemy_data_t* enemy_data = enemy.second;
        randomizeEnemyStatsNormal( enemy.second );
      }
    }

    if (randomize_enemy_stats_defensive_normalized)
    {
      printf( "Randomizing Enemy Defensive Stats\n" );
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
      printf( "Shuffling Enemy Stats\n" );
      for (auto& enemy : enemy_data)
      {
        enemy_data_t* enemy_data = enemy.second;
        addEnemyDefenses( enemy.second );
      }
      for (auto& enemy : enemy_data)
      {
        enemy_data_t* enemy_data = enemy.second;
        shuffleStats( enemy.second );
      }
    }

    printf( "Reconstructing Enemy Files" );
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

    printf( "Randomizing Item Shops\n" );
    std::thread item_thread( &randomizer_t::randomizeItemShops, this );
    printf( "Randomizing Gear Shops\n" );
    std::thread gear_thread( &randomizer_t::randomizeGearShops, this );

    item_thread.join();
    gear_thread.join();

    printf( "Reconstructing item_shop.bin\n" );
    std::thread item_shop_thread( &randomizer_t::reconstructItemShopData, this );
    printf( "Reconstructing arms_shop.bin\n" );
    std::thread arms_shop_thread( &randomizer_t::reconstructArmsShopData, this );

    item_shop_thread.join();
    arms_shop_thread.join();
  }

  void doPriceRandomization()
  {
    if (!randomize_shop_prices)
      return;

    printf( "Randomizing Item Prices\n" );
    randomizeItemPrices();
    printf( "Reconstructing item_rate.bin\n" );
    reconstructItemRateData();
  }

  void doFieldRandomization()
  {
    if (!randomize_field_items)
      return;

    printf( "Randomizing Field Items\n" );
    randomizeFieldItems();
    printf( "Reconstructing takara.bin\n" );
    reconstructTakaraData();
  }

  void doAbilityRandomization()
  {
    if (!randomize_gear_abilities)
      return;

    printf( "Randomizing shop_arms.bin Abilities\n" );
    std::thread shop_arms_thread( &randomizer_t::randomizeShopArmsAbilities, this );
    printf( "Randomizing buki_get.bin Abilities\n" );
    std::thread buki_thread( &randomizer_t::randomizeBukiAbilities, this );
    printf( "Randomizing weapon.bin Abilities\n" );
    std::thread weapon_thread( &randomizer_t::randomizeWeaponsAbilities, this );

    shop_arms_thread.join();
    buki_thread.join();
    weapon_thread.join();

    printf( "Reconstructing shop_arms.bin\n" );
    std::thread shop_arms_data_thread( &randomizer_t::reconstructShopArmsData, this );
    printf( "Reconstructing buki_get.bin\n" );
    std::thread buki_data_thread( &randomizer_t::reconstructBukiData, this );
    printf( "Reconstructing weapon.bin\n" );
    std::thread weapon_data_thread( &randomizer_t::reconstructWeaponData, this );

    shop_arms_data_thread.join();
    buki_data_thread.join();
    weapon_data_thread.join();
  }

  void randomize()
  {
    printf( "Starting Randomizer\n" );

    // Clean the output folder to prevent any issues
    std::filesystem::remove_all( OUTPUT_FOLDER );

    std::thread enemy_thread( &randomizer_t::doEnemyRandomization, this );
    std::thread shop_thread( &randomizer_t::doShopRandomization, this );
    std::thread price_thread( &randomizer_t::doPriceRandomization, this );
    std::thread field_thread( &randomizer_t::doFieldRandomization, this );
    std::thread ability_thread( &randomizer_t::doAbilityRandomization, this );

    enemy_thread.join();
    shop_thread.join();
    price_thread.join();
    field_thread.join();
    ability_thread.join();
  }
};