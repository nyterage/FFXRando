#include "Randomizer.hpp"

void randomizer_t::reconstructItemShopData()
{
  std::string name = "item_shop.bin";
  genericReconstructor( btl_kernel_input, btl_kernel_output, name, data_pack.item_shop_data, true );
}

void randomizer_t::reconstructArmsShopData()
{
  std::string name = "arms_shop.bin";
  genericReconstructor( btl_kernel_input, btl_kernel_output, name, data_pack.gear_shop_data, true );
}

void randomizer_t::reconstructArmsRateData()
{
  std::string name = "arms_rate.bin";
  genericReconstructor( btl_kernel_input, btl_kernel_output, name, data_pack.arms_rate_data, true );
}

void randomizer_t::reconstructItemRateData()
{
  std::string name = "item_rate.bin";
  genericReconstructor( btl_kernel_input, btl_kernel_output, name, data_pack.item_rate_data, true );
}

void randomizer_t::randomizeArmsPrices()
{
  for (auto& price : data_pack.arms_rate_data)
  {
    arms_rate_t& arms_rate = *price;
    if (arms_rate.rate > 1 && options_pack.keep_things_sane)
      arms_rate.rate = normal<uint32_t>( arms_rate.rate, arms_rate.rate, 1, UINT16_MAX );
    else
      arms_rate.rate = uniform<uint32_t>( 1, UINT16_MAX );
    arms_rate.writeToBytes();
  }
}

void randomizer_t::randomizeItemPrices()
{
  for (auto& price : data_pack.item_rate_data)
  {
    item_rate_t& item_rate = *price;
    if (item_rate.rate > 1 && item_rate.rate != 2 && options_pack.keep_things_sane)
      item_rate.rate = normal<uint32_t>( item_rate.rate, item_rate.rate, 1, UINT16_MAX );
    else if (item_rate.rate == 2 && options_pack.keep_things_sane)
      // Spheres normally cost 2 gil in data, since they are never sold by vendors. 
      // Since this can happen with randomization, bump the price to something more reasonable. 
      item_rate.rate = normal<uint32_t>( 500, 250, 1, UINT16_MAX );
    else
      item_rate.rate = uniform<uint32_t>( 1, UINT16_MAX );
    item_rate.writeToBytes();
  }
}

void randomizer_t::randomizeItemShops()
{
  for (auto& shop : data_pack.item_shop_data)
  {
    shop_data_t* item_shop = shop;
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
      while (found = std::find( item_shop->item_indexes.begin(), item_shop->item_indexes.end(), potential_item->id ) != item_shop->item_indexes.end() && potential_item->id < 10000);

      item_shop->item_indexes.at( i ) = potential_item->id;
    }
    item_shop->writeToBytes();
  }
}

int randomizer_t::getRandomShopArmsIndex()
{
  std::uniform_int_distribution<size_t> dist( 0, data_pack.shop_arms_data.size() - 1 );
  return dist( rng );
}

void randomizer_t::randomizeGearShops()
{
  for (auto& shop : data_pack.gear_shop_data)
  {
    shop_data_t* gear_shop = shop;
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

void randomizer_t::doShopRandomization()
{
  if (!options_pack.randomize_item_shops && !options_pack.randomize_gear_shops)
    return;

  if (options_pack.randomize_item_shops)
  {
    printf( "Randomizing Item Shops...\n" );
    randomizeItemShops();
    reconstructItemShopData();
  }

  if (options_pack.randomize_gear_shops)
  {
    printf( "Randomizing Gear Shops...\n" );
    randomizeGearShops();
    reconstructArmsShopData();
  }
}

void randomizer_t::doPriceRandomization()
{
  if (!options_pack.randomize_item_shop_prices && !options_pack.randomize_gear_shop_prices)
    return;

  if (options_pack.randomize_item_shop_prices)
  {
    printf( "Randomizing Item Prices...\n" );
    randomizeItemPrices();
    printf( "Reconstructing item_rate.bin...\n" );
    reconstructItemRateData();
  }

  if (options_pack.randomize_gear_shop_prices)
  {
    printf( "Randomizing Gear Prices...\n" );
    randomizeArmsPrices();
    printf( "Reconstructing arms_rate.bin...\n" );
    reconstructArmsRateData();
  }
}