#include "Randomizer.hpp"

void randomizer_t::getRandomEncounterIDs()
{
  for (auto& encounter : data_pack.encounter_files)
  {
    for (auto& monster : encounter->formation->monster_ids)
    {
      if (monster == ( 0xFFFF - 0x1000 ))
        continue;
      if (std::find( random_monster_encounter_ids.begin(), random_monster_encounter_ids.end(), monster ) != random_monster_encounter_ids.end())
        continue;
      enemy_data_t& enemy = *data_pack.enemy_data.at( monster );
      enemy_stat_data_t& stats = *enemy.stats_data;
      if (stats.arena_id != 255 && ( stats.arena_id != 0 || monster == 1 ) )
      {
        random_monster_encounter_ids.push_back( monster );
        continue;
      }
      bool in_boss_list = std::find( boss_id_whitelist.begin(), boss_id_whitelist.end(), monster ) != boss_id_whitelist.end();
      if (in_boss_list)
      {
        random_monster_encounter_ids.push_back( monster );
        continue;
      }
      bool in_whitelist = std::find( enemy_id_whitelist.begin(), enemy_id_whitelist.end(), monster ) != enemy_id_whitelist.end();
      if (in_whitelist)
      {
        random_monster_encounter_ids.push_back( monster );
        continue;
      }
    }
  }
}

void randomizer_t::adjustStats()
{
  if (!options_pack.swap_random_stats && !options_pack.scale_encounter_stats)
    return;

  for (auto& pair : paired_mosnter_ids)
  {
    if (pair.second == 211)
      continue;
    const enemy_data_t& monster = *data_pack.unmodified_enemy_data.at(pair.first);
    enemy_data_t& new_monster = *data_pack.enemy_data.at(pair.second);
    const enemy_stat_data_t* stats = monster.stats_data;
    enemy_stat_data_t* new_stats = new_monster.stats_data;
    const enemy_loot_data_t* loot = monster.loot_data;
    enemy_loot_data_t* new_loot = new_monster.loot_data;

    if (options_pack.scale_encounter_stats)
    {
      float old_hp = stats->hp;
      float new_hp = new_stats->hp;
      float hp = std::ceil( old_hp * std::pow( std::pow( new_hp, 1 / 3.2 ) / std::pow( old_hp, 1 / 3.2 ), 1 / 3.2 ) / 25 ) * 25;
      new_stats->hp = std::clamp( static_cast< unsigned int >( hp ), std::min( stats->hp, new_stats->hp ), std::max( stats->hp, new_stats->hp ) );

      float old_mp = stats->mp;
      float new_mp = new_stats->mp;
      float mp = std::ceil( stats->mp * std::sqrt( std::sqrt( new_stats->mp ) / std::sqrt( stats->mp ) ) / 5 ) * 5;
      new_stats->mp = std::clamp( static_cast< unsigned int >( mp ), std::min( stats->mp, new_stats->mp ), std::max( stats->mp, new_stats->mp ) );

      float old_str = stats->str;
      float new_str = new_stats->str;
      float str = std::ceil( stats->str * std::sqrt( new_stats->str ) / std::sqrt( stats->str ) );
      new_stats->str = std::clamp( static_cast< uint8_t >( str ), std::min( stats->str, new_stats->str ), std::max( stats->str, new_stats->str ) );

      float old_mag = stats->mag;
      float new_mag = new_stats->mag;
      float mag = std::ceil( stats->mag * std::sqrt( new_stats->mag ) / std::sqrt( stats->mag ) );
      new_stats->mag = std::clamp( static_cast< uint8_t >( mag ), std::min( stats->mag, new_stats->mag ), std::max( stats->mag, new_stats->mag ) );

      float old_agi = stats->agi;
      float new_agi = new_stats->agi;
      float agi = std::ceil( stats->agi * std::sqrt( new_stats->agi ) / std::sqrt( stats->agi ) );
      new_stats->agi = std::clamp( static_cast< uint8_t >( agi ), std::min( stats->agi, new_stats->agi ), std::max( stats->agi, new_stats->agi ) );

      float old_acc = stats->acc;
      float new_acc = new_stats->acc;
      float acc = std::ceil( stats->acc * std::sqrt( new_stats->acc ) / std::sqrt( stats->acc ) );
      new_stats->acc = std::clamp( static_cast< uint8_t >( acc ), std::min( stats->acc, new_stats->acc ), std::max( stats->acc, new_stats->acc ) );

      float old_luck = stats->luck;
      float new_luck = new_stats->luck;
      float luck = std::ceil( stats->luck * std::sqrt( new_stats->luck ) / std::sqrt( stats->luck ) );
      new_stats->luck = std::clamp( static_cast< uint8_t >( luck ), std::min( stats->luck, new_stats->luck ), std::max( stats->luck, new_stats->luck ) );

      float old_ap = loot->ap;
      float new_ap = new_loot->ap;
      float ap = std::ceil( loot->ap * std::pow( std::pow( new_ap, 1 / 3.2 ) / std::pow( old_ap, 1 / 3.2 ), 1 / 3.2 ) );
      new_loot->ap = std::clamp( static_cast< uint16_t >( ap ), std::min( loot->ap, new_loot->ap ), std::max( loot->ap, new_loot->ap ) );

      float old_overkill_ap = loot->ap_overkill;
      float new_overkill_ap = new_loot->ap_overkill;
      float overkill_ap = std::ceil( loot->ap_overkill * std::pow( std::pow( new_overkill_ap, 1 / 3.2 ) / std::pow( old_overkill_ap, 1 / 3.2 ), 1 / 3.2 ) );
      new_loot->ap_overkill = std::clamp( static_cast< uint16_t >( overkill_ap ), std::min( loot->ap_overkill, new_loot->ap_overkill ), std::max( loot->ap_overkill, new_loot->ap_overkill ) );

      float old_gil = loot->gil;
      float new_gil = new_loot->gil;
      float gil = std::ceil( loot->gil * std::pow( std::pow( new_gil, 1 / 3.2 ) / std::pow( old_gil, 1 / 3.2 ), 1 / 3.2 ) );
      new_loot->gil = std::clamp( static_cast< uint16_t >( gil ), std::min( loot->gil, new_loot->gil ), std::max( loot->gil, new_loot->gil ) );
    }

    if (options_pack.swap_random_stats)
    {
      new_stats->hp = stats->hp;
      new_stats->mp = stats->mp;
      new_stats->str = stats->str;
      new_stats->def = stats->def;
      new_stats->mag = stats->mag;
      new_stats->mdef = stats->mdef;
      new_stats->agi = stats->agi;
      new_stats->acc = stats->acc;
      new_stats->eva = stats->eva;
      new_stats->luck = stats->luck;
      new_loot->ap = loot->ap;
      new_loot->ap_overkill = loot->ap_overkill;
      new_loot->gil = loot->gil;
    }

    if (options_pack.swap_random_stats || options_pack.scale_encounter_stats)
    {
      new_stats->writeToBytes();
      new_monster.stats_data = new_stats;
      new_monster.writeStatsData( *new_stats );

      new_loot->writeToBytes();
      new_monster.loot_data = new_loot;
      new_monster.writeLootData( *new_loot );
    }
  }
}

void randomizer_t::randomizeEncounters( encounter_file_t& encounter )
{
  formation_data_t& formation_data = *encounter.formation;
  for (auto& mon : formation_data.monster_ids)
  {
    std::unordered_map<uint16_t, uint16_t>::iterator it = paired_mosnter_ids.find( mon );
    bool found = it != paired_mosnter_ids.end();
    if (!found)
      continue;

    mon = it->second;
  }
}

void randomizer_t::doRandomEcnounterRandomization()
{
  if (!options_pack.randomize_encounters)
    return;

  shuffled_random_monster_encounter_ids.clear();
  shuffled_random_monster_encounter_ids = random_monster_encounter_ids;
  std::shuffle( shuffled_random_monster_encounter_ids.begin(), shuffled_random_monster_encounter_ids.end(), rng );

  for (int i = 0; i < random_monster_encounter_ids.size(); i++)
  {
    paired_mosnter_ids.insert( std::make_pair( random_monster_encounter_ids[ i ], shuffled_random_monster_encounter_ids[ i ] ) );
  }
  printf( "Adjusting Random Ecnounter Stats...\n" );
  adjustStats();

  printf( "Randomizing Encounters...\n" );
  for (auto& encounter : data_pack.encounter_files)
  {
    encounter_file_t& encounter_file = *encounter;

    randomizeEncounters( encounter_file );

    encounter_file.writeFormationData();
    std::string pathstr = OUTPUT_FOLDER + prefix + BTL_FOLDER + encounter_file.name;
    std::filesystem::path path = pathstr;
    std::filesystem::create_directories( path );
    std::string filepath = pathstr + "/" + encounter_file.name + ".bin";
    encounter_file.writeBytesToNewFile( encounter_file.bytes, filepath );
  }
}
