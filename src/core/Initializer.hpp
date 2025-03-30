#pragma once
#include <string>
#include <unordered_map>
#include <random>
#include <thread>
#include "BytesHelper.hpp"
#include "Data.hpp"
#include "GUI.hpp"

struct initializer_t
{
  gui_t* gui;

  initializer_t() : gui( nullptr )
  {
    initializeGUI();
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
  void initializeItemRateData() const;
  void initializeGUI();
  void initializeAllData() const;

  void runEnemyTests();
  void runFieldTests();
  void runShopTests();
  void runBukiTests();
  void runWeaponTests();
  void runShopArmsTests();
  void runEnemyLootTests();
  void runItemRateTests();

  void runTests();
};