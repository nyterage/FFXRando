#include "Randomizer.hpp"

void randomizer_t::getRandomEncounterIDs()
{
  for (auto& encounter : data_pack.encounter_files)
  {
    for (auto& monster : encounter->formation->monster_ids)
    {
      if (monster == ( 0xFFFF - 0x1000 ) )
        continue;
      bool found = std::find( random_monster_encounter_ids.begin(), random_monster_encounter_ids.end(), monster ) != random_monster_encounter_ids.end();
      if (found)
        continue;
      enemy_data_t& enemy = data_pack.enemy_data[ monster ];
      enemy_stat_data_t& stats = *enemy.stats_data;
      if (stats.arena_id == 255 && std::find( enemy_id_whitelist.begin(), enemy_id_whitelist.end(), monster ) == enemy_id_whitelist.end() &&
           std::find( boss_id_whitelist.begin(), boss_id_whitelist.end(), monster ) == boss_id_whitelist.end())
        continue;
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
    const enemy_data_t& monster = data_pack.unmodified_enemy_data.at( pair.first );
    enemy_data_t& new_monster = data_pack.enemy_data.at( pair.second );
    const enemy_stat_data_t* stats = monster.stats_data;
    enemy_stat_data_t* new_stats = new_monster.stats_data;

    if (options_pack.scale_encounter_stats)
    {
      float monster_stats_total = stats->str + stats->def + stats->mag + stats->mdef + stats->agi + stats->acc + stats->eva + stats->luck;
      float new_monster_stats_total = new_stats->str + new_stats->def + new_stats->mag + new_stats->mdef + new_stats->agi + new_stats->acc + new_stats->eva + new_stats->luck;
      if (new_monster_stats_total == 0)
        new_stats->test();
      if (monster_stats_total == 0)
        stats->test();

      float delta = monster_stats_total / new_monster_stats_total;

      if (delta <= 0.1)
      {
        printf( "Original Monster stat total: %d\n", monster_stats_total );
        printf( "New Monster stat total: %d\n", new_monster_stats_total );
        printf( "Delta: %f\n", delta );
      }

      new_stats->hp = std::max<uint32_t>( std::ceil( stats->hp * delta ), 150 );
      new_stats->mp = std::max<uint32_t>( std::ceil( stats->mp * delta ), 25 );
      new_stats->str = std::max<uint8_t>( std::ceil( stats->str * delta ), 0 );
      new_stats->def = std::max<uint8_t>( std::ceil( stats->def * delta ), 0 );
      new_stats->mag = std::max<uint8_t>( std::ceil( stats->mag * delta ), 0 );
      new_stats->mdef = std::max<uint8_t>( std::ceil( stats->mdef * delta ), 0 );
      new_stats->agi = std::max<uint8_t>( std::ceil( stats->agi * delta ), 0 );
      new_stats->acc = std::max<uint8_t>( std::ceil( stats->acc * delta ), 0 );
      new_stats->eva = std::max<uint8_t>( std::ceil( stats->eva * delta ), 0 );
      new_stats->luck = std::max<uint8_t>( std::ceil( stats->luck * delta ), 0 );
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
