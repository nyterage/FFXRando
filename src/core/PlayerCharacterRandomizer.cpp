#include "Randomizer.hpp"

void randomizer_t::reconstructPlayerStatsData()
{
  for (auto& locale : LOCALIZATIONS)
  {
    std::string path = INPUT_FOLDER + locale.second + "ply_save.bin";
    std::vector<char> original_bytes = bytes_mapper_t::fileToBytes( path );
    for (size_t j = 0; j < data_pack.player_stats_data.size(); j++)
    {
      character_stats_t& player_stats = *data_pack.player_stats_data[ j ];
      std::vector<char> player_stats_bytes = player_stats.bytes;
      for (size_t i = 0; i < player_stats_bytes.size(); i++)
      {
        original_bytes[ 20 + j * player_stats_bytes.size() + i ] = player_stats_bytes[ i ];
      }
    }
    std::string output_path = OUTPUT_FOLDER + prefix + locale.second;
    std::filesystem::create_directories( output_path );
    std::string file = output_path + "ply_save.bin";
    bytes_mapper_t::writeBytesToNewFile( original_bytes, file );
  }
}

void randomizer_t::reconstructAeonScalingData()
{
  for (auto& locale : LOCALIZATIONS)
  {
    std::string path = INPUT_FOLDER + locale.second + "ply_rom.bin";
    std::vector<char> original_bytes = bytes_mapper_t::fileToBytes( path );
    for (size_t j = 0; j < data_pack.aeon_scaling_data.size(); j++)
    {
      aeon_scaling_data_t& aeon_scaling = *data_pack.aeon_scaling_data[ j ];
      std::vector<char> aeon_scaling_bytes = aeon_scaling.bytes;
      for (size_t i = 0; i < aeon_scaling_bytes.size(); i++)
      {
        original_bytes[ 20 + j * aeon_scaling_bytes.size() + i ] = aeon_scaling_bytes[ i ];
      }
    }
    std::string output_path = OUTPUT_FOLDER + prefix + locale.second;
    std::filesystem::create_directories( output_path );
    std::string file = output_path + "ply_rom.bin";
    bytes_mapper_t::writeBytesToNewFile( original_bytes, file );
  }
}

void randomizer_t::reconstructAeonStatData()
{
  std::string path = INPUT_FOLDER + BATTLE_KERNEL_FOLDER + "sum_assure.bin";
  std::vector<char> original_bytes = bytes_mapper_t::fileToBytes( path );
  for (size_t j = 0; j < data_pack.aeon_stat_data.size(); j++)
  {
    aeon_stat_data_t& aeon_stats = *data_pack.aeon_stat_data[ j ];
    std::vector<char> aeon_stat_bytes = aeon_stats.bytes;
    for (size_t i = 0; i < aeon_stat_bytes.size(); i++)
    {
      original_bytes[ 20 + j * aeon_stat_bytes.size() + i ] = aeon_stat_bytes[ i ];
    }
  }
  std::string output_path = OUTPUT_FOLDER + prefix + BATTLE_KERNEL_FOLDER;
  std::filesystem::create_directories( output_path );
  std::string file = output_path + "sum_assure.bin";
  bytes_mapper_t::writeBytesToNewFile( original_bytes, file );
}

void randomizer_t::randomizePlayerStats()
{
  for (int i = 0; i < 7; i++)
  {
    character_stats_t& stats = *data_pack.player_stats_data[ i ];
    stats.base_hp = normal<uint32_t>( stats.base_hp, stats.base_hp / 2, 50, 9999 );
    if (stats.base_hp < 50)
      stats.base_hp = 50;
    stats.base_mp = normal<uint32_t>( stats.base_mp, stats.base_mp / 2, 1, 999 );
    bool tidus_or_auron = i == 0 || i == 2;
    stats.base_str = normal<uint8_t>( stats.base_str, stats.base_str / 2, tidus_or_auron ? 14 : 0, stats.base_str * 3 );
    stats.base_def = normal<uint8_t>( stats.base_def, stats.base_def / 2, 0, stats.base_def * 3 );
    stats.base_mag = normal<uint8_t>( stats.base_mag, stats.base_mag / 2, 0, stats.base_mag * 3 );
    stats.base_mdef = normal<uint8_t>( stats.base_mdef, stats.base_mdef / 2, 0, stats.base_mdef * 3 );
    stats.base_agi = normal<uint8_t>( stats.base_agi, stats.base_agi / 2, 0, stats.base_agi * 3 );
    stats.base_acc = normal<uint8_t>( stats.base_acc, stats.base_acc / 2, 0, stats.base_acc * 3 );
    stats.base_luck = normal<uint8_t>( stats.base_luck, stats.base_luck / 2, 0, stats.base_luck * 3 );
    stats.current_ap = normal<uint16_t>( stats.current_ap, stats.current_ap / 2, 0, UINT16_MAX );
    stats.current_hp = normal<uint32_t>( stats.current_hp, stats.current_hp / 2, 1, 9999 );
    stats.current_mp = normal<uint32_t>( stats.current_mp, stats.current_mp / 2, 1, 999 );
    stats.max_hp = stats.base_hp;
    stats.max_mp = stats.base_mp;
    stats.str = normal<uint8_t>( stats.str, stats.str / 2, 0, stats.str * 3 );
    stats.def = normal<uint8_t>( stats.def, stats.def / 2, 0, stats.def * 3 );
    stats.mag = normal<uint8_t>( stats.mag, stats.mag / 2, 0, stats.mag * 3 );
    stats.mdef = normal<uint8_t>( stats.mdef, stats.mdef / 2, 0, stats.mdef * 3 );
    stats.agi = normal<uint8_t>( stats.agi, stats.agi / 2, 0, stats.agi * 3 );
    stats.acc = normal<uint8_t>( stats.acc, stats.acc / 2, 0, stats.acc * 3 );
    stats.luck = normal<uint8_t>( stats.luck, stats.luck / 2, 0, stats.luck * 3 );
    stats.writeToBytes();
  }
}

void randomizer_t::shuffleCharacterStats()
{
  for (int i = 0; i < 7; i++)
  {
    character_stats_t& stats = *data_pack.player_stats_data[ i ];
    character_stats_t& new_stats = *shuffled_player_stats_data[ i ];
    stats.base_hp = new_stats.base_hp;
    stats.base_mp = new_stats.base_mp;
    if (( i == 0 || i == 2 ) && new_stats.base_str < 14)
      new_stats.base_str = 14;
    stats.base_str = new_stats.base_str;
    stats.base_def = new_stats.base_def;
    stats.base_mag = new_stats.base_mag;
    stats.base_mdef = new_stats.base_mdef;
    stats.base_agi = new_stats.base_agi;
    stats.base_acc = new_stats.base_acc;
    stats.base_luck = new_stats.base_luck;
    stats.current_ap = new_stats.current_ap;
    stats.current_hp = new_stats.current_hp;
    stats.current_mp = new_stats.current_mp;
    stats.max_hp = new_stats.max_hp;
    stats.max_mp = new_stats.max_mp;
    stats.str = new_stats.str;
    stats.def = new_stats.def;
    stats.mag = new_stats.mag;
    stats.mdef = new_stats.mdef;
    stats.agi = new_stats.agi;
    stats.acc = new_stats.acc;
    stats.luck = new_stats.luck;
    stats.writeToBytes();
  }
}

void randomizer_t::randomizeAeonStatScaling()
{
  for (auto& aeon : data_pack.aeon_scaling_data)
  {
    if (!aeon->is_yuna_summon)
      continue;
    aeon->ap_req_coef1 = normal<uint16_t>( aeon->ap_req_coef1, aeon->ap_req_coef1 / 2, 0, UINT16_MAX );
    aeon->ap_req_coef2 = normal<uint16_t>( aeon->ap_req_coef2, aeon->ap_req_coef2 / 2, 0, UINT16_MAX );
    aeon->ap_req_coef3 = normal<uint16_t>( aeon->ap_req_coef3, aeon->ap_req_coef3 / 2, 0, UINT16_MAX );
    aeon->ap_req_max = normal<uint16_t>( aeon->ap_req_max, aeon->ap_req_max / 2, 0, UINT16_MAX );
    aeon->hp_coef1 = normal<uint16_t>( aeon->hp_coef1, aeon->hp_coef1 / 2, 0, UINT16_MAX );
    aeon->hp_coef2 = normal<uint16_t>( aeon->hp_coef2, aeon->hp_coef2 / 2, 0, UINT16_MAX );
    aeon->mp_coef1 = normal<uint16_t>( aeon->mp_coef1, aeon->mp_coef1 / 2, 0, UINT16_MAX );
    aeon->mp_coef2 = normal<uint16_t>( aeon->mp_coef2, aeon->mp_coef2 / 2, 0, UINT16_MAX );
    aeon->str_coef1 = normal<uint16_t>( aeon->str_coef1, aeon->str_coef1 / 2, 0, UINT16_MAX );
    aeon->str_coef2 = normal<uint16_t>( aeon->str_coef2, aeon->str_coef2 / 2, 0, UINT16_MAX );
    aeon->def_coef1 = normal<uint16_t>( aeon->def_coef1, aeon->def_coef1 / 2, 0, UINT16_MAX );
    aeon->def_coef2 = normal<uint16_t>( aeon->def_coef2, aeon->def_coef2 / 2, 0, UINT16_MAX );
    aeon->mag_coef1 = normal<uint16_t>( aeon->mag_coef1, aeon->mag_coef1 / 2, 0, UINT16_MAX );
    aeon->mag_coef2 = normal<uint16_t>( aeon->mag_coef2, aeon->mag_coef2 / 2, 0, UINT16_MAX );
    aeon->mdef_coef1 = normal<uint16_t>( aeon->mdef_coef1, aeon->mdef_coef1 / 2, 0, UINT16_MAX );
    aeon->mdef_coef2 = normal<uint16_t>( aeon->mdef_coef2, aeon->mdef_coef2 / 2, 0, UINT16_MAX );
    aeon->agi_coef1 = normal<uint16_t>( aeon->agi_coef1, aeon->agi_coef1 / 2, 0, UINT16_MAX );
    aeon->agi_coef2 = normal<uint16_t>( aeon->agi_coef2, aeon->agi_coef2 / 2, 0, UINT16_MAX );
    aeon->acc_coef1 = normal<uint16_t>( aeon->acc_coef1, aeon->acc_coef1 / 2, 0, UINT16_MAX );
    aeon->acc_coef2 = normal<uint16_t>( aeon->acc_coef2, aeon->acc_coef2 / 2, 0, UINT16_MAX );
    aeon->writeToBytes();
  }
}

void randomizer_t::randomizeAeonBaseStats()
{
  for (auto& aeon : data_pack.aeon_stat_data)
  {
    aeon->hp = normal<uint32_t>( aeon->hp, aeon->hp / 2, 50, 99999 );
    aeon->mp = normal<uint32_t>( aeon->mp, aeon->mp / 2, 1, 9999 );
    aeon->str = normal<uint8_t>( aeon->str, aeon->str / 2, 0, UINT8_MAX );
    aeon->def = normal<uint8_t>( aeon->def, aeon->def / 2, 0, UINT8_MAX );
    aeon->mag = normal<uint8_t>( aeon->mag, aeon->mag / 2, 0, UINT8_MAX );
    aeon->mdef = normal<uint8_t>( aeon->mdef, aeon->mdef / 2, 0, UINT8_MAX );
    aeon->agi = normal<uint8_t>( aeon->agi, aeon->agi / 2, 0, UINT8_MAX );
    aeon->acc = normal<uint8_t>( aeon->acc, aeon->acc / 2, 0, UINT8_MAX );
    aeon->writeToBytes();
  }
}

void randomizer_t::shuffleAeonStatScaling()
{
  int idx = 0;
  for (auto& aeon_sd : data_pack.aeon_scaling_data)
  {
    aeon_scaling_data_t& aeon = *aeon_sd;
    if (!aeon.is_yuna_summon)
      continue;
    aeon_scaling_data_t& shuffled_aeon = *shuffled_aeon_scaling_data[ idx ];
    idx++;
    aeon.bytes = shuffled_aeon.bytes;
  }
}

void randomizer_t::shuffleAeonBaseStats()
{
  std::shuffle( data_pack.aeon_stat_data.begin(), data_pack.aeon_stat_data.end(), rng );
  for (size_t i = 0; i < data_pack.aeon_stat_data.size(); i++)
  {
    aeon_stat_data_t& aeon = *data_pack.aeon_stat_data[ i ];
    aeon_stat_data_t& shuffled_aeon = *data_pack.aeon_stat_data[ i ];
    aeon.bytes = shuffled_aeon.bytes;
  }
}

void randomizer_t::doPlayerStatRandomization()
{
  if (!options_pack.randomize_player_stats && !options_pack.randomize_aeon_stat_scaling && !options_pack.shuffle_player_stats &&
       !options_pack.shuffle_aeon_stat_scaling && !options_pack.poison_is_deadly && !options_pack.randomize_starting_overdrive_mode &&
       !options_pack.shuffle_sphere_grid && !options_pack.randomize_sphere_grid)
    return;

  if (options_pack.randomize_player_stats)
  {
    printf( "Randomizing Party Stats...\n" );
    randomizePlayerStats();
  }

  if (options_pack.randomize_aeon_stat_scaling)
  {
    printf( "Randomizing Aeon Stat Scaling...\n" );
    randomizeAeonStatScaling();
  }

  if (options_pack.randomize_aeon_base_stats)
  {
    printf( "Randomizing Aeon Base Stats...\n" );
    randomizeAeonBaseStats();
  }

  if (options_pack.shuffle_player_stats)
  {
    for (int i = 0; i < 7; i++)
    {
      character_stats_t* stats = data_pack.player_stats_data[ i ];
      shuffled_player_stats_data.push_back( stats );
    }
    std::shuffle( shuffled_player_stats_data.begin(), shuffled_player_stats_data.end(), rng );
    printf( "Shuffling Party Stats...\n" );
    shuffleCharacterStats();
  }

  if (options_pack.shuffle_aeon_stat_scaling)
  {
    printf( "Shuffling Aeon Stat Scaling...\n" );
    for (auto& aeon_scaling_data : data_pack.aeon_scaling_data)
    {
      if (!aeon_scaling_data->is_yuna_summon)
        continue;
      shuffled_aeon_scaling_data.push_back( aeon_scaling_data );
      std::shuffle( shuffled_aeon_scaling_data.begin(), shuffled_aeon_scaling_data.end(), rng );
    }
    shuffleAeonStatScaling();
  }

  if (options_pack.shuffle_aeon_base_stats)
  {
    printf( "Shuffling Aeon Base Stats...\n" );
    shuffleAeonBaseStats();
  }

  if (options_pack.poison_is_deadly)
  {
    printf( "Making Poison Deadly...\n" );
    for (auto& stats : data_pack.player_stats_data)
    {
      stats->poison_damage = 50;
      stats->writeToBytes();
    }
  }

  if (options_pack.randomize_starting_overdrive_mode)
  {
    printf( "Randomizing Starting Overdrive Mode...\n" );
    for (int i = 0; i < 7; i++)
    {
      character_stats_t& stats = *data_pack.player_stats_data.at( i );
      if (i == ply_save_e::CHARACTER_AURON)
        continue; // Auron's overdrive mode is always 2
      uint8_t overdrive_mode = uniform<uint8_t>( 0, 16 );
      stats.overdrive_current = overdrive_mode;
      stats.overdrive_mode = overdrive_mode;
      if (overdrive_mode != 2)
        stats.overdrive.bits.stoic = 0;

      switch (overdrive_mode)
      {
        case 0:
          stats.overdrive.bits.warrior = 1;
          break;
        case 1:
          stats.overdrive.bits.comrade = 1;
          break;
        case 2:
          stats.overdrive.bits.stoic = 1;
          break;
        case 3:
          stats.overdrive.bits.healer = 1;
          break;
        case 4:
          stats.overdrive.bits.tactician = 1;
          break;
        case 5:
          stats.overdrive.bits.victim = 1;
          break;
        case 6:
          stats.overdrive.bits.dancer = 1;
          break;
        case 7:
          stats.overdrive.bits.avenger = 1;
          break;
        case 8:
          stats.overdrive.bits.slayer = 1;
          break;
        case 9:
          stats.overdrive.bits.hero = 1;
          break;
        case 10:
          stats.overdrive.bits.rook = 1;
          break;
        case 11:
          stats.overdrive.bits.victor = 1;
          break;
        case 12:
          stats.overdrive.bits.coward = 1;
          break;
        case 13:
          stats.overdrive.bits.ally = 1;
          break;
        case 14:
          stats.overdrive.bits.sufferer = 1;
          break;
        case 15:
          stats.overdrive.bits.daredevil = 1;
          break;
        case 16:
          stats.overdrive.bits.loner = 1;
          break;
      }
      stats.writeToBytes();
      // stats.test();
    }
  }

  printf( "Reconstructing ply_save.bin...\n" );
  reconstructPlayerStatsData();

  if (options_pack.randomize_aeon_stat_scaling || options_pack.shuffle_aeon_stat_scaling)
  {
    printf( "Reconstructing ply_rom.bin...\n" );
    reconstructAeonScalingData();
  }

  if (options_pack.randomize_aeon_base_stats || options_pack.shuffle_aeon_base_stats)
  {
    printf( "Reconstructing sum_assure.bin...\n" );
    reconstructAeonStatData();
  }
}