#pragma once
#include <string>
#include <unordered_map>
#include <random>
#include <thread>
#include <vector>
#include "BytesHelper.hpp"
#include "Data.hpp"
#include "GUI.hpp"

struct initializer_t
{
  gui_t* gui;
  data_pack_t* data_pack;

  // Dynamic data
  std::vector<enemy_data_t*> enemy_data;
  std::vector<field_data_t*> field_data;
  std::vector<shop_data_t*> item_shop_data;
  std::vector<shop_data_t*> gear_shop_data;
  std::vector<gear_data_t*> buki_data;
  std::vector<gear_data_t*> weapon_data;
  std::vector<gear_data_t*> shop_arms_data;
  std::vector<item_rate_t*> item_rate_data;
  std::vector<character_stats_t*> player_stats_data;
  std::vector<aeon_scaling_data_t*> aeon_scaling_data;
  std::vector<aeon_stat_data_t*> aeon_stat_data;
  std::vector<sphere_grid_data_t*> sphere_grid_data;

  initializer_t() : gui( nullptr ), data_pack( nullptr ),
    enemy_data(), field_data(), item_shop_data(), gear_shop_data(),
    buki_data(), weapon_data(), shop_arms_data(), item_rate_data(),
    player_stats_data(), aeon_scaling_data(), aeon_stat_data(), 
    sphere_grid_data()
  {
    initializeGUI();
  }

  std::vector<chunk_t> chunkData( std::vector<char>& bytes, int size, bool is_shop_data = false ) const;
  std::vector<char> getDataFromFile( const std::string& filepath, bool skip_header = false ) const;

  template <typename T>
  inline void genericExcelReader( const std::string& filepath, std::vector<T*>& vector, int chunk_size, bool gear = false, bool is_aeon_scaling_data = false ) const
  {
    std::vector<char> bytes = initializer_t::getDataFromFile( filepath, true );
    std::vector<chunk_t> chunks = initializer_t::chunkData( bytes, chunk_size, gear );
    for (auto& chunk : chunks)
    {
      if (is_aeon_scaling_data)
      {
        char ap_req_coef1 = bytes_mapper_t::read1Byte( chunk.data, 0x11 );
        char ap_req_coef2 = bytes_mapper_t::read1Byte( chunk.data, 0x12 );
        char ap_req_coef3 = bytes_mapper_t::read1Byte( chunk.data, 0x13 );
        char hp_coef1 = bytes_mapper_t::read1Byte( chunk.data, 0x18 );
        if (ap_req_coef1 == 0 && ap_req_coef2 == 0 && ap_req_coef3 == 0 && hp_coef1 > 0)
        {
          T* data = new T( chunk );
          vector.push_back( data );
        }
      }
      else
      {
        T* data = new T( chunk );
        vector.push_back( data );
      }
    }
  }

  void initializeEnemyData();
  void initializeFieldData();
  void initializeShopData( bool gear );
  void initializeBukiData();
  void initializeWeaponData();
  void initializeShopArmsData();
  void initializeItemRateData();
  void initializePlayerStatData();
  void initializeAeonScalingData();
  void initializeAeonStatData();
  void initializeSphereGridData();
  void initializeGUI();
  void initializeAllData();

  void runEnemyTests();
  void runFieldTests();
  void runShopTests();
  void runBukiTests();
  void runWeaponTests();
  void runShopArmsTests();
  void runEnemyLootTests();
  void runItemRateTests();
  void runSphereGridTests();

  void runTests();
};