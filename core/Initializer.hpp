#pragma once
#include <string>
#include <unordered_map>
#include <chrono>
#include <random>
#include <thread>
#include "BytesHelper.hpp"
#include "Data.hpp"
#include "Randomizer.hpp"

struct initializer_t
{
  randomizer_t* randomizer;

  initializer_t() : randomizer( nullptr )
  {
    initializeAllData();
    getFieldItems();
    getMonsterItems();
    getShopItems();
    initializeRandomizer();
    // TODO - Implement actual debugging tests rather than just commenting this line out :| 
    // runTests( *this );
  }

  std::vector<chunk_t> chunkData( std::vector<char>& bytes, int size ) const;
  void initializeEnemyData() const;
  void initializeFieldData() const;
  void initializeShopData( bool gear ) const;
  void initializeBukiData() const;
  void initializeWeaponData() const;
  void initializeShopArmsData() const;
  void initializeRandomizer();
  void initializeAllData() const;

  void checkItemList( uint16_t& id, int& quantity, bool key ) const;
  void getFieldItems() const;
  void getMonsterItems() const;
  void getShopItems() const;

  void runEnemyTests();
  void runFieldTests();
  void runShopTests();
  void runBukiTests();
  void runWeaponTests();
  void runShopArmsTests();
  void runEnemyLootTests();
  void runItemListTests();

  void runTests( initializer_t& init );
};