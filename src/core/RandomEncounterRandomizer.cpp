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
      enemy_data_t& enemy = data_pack.enemy_data.at( monster );
      enemy_stat_data_t& stats = *enemy.stats_data;
      if (stats.arena_id != 255)
        random_monster_encounter_ids.push_back( monster );
      if (std::find( boss_id_whitelist.begin(), boss_id_whitelist.end(), monster ) != boss_id_whitelist.end())
        random_monster_encounter_ids.push_back( monster );
      if (std::find( enemy_id_whitelist.begin(), enemy_id_whitelist.end(), monster ) != enemy_id_whitelist.end())
        random_monster_encounter_ids.push_back( monster );
    }
  }
}

void randomizer_t::adjustStats()
{
  if (!options_pack.swap_random_stats && !options_pack.scale_encounter_stats)
    return;

  for (auto& pair : paired_mosnter_ids)
  {
    const enemy_data_t& monster = data_pack.unmodified_enemy_data.at(pair.first);
    enemy_data_t& new_monster = data_pack.enemy_data.at(pair.second);
    const enemy_stat_data_t* stats = monster.stats_data;
    enemy_stat_data_t* new_stats = new_monster.stats_data;

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
    }

    if (options_pack.swap_random_stats || options_pack.scale_encounter_stats)
    {
      new_stats->writeToBytes();
      new_monster.stats_data = new_stats;
      new_monster.writeStatsData( *new_stats );
      // new_monster.stats_data->test();
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
