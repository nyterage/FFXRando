#include "Initializer.hpp"

std::vector<chunk_t> initializer_t::chunkData( std::vector<char>& bytes, int size ) const
{
  std::vector<chunk_t> chunks;
  for (int i = 0; i < bytes.size(); i += size)
  {
    chunk_t chunk = chunk_t( bytes, i, i + size );
    chunks.push_back( chunk );
  }
  return chunks;
}

void initializer_t::initializeEnemyData() const
{
  for (int i = 0; i < ENEMY_COUNT; i++)
  {
    std::string monster_id = std::to_string( i );
    while (monster_id.size() < 3)
      monster_id.insert( 0, "0" );
    monster_id.insert( 0, "m" );
    std::string path = INPUT_FOLDER + MONSTER_FOLDER + "_" + monster_id;
    std::string monster_file = path + "/" + monster_id + ".bin";
    std::vector<char> bytes = bytes_mapper_t::fileToBytes( monster_file );
    monster_id.erase( 0, 1 );
    enemy_data_t* enemy = new enemy_data_t( monster_id, bytes );
    enemy_data.insert( { i , enemy } );
  }
}

void initializer_t::initializeFieldData() const
{
  std::string path = INPUT_FOLDER + BATTLE_KERNEL_FOLDER + "takara.bin";
  std::vector<char> bytes = bytes_mapper_t::fileToBytes( path );
  bytes = std::vector<char>( bytes.begin() + 20, bytes.end() );
  // Split the field data into 4 byte chunks
  std::vector<chunk_t> field_chunks = initializer_t::chunkData( bytes, 4 );
  for (int i = 0; i < field_chunks.size(); i++)
  {
    field_data_t* field = new field_data_t( i, field_chunks[ i ].data );
    field_data.push_back( field );
  }
}

void initializer_t::initializeShopData( bool gear ) const
{
  std::string file = gear ? "arms_shop.bin" : "item_shop.bin";
  std::string path = INPUT_FOLDER + BATTLE_KERNEL_FOLDER + file;
  std::vector<char> bytes = bytes_mapper_t::fileToBytes( path );
  bytes = std::vector<char>( bytes.begin() + 20, bytes.end() );
  // Split the shop data into 34 byte chunks
  std::vector<chunk_t> shop_chunks = initializer_t::chunkData( bytes, 34 );
  for (int i = 0; i < shop_chunks.size(); i++)
  {
    shop_data_t* shop = new shop_data_t( shop_chunks[ i ].data, gear );
    if (gear)
      gear_shop_data.push_back( shop );
    else
      item_shop_data.push_back( shop );
  }
}

void initializer_t::initializeBukiData() const
{
  std::string path = INPUT_FOLDER + BATTLE_KERNEL_FOLDER + "buki_get.bin";
  std::vector<char> bytes = bytes_mapper_t::fileToBytes( path );
  bytes = std::vector<char>( bytes.begin() + 20, bytes.end() );
  // Split the buki data into 16 byte chunks
  std::vector<chunk_t> buki_chunks = initializer_t::chunkData( bytes, 16 );
  for (int i = 0; i < buki_chunks.size(); i++)
  {
    gear_data_t* buki = new gear_data_t( buki_chunks[ i ].data );
    buki_data.push_back( buki );
  }
}

void initializer_t::initializeWeaponData() const
{
  std::string path = INPUT_FOLDER + BATTLE_KERNEL_FOLDER + "weapon.bin";
  std::vector<char> bytes = bytes_mapper_t::fileToBytes( path );
  bytes = std::vector<char>( bytes.begin() + 20, bytes.end() );
  // Split the weapon data into 22 byte chunks
  std::vector<chunk_t> weapon_chunks = initializer_t::chunkData( bytes, 22 );
  for (int i = 0; i < weapon_chunks.size() - 1; i++)
  {
    gear_data_t* weapon = new gear_data_t( weapon_chunks[ i ].data );
    weapon_data.push_back( weapon );
  }
}

void initializer_t::initializeShopArmsData() const
{
  std::string path = INPUT_FOLDER + BATTLE_KERNEL_FOLDER + "shop_arms.bin";
  std::vector<char> bytes = bytes_mapper_t::fileToBytes( path );
  bytes = std::vector<char>( bytes.begin() + 20, bytes.end() );
  // Split the shop arms data into 22 byte chunks
  std::vector<chunk_t> shop_arms_chunks = initializer_t::chunkData( bytes, 22 );
  for (int i = 0; i < shop_arms_chunks.size() - 1; i++)
  {
    gear_data_t* shop_arms = new gear_data_t( shop_arms_chunks[ i ].data );
    shop_arms_data.push_back( shop_arms );
  }
}

void initializer_t::initializeItemRateData() const
{
  std::string path = INPUT_FOLDER + BATTLE_KERNEL_FOLDER + "item_rate.bin";
  std::vector<char> bytes = bytes_mapper_t::fileToBytes( path );
  bytes = std::vector<char>( bytes.begin() + 20, bytes.end() );
  // Split the item rate data into 4 byte chunks
  std::vector<chunk_t> item_rate_chunks = initializer_t::chunkData( bytes, 4 );
  for (int i = 0; i < item_rate_chunks.size(); i++)
  {
    item_rate_t* item_rate = new item_rate_t( item_rate_chunks[ i ].data );
    item_rate_data.push_back( item_rate );
  }
}

void initializer_t::initializePlayerStatData() const
{
  std::string path = INPUT_FOLDER + USPC_BTL_KERN_FOLDER + "ply_save.bin";
  std::vector<char> bytes = bytes_mapper_t::fileToBytes( path );
  bytes = std::vector<char>( bytes.begin() + 20, bytes.end() );
  // Split the player stats data into 148 byte chunks
  std::vector<chunk_t> player_stats_chunks = initializer_t::chunkData( bytes, 148 );
  for (int i = 0; i < 18; i++)
  {
    character_stats_t* player_stats = new character_stats_t( i, player_stats_chunks[ i ].data );
    player_stats_data.push_back( player_stats );
  }
}

void initializer_t::initializeAeonScalingData() const
{
  std::string path = INPUT_FOLDER + USPC_BTL_KERN_FOLDER + "ply_rom.bin";
  std::vector<char> bytes = bytes_mapper_t::fileToBytes( path );
  bytes = std::vector<char>( bytes.begin() + 20, bytes.end() );
  // Split the aeon scaling data into 44 byte chunks
  std::vector<chunk_t> aeon_scaling_chunks = initializer_t::chunkData( bytes, 44 );
  for (int i = 0; i < aeon_scaling_chunks.size(); i++)
  {
    new aeon_scaling_data_t( aeon_scaling_chunks[ i ].data, aeon_scaling_chunks[ i ].initial_offset );
  }
}

void initializer_t::initializeAeonStatData() const
{
  std::string path = INPUT_FOLDER + BATTLE_KERNEL_FOLDER + "sum_assure.bin";
  std::vector<char> bytes = bytes_mapper_t::fileToBytes( path );
  bytes = std::vector<char>( bytes.begin() + 20, bytes.end() );
  // Split the aeon stat data into 120 byte chunks
  std::vector<chunk_t> aeon_stat_chunks = initializer_t::chunkData( bytes, 120 );
  for (int i = 0; i < aeon_stat_chunks.size(); i++)
  {
    aeon_stat_data_t* aeon = new aeon_stat_data_t( i, aeon_stat_chunks[ i ].data );
    aeon_stat_data.push_back( aeon );
  }
}

void initializer_t::initializeGUI()
{
  initializeAllData();
  gui = new gui_t( enemy_data, field_data, item_shop_data, gear_shop_data, buki_data, weapon_data, shop_arms_data, item_rate_data, player_stats_data, aeon_scaling_data, aeon_stat_data );
  wxApp::SetInstance( gui );
  wxEntryStart( 0, nullptr );
  wxTheApp->CallOnInit();
  wxTheApp->OnRun();
  wxTheApp->OnExit();
  wxEntryCleanup();
}

void initializer_t::initializeAllData() const
{
  std::thread enemy_thread( &initializer_t::initializeEnemyData, this );
  std::thread field_thread( &initializer_t::initializeFieldData, this );
  std::thread shop_item_thread( &initializer_t::initializeShopData, this, false );
  std::thread shop_gear_thread( &initializer_t::initializeShopData, this, true );
  std::thread buki_thread( &initializer_t::initializeBukiData, this );
  std::thread weapon_thread( &initializer_t::initializeWeaponData, this );
  std::thread shop_arms_thread( &initializer_t::initializeShopArmsData, this );
  std::thread item_rate_thread( &initializer_t::initializeItemRateData, this );
  std::thread player_stats_thread( &initializer_t::initializePlayerStatData, this );
  std::thread aeon_scaling_thread( &initializer_t::initializeAeonScalingData, this );
  std::thread aeon_stat_thread( &initializer_t::initializeAeonStatData, this );

  enemy_thread.join();
  field_thread.join();
  shop_item_thread.join();
  shop_gear_thread.join();
  buki_thread.join();
  weapon_thread.join();
  shop_arms_thread.join();
  item_rate_thread.join();
  player_stats_thread.join();
  aeon_scaling_thread.join();
  aeon_stat_thread.join();
}

void initializer_t::runEnemyTests()
{
  for (auto& enemy : enemy_data)
  {
    enemy.second->test();
  }
}

void initializer_t::runFieldTests()
{
  for (auto& item : field_data)
  {
    item->test();
  }
}

void initializer_t::runShopTests()
{
  for (auto& shop : gear_shop_data)
  {
    shop->test();
  }
  for (auto& shop : item_shop_data)
  {
    shop->test();
  }
}

void initializer_t::runBukiTests()
{
  for (auto& buki : buki_data)
  {
    buki->test();
  }
}

void initializer_t::runWeaponTests()
{
  for (auto& weapon : weapon_data)
  {
    weapon->test();
  }
}

void initializer_t::runShopArmsTests()
{
  for (auto& shop : shop_arms_data)
  {
    shop->test();
  }
}

void initializer_t::runEnemyLootTests()
{
  for (auto& loot : enemy_data)
  {
    loot.second->loot_data->test();
  }
}

void initializer_t::runItemRateTests()
{
  for (auto& item_rate : item_rate_data)
  {
    item_rate->test();
  }
  printf( "Item Rate Data Size: %zu\n", item_rate_data.size() );
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

  enemy_thread.join();
  field_thread.join();
  shop_thread.join();
  buki_thread.join();
  weapon_thread.join();
  shop_arms_thread.join();
  enemy_loot_thread.join();
  item_rate_thread.join();
}

