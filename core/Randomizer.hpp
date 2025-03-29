#pragma once
#include <fstream>
#include <filesystem>
#include <iostream>
#include <unordered_map>
#include <chrono>
#include <random>
#include <type_traits>
#include <limits>
#include <sstream>
#include <string>
#include <vector>
#include <cstdint>
#include "Data.hpp"
#include "BytesHelper.hpp"

struct randomizer_t
{
private:
  std::mt19937 rng;

public:
  std::unordered_map<int, enemy_data_t*> enemy_data;
  std::unordered_map<int, field_data_t*> field_data;
  std::unordered_map<int, shop_data_t*> item_shop_data;
  std::unordered_map<int, shop_data_t*> gear_shop_data;
  std::unordered_map<int, gear_data_t*> buki_data;
  std::unordered_map<int, gear_data_t*> weapon_data;
  std::unordered_map<int, gear_data_t*> arms_shop_data;
  std::unordered_map<int, item_t*> all_items;
  std::unordered_map<int, item_t*> all_non_key_items;
  std::vector<gear_data_t*> all_armor;
  std::vector<gear_data_t*> all_weapons;
  std::vector<uint16_t> armor_abilities;
  std::vector<uint16_t> weapon_abilities;

  randomizer_t( int seed,
                std::unordered_map<int, enemy_data_t*> enemy_data,
                std::unordered_map<int, field_data_t*> field_data,
                std::unordered_map<int, shop_data_t*> item_shop_data,
                std::unordered_map<int, shop_data_t*> gear_shop_data,
                std::unordered_map<int, gear_data_t*> buki_data,
                std::unordered_map<int, gear_data_t*> weapon_data,
                std::unordered_map<int, gear_data_t*> arms_shop_data,
                std::unordered_map<int, item_t*> all_items,
                std::unordered_map<int, item_t*> all_non_key_items )
    : rng( seed ), enemy_data( enemy_data ), field_data( field_data ), item_shop_data( item_shop_data ),
    gear_shop_data( gear_shop_data ), buki_data( buki_data ), weapon_data( weapon_data ),
    arms_shop_data( arms_shop_data ), all_items( all_items ), all_non_key_items( all_non_key_items )
  {
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
    if (item->getAverageQuantity() > 2 && item->getMaxQuantity() > item->getMinQuantity() + 1)
      return normal<int>( item->getAverageQuantity(), item->getStandardDeviation(), item->getMinQuantity(), item->getMaxQuantity() );
    else if (item->getMaxQuantity() > item->getMinQuantity())
      return uniform<int>( item->getMinQuantity(), item->getMaxQuantity() );
    else
      return item->getMinQuantity();
  }

  void randomizeEnemyDrops( enemy_data_t* enemy, std::unordered_map<int, item_t*> map )
  {
    enemy_loot_data_t& loot = *enemy->loot_data;
    if (loot.gil > 0)
      loot.gil = normal<uint16_t>( loot.gil, loot.gil, 0, UINT16_MAX );
    if (loot.ap > 0)
      loot.ap = normal<uint16_t>( loot.ap, loot.ap, 0, UINT16_MAX );
    if (loot.ap_overkill > 0)
      loot.ap_overkill = normal<uint16_t>( loot.ap_overkill, loot.ap_overkill, 0, UINT16_MAX );
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

  uint16_t getRandomAbility( bool is_armor )
  {
    std::vector<uint16_t>& abilities = is_armor ? armor_abilities : weapon_abilities;
    std::uniform_int_distribution<size_t> dist( 0, abilities.size() - 1 );
    return abilities[ dist( rng ) ];
  }

  void populateAbilityData()
  {
    for (auto& gear : all_armor)
    {
      gear_data_t* armor = gear;
      armor->mapAbilities( armor_abilities );
    }
    for (auto& gear : all_weapons)
    {
      gear_data_t* weapon = gear;
      weapon->mapAbilities( weapon_abilities );
    }
    for (auto& enemy : enemy_data)
    {
      enemy_data_t* enemy_data = enemy.second;
      enemy_loot_data_t& loot = *enemy_data->loot_data;
      for (int chr = 0; chr < 7; chr++)
      {
        for (int i = 0; i < 8; i++)
        {
          bool found = std::find( weapon_abilities.begin(), weapon_abilities.end(), loot.weapon_abilities_by_char.at( chr ) ) != weapon_abilities.end();
          if (!found && loot.weapon_abilities_by_char.at( chr ) != 255)
            weapon_abilities.push_back( loot.weapon_abilities_by_char.at( chr ) );
        }
      }
      for (int chr = 0; chr < 7; chr++)
      {
        for (int i = 0; i < 8; i++)
        {
          bool found = std::find( armor_abilities.begin(), armor_abilities.end(), loot.gear_abilities_by_char.at( chr ) ) != armor_abilities.end();
          if (!found && loot.gear_abilities_by_char.at( chr ) != 255)
            armor_abilities.push_back( loot.gear_abilities_by_char.at( chr ) );
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
        loot.weapon_abilities_by_char.at( chr ) = getRandomAbility( false );
      }
    }

    for (int chr = 0; chr < 7; chr++)
    {
      for (int i = 0; i < 8; i++)
      {
        loot.gear_abilities_by_char.at( chr ) = getRandomAbility( true );
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
      abilities.push_back( getRandomAbility( gear->is_armor ) );
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

  void randomizerTest()
  {
    poplateGearLists();
    populateAbilityData();
    printf( "Randomizer Test\n" );
    printf( "Randomizing Enemy Drops\n" );
    for (auto& enemy : enemy_data)
    {
      enemy_data_t* enemy_data = enemy.second;
      std::string pathstr = OUTPUT_FOLDER + MONSTER_FOLDER + "_m" + enemy_data->monster_id;
      std::filesystem::path path = pathstr;
      std::filesystem::create_directories( path );
      std::string filepath = pathstr + "/m" + enemy_data->monster_id + ".bin";
      printf( "Randomizing enemy loot for enemy: %d\n", enemy.first );
      bool with_key_items = false;
      std::unordered_map<int, item_t*> map = with_key_items ? all_items : all_non_key_items;
      randomizeEnemyDrops( enemy.second, map );
      randomizeEnemySteal( enemy.second, map );
      randomizeEnemyBribe( enemy.second, map );
      randomizeEnemyGearDrops( enemy.second );
      //enemy_data->test();
      //enemy_data->loot_data->test();
      enemy_data->writeBytesToNewFile( enemy_data->bytes, filepath );
    }
    printf( "Randomizing shop_arms.bin Abilities\n" );
    randomizeShopArmsAbilities();
    printf( "Randomizing buki_get.bin Abilities\n" );
    randomizeBukiAbilities();
    printf( "Randomizing weapon.bin Abilities\n" );
    randomizeWeaponsAbilities();
    printf( "Randomizing Item Shops\n" );
    randomizeItemShops();
    printf( "Randomizing Gear Shops\n" );
    randomizeGearShops();
    printf( "Randomizing Field Items\n" );
    randomizeFieldItems();
    reconstructBukiData();
    reconstructWeaponData();
    reconstructShopArmsData();
    reconstructTakaraData();
    reconstructArmsShopData();
    reconstructItemShopData();
  }

  void randomize()
  {
    // TODO Implement different modes with actual options for players to toggle
    randomizerTest();
  }
};