#include "Initializer.hpp"
#include <atomic>
#include <algorithm>

std::vector<chunk_t> initializer_t::chunkData( std::vector<char>& bytes, size_t size ) const
{
  std::vector<chunk_t> chunks;
  if (size == 0)
    return chunks;
  chunks.reserve( bytes.size() / size + 1 );
  int index = 0;
  for (size_t i = 0; i < bytes.size(); i += size)
  {
    chunks.emplace_back( bytes, i, i + size, index );
    index++;
  }
  return chunks;
}

std::vector<char> initializer_t::getDataFromFile( const std::string& filepath, bool skip_header ) const
{
  std::vector<char> bytes = bytes_mapper_t::fileToBytes( filepath );

  if (skip_header)
    bytes = std::vector<char>( bytes.begin() + 20, bytes.end() );

  return bytes;
}

void initializer_t::initializeEnemyData( std::string monster_id, const std::string monster_file )
{
  std::vector<char> bytes = bytes_mapper_t::fileToBytes( INPUT_FOLDER + MONSTER_FOLDER + monster_file );
  // Erase the leading m
  monster_id.erase( 0, 1 );
  enemy_data_t* enemy = new enemy_data_t( monster_id, bytes );
  enemy_data_t* unmodified = new enemy_data_t( monster_id, bytes );
  {
    std::lock_guard<std::mutex> lock(enemy_data_mutex);
    enemy_data.emplace( std::stoi( monster_id ), enemy );
    unmodified_enemy_data.emplace( std::stoi( monster_id ), unmodified );
  }
}

void initializer_t::initializeFieldData()
{
  field_data.reserve( 498 );
  std::string path = INPUT_FOLDER + BATTLE_KERNEL_FOLDER + "takara.bin";
  genericExcelReader<field_data_t>( path, field_data, 4 );
}

void initializer_t::initializeShopData( bool gear )
{
  gear_shop_data.reserve( 47 );
  item_shop_data.reserve( 47 );
  std::string file = gear ? "arms_shop.bin" : "item_shop.bin";
  std::string path = INPUT_FOLDER + BATTLE_KERNEL_FOLDER + file;
  if (gear)
    genericExcelReader<gear_shop_t>( path, gear_shop_data, 34 );
  else
    genericExcelReader<item_shop_t>( path, item_shop_data, 34 );
}

void initializer_t::initializeBukiData()
{
  buki_data.reserve( 86 );
  std::string path = INPUT_FOLDER + BATTLE_KERNEL_FOLDER + "buki_get.bin";
  genericExcelReader<gear_data_t>( path, buki_data, 16 );
}

void initializer_t::initializeWeaponData()
{
  weapon_data.reserve( 153 );
  std::string path = INPUT_FOLDER + BATTLE_KERNEL_FOLDER + "weapon.bin";
  genericExcelReader<gear_data_t>( path, weapon_data, 22 );
}

void initializer_t::initializeShopArmsData()
{
  shop_arms_data.reserve( 428 );
  std::string path = INPUT_FOLDER + BATTLE_KERNEL_FOLDER + "shop_arms.bin";
  genericExcelReader<gear_data_t>( path, shop_arms_data, 22 );
}

void initializer_t::initializeItemRateData()
{
  item_rate_data.reserve( 253 );
  std::string path = INPUT_FOLDER + BATTLE_KERNEL_FOLDER + "item_rate.bin";
  genericExcelReader<item_rate_t>( path, item_rate_data, 4 );
}

void initializer_t::initializeArmsRateData()
{
  arms_rate_data.reserve( 134 );
  std::string path = INPUT_FOLDER + BATTLE_KERNEL_FOLDER + "arms_rate.bin";
  genericExcelReader<arms_rate_t>( path, arms_rate_data, 4 );
}

void initializer_t::initializePlayerStatData()
{
  player_stats_data.reserve( 20 );
  std::string path = INPUT_FOLDER + USPC_BTL_KERN_FOLDER + "ply_save.bin";
  genericExcelReader<character_stats_t>( path, player_stats_data, 148 );
}

void initializer_t::initializeAeonScalingData()
{
  aeon_scaling_data.reserve( 8 );
  std::string path = INPUT_FOLDER + USPC_BTL_KERN_FOLDER + "ply_rom.bin";
  genericExcelReader<aeon_scaling_data_t>( path, aeon_scaling_data, 44, true, 8 );
}

void initializer_t::initializeAeonStatData()
{
  aeon_stat_data.reserve( 20 );
  std::string path = INPUT_FOLDER + BATTLE_KERNEL_FOLDER + "sum_assure.bin";
  genericExcelReader<aeon_stat_data_t>( path, aeon_stat_data, 120 );
}

void initializer_t::initializeSphereGridData()
{
  sphere_grid_data.reserve( 3 );
  for (int i = 0; i < 3; i++)
  {
    std::string name = "dat0" + std::to_string( i + 1 ) + ".dat";
    std::string path = INPUT_FOLDER + ABMAP_FOLDER + name;
    std::vector<char> bytes = bytes_mapper_t::fileToBytes( path );
    sphere_grid_data_t* data = new sphere_grid_data_t( bytes, static_cast< sphere_grid_type_e >( i ) );
    sphere_grid_data.push_back( data );
  }
}

void initializer_t::initializeBtlData()
{
  encounter_file_data.reserve( 414 );
  std::string path = INPUT_FOLDER + BATTLE_KERNEL_FOLDER + "btl.bin";
  btl_data_t btl_data = btl_data_t( getDataFromFile( path ) );

  btl_data.getEncounterFiles( encounter_file_data );
}

void initializer_t::initializeGearCustomizeData()
{
  gear_customize_data.reserve( 20 );
  std::string path = INPUT_FOLDER + BATTLE_KERNEL_FOLDER + "kaizou.bin";
  genericExcelReader<customize_data_t>( path, gear_customize_data, 8 );
}

void initializer_t::initializeAeonStatCustomizeData()
{
  aeon_stat_customize_data.reserve( 20 );
  std::string path = INPUT_FOLDER + BATTLE_KERNEL_FOLDER + "sum_grow.bin";
  genericExcelReader<customize_data_t>( path, aeon_stat_customize_data, 8 );
}

void initializer_t::initializeGUI()
{
  gui = new gui_t( *data_pack );
  wxApp::SetInstance( gui );
  wxEntryStart( 0, nullptr );
  wxTheApp->CallOnInit();
  wxTheApp->OnRun();
  wxTheApp->OnExit();
  wxEntryCleanup();
}

void initializer_t::initializeAllData()
{
  enemy_data.reserve( ENEMY_COUNT );
  unmodified_enemy_data.reserve( ENEMY_COUNT );

  // Build list of enemy tasks
  std::vector<std::pair<std::string, std::string>> enemy_tasks;
  enemy_tasks.reserve( ENEMY_COUNT );

  std::string monster_id;
  monster_id.reserve( 5 );
  std::string filename;
  filename.reserve( 5 );
  std::string monster_file;
  monster_file.reserve( 15 );
  for (const auto& file : std::filesystem::directory_iterator( INPUT_FOLDER + MONSTER_FOLDER ))
  {
    filename = file.path().filename().string();
    monster_id = filename;
    // Erase the leading underscore
    monster_id.erase( 0, 1 );
    monster_file = filename + "/" + monster_id + ".bin";
    enemy_tasks.emplace_back( monster_id, monster_file );
  }

  // Thread pool for enemy loading
  std::vector<std::thread> enemy_workers;
  std::atomic<size_t> next_task{0};
  unsigned int worker_count = std::thread::hardware_concurrency();
  if (worker_count == 0) 
    worker_count = 4; // sensible default
  worker_count = std::min<unsigned int>( worker_count, static_cast<unsigned int>( enemy_tasks.size() == 0 ? 1 : enemy_tasks.size() ) );

  enemy_workers.reserve( worker_count );
  for (unsigned int i = 0; i < worker_count; ++i)
  {
    enemy_workers.emplace_back([this, &enemy_tasks, &next_task]() {
      for (;;)
      {
        size_t idx = next_task.fetch_add(1, std::memory_order_relaxed);
        if (idx >= enemy_tasks.size()) break;
        auto& task = enemy_tasks[idx];
        this->initializeEnemyData( task.first, task.second );
      }
    });
  }

  std::thread btl_data_thread( &initializer_t::initializeBtlData, this );
  std::thread field_thread( &initializer_t::initializeFieldData, this );
  std::thread shop_item_thread( &initializer_t::initializeShopData, this, false );
  std::thread shop_gear_thread( &initializer_t::initializeShopData, this, true );
  std::thread buki_thread( &initializer_t::initializeBukiData, this );
  std::thread weapon_thread( &initializer_t::initializeWeaponData, this );
  std::thread shop_arms_thread( &initializer_t::initializeShopArmsData, this );
  std::thread item_rate_thread( &initializer_t::initializeItemRateData, this );
  std::thread arms_rate_thread( &initializer_t::initializeArmsRateData, this );
  std::thread player_stats_thread( &initializer_t::initializePlayerStatData, this );
  std::thread aeon_scaling_thread( &initializer_t::initializeAeonScalingData, this );
  std::thread aeon_stat_thread( &initializer_t::initializeAeonStatData, this );
  std::thread sphere_grid_thread( &initializer_t::initializeSphereGridData, this );
  std::thread gear_customize_thread( &initializer_t::initializeGearCustomizeData, this );
  std::thread aeon_stat_customize_thread( &initializer_t::initializeAeonStatCustomizeData, this );

  field_thread.join();
  shop_item_thread.join();
  shop_gear_thread.join();
  buki_thread.join();
  weapon_thread.join();
  shop_arms_thread.join();
  item_rate_thread.join();
  arms_rate_thread.join();
  player_stats_thread.join();
  aeon_scaling_thread.join();
  aeon_stat_thread.join();
  sphere_grid_thread.join();
  gear_customize_thread.join();
  aeon_stat_customize_thread.join();
  btl_data_thread.join();

  for (auto& t : enemy_workers)
    if (t.joinable())
      t.join();
}

void initializer_t::runEnemyTests()
{
  for (auto& enemy : enemy_data)
    enemy.second->test();
}

void initializer_t::runFieldTests()
{
  for (auto& item : field_data)
    item->test();
}

void initializer_t::runShopTests()
{
  for (auto& shop : gear_shop_data)
    shop->test();
  for (auto& shop : item_shop_data)
    shop->test();
}

void initializer_t::runBukiTests()
{
  for (auto& buki : buki_data)
    buki->test();
}

void initializer_t::runWeaponTests()
{
  for (auto& weapon : weapon_data)
    weapon->test();
}

void initializer_t::runShopArmsTests()
{
  for (auto& shop : shop_arms_data)
    shop->test();
}

void initializer_t::runEnemyLootTests()
{
  for (auto& loot : enemy_data)
    loot.second->loot_data->test();
}

void initializer_t::runItemRateTests()
{
  for (auto& item_rate : item_rate_data)
    item_rate->test();
}

void initializer_t::runSphereGridTests()
{
  for (auto& grid : sphere_grid_data)
    grid->test();
}

void initializer_t::runTests()
{
  std::thread enemy_thread( &initializer_t::runEnemyTests, this );
  std::thread field_thread( &initializer_t::runFieldTests, this );
  std::thread shop_thread( &initializer_t::runShopTests, this );
  std::thread buki_thread( &initializer_t::runBukiTests, this );
  std::thread weapon_thread( &initializer_t::runWeaponTests, this );
  std::thread shop_arms_thread( &initializer_t::runShopArmsTests, this );
  std::thread enemy_loot_thread( &initializer_t::runEnemyLootTests, this );
  std::thread item_rate_thread( &initializer_t::runItemRateTests, this );
  std::thread sphere_grid_thread( &initializer_t::runSphereGridTests, this );

  enemy_thread.join();
  field_thread.join();
  shop_thread.join();
  buki_thread.join();
  weapon_thread.join();
  shop_arms_thread.join();
  enemy_loot_thread.join();
  item_rate_thread.join();
  sphere_grid_thread.join();
}

// Destructor implementation: free owned pointers
initializer_t::~initializer_t()
{
  // Do not delete gui: wxEntryCleanup handles wxApp lifetime in initializeGUI.

  auto clearMap = [](auto& m) {
    for (auto& kv : m) delete kv.second;
    m.clear();
  };
  auto clearVec = [](auto& v) {
    for (auto* p : v) delete p;
    v.clear();
  };

  clearMap(enemy_data);
  clearMap(unmodified_enemy_data);

  clearVec(field_data);
  clearVec(item_shop_data);
  clearVec(gear_shop_data);
  clearVec(buki_data);
  clearVec(weapon_data);
  clearVec(shop_arms_data);
  clearVec(item_rate_data);
  clearVec(arms_rate_data);
  clearVec(player_stats_data);
  clearVec(aeon_scaling_data);
  clearVec(aeon_stat_data);
  clearVec(sphere_grid_data);
  clearVec(encounter_file_data);
  clearVec(gear_customize_data);
  clearVec(aeon_stat_customize_data);

  delete data_pack;
  data_pack = nullptr;
}
