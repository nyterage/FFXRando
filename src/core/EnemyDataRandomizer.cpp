#include "Randomizer.hpp"


void randomizer_t::randomizeEnemyDrops( enemy_data_t* enemy )
{
  enemy_loot_data_t& loot = *enemy->loot_data;
  if (options_pack.keep_things_sane)
  {
    if (loot.gil > 0)
      loot.gil = normal<uint16_t>( loot.gil, loot.gil / 2, loot.gil * 0.05, static_cast< uint16_t >( std::min<double>( loot.gil * 3, UINT16_MAX ) ) );
    else
      loot.gil = 0;
    if (loot.ap > 0)
      loot.ap = normal<uint16_t>( loot.ap, loot.ap / 2, loot.ap * 0.05, static_cast< uint16_t >( std::min<double>( loot.ap * 3, UINT16_MAX ) ) );
    else
      loot.ap = 0;
    if (loot.ap_overkill > 0)
      loot.ap_overkill = normal<uint16_t>( loot.ap_overkill, loot.ap_overkill / 2, loot.ap_overkill * 0.05, static_cast< uint16_t >( std::min<double>( loot.ap_overkill * 3, UINT16_MAX ) ) );
    else
      loot.ap_overkill = 0;
  }
  else
  {
    loot.gil = uniform<uint16_t>( 1, UINT16_MAX );
    loot.ap = uniform<uint16_t>( 1, UINT16_MAX );
    loot.ap_overkill = uniform<uint16_t>( 1, UINT16_MAX );
  }

  // Normal Item Drop
  item_t* normal_drop = getRandomItem();
  int normal_drop_quantity = getRandomItemQuantity( normal_drop );

  // Rare Item Drop
  item_t* rare_drop = getRandomItem();
  int rare_drop_quantity = getRandomItemQuantity( rare_drop );

  // Secondary Item Drop
  item_t* secondary_normal_drop = getRandomItem();
  int secondary_normal_drop_quantity = getRandomItemQuantity( secondary_normal_drop );

  // Secondary Rare Item Drop
  item_t* secondary_rare_drop = getRandomItem();
  int secondary_rare_drop_quantity = getRandomItemQuantity( secondary_rare_drop );

  // Normal Overkill Drop
  item_t* normal_overkill_drop = getRandomItem();
  int normal_overkill_drop_quantity = getRandomItemQuantity( normal_overkill_drop );

  // Rare Overkill Drop
  item_t* rare_overkill_drop = getRandomItem();
  int rare_overkill_drop_quantity = getRandomItemQuantity( rare_overkill_drop );

  // Secondary Overkill Drop
  item_t* secondary_overkill_drop = getRandomItem();
  int secondary_overkill_drop_quantity = getRandomItemQuantity( secondary_overkill_drop );

  // Secondary Rare Overkill Drop
  item_t* secondary_rare_overkill_drop = getRandomItem();
  int secondary_rare_overkill_drop_quantity = getRandomItemQuantity( secondary_rare_overkill_drop );

  loot.primary_normal_drop = normal_drop->id;
  loot.primary_normal_drop_rare = rare_drop->id;
  if (options_pack.keep_things_sane && loot.primary_drop_chance > 0)
    loot.primary_drop_chance = normal<uint8_t>( loot.primary_drop_chance, loot.primary_drop_chance / 2, 0, 255 );
  else
    loot.primary_drop_chance = uniform<uint8_t>( 0, 255 );
  loot.secondary_normal_drop = secondary_normal_drop->id;
  loot.secondary_normal_drop_rare = secondary_rare_drop->id;
  if (options_pack.keep_things_sane && loot.secondary_drop_chance > 0)
    loot.secondary_drop_chance = normal<uint8_t>( loot.secondary_drop_chance, loot.secondary_drop_chance / 2, 0, 255 );
  else
    loot.secondary_drop_chance = uniform<uint8_t>( 0, 255 );
  loot.primary_normal_drop_overkill = normal_overkill_drop->id;
  loot.primary_normal_drop_overkill_rare = rare_overkill_drop->id;
  loot.secondary_normal_drop_overkill = secondary_overkill_drop->id;
  loot.secondary_normal_drop_overkill_rare = secondary_rare_overkill_drop->id;
  loot.n_primary_normal_drop = normal_drop_quantity;
  loot.n_primary_normal_drop_rare = rare_drop_quantity;
  loot.n_secondary_normal_drop = secondary_normal_drop_quantity;
  loot.n_secondary_normal_drop_rare = secondary_rare_drop_quantity;
  loot.n_primary_normal_drop_overkill = normal_overkill_drop_quantity;
  loot.n_primary_normal_drop_overkill_rare = rare_overkill_drop_quantity;
  loot.n_secondary_normal_drop_overkill = secondary_overkill_drop_quantity;
  loot.n_secondary_normal_drop_overkill_rare = secondary_rare_overkill_drop_quantity;
  loot.writeToBytes();
  enemy->loot_data = &loot;
  enemy->writeLootData( loot );
};

void randomizer_t::randomizeEnemySteal( enemy_data_t* enemy )
{
  enemy_loot_data_t& loot = *enemy->loot_data;
  item_t* steal_item = getRandomItem();
  int steal_item_quantity = getRandomItemQuantity( steal_item );
  item_t* rare_steal_item = getRandomItem();
  int rare_steal_item_quantity = getRandomItemQuantity( rare_steal_item );
  loot.steal_chance = 255;
  loot.steal_item = steal_item->id;
  loot.steal_item_rare = rare_steal_item->id;
  loot.n_steal_item = steal_item_quantity;
  loot.n_steal_item_rare = rare_steal_item_quantity;
  if (loot.n_gil_steal > 0)
  {
    if (options_pack.keep_things_sane)
      loot.n_gil_steal = normal<uint8_t>( loot.n_gil_steal, loot.n_gil_steal / 2, 1, UINT8_MAX );
    else
      loot.n_gil_steal = uniform<uint8_t>( 1, UINT8_MAX );
  }
  loot.writeToBytes();
  enemy->loot_data = &loot;
  enemy->writeLootData( loot );
}

void randomizer_t::randomizeEnemyBribe( enemy_data_t* enemy )
{
  enemy_loot_data_t& loot = *enemy->loot_data;
  item_t* bribe_item = getRandomItem();
  int bribe_item_quantity = getRandomItemQuantity( bribe_item );
  loot.bribe_item = bribe_item->id;
  loot.n_bribe_item = bribe_item_quantity;
  loot.writeToBytes();
  enemy->loot_data = &loot;
  enemy->writeLootData( loot );
}

void randomizer_t::randomizeEnemyStatsNormal( enemy_data_t* enemy )
{
  if (enemy->monster_id == "211" || enemy->monster_id == "237")
    return;
  enemy_stat_data_t& stats = *enemy->stats_data;
  if (stats.hp <= 1)
    return;
  if (stats.hp > 1)
    stats.hp = normal<uint32_t>( stats.hp, stats.hp / 2, std::floor( stats.hp * 0.5 ), stats.hp * 3 );
  if (stats.hp < 50)
    stats.hp = 50;
  stats.mp = normal<uint32_t>( stats.mp, stats.mp / 2, 1, 999 );
  stats.overkill_threshold = normal<uint32_t>( stats.overkill_threshold / 2, stats.overkill_threshold, 1, 99999 );
  if (options_pack.keep_things_sane)
  {
    stats.str = normal<uint8_t>( stats.str, stats.str / 2, 0, std::min<uint8_t>( stats.str * 2, UINT8_MAX ) );
    stats.def = normal<uint8_t>( stats.def, stats.def / 2, 0, std::min<uint8_t>( stats.def * 2, UINT8_MAX ) );
    stats.mag = normal<uint8_t>( stats.mag, stats.mag / 2, 0, std::min<uint8_t>( stats.mag * 2, UINT8_MAX ) );
    stats.mdef = normal<uint8_t>( stats.mdef, stats.mdef / 2, 0, std::min<uint8_t>( stats.mdef * 2, UINT8_MAX ) );
    stats.agi = normal<uint8_t>( stats.agi, stats.agi / 2, 0, std::min<uint8_t>( stats.agi * 2, UINT8_MAX ) );
    stats.acc = normal<uint8_t>( stats.acc, stats.acc / 2, 0, std::min<uint8_t>( stats.acc * 2, UINT8_MAX ) );
  }
  else
  {
    stats.str = normal<uint8_t>( stats.str, stats.str / 2, 0, UINT8_MAX );
    stats.def = normal<uint8_t>( stats.def, stats.def / 2, 0, UINT8_MAX );
    stats.mag = normal<uint8_t>( stats.mag, stats.mag / 2, 0, UINT8_MAX );
    stats.mdef = normal<uint8_t>( stats.mdef, stats.mdef / 2, 0, UINT8_MAX );
    stats.agi = normal<uint8_t>( stats.agi, stats.agi / 2, 0, UINT8_MAX );
    stats.acc = normal<uint8_t>( stats.acc, stats.acc / 2, 0, UINT8_MAX );
  }
  stats.flags1.bits.armored = rand() % 4 == 0;
  stats.writeToBytes();
  enemy->stats_data = &stats;
  enemy->writeStatsData( stats );
}

void randomizer_t::addEnemyDefenses( enemy_data_t* enemy )
{
  enemy_stat_data_t& stats = *enemy->stats_data;
  if (stats.hp <= 1)
    return;
  def_pool.push_back( stats.def );
  mdef_pool.push_back( stats.mdef );
  eva_pool.push_back( stats.eva );
}

void randomizer_t::randomizeEnemyStatsDefensiveNormalization( enemy_data_t* enemy )
{
  if (enemy->monster_id == "211" || enemy->monster_id == "237")
    return;
  enemy_stat_data_t& stats = *enemy->stats_data;
  if (stats.hp <= 1)
    return;

  if (stats.mp > 0)
    stats.mp = normal<uint32_t>( stats.mp, stats.mp / 2, 1, 999 );

  stats.overkill_threshold = normal<uint32_t>( stats.overkill_threshold, stats.overkill_threshold / 2, 1, UINT32_MAX );
  stats.str = normal<uint8_t>( stats.str, stats.str / 2, 0, UINT8_MAX );

  std::uniform_int_distribution<size_t> dist( 0, def_pool.size() - 1 );
  uint8_t def = def_pool[ dist( rng ) ];
  stats.def = def;
  double def_factor = 1;
  if (def != 0)
    def_factor = ( 1.0 - ( def / 255.0 ) / 3 );

  std::uniform_int_distribution<size_t> dist2( 0, mdef_pool.size() - 1 );
  uint8_t mdef = mdef_pool[ dist2( rng ) ];
  stats.mdef = mdef;
  double mdef_factor = 1;
  if (mdef != 0)
    mdef_factor = ( 1.0 - ( mdef / 255.0 ) / 3 );

  std::uniform_int_distribution<size_t> dist3( 0, eva_pool.size() - 1 );
  uint8_t eva = eva_pool[ dist3( rng ) ];
  stats.eva = eva;
  double evasion_factor = 1;
  if (eva != 0)
    evasion_factor = ( 1.0 - ( eva / 255.0 ) / 3 );

  double defensive_factor = ( def_factor + mdef_factor + evasion_factor ) * 2;
  if (defensive_factor < 0.33)
    stats.flags1.bits.armored = 0;
  else
    stats.flags1.bits.armored = rand() % 4 == 0;

  uint32_t base_hp = 1;
  if (stats.hp > 1)
    base_hp = stats.hp * defensive_factor;
  if (base_hp <= 1)
    base_hp = 50;
  uint32_t hp = normal<uint32_t>( base_hp, base_hp / 2, 50, UINT32_MAX );
  stats.hp = hp;
  if (stats.hp < 50)
    stats.hp = 50;
  stats.mag = normal<uint8_t>( stats.mag, stats.mag / 2, 0, UINT8_MAX );
  stats.agi = normal<uint8_t>( stats.agi, stats.agi / 2, 0, UINT8_MAX );
  stats.acc = normal<uint8_t>( stats.acc, stats.acc / 2, 0, UINT8_MAX );
  enemy->loot_data->gil /= defensive_factor;
  enemy->loot_data->ap /= defensive_factor;
  stats.writeToBytes();
  enemy->stats_data = &stats;
  enemy->writeStatsData( stats );
}

void randomizer_t::shuffleEnemyStats( enemy_data_t* enemy )
{
  if (enemy->monster_id == "211" || enemy->monster_id == "237")
    return;
  enemy_stat_data_t& stats = *enemy->stats_data;
  if (stats.hp <= 1)
    return;
  // Pick a random index to pull the stats from
  std::uniform_int_distribution<size_t> dist( 0, data_pack.enemy_data.size() - 1 );
  int index = dist( rng );
  if (stats.hp > 1)
    stats.hp = normal<uint32_t>( stats.hp, stats.hp / 2, 50, UINT32_MAX );
  if (stats.hp < 50)
    stats.hp = 50;
  stats.mp = normal<uint32_t>( stats.mp, stats.mp / 2, 1, 9999 );
  stats.overkill_threshold = normal<uint32_t>( stats.overkill_threshold / 2, stats.overkill_threshold, 1, UINT32_MAX );
  stats.str = normal<uint8_t>( stats.str, stats.str / 2, 0, UINT8_MAX );
  stats.def = def_pool[ index ];
  stats.mdef = mdef_pool[ index ];
  stats.eva = eva_pool[ index ];
  stats.flags1.bits.armored = rand() % 4 == 0;
  stats.agi = normal<uint8_t>( stats.agi, stats.agi / 2, 0, UINT8_MAX );
  stats.luck = normal<uint8_t>( stats.luck, stats.luck / 2, 0, UINT8_MAX );
  stats.acc = normal<uint8_t>( stats.acc, stats.acc / 2, 0, UINT8_MAX );
  stats.writeToBytes();
  enemy->stats_data = &stats;
  enemy->writeStatsData( stats );
}

void randomizer_t::randomizeEnemyElementalAffinities( enemy_data_t* enemy )
{
  enemy_stat_data_t& stats = *enemy->stats_data;
  if (stats.hp <= 1)
    return;

  int fire_roll = uniform<int>( 0, 69 );
  int ice_roll = uniform<int>( 0, 69 );
  int lightning_roll = uniform<int>( 0, 69 );
  int water_roll = uniform<int>( 0, 69 );
  int holy_roll = uniform<int>( 0, 69 );

  stats.element_weakness_flags.bits.fire = fire_roll < 20;
  stats.element_weakness_flags.bits.ice = ice_roll < 20;
  stats.element_weakness_flags.bits.lightning = lightning_roll < 20;
  stats.element_weakness_flags.bits.water = water_roll < 20;
  stats.element_weakness_flags.bits.holy = holy_roll < 20;

  stats.element_resist_flags.bits.fire = fire_roll < 25 && fire_roll >= 20;
  stats.element_resist_flags.bits.ice = ice_roll < 25 && ice_roll >= 20;
  stats.element_resist_flags.bits.lightning = lightning_roll < 25 && lightning_roll >= 20;
  stats.element_resist_flags.bits.water = water_roll < 25 && water_roll >= 20;
  stats.element_resist_flags.bits.holy = holy_roll < 25 && holy_roll >= 20;

  stats.element_immune_flags.bits.fire = fire_roll < 30 && fire_roll >= 25;
  stats.element_immune_flags.bits.ice = ice_roll < 30 && ice_roll >= 25;
  stats.element_immune_flags.bits.lightning = lightning_roll < 30 && lightning_roll >= 25;
  stats.element_immune_flags.bits.water = water_roll < 30 && water_roll >= 25;
  stats.element_immune_flags.bits.holy = holy_roll < 30 && holy_roll >= 25;

  stats.element_absorb_flags.bits.fire = fire_roll < 35 && fire_roll >= 30;
  stats.element_absorb_flags.bits.ice = ice_roll < 35 && ice_roll >= 30;
  stats.element_absorb_flags.bits.lightning = lightning_roll < 35 && lightning_roll >= 30;
  stats.element_absorb_flags.bits.water = water_roll < 35 && water_roll >= 30;
  stats.element_absorb_flags.bits.holy = holy_roll < 35 && holy_roll >= 30;

  stats.writeToBytes();
  enemy->stats_data = &stats;
  enemy->writeStatsData( stats );
}

void randomizer_t::randomizeEnemyGearDrops( enemy_data_t* enemy )
{
  enemy_loot_data_t& loot = *enemy->loot_data;
  if (options_pack.keep_things_sane)
    loot.gear_ability_count_byte = uniform<uint8_t>( 0, 16 );
  else
    loot.gear_ability_count_byte = uniform<uint8_t>( 0, 20 );
  if (options_pack.keep_things_sane && loot.gear_drop_chance > 0)
    loot.gear_drop_chance = normal<uint8_t>( loot.gear_drop_chance, loot.gear_drop_chance / 2, 0, 101 );
  else
    loot.gear_drop_chance = uniform<uint8_t>( 0, 255 );
  if (options_pack.randomize_weapon_attack_power && loot.gear_attack_power > 0)
  {
    if (options_pack.keep_things_sane)
      loot.gear_attack_power = normal<uint8_t>( loot.gear_attack_power, loot.gear_attack_power / 2, 1, 24 );
    else
      loot.gear_attack_power = uniform<uint8_t>( 1, 100 );
  }
  if (options_pack.randomize_weapon_crit && loot.gear_crit_bonus > 0)
  {
    if (options_pack.keep_things_sane)
      loot.gear_crit_bonus = normal<uint8_t>( loot.gear_crit_bonus, loot.gear_crit_bonus / 2, 0, 100 );
    else
      loot.gear_crit_bonus = uniform<uint8_t>( 1, 100 );
  }
  if (options_pack.randomize_weapon_damage_formula && loot.gear_damage_calc > 0)
  {
    loot.gear_damage_calc = getRandomFormula();
  }

  for (int chr = 0; chr < 7; chr++)
  {
    for (int i = 0; i < 8; i++)
    {
      loot.weapon_abilities_by_char.at( chr ) = getRandomAbility();
    }
  }

  for (int chr = 0; chr < 7; chr++)
  {
    for (int i = 0; i < 8; i++)
    {
      loot.gear_abilities_by_char.at( chr ) = getRandomAbility();
    }
  }

  loot.writeToBytes();
  enemy->loot_data = &loot;
  enemy->writeLootData( loot );
}

void randomizer_t::doEnemyRandomization()
{
  if (!options_pack.randomize_enemy_drops && !options_pack.randomize_enemy_steals && !options_pack.randomize_enemy_bribes && !options_pack.randomize_enemy_gear_drops &&
       !options_pack.randomize_enemy_stats && !options_pack.randomize_enemy_stats_defensive && !options_pack.randomize_enemy_stats_shuffle &&
       !options_pack.randomize_enemy_elemental_affinities && !options_pack.swap_random_stats && !options_pack.scale_encounter_stats)
    return;

  doRandomEcnounterRandomization();

  // Generate the enemy defensive stats pool before going into the main loop
  if (options_pack.randomize_enemy_stats_defensive || options_pack.randomize_enemy_stats_shuffle)
    for (auto& enemy : data_pack.enemy_data)
      addEnemyDefenses( &enemy );

  for (auto& enemy : data_pack.enemy_data)
  {
    if (options_pack.randomize_enemy_drops)
    {
      printf( "Randomizing Enemy Drops for monster %s\n", enemy.monster_id.c_str() );
      randomizeEnemyDrops( &enemy );
    }
    if (options_pack.randomize_enemy_steals)
    {
      printf( "Randomizing Enemy Steals for monster %s\n", enemy.monster_id.c_str() );
      randomizeEnemySteal( &enemy );
    }
    if (options_pack.randomize_enemy_bribes)
    {
      printf( "Randomizing Enemy Bribes for monster %s\n", enemy.monster_id.c_str() );
      randomizeEnemyBribe( &enemy );
    }
    if (options_pack.randomize_enemy_gear_drops)
    {
      printf( "Randomizing Enemy Gear Drops for monster %s\n", enemy.monster_id.c_str() );
      randomizeEnemyGearDrops( &enemy );
    }
    if (options_pack.randomize_enemy_stats)
    {
      printf( "Randomizing Enemy Stats for monster %s\n", enemy.monster_id.c_str() );
      randomizeEnemyStatsNormal( &enemy );
    }
    if (options_pack.randomize_enemy_stats_defensive)
    {
      printf( "Randomizing Enemy Defensive for monster %s\n", enemy.monster_id.c_str() );
      randomizeEnemyStatsDefensiveNormalization( &enemy );
    }
    if (options_pack.randomize_enemy_stats_shuffle)
    {
      printf( "Shuffling Enemy Stats for monster %s\n", enemy.monster_id.c_str() );
      shuffleEnemyStats( &enemy );
    }
    if (options_pack.randomize_enemy_elemental_affinities)
    {
      printf( "Randomizing Enemy Elemental Affinities for monster %s\n", enemy.monster_id.c_str() );
      randomizeEnemyElementalAffinities( &enemy );
    }

    printf( "Reconstructing files for for monster %s\n", enemy.monster_id.c_str() );
    std::string pathstr = OUTPUT_FOLDER + prefix + MONSTER_FOLDER + "_m" + enemy.monster_id;
    std::filesystem::path path = pathstr;
    std::filesystem::create_directories( path );
    std::string filepath = pathstr + "/m" + enemy.monster_id + ".bin";
    enemy.writeBytesToNewFile( enemy.bytes, filepath );
  }
}