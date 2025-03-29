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
    field_data_t* field = new field_data_t( field_chunks[ i ].data );
    field_data.insert( { i , field } );
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
      gear_shop_data.insert( { i , shop } );
    else
      item_shop_data.insert( { i , shop } );
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
    buki_data.insert( { i , buki } );
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
    weapon_data.insert( { i , weapon } );
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
    shop_arms_data.insert( { i , shop_arms } );
  }
}

void initializer_t::initializeRandomizer()
{
  // TODO - Actual seeds rather than random seeds
  int seed = static_cast< int >( std::chrono::system_clock::now().time_since_epoch().count() );
  randomizer = new randomizer_t( seed, enemy_data, field_data, item_shop_data, gear_shop_data,
                                 buki_data, weapon_data, shop_arms_data, all_items, all_non_key_items );
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

  enemy_thread.join();
  field_thread.join();
  shop_item_thread.join();
  shop_gear_thread.join();
  buki_thread.join();
  weapon_thread.join();
  shop_arms_thread.join();
}

void initializer_t::checkItemList( uint16_t& id, int& quantity, bool key = false ) const
{
  if (id < 8192)
    return;

  bool found = all_items.find( id ) != all_items.end();
  if (!found)
  {
    item_t* item = new item_t( id, quantity, quantity );
    all_items.insert( { id , item } );
    if (!key)
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

void initializer_t::getFieldItems() const
{
  for (int i = 0; i < field_data.size(); i++)
  {
    field_data_t& field = *field_data.at( i );
    if (field.flag == 10 || field.flag == 2)
      checkItemList( field.type, field.quantity, field.flag == 10 );
  }
}

void initializer_t::getMonsterItems() const
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

void initializer_t::getShopItems() const
{
  int quantity = 1;
  for (uint16_t i = 0; i < item_shop_data.size(); i++)
  {
    shop_data_t& shop = *item_shop_data.at( i );
    for (uint16_t j = 0; j < shop.item_indexes.size(); j++)
    {
      checkItemList( shop.item_indexes[ j ], quantity );
    }
  }
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
    item.second->test();
  }
}

void initializer_t::runShopTests()
{
  for (auto& shop : gear_shop_data)
  {
    shop.second->test();
  }
  for (auto& shop : item_shop_data)
  {
    shop.second->test();
  }
}

void initializer_t::runBukiTests()
{
  for (auto& buki : buki_data)
  {
    buki.second->test();
  }
}

void initializer_t::runWeaponTests()
{
  for (auto& weapon : weapon_data)
  {
    weapon.second->test();
  }
}

void initializer_t::runShopArmsTests()
{
  for (auto& shop : shop_arms_data)
  {
    shop.second->test();
  }
}

void initializer_t::runEnemyLootTests()
{
  for (auto& loot : enemy_data)
  {
    loot.second->loot_data->test();
  }
}

void initializer_t::runItemListTests()
{
  for (auto& item : all_items)
  {
    item.second->test();
  }
}

void initializer_t::runTests( initializer_t& init )
{
  std::thread enemy_thread( &initializer_t::runEnemyTests, &init );
  std::thread field_thread( &initializer_t::runFieldTests, &init );
  std::thread shop_thread( &initializer_t::runShopTests, &init );
  std::thread buki_thread( &initializer_t::runBukiTests, &init );
  std::thread weapon_thread( &initializer_t::runWeaponTests, &init );
  std::thread shop_arms_thread( &initializer_t::runShopArmsTests, &init );
  std::thread enemy_loot_thread( &initializer_t::runEnemyLootTests, &init );
  std::thread item_list_thread( &initializer_t::runItemListTests, &init );

  enemy_thread.join();
  field_thread.join();
  shop_thread.join();
  buki_thread.join();
  weapon_thread.join();
  shop_arms_thread.join();
  enemy_loot_thread.join();
  item_list_thread.join();
}