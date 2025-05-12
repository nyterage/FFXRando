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

  // Static Data
  btl_data_t* btl_data;

  // Dynamic data
  std::unordered_map<int, enemy_data_t> enemy_data;
  std::unordered_map<int, enemy_data_t> unmodified_enemy_data;
  std::vector<field_data_t*> field_data;
  std::vector<item_shop_t*> item_shop_data;
  std::vector<gear_shop_t*> gear_shop_data;
  std::vector<gear_data_t*> buki_data;
  std::vector<gear_data_t*> weapon_data;
  std::vector<gear_data_t*> shop_arms_data;
  std::vector<item_rate_t*> item_rate_data;
  std::vector<arms_rate_t*> arms_rate_data;
  std::vector<character_stats_t*> player_stats_data;
  std::vector<aeon_scaling_data_t*> aeon_scaling_data;
  std::vector<aeon_stat_data_t*> aeon_stat_data;
  std::vector<sphere_grid_data_t*> sphere_grid_data;
  std::vector<encounter_file_t*> encounter_file_data;

  initializer_t() : gui( nullptr ), data_pack( nullptr ), btl_data( nullptr ),
    enemy_data(), unmodified_enemy_data(),
    field_data(), item_shop_data(), gear_shop_data(),
    buki_data(), weapon_data(), shop_arms_data(), item_rate_data(),
    arms_rate_data(), player_stats_data(), aeon_scaling_data(),
    aeon_stat_data(), sphere_grid_data(), encounter_file_data()
  {
    if (!std::filesystem::exists( INPUT_FOLDER + JPPC_FOLDER ))
    {
      const WCHAR* message = L"Input files do not exist.\n Please be sure your extracted ffx_ps2 folder is in the input folder";
      MessageBox( nullptr, message, L"Error", MB_OK | MB_ICONERROR );
      return;
    }
    std::thread data_thread( &initializer_t::initializeAllData, this );
    std::thread gui_thread( &initializer_t::initializeGUI, this );
    // TODO - Implement actual debugging tests rather than just commenting this line out :| 
    // runTests();
    data_thread.join();
    gui_thread.join();
  }

  std::vector<chunk_t> chunkData( std::vector<char>& bytes, int size ) const;
  std::vector<char> getDataFromFile( const std::string& filepath, bool skip_header = false ) const;

  template <typename T>
  inline void genericExcelReader( const std::string& filepath, std::vector<T*>& vector, size_t chunk_size, bool limit_chunks = false, int chunk_limit = 0 ) const
  {
    std::vector<char> bytes = initializer_t::getDataFromFile( filepath, true );
    std::vector<chunk_t> chunks = initializer_t::chunkData( bytes, chunk_size );
    for (auto& chunk : chunks)
    {
      if (limit_chunks && chunk.index >= chunk_limit)
        break;
      if (chunk.data.size() < chunk_size)
        continue;

      T* data = new T( chunk );
      vector.push_back( data );
    }
  }

  void initializeEnemyData( const std::string filename, std::string monster_id, const std::string monster_file );
  void initializeFieldData();
  void initializeShopData( bool gear );
  void initializeBukiData();
  void initializeWeaponData();
  void initializeShopArmsData();
  void initializeItemRateData();
  void initializeArmsRateData();
  void initializePlayerStatData();
  void initializeAeonScalingData();
  void initializeAeonStatData();
  void initializeSphereGridData();
  void initializeBtlData();
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