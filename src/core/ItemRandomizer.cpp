#include "Randomizer.hpp"

void randomizer_t::reconstructTakaraData()
{
  std::string name = "takara.bin";
  genericReconstructor( btl_kernel_input, btl_kernel_output, name, data_pack.field_data, true );
}

void randomizer_t::checkItemList( uint16_t& id, uint8_t& quantity, bool key )
{
  bool key_item = key;
  if (id == 0)
    return;
  if (quantity == 0)
    quantity = 1;
  if (id > 9000)
    key_item = true;

  std::unordered_map<int, item_t*>::iterator it = all_items.find( id );

  bool found = it != all_items.end();
  if (!found)
  {
    item_t* item = new item_t( id, quantity, quantity );
    item->addInstance( quantity );
    all_items.insert( { id , item } );
    if (!key_item)
      all_non_key_items.insert( { id , item } );
    if (key_item)
      all_key_items.insert( { id , item } );
  }
  else
  {
    item_t& item = *all_items.at( id );
    if (item.getMinQuantity() > quantity)
      item.setMinQuantity( quantity );
    if (item.getMaxQuantity() < quantity)
      item.setMaxQuantity( quantity );
    item.addInstance( quantity );
  }
}

void randomizer_t::getFieldItems()
{
  for (auto& item : data_pack.field_data)
  {
    field_data_t& field = *item;
    if (( field.flag == 2 || field.flag == 10 ) && field.type != 203 && field.type != 177)
      checkItemList( field.type, field.quantity, field.flag == 10 );
  }
}

void randomizer_t::getMonsterItems()
{
  for (auto& enemy : data_pack.enemy_data)
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

void randomizer_t::getShopItems()
{
  uint8_t quantity = 1;
  for (auto& shop : data_pack.item_shop_data)
  {
    shop_data_t& item_shop = *shop;
    for (auto& item : item_shop.item_indexes)
    {
      checkItemList( item, quantity );
    }
  }
}

item_t* randomizer_t::getRandomItem()
{
  std::vector<item_t*> items;
  for (auto& item : all_non_key_items)
    items.push_back( item.second );

  std::uniform_int_distribution<size_t> dist( 0, items.size() - 1 );
  int index = dist( rng );
  return items[ index ];
}

item_t* randomizer_t::getRandomKeyItem()
{
  std::vector<item_t*> items;
  for (auto& item : all_key_items)
    items.push_back( item.second );

  std::uniform_int_distribution<size_t> dist( 0, items.size() - 1 );
  int index = dist( rng );

  all_key_items.erase( items[ index ]->id );

  return items[ index ];
}

int randomizer_t::getRandomItemQuantity( item_t* item, bool is_monster )
{
  if (options_pack.keep_things_sane)
  {
    if (is_monster)
      return uniform<uint8_t>( 1, 4 );
    if (item->getAverageQuantity() > 10)
      return normal<uint8_t>( std::min<uint8_t>( item->getMinQuantity() * 5, 7 ), std::min<uint8_t>( item->getMinQuantity() * 5, 7 ) / 5, std::min<uint8_t>( item->getMinQuantity(), 1 ), 99 );
    if (item->getAverageQuantity() < 10)
      return normal<uint8_t>( item->getAverageQuantity(), item->getStandardDeviation(), item->getMinQuantity(), item->getMaxQuantity() );
    else
      return item->getMinQuantity();
  }

  return uniform<uint8_t>( 0, 99 );
}

void randomizer_t::randomizeFieldItems()
{
  std::vector<int> blacklist = { 177, 203 };
  if (!options_pack.randomize_celestials)
  {
    blacklist.push_back( 5 );
    blacklist.push_back( 93 );
    blacklist.push_back( 99 );
    blacklist.push_back( 113 );
    blacklist.push_back( 114 );
    blacklist.push_back( 188 );
    blacklist.push_back( 214 );
  }
  if (!options_pack.randomize_brotherhood)
  {
    blacklist.push_back( 207 );
    blacklist.push_back( 208 );
  }
  for (auto& field : data_pack.field_data)
  {
    field_data_t& field_data = *field;
    if (std::find( blacklist.begin(), blacklist.end(), field_data.index ) != blacklist.end())
      continue;

    if (field_data.flag != 10 || options_pack.randomize_key_items)
    {
      int roll;
      if( options_pack.randomize_key_items )
        roll = std::discrete_distribution<int>( { 0.4, 0.3, 0.2, 0.1 } )( rng );
      else
        roll = std::discrete_distribution<int>( { 0.5, 0.3, 0.2 } )( rng );

      item_t* item = nullptr;
      switch (roll)
      {
        case 0:
          item = getRandomItem();
          field_data.flag = 2;
          field_data.type = item->id;
          field_data.quantity = getRandomItemQuantity( item, false );
          field_data.writeToBytes();
          break;
        case 1:
          field_data.flag = 5;
          field_data.type = uniform<uint16_t>( 0, data_pack.buki_data.size() - 1 );
          field_data.quantity = 1;
          field_data.writeToBytes();
          break;
        case 2:
          field_data.flag = 0;
          field_data.quantity = normal<uint8_t>( 15, 5, 1, 255 );
          field_data.writeToBytes();
          break;
        case 3:
          if (all_key_items.size() == 0)
          {
            item = getRandomItem();
            field_data.flag = 2;
          }
          else
          {
            item = getRandomKeyItem();
            field_data.flag = 10;
          }
          field_data.type = item->id;
          field_data.quantity = getRandomItemQuantity( item, false );
          field_data.writeToBytes();
          break;
        default:
          break;
      }
    }
  }

  // Ensure all key items are in the pool
  while (all_key_items.size() > 0 && options_pack.randomize_key_items)
  {
    int random_field_index = uniform<int>( 0, data_pack.field_data.size() - 1 );
    field_data_t& field_data = *data_pack.field_data.at( random_field_index );
    if (field_data.flag == 10)
      continue;
    if (std::find( blacklist.begin(), blacklist.end(), field_data.index ) != blacklist.end())
      continue;

    item_t* item = getRandomKeyItem();
    field_data.flag = 10;
    field_data.type = item->id;
    field_data.quantity = getRandomItemQuantity( item, false );
    field_data.writeToBytes();
  }
}

void randomizer_t::doFieldRandomization()
{
  for (auto& item : all_non_key_items)
  {
    item.second->test();
  }
  if (!options_pack.randomize_field_items)
    return;

  printf( "Randomizing Field Items...\n" );
  randomizeFieldItems();
  printf( "Reconstructing takara.bin...\n" );
  reconstructTakaraData();
}