#include "Randomizer.hpp"

void randomizer_t::reconstructBukiData()
{
  std::string name = "buki_get.bin";
  genericReconstructor( btl_kernel_input, btl_kernel_output, name, data_pack.buki_data, true );
}

void randomizer_t::reconstructWeaponData()
{
  std::string name = "weapon.bin";
  genericReconstructor( btl_kernel_input, btl_kernel_output, name, data_pack.weapon_data, true );
}

void randomizer_t::reconstructShopArmsData()
{
  std::string name = "shop_arms.bin";
  genericReconstructor( btl_kernel_input, btl_kernel_output, name, data_pack.shop_arms_data, true );
}


void randomizer_t::poplateGearLists()
{
  for (auto& gear : data_pack.buki_data)
  {
    gear_data_t* armor = gear;
    if (gear->is_brotherhood && !options_pack.randomize_brotherhood)
      continue;
    if (armor->is_celestial && !options_pack.randomize_celestials)
      continue;
    if (armor->is_armor)
      all_armor.push_back( armor );
    else
      all_weapons.push_back( armor );
  }
  for (auto& gear : data_pack.weapon_data)
  {
    gear_data_t* armor = gear;
    if (armor->is_armor)
      all_armor.push_back( armor );
    else
      all_weapons.push_back( armor );
  }
  for (auto& gear : data_pack.shop_arms_data)
  {
    gear_data_t* armor = gear;
    if (armor->is_armor)
      all_armor.push_back( armor );
    else
      all_weapons.push_back( armor );
  }
}

uint16_t randomizer_t::getRandomAbility()
{
  std::uniform_int_distribution<size_t> dist( 0, abilities.size() - 1 );
  return abilities[ dist( rng ) ];
}

void randomizer_t::populateAbilityData()
{
  for (auto& gear : all_armor)
  {
    gear_data_t* armor = gear;
    armor->mapAbilities( abilities );
  }
  for (auto& gear : all_weapons)
  {
    gear_data_t* weapon = gear;
    weapon->mapAbilities( abilities );
  }
  for (auto& enemy : data_pack.enemy_data)
  {
    enemy_loot_data_t& loot = *enemy.second.loot_data;
    for (int chr = 0; chr < 7; chr++)
    {
      for (int i = 0; i < 8; i++)
      {
        bool found = std::find( abilities.begin(), abilities.end(), loot.weapon_abilities_by_char.at( chr ) ) != abilities.end();
        if (!found && loot.weapon_abilities_by_char.at( chr ) != 255)
          abilities.push_back( loot.weapon_abilities_by_char.at( chr ) );
      }
    }
    for (int chr = 0; chr < 7; chr++)
    {
      for (int i = 0; i < 8; i++)
      {
        bool found = std::find( abilities.begin(), abilities.end(), loot.gear_abilities_by_char.at( chr ) ) != abilities.end();
        if (!found && loot.gear_abilities_by_char.at( chr ) != 255)
          abilities.push_back( loot.gear_abilities_by_char.at( chr ) );
      }
    }
  }
}

uint8_t randomizer_t::getRandomFormula()
{
  std::uniform_int_distribution<size_t> dist( 0, weapon_formulas.size() - 1 );
  return weapon_formulas[ dist( rng ) ];
}

void randomizer_t::populateWeaponFormulas()
{
  for (auto& gear : all_weapons)
  {
    gear_data_t& weapon = *gear;
    weapon.mapFormulas( weapon_formulas );
  }
  for (auto& enemy : data_pack.enemy_data)
  {
    enemy_loot_data_t& loot = *enemy.second.loot_data;
    bool found = std::find( weapon_formulas.begin(), weapon_formulas.end(), loot.gear_damage_calc ) != weapon_formulas.end();
    if (!found)
      weapon_formulas.push_back( loot.gear_damage_calc );
  }
}

void randomizer_t::writeGearData( gear_data_t& gear )
{
  if (( gear.is_celestial && !options_pack.randomize_celestials ) || ( gear.is_brotherhood && !options_pack.randomize_brotherhood ))
    return;

  uint8_t n_abilities = uniform<uint8_t>( 0, 3 );

  std::vector<uint16_t> abilities;

  for (uint8_t i = 0; i < 4; i++)
  {
    if (i >= n_abilities)
    {
      abilities.push_back( 255 );
      continue;
    }
    abilities.push_back( getRandomAbility() );
  }

  gear.slots = n_abilities;
  gear.ability_slot1 = abilities.at( 0 );
  gear.ability_slot2 = abilities.at( 1 );
  gear.ability_slot3 = abilities.at( 2 );
  gear.ability_slot4 = abilities.at( 3 );

  gear.writeToBytes();
}

void randomizer_t::randomizeShopArmsAbilities()
{
  for (auto& gear : data_pack.shop_arms_data)
  {
    gear_data_t& gear_data = *gear;
    writeGearData( gear_data );
  }
}

void randomizer_t::randomizeBukiAbilities()
{
  for (auto& gear : data_pack.buki_data)
  {
    gear_data_t& gear_data = *gear;
    writeGearData( gear_data );
  }
}

void randomizer_t::randomizeWeaponsAbilities()
{
  for (auto& gear : data_pack.weapon_data)
  {
    gear_data_t& gear_data = *gear;
    writeGearData( gear_data );
  }
}

void randomizer_t::randomizeWeaponCrit()
{
  for (auto& gear : data_pack.shop_arms_data)
  {
    gear_data_t& gear_data = *gear;
    if (gear_data.is_armor || ( gear_data.is_celestial && !options_pack.randomize_celestials ) || ( gear_data.is_brotherhood && !options_pack.randomize_brotherhood ))
      continue;
    if (options_pack.keep_things_sane)
      gear_data.crit_bonus = normal<uint8_t>( gear_data.crit_bonus, gear_data.crit_bonus / 2, 1, 100 );
    else
      gear_data.crit_bonus = uniform<uint8_t>( 0, 100 );
    gear_data.writeToBytes();
  }
  for (auto& gear : data_pack.buki_data)
  {
    gear_data_t& gear_data = *gear;
    if (gear_data.is_armor || ( gear_data.is_celestial && !options_pack.randomize_celestials ) || ( gear_data.is_brotherhood && !options_pack.randomize_brotherhood ))
      continue;
    if (options_pack.keep_things_sane)
      gear_data.crit_bonus = normal<uint8_t>( gear_data.crit_bonus, gear_data.crit_bonus / 2, 1, 100 );
    else
      gear_data.crit_bonus = uniform<uint8_t>( 0, 100 );
    gear_data.writeToBytes();
  }
  for (auto& gear : data_pack.weapon_data)
  {
    gear_data_t& gear_data = *gear;
    if (gear_data.is_armor || ( gear_data.is_celestial && !options_pack.randomize_celestials ) || ( gear_data.is_brotherhood && !options_pack.randomize_brotherhood ))
      continue;
    if (options_pack.keep_things_sane)
      gear_data.crit_bonus = normal<uint8_t>( gear_data.crit_bonus, gear_data.crit_bonus / 2, 1, 100 );
    else
      gear_data.crit_bonus = uniform<uint8_t>( 0, 100 );
    gear_data.writeToBytes();
  }
}

void randomizer_t::randomizeWeaponAttackPower()
{
  for (auto& gear : data_pack.shop_arms_data)
  {
    gear_data_t& gear_data = *gear;
    if (gear_data.is_armor || ( gear_data.is_celestial && !options_pack.randomize_celestials ) || ( gear_data.is_brotherhood && !options_pack.randomize_brotherhood ))
      continue;
    if (options_pack.keep_things_sane)
      gear_data.attack_power = normal<uint8_t>( gear_data.attack_power, gear_data.attack_power / 2, 1, 24 );
    else
      gear_data.attack_power = uniform<uint8_t>( 0, 100 );

    gear_data.writeToBytes();
  }
  for (auto& gear : data_pack.buki_data)
  {
    gear_data_t& gear_data = *gear;
    if (gear_data.is_armor || ( gear_data.is_celestial && !options_pack.randomize_celestials ) || ( gear_data.is_brotherhood && !options_pack.randomize_brotherhood ))
      continue;
    if (options_pack.keep_things_sane)
      gear_data.attack_power = normal<uint8_t>( gear_data.attack_power, gear_data.attack_power / 2, 1, 24 );
    else
      gear_data.attack_power = uniform<uint8_t>( 0, 100 );
    gear_data.writeToBytes();
  }
  for (auto& gear : data_pack.weapon_data)
  {
    gear_data_t& gear_data = *gear;
    if (gear_data.is_armor || ( gear_data.is_celestial && !options_pack.randomize_celestials ) || ( gear_data.is_brotherhood && !options_pack.randomize_brotherhood ))
      continue;
    if (options_pack.keep_things_sane)
      gear_data.attack_power = normal<uint8_t>( gear_data.attack_power, gear_data.attack_power / 2, 1, 24 );
    else
      gear_data.attack_power = uniform<uint8_t>( 0, 100 );
    gear_data.writeToBytes();
  }
}

void randomizer_t::randomizeWeaponDamageFormula()
{
  for (auto& gear : data_pack.shop_arms_data)
  {
    gear_data_t& gear_data = *gear;
    if (gear_data.is_armor || ( gear_data.is_celestial && !options_pack.randomize_celestials ) || ( gear_data.is_brotherhood && !options_pack.randomize_brotherhood ))
      continue;

    gear_data.damage_calc = getRandomFormula();
    gear_data.writeToBytes();
  }
  for (auto& gear : data_pack.buki_data)
  {
    gear_data_t& gear_data = *gear;
    if (gear_data.is_armor || ( gear_data.is_celestial && !options_pack.randomize_celestials ) || ( gear_data.is_brotherhood && !options_pack.randomize_brotherhood ))
      continue;

    gear_data.damage_calc = getRandomFormula();
    gear_data.writeToBytes();
  }
  for (auto& gear : data_pack.weapon_data)
  {
    gear_data_t& gear_data = *gear;
    if (gear_data.is_armor || ( gear_data.is_celestial && !options_pack.randomize_celestials ) || ( gear_data.is_brotherhood && !options_pack.randomize_brotherhood ))
      continue;

    gear_data.damage_calc = getRandomFormula();
    gear_data.writeToBytes();
  }
}

void randomizer_t::doGearRandomization()
{
  if (!options_pack.randomize_gear_abilities && !options_pack.randomize_weapon_attack_power && !options_pack.randomize_weapon_crit &&
       !options_pack.randomize_weapon_damage_formula)
    return;

  if (options_pack.randomize_gear_abilities)
  {
    printf( "Randomizing shop_arms.bin Abilities...\n" );
    std::thread shop_arms_thread( &randomizer_t::randomizeShopArmsAbilities, this );
    printf( "Randomizing buki_get.bin Abilities...\n" );
    std::thread buki_thread( &randomizer_t::randomizeBukiAbilities, this );
    printf( "Randomizing weapon.bin Abilities...\n" );
    std::thread weapon_thread( &randomizer_t::randomizeWeaponsAbilities, this );

    shop_arms_thread.join();
    buki_thread.join();
    weapon_thread.join();
  }

  if (options_pack.randomize_weapon_attack_power)
  {
    printf( "Randomizing weapon.bin Attack Power...\n" );
    randomizeWeaponAttackPower();
  }

  if (options_pack.randomize_weapon_crit)
  {
    printf( "Randomizing weapon.bin Crit Chance...\n" );
    randomizeWeaponCrit();
  }

  if (options_pack.randomize_weapon_damage_formula)
  {
    printf( "Randomizing weapon.bin Damage Formula...\n" );
    randomizeWeaponDamageFormula();
  }

  printf( "Reconstructing shop_arms.bin...\n" );
  std::thread shop_arms_data_thread( &randomizer_t::reconstructShopArmsData, this );
  printf( "Reconstructing buki_get.bin...\n" );
  std::thread buki_data_thread( &randomizer_t::reconstructBukiData, this );
  printf( "Reconstructing weapon.bin...\n" );
  std::thread weapon_data_thread( &randomizer_t::reconstructWeaponData, this );

  shop_arms_data_thread.join();
  buki_data_thread.join();
  weapon_data_thread.join();
}