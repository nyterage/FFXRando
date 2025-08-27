#include "Data.hpp"

void gear_data_t::mapBytesNormal() {
  byte00_name_id_maybe = read1Byte( bytes, 0x00 );
  byte01_name_id_maybe = read1Byte( bytes, 0x01 );
  byte02_exists_maybe = read1Byte( bytes, 0x02 );
  misc_flags = read1Byte( bytes, 0x03 );
  character_id = read1Byte( bytes, 0x04 );
  armor_byte = read1Byte( bytes, 0x05 );
  byte06_equipper_maybe = read1Byte( bytes, 0x06 );
  byte07_equipper_maybe = read1Byte( bytes, 0x07 );
  damage_calc = read1Byte( bytes, 0x08 );
  attack_power = read1Byte( bytes, 0x09 );
  crit_bonus = read1Byte( bytes, 0x0A );
  slots = read1Byte( bytes, 0x0B );
  model_id = read2Bytes( bytes, 0x0C );
  ability_slot1 = read2Bytes( bytes, 0x0E );
  ability_slot2 = read2Bytes( bytes, 0x10 );
  ability_slot3 = read2Bytes( bytes, 0x12 );
  ability_slot4 = read2Bytes( bytes, 0x14 );
}

void gear_data_t::mapBytesBukiGet() {
  misc_flags = read1Byte( bytes, 0x00 );
  character_id = read1Byte( bytes, 0x01 );
  armor_byte = read1Byte( bytes, 0x02 );
  byte03_constant_zero = read1Byte( bytes, 0x03 );
  damage_calc = read1Byte( bytes, 0x04 );
  attack_power = read1Byte( bytes, 0x05 );
  crit_bonus = read1Byte( bytes, 0x06 );
  slots = read1Byte( bytes, 0x07 );
  ability_slot1 = read2Bytes( bytes, 0x08 );
  ability_slot2 = read2Bytes( bytes, 0x0A );
  ability_slot3 = read2Bytes( bytes, 0x0C );
  ability_slot4 = read2Bytes( bytes, 0x0E );
}

void gear_data_t::writeBytesNormal()
{
  write1Byte( bytes, 0x00, byte00_name_id_maybe );
  write1Byte( bytes, 0x01, byte01_name_id_maybe );
  write1Byte( bytes, 0x02, byte02_exists_maybe );
  write1Byte( bytes, 0x03, misc_flags );
  write1Byte( bytes, 0x04, character_id );
  write1Byte( bytes, 0x05, armor_byte );
  write1Byte( bytes, 0x06, byte06_equipper_maybe );
  write1Byte( bytes, 0x07, byte07_equipper_maybe );
  write1Byte( bytes, 0x08, damage_calc );
  write1Byte( bytes, 0x09, attack_power );
  write1Byte( bytes, 0x0A, crit_bonus );
  write1Byte( bytes, 0x0B, slots );
  write2Bytes( bytes, 0x0C, model_id );
  write2Bytes( bytes, 0x0E, ability_slot1 );
  write2Bytes( bytes, 0x10, ability_slot2 );
  write2Bytes( bytes, 0x12, ability_slot3 );
  write2Bytes( bytes, 0x14, ability_slot4 );
}

void gear_data_t::writeBytesBukiGet()
{
  write1Byte( bytes, 0x00, misc_flags );
  write1Byte( bytes, 0x01, character_id );
  write1Byte( bytes, 0x02, armor_byte );
  write1Byte( bytes, 0x03, byte03_constant_zero );
  write1Byte( bytes, 0x04, damage_calc );
  write1Byte( bytes, 0x05, attack_power );
  write1Byte( bytes, 0x06, crit_bonus );
  write1Byte( bytes, 0x07, slots );
  write2Bytes( bytes, 0x08, ability_slot1 );
  write2Bytes( bytes, 0x0A, ability_slot2 );
  write2Bytes( bytes, 0x0C, ability_slot3 );
  write2Bytes( bytes, 0x0E, ability_slot4 );
}

void gear_data_t::writeToBytes()
{
  if (is_buki_get)
    writeBytesBukiGet();
  else
    writeBytesNormal();
}

void gear_data_t::mapFlags() {
  is_armor = armor_byte != 0;
  is_flag1 = ( misc_flags & 0x01 ) > 0;
  is_hidden_in_menu = ( misc_flags & 0x02 ) > 0;
  is_celestial = ( misc_flags & 0x04 ) > 0;
  is_brotherhood = ( misc_flags & 0x08 ) > 0;
  is_unknown_flag = misc_flags >= 0x10;
}

void gear_data_t::test() const
{
  bytes_mapper_t::test();
  printf( "Is Buki Get: %d\n", is_buki_get );
  printf( "Is Armor: %d\n", is_armor );
  printf( "Is Flag 1: %d\n", is_flag1 );
  printf( "Is Hidden in Menu: %d\n", is_hidden_in_menu );
  printf( "Is Celestial: %d\n", is_celestial );
  printf( "Is Brotherhood: %d\n", is_brotherhood );
  printf( "Is Unknown Flag: %d\n", is_unknown_flag );
  if (!is_buki_get)
  {
    printf( "Byte 00 Name ID Maybe: %d\n", byte00_name_id_maybe );
    printf( "Byte 01 Name ID Maybe: %d\n", byte01_name_id_maybe );
    printf( "Byte 02 Exists Maybe: %d\n", byte02_exists_maybe );
    printf( "Misc Flags: %d\n", misc_flags );
    printf( "Character ID: %d\n", character_id );
    printf( "Armor Byte: %d\n", armor_byte );
    printf( "Byte 06 Equipper Maybe: %d\n", byte06_equipper_maybe );
    printf( "Byte 07 Equipper Maybe: %d\n", byte07_equipper_maybe );
    printf( "Damage Calc: %d\n", damage_calc );
    printf( "Attack Power: %d\n", attack_power );
    printf( "Crit Bonus: %d\n", crit_bonus );
    printf( "Slots: %d\n", slots );
    printf( "Model ID: %d\n", model_id );
    printf( "Ability Slot 1: %d\n", ability_slot1 );
    printf( "Ability Slot 2: %d\n", ability_slot2 );
    printf( "Ability Slot 3: %d\n", ability_slot3 );
    printf( "Ability Slot 4: %d\n", ability_slot4 );
  }
  else
  {
    printf( "Misc Flags: %d\n", misc_flags );
    printf( "Character ID: %d\n", character_id );
    printf( "Armor Byte: %d\n", armor_byte );
    printf( "Byte 03 Constant Zero: %d\n", byte03_constant_zero );
    printf( "Damage Calc: %d\n", damage_calc );
    printf( "Attack Power: %d\n", attack_power );
    printf( "Crit Bonus: %d\n", crit_bonus );
    printf( "Slots: %d\n", slots );
    printf( "Ability Slot 1: %d\n", ability_slot1 );
    printf( "Ability Slot 2: %d\n", ability_slot2 );
    printf( "Ability Slot 3: %d\n", ability_slot3 );
    printf( "Ability Slot 4: %d\n", ability_slot4 );
  }
}

void gear_data_t::mapAbilities( std::vector<uint16_t>& abilities )
{
  if (ability_slot1 != 0 && ability_slot1 != UINT8_MAX && ability_slot1 != UINT16_MAX)
  {
    bool found = std::find( abilities.begin(), abilities.end(), ability_slot1 ) != abilities.end();
    if (!found)
      abilities.push_back( ability_slot1 );
  }
  if (ability_slot2 != 0 && ability_slot2 != UINT8_MAX && ability_slot2 != UINT16_MAX)
  {
    bool found = std::find( abilities.begin(), abilities.end(), ability_slot2 ) != abilities.end();
    if (!found)
      abilities.push_back( ability_slot2 );
  }
  if (ability_slot3 != 0 && ability_slot3 != UINT8_MAX && ability_slot3 != UINT16_MAX)
  {
    bool found = std::find( abilities.begin(), abilities.end(), ability_slot3 ) != abilities.end();
    if (!found)
      abilities.push_back( ability_slot3 );
  }
  if (ability_slot4 != 0 && ability_slot4 != UINT8_MAX && ability_slot4 != UINT16_MAX)
  {
    bool found = std::find( abilities.begin(), abilities.end(), ability_slot4 ) != abilities.end();
    if (!found)
      abilities.push_back( ability_slot4 );
  }
}

void gear_data_t::mapFormulas( std::vector<uint8_t>& formulas )
{
  if (!is_armor)
  {
    bool found = std::find( formulas.begin(), formulas.end(), damage_calc ) != formulas.end();
    if (!found)
      formulas.push_back( damage_calc );
  }
}

void enemy_loot_data_t::mapBytes() {
  gil = read2Bytes( bytes, 0x00 );
  ap = read2Bytes( bytes, 0x02 );
  ap_overkill = read2Bytes( bytes, 0x04 );
  ronso_rage = read2Bytes( bytes, 0x06 );
  primary_drop_chance = read1Byte( bytes, 0x08 );
  secondary_drop_chance = read1Byte( bytes, 0x09 );
  steal_chance = read1Byte( bytes, 0x0A );
  gear_drop_chance = read1Byte( bytes, 0x0B );
  primary_normal_drop = read2Bytes( bytes, 0x0C );
  primary_normal_drop_rare = read2Bytes( bytes, 0x0E );
  secondary_normal_drop = read2Bytes( bytes, 0x10 );
  secondary_normal_drop_rare = read2Bytes( bytes, 0x12 );
  n_primary_normal_drop = read1Byte( bytes, 0x14 );
  n_primary_normal_drop_rare = read1Byte( bytes, 0x15 );
  n_secondary_normal_drop = read1Byte( bytes, 0x16 );
  n_secondary_normal_drop_rare = read1Byte( bytes, 0x17 );
  primary_normal_drop_overkill = read2Bytes( bytes, 0x18 );
  primary_normal_drop_overkill_rare = read2Bytes( bytes, 0x1A );
  secondary_normal_drop_overkill = read2Bytes( bytes, 0x1C );
  secondary_normal_drop_overkill_rare = read2Bytes( bytes, 0x1E );
  n_primary_normal_drop_overkill = read1Byte( bytes, 0x20 );
  n_primary_normal_drop_overkill_rare = read1Byte( bytes, 0x21 );
  n_secondary_normal_drop_overkill = read1Byte( bytes, 0x22 );
  n_secondary_normal_drop_overkill_rare = read1Byte( bytes, 0x23 );
  steal_item = read2Bytes( bytes, 0x24 );
  steal_item_rare = read2Bytes( bytes, 0x26 );
  n_steal_item = read1Byte( bytes, 0x28 );
  n_steal_item_rare = read1Byte( bytes, 0x29 );
  bribe_item = read2Bytes( bytes, 0x2A );
  n_bribe_item = read1Byte( bytes, 0x2C );
  gear_slot_count_byte = read1Byte( bytes, 0x2D );
  gear_damage_calc = read1Byte( bytes, 0x2E );
  gear_crit_bonus = read1Byte( bytes, 0x2F );
  gear_attack_power = read1Byte( bytes, 0x30 );
  gear_ability_count_byte = read1Byte( bytes, 0x31 );

  for (int chr = 0; chr < 7; chr++)
  {
    int baseOffset = 0x32 + chr * 0x20;
    for (int i = 0; i < 8; i++)
    {
      weapon_abilities_by_char.insert( { chr, read2Bytes( bytes, baseOffset + i * 2 ) } );
    }
    for (int i = 0; i < 8; i++)
    {
      gear_abilities_by_char.insert( { chr, read2Bytes( bytes, baseOffset + 0x10 + i * 2 ) } );
    }
  }

  zanmato_level_byte = read1Byte( bytes, 0x112 );
  n_gil_steal = read1Byte( bytes, 0x113 );
  arena_price = read4Bytes( bytes, 0x114 );
}

void enemy_loot_data_t::writeToBytes()
{
  std::vector<char> newBytes;
  newBytes.resize( BYTE_LENGTH );
  write2Bytes( newBytes, 0x00, gil );
  write2Bytes( newBytes, 0x02, ap );
  write2Bytes( newBytes, 0x04, ap_overkill );
  write2Bytes( newBytes, 0x06, ronso_rage );
  write1Byte( newBytes, 0x08, primary_drop_chance );
  write1Byte( newBytes, 0x09, secondary_drop_chance );
  write1Byte( newBytes, 0x0A, steal_chance );
  write1Byte( newBytes, 0x0B, gear_drop_chance );
  write2Bytes( newBytes, 0x0C, primary_normal_drop );
  write2Bytes( newBytes, 0x0E, primary_normal_drop_rare );
  write2Bytes( newBytes, 0x10, secondary_normal_drop );
  write2Bytes( newBytes, 0x12, secondary_normal_drop_rare );
  write1Byte( newBytes, 0x14, n_primary_normal_drop );
  write1Byte( newBytes, 0x15, n_primary_normal_drop_rare );
  write1Byte( newBytes, 0x16, n_secondary_normal_drop );
  write1Byte( newBytes, 0x17, n_secondary_normal_drop_rare );
  write2Bytes( newBytes, 0x18, primary_normal_drop_overkill );
  write2Bytes( newBytes, 0x1A, primary_normal_drop_overkill_rare );
  write2Bytes( newBytes, 0x1C, secondary_normal_drop_overkill );
  write2Bytes( newBytes, 0x1E, secondary_normal_drop_overkill_rare );
  write1Byte( newBytes, 0x20, n_primary_normal_drop_overkill );
  write1Byte( newBytes, 0x21, n_primary_normal_drop_overkill_rare );
  write1Byte( newBytes, 0x22, n_secondary_normal_drop_overkill );
  write1Byte( newBytes, 0x23, n_secondary_normal_drop_overkill_rare );
  write2Bytes( newBytes, 0x24, steal_item );
  write2Bytes( newBytes, 0x26, steal_item_rare );
  write1Byte( newBytes, 0x28, n_steal_item );
  write1Byte( newBytes, 0x29, n_steal_item_rare );
  write2Bytes( newBytes, 0x2A, bribe_item );
  write1Byte( newBytes, 0x2C, n_bribe_item );
  write1Byte( newBytes, 0x2D, gear_slot_count_byte );
  write1Byte( newBytes, 0x2E, gear_damage_calc );
  write1Byte( newBytes, 0x2F, gear_crit_bonus );
  write1Byte( newBytes, 0x30, gear_attack_power );
  write1Byte( newBytes, 0x31, gear_ability_count_byte );

  for (int chr = 0; chr < 7; chr++)
  {
    int baseOffset = 0x32 + chr * 0x20;
    for (int i = 0; i < 8; i++)
    {
      write2Bytes( newBytes, baseOffset + i * 2, weapon_abilities_by_char.at( chr ) );
    }
    for (int i = 0; i < 8; i++)
    {
      write2Bytes( newBytes, baseOffset + 0x10 + i * 2, gear_abilities_by_char.at( chr ) );
    }
  }

  write1Byte( newBytes, 0x112, zanmato_level_byte );
  write1Byte( newBytes, 0x113, n_gil_steal );
  write4Bytes( newBytes, 0x114, arena_price );
  bytes = newBytes;
}

void enemy_loot_data_t::test() const
{
  bytes_mapper_t::test();
  printf( "Monster ID: %s\n", monster_id.c_str() );
  printf( "Gil: %d\n", gil );
  printf( "AP: %d\n", ap );
  printf( "AP Overkill: %d\n", ap_overkill );
  printf( "Ronso Rage: %d\n", ronso_rage );
  printf( "Primary Drop Chance: %d\n", primary_drop_chance );
  printf( "Secondary Drop Chance: %d\n", secondary_drop_chance );
  printf( "Steal Chance: %d\n", steal_chance );
  printf( "Gear Drop Chance: %d\n", gear_drop_chance );
  printf( "Primary Normal Drop: %d\n", primary_normal_drop );
  printf( "Primary Normal Drop Rare: %d\n", primary_normal_drop_rare );
  printf( "Secondary Normal Drop: %d\n", secondary_normal_drop );
  printf( "Secondary Normal Drop Rare: %d\n", secondary_normal_drop_rare );
  printf( "N Primary Normal Drop: %d\n", n_primary_normal_drop );
  printf( "N Primary Normal Drop Rare: %d\n", n_primary_normal_drop_rare );
  printf( "N Secondary Normal Drop: %d\n", n_secondary_normal_drop );
  printf( "N Secondary Normal Drop Rare: %d\n", n_secondary_normal_drop_rare );
  printf( "Primary Normal Drop Overkill: %d\n", primary_normal_drop_overkill );
  printf( "Primary Normal Drop Overkill Rare: %d\n", primary_normal_drop_overkill_rare );
  printf( "Secondary Normal Drop Overkill: %d\n", secondary_normal_drop_overkill );
  printf( "Secondary Normal Drop Overkill Rare: %d\n", secondary_normal_drop_overkill_rare );
  printf( "N Primary Normal Drop Overkill: %d\n", n_primary_normal_drop_overkill );
  printf( "N Primary Normal Drop Overkill Rare: %d\n", n_primary_normal_drop_overkill_rare );
  printf( "N Secondary Normal Drop Overkill: %d\n", n_secondary_normal_drop_overkill );
  printf( "N Secondary Normal Drop Overkill Rare: %d\n", n_secondary_normal_drop_overkill_rare );
  printf( "Steal Item: %d\n", steal_item );
  printf( "Steal Item Rare: %d\n", steal_item_rare );
  printf( "N Steal Item: %d\n", n_steal_item );
  printf( "N Steal Item Rare: %d\n", n_steal_item_rare );
  printf( "Bribe Item: %d\n", bribe_item );
  printf( "N Bribe Item: %d\n", n_bribe_item );
  printf( "Gear Slot Count Byte: %d\n", gear_slot_count_byte );
  printf( "Gear Damage Calc: %d\n", gear_damage_calc );
  printf( "Gear Crit Bonus: %d\n", gear_crit_bonus );
  printf( "Gear Attack Power: %d\n", gear_attack_power );
  printf( "Gear Ability Count Byte: %d\n", gear_ability_count_byte );
  printf( "Weapon Abilities by Char:\n" );
  for (int chr = 0; chr < 7; chr++)
  {
    printf( "Character %d: ", chr );
    for (int i = 0; i < 8; i++)
    {
      printf( "%d ", weapon_abilities_by_char.at( chr ) );
    }
    printf( "\n" );
  }
  printf( "Gear Abilities by Char:\n" );
  for (int chr = 0; chr < 7; chr++)
  {
    printf( "Character %d: ", chr );
    for (int i = 0; i < 8; i++)
    {
      printf( "%d ", gear_abilities_by_char.at( chr ) );
    }
    printf( "\n" );
  }
  printf( "Zanmato Level Byte: %d\n", zanmato_level_byte );
  printf( "N Gil Steal: %d\n", n_gil_steal );
  printf( "Arena Price: %u\n", arena_price );
}

void enemy_stat_data_t::mapBytes()
{
  name_offset = read2Bytes( bytes, 0x00 );
  name_key = read2Bytes( bytes, 0x02 );
  sensor_text_offset = read2Bytes( bytes, 0x04 );
  sensor_text_key = read2Bytes( bytes, 0x06 );
  unused_str_offset = read2Bytes( bytes, 0x08 );
  unused_str_key = read2Bytes( bytes, 0x0A );
  scan_text_offset = read2Bytes( bytes, 0x0C );
  scan_text_key = read2Bytes( bytes, 0x0E );
  unused_str2_offset = read2Bytes( bytes, 0x10 );
  unused_str2_key = read2Bytes( bytes, 0x12 );
  hp = read4Bytes( bytes, 0x14 );
  mp = read4Bytes( bytes, 0x18 );
  overkill_threshold = read4Bytes( bytes, 0x1C );
  str = read1Byte( bytes, 0x20 );
  def = read1Byte( bytes, 0x21 );
  mag = read1Byte( bytes, 0x22 );
  mdef = read1Byte( bytes, 0x23 );
  agi = read1Byte( bytes, 0x24 );
  luck = read1Byte( bytes, 0x25 );
  eva = read1Byte( bytes, 0x26 );
  acc = read1Byte( bytes, 0x27 );
  flag_map1 = read1Byte( bytes, 0x28 );
  flag_map2 = read1Byte( bytes, 0x29 );
  poison_damage = read1Byte( bytes, 0x2A );
  element_absorb = read1Byte( bytes, 0x2B );
  element_immune = read1Byte( bytes, 0x2C );
  element_resist = read1Byte( bytes, 0x2D );
  element_weakness = read1Byte( bytes, 0x2E );
  death_resist = read1Byte( bytes, 0x2F );
  zombie_resist = read1Byte( bytes, 0x30 );
  petrify_resist = read1Byte( bytes, 0x31 );
  poison_resist = read1Byte( bytes, 0x32 );
  pwr_break_resist = read1Byte( bytes, 0x33 );
  mag_break_resist = read1Byte( bytes, 0x34 );
  armor_break_resist = read1Byte( bytes, 0x35 );
  mental_break_resist = read1Byte( bytes, 0x36 );
  confuse_resist = read1Byte( bytes, 0x37 );
  berserk_resist = read1Byte( bytes, 0x38 );
  provoke_resist = read1Byte( bytes, 0x39 );
  threaten_chance = read1Byte( bytes, 0x3A );
  sleep_resist = read1Byte( bytes, 0x3B );
  silence_resist = read1Byte( bytes, 0x3C );
  darkness_resist = read1Byte( bytes, 0x3D );
  shell_resist = read1Byte( bytes, 0x3E );
  protect_resist = read1Byte( bytes, 0x3F );
  reflect_resist = read1Byte( bytes, 0x40 );
  nul_tide_resist = read1Byte( bytes, 0x41 );
  nul_blaze_resist = read1Byte( bytes, 0x42 );
  nul_shock_resist = read1Byte( bytes, 0x43 );
  nul_frost_resist = read1Byte( bytes, 0x44 );
  regen_resist = read1Byte( bytes, 0x45 );
  haste_resist = read1Byte( bytes, 0x46 );
  slow_resist = read1Byte( bytes, 0x47 );
  auto_statuses = read2Bytes( bytes, 0x48 );
  auto_statuses_temporal = read2Bytes( bytes, 0x4A );
  auto_statuses_extra = read2Bytes( bytes, 0x4C );
  extra_status_immunities = read2Bytes( bytes, 0x4E );

  for (int i = 0; i < 0x10; i++)
  {
    abilities.insert( { i, read2Bytes( bytes, 0x50 + i * 2 ) } );
  }

  forced_action = read2Bytes( bytes, 0x70 );
  index = read2Bytes( bytes, 0x72 );
  model_id = read2Bytes( bytes, 0x74 );
  icon_type = read1Byte( bytes, 0x76 );
  doom_count = read1Byte( bytes, 0x77 );
  arena_id = read2Bytes( bytes, 0x78 );
  model_id_other = read2Bytes( bytes, 0x7A );
  always_zero1 = read1Byte( bytes, 0x7C );
  always_zero2 = read1Byte( bytes, 0x7D );
  always_zero3 = read1Byte( bytes, 0x7E );
  always_zero4 = read1Byte( bytes, 0x7F );
}

void enemy_stat_data_t::writeToBytes()
{
  write2Bytes( bytes, 0x00, name_offset );
  write2Bytes( bytes, 0x02, name_key );
  write2Bytes( bytes, 0x04, sensor_text_offset );
  write2Bytes( bytes, 0x06, sensor_text_key );
  write2Bytes( bytes, 0x08, unused_str_offset );
  write2Bytes( bytes, 0x0A, unused_str_key );
  write2Bytes( bytes, 0x0C, scan_text_offset );
  write2Bytes( bytes, 0x0E, scan_text_key );
  write2Bytes( bytes, 0x10, unused_str2_offset );
  write2Bytes( bytes, 0x12, unused_str2_key );
  write4Bytes( bytes, 0x14, hp );
  write4Bytes( bytes, 0x18, mp );
  write4Bytes( bytes, 0x1C, overkill_threshold );
  write1Byte( bytes, 0x20, str );
  write1Byte( bytes, 0x21, def );
  write1Byte( bytes, 0x22, mag );
  write1Byte( bytes, 0x23, mdef );
  write1Byte( bytes, 0x24, agi );
  write1Byte( bytes, 0x25, luck );
  write1Byte( bytes, 0x26, eva );
  write1Byte( bytes, 0x27, acc );
  write1Byte( bytes, 0x2A, poison_damage );
  write1Byte( bytes, 0x2F, death_resist );
  write1Byte( bytes, 0x30, zombie_resist );
  write1Byte( bytes, 0x31, petrify_resist );
  write1Byte( bytes, 0x32, poison_resist );
  write1Byte( bytes, 0x33, pwr_break_resist );
  write1Byte( bytes, 0x34, mag_break_resist );
  write1Byte( bytes, 0x35, armor_break_resist );
  write1Byte( bytes, 0x36, mental_break_resist );
  write1Byte( bytes, 0x37, confuse_resist );
  write1Byte( bytes, 0x38, berserk_resist );
  write1Byte( bytes, 0x39, provoke_resist );
  write1Byte( bytes, 0x3A, threaten_chance );
  write1Byte( bytes, 0x3B, sleep_resist );
  write1Byte( bytes, 0x3C, silence_resist );
  write1Byte( bytes, 0x3D, darkness_resist );
  write1Byte( bytes, 0x3E, shell_resist );
  write1Byte( bytes, 0x3F, protect_resist );
  write1Byte( bytes, 0x40, reflect_resist );
  write1Byte( bytes, 0x41, nul_tide_resist );
  write1Byte( bytes, 0x42, nul_blaze_resist );
  write1Byte( bytes, 0x43, nul_shock_resist );
  write1Byte( bytes, 0x44, nul_frost_resist );
  write1Byte( bytes, 0x45, regen_resist );
  write1Byte( bytes, 0x46, haste_resist );
  write1Byte( bytes, 0x47, slow_resist );
  write2Bytes( bytes, 0x48, auto_statuses );
  write2Bytes( bytes, 0x4A, auto_statuses_temporal );
  write2Bytes( bytes, 0x4C, auto_statuses_extra );
  write2Bytes( bytes, 0x4E, extra_status_immunities );

  for (int i = 0; i < 0x10; i++)
  {
    write2Bytes( bytes, 0x50 + i * 2, abilities[ i ] );
  }

  write2Bytes( bytes, 0x70, forced_action );
  write2Bytes( bytes, 0x72, index );
  write2Bytes( bytes, 0x74, model_id );
  write1Byte( bytes, 0x76, icon_type );
  write1Byte( bytes, 0x77, doom_count );
  write2Bytes( bytes, 0x78, arena_id );
  write2Bytes( bytes, 0x7A, model_id_other );
  write1Byte( bytes, 0x7C, always_zero1 );
  write1Byte( bytes, 0x7D, always_zero2 );
  write1Byte( bytes, 0x7E, always_zero3 );
  write1Byte( bytes, 0x7F, always_zero4 );

  flag_map1 = flags1.byte;
  write1Byte( bytes, 0x28, flag_map1 );
  flag_map2 = flags2.byte;
  write1Byte( bytes, 0x29, flag_map2 );

  element_absorb = element_absorb_flags.byte;
  write1Byte( bytes, 0x2B, element_absorb );
  element_immune = element_immune_flags.byte;
  write1Byte( bytes, 0x2C, element_immune );
  element_resist = element_resist_flags.byte;
  write1Byte( bytes, 0x2D, element_resist );
  element_weakness = element_weakness_flags.byte;
  write1Byte( bytes, 0x2E, element_weakness );
}

void enemy_stat_data_t::test() const
{
  bytes_mapper_t::test();
  printf( "Name Offset: %d\n", name_offset );
  printf( "Name Key: %d\n", name_key );
  printf( "Sensor Text Offset: %d\n", sensor_text_offset );
  printf( "Sensor Text Key: %d\n", sensor_text_key );
  printf( "Unused Str Offset: %d\n", unused_str_offset );
  printf( "Unused Str Key: %d\n", unused_str_key );
  printf( "Scan Text Offset: %d\n", scan_text_offset );
  printf( "Scan Text Key: %d\n", scan_text_key );
  printf( "Unused Str2 Offset: %d\n", unused_str2_offset );
  printf( "Unused Str2 Key: %d\n", unused_str2_key );
  printf( "HP: %d\n", hp );
  printf( "MP: %d\n", mp );
  printf( "Overkill Threshold: %d\n", overkill_threshold );
  printf( "STR: %d\n", str );
  printf( "DEF: %d\n", def );
  printf( "MAG: %d\n", mag );
  printf( "MDEF: %d\n", mdef );
  printf( "AGI: %d\n", agi );
  printf( "LUCK: %d\n", luck );
  printf( "EVA: %d\n", eva );
  printf( "ACC: %d\n", acc );
  printf( "UNK1: %d\n", flag_map1 );
  printf( "UNK2: %d\n", flag_map2 );
  printf( "Poison Damage: %d\n", poison_damage );
  printf( "Element Absorb: %d\n", element_absorb );
  printf( "Element Immune: %d\n", element_immune );
  printf( "Element Resist: %d\n", element_resist );
  printf( "Element Weakness: %d\n", element_weakness );
  printf( "Death Resist: %d\n", death_resist );
  printf( "Zombie Resist: %d\n", zombie_resist );
  printf( "Petrify Resist: %d\n", petrify_resist );
  printf( "Poison Resist: %d\n", poison_resist );
  printf( "Pwr Break Resist: %d\n", pwr_break_resist );
  printf( "Mag Break Resist: %d\n", mag_break_resist );
  printf( "Armor Break Resist: %d\n", armor_break_resist );
  printf( "Mental Break Resist: %d\n", mental_break_resist );
  printf( "Confuse Resist: %d\n", confuse_resist );
  printf( "Berserk Resist: %d\n", berserk_resist );
  printf( "Provoke Resist: %d\n", provoke_resist );
  printf( "Threaten Chance: %d\n", threaten_chance );
  printf( "Sleep Resist: %d\n", sleep_resist );
  printf( "Silence Resist: %d\n", silence_resist );
  printf( "Darkness Resist: %d\n", darkness_resist );
  printf( "Shell Resist: %d\n", shell_resist );
  printf( "Protect Resist: %d\n", protect_resist );
  printf( "Reflect Resist: %d\n", reflect_resist );
  printf( "Nul Tide Resist: %d\n", nul_tide_resist );
  printf( "Nul Blaze Resist: %d\n", nul_blaze_resist );
  printf( "Nul Shock Resist: %d\n", nul_shock_resist );
  printf( "Nul Frost Resist: %d\n", nul_frost_resist );
  printf( "Regen Resist: %d\n", regen_resist );
  printf( "Haste Resist: %d\n", haste_resist );
  printf( "Slow Resist: %d\n", slow_resist );
  printf( "Auto Statuses: %d\n", auto_statuses );
  printf( "Auto Statuses Temporal: %d\n", auto_statuses_temporal );
  printf( "Auto Statuses Extra: %d\n", auto_statuses_extra );
  printf( "Extra Status Immunities: %d\n", extra_status_immunities );
  printf( "Abilities: \n" );
  for (int i = 0; i < 0x10; i++)
  {
    printf( "%d ", abilities.at( i ) );
  }
  printf( "\n" );
  printf( "Forced Action: %d\n", forced_action );
  printf( "Index: %d\n", index );
  printf( "Model ID: %d\n", model_id );
  printf( "Icon Type: %d\n", icon_type );
  printf( "Doom Count: %d\n", doom_count );
  printf( "Arena ID: %d\n", arena_id );
  printf( "Model ID Other: %d\n", model_id_other );
  printf( "Always Zero 1: %d\n", always_zero1 );
  printf( "Always Zero 2: %d\n", always_zero2 );
  printf( "Always Zero 3: %d\n", always_zero3 );
  printf( "Always Zero 4: %d\n", always_zero4 );
  printf( "Flags: %d %d %d %d %d %d %d %d\n", flags1.bits.armored, flags1.bits.immune_fractional_damage, flags1.bits.immune_life, flags1.bits.immune_sensor, flags1.bits.unknown_flag, flags1.bits.immune_physical_damage, flags1.bits.immune_magic_damage, flags1.bits.immune_all_damage );
  printf( "Element Absorb Flags:\n" );
  printf( "Absorb Fire: %d\n", element_absorb_flags.bits.fire );
  printf( "Absorb Ice: %d\n", element_absorb_flags.bits.ice );
  printf( "Absorb Lightning: %d\n", element_absorb_flags.bits.lightning );
  printf( "Absorb Water: %d\n", element_absorb_flags.bits.water );
  printf( "Absorb Holy: %d\n", element_absorb_flags.bits.holy );
  printf( "Element Immune Flags:\n" );
  printf( "Immune Fire: %d\n", element_immune_flags.bits.fire );
  printf( "Immune Ice: %d\n", element_immune_flags.bits.ice );
  printf( "Immune Lightning: %d\n", element_immune_flags.bits.lightning );
  printf( "Immune Water: %d\n", element_immune_flags.bits.water );
  printf( "Immune Holy: %d\n", element_immune_flags.bits.holy );
  printf( "Element Resist Flags:\n" );
  printf( "Resist Fire: %d\n", element_resist_flags.bits.fire );
  printf( "Resist Ice: %d\n", element_resist_flags.bits.ice );
  printf( "Resist Lightning: %d\n", element_resist_flags.bits.lightning );
  printf( "Resist Water: %d\n", element_resist_flags.bits.water );
  printf( "Resist Holy: %d\n", element_resist_flags.bits.holy );
  printf( "Element Weakness Flags:\n" );
  printf( "Weakness Fire: %d\n", element_weakness_flags.bits.fire );
  printf( "Weakness Ice: %d\n", element_weakness_flags.bits.ice );
  printf( "Weakness Lightning: %d\n", element_weakness_flags.bits.lightning );
  printf( "Weakness Water: %d\n", element_weakness_flags.bits.water );
  printf( "Weakness Holy: %d\n", element_weakness_flags.bits.holy );
}

void enemy_stat_data_t::mapFlags()
{
  flags1.bits.armored = ( flag_map1 & 0x01 ) > 0;
  flags1.bits.immune_fractional_damage = ( flag_map1 & 0x02 ) > 0;
  flags1.bits.immune_life = ( flag_map1 & 0x04 ) > 0;
  flags1.bits.immune_sensor = ( flag_map1 & 0x08 ) > 0;
  flags1.bits.unknown_flag = ( flag_map1 & 0x10 ) > 0;
  flags1.bits.immune_physical_damage = ( flag_map1 & 0x20 ) > 0;
  flags1.bits.immune_magic_damage = ( flag_map1 & 0x40 ) > 0;
  flags1.bits.immune_all_damage = ( flag_map1 & 0x80 ) > 0;

  flags2.bits.immune_delay = ( flag_map2 & 0x01 ) > 0;
  flags2.bits.immune_slice = ( flag_map2 & 0x02 ) > 0;
  flags2.bits.immune_bribe = ( flag_map2 & 0x04 ) > 0;

  element_absorb_flags.bits.fire = ( element_absorb & 0x01 ) > 0;
  element_absorb_flags.bits.ice = ( element_absorb & 0x02 ) > 0;
  element_absorb_flags.bits.lightning = ( element_absorb & 0x04 ) > 0;
  element_absorb_flags.bits.water = ( element_absorb & 0x08 ) > 0;
  element_absorb_flags.bits.holy = ( element_absorb & 0x10 ) > 0;

  element_immune_flags.bits.fire = ( element_immune & 0x01 ) > 0;
  element_immune_flags.bits.ice = ( element_immune & 0x02 ) > 0;
  element_immune_flags.bits.lightning = ( element_immune & 0x04 ) > 0;
  element_immune_flags.bits.water = ( element_immune & 0x08 ) > 0;
  element_immune_flags.bits.holy = ( element_immune & 0x10 ) > 0;

  element_resist_flags.bits.fire = ( element_resist & 0x01 ) > 0;
  element_resist_flags.bits.ice = ( element_resist & 0x02 ) > 0;
  element_resist_flags.bits.lightning = ( element_resist & 0x04 ) > 0;
  element_resist_flags.bits.water = ( element_resist & 0x08 ) > 0;
  element_resist_flags.bits.holy = ( element_resist & 0x10 ) > 0;

  element_weakness_flags.bits.fire = ( element_weakness & 0x01 ) > 0;
  element_weakness_flags.bits.ice = ( element_weakness & 0x02 ) > 0;
  element_weakness_flags.bits.lightning = ( element_weakness & 0x04 ) > 0;
  element_weakness_flags.bits.water = ( element_weakness & 0x08 ) > 0;
  element_weakness_flags.bits.holy = ( element_weakness & 0x10 ) > 0;
}

void enemy_data_t::mapChunks() {
  script = chunks.at( 0 ).data;
  mapping_bytes = chunks.at( 1 ).data;
  stats_bytes = chunks.at( 2 ).data;
  chunk_3_bytes = chunks.at( 3 ).data;
  loot_bytes = chunks.at( 4 ).data;
  audio_bytes = chunks.at( 5 ).data;
  text_bytes = chunks.at( 6 ).data;

  stats_data = new enemy_stat_data_t( stats_bytes, chunks.at( 2 ).initial_offset, monster_id );
  loot_data = new enemy_loot_data_t( loot_bytes, chunks.at( 4 ).initial_offset, monster_id );
}

void enemy_data_t::writeLootData( const enemy_loot_data_t& lootData )
{
  loot_bytes = lootData.bytes;
  for (int i = 0; i < lootData.BYTE_LENGTH; i++)
  {
    bytes[ loot_data->initial_offset + i] = loot_bytes[i];
  }
}

void enemy_data_t::writeStatsData( const enemy_stat_data_t& statsData )
{
  stats_bytes = statsData.bytes;
  for (int i = 0; i < statsData.BYTE_LENGTH; i++)
  {
    bytes[ stats_data->initial_offset + i ] = stats_bytes[ i ];
  }
}

void enemy_data_t::test() const {
  bytes_mapper_t::test();
  std::cout << "Monster ID: " << monster_id << std::endl;
  std::cout << "Byte Length: " << bytes.size() << std::endl;
}

void field_data_t::mapBytes()
{
  flag = read1Byte( bytes, 0x00 );
  quantity = read1Byte( bytes, 0x01 );
  type = read1Byte( bytes, 0x02 ) | ( read1Byte( bytes, 0x03 ) << 8 );
}

void field_data_t::writeToBytes()
{
  write1Byte( bytes, 0x00, flag );
  write1Byte( bytes, 0x01, quantity );
  write1Byte( bytes, 0x02, type & 0xFF );
  write1Byte( bytes, 0x03, ( type >> 8 ) & 0xFF );
}

void field_data_t::test() const
{
  bytes_mapper_t::test();
  printf( "____________________\n" );
  printf( "Index: %d\n", index );
  printf( "Flag: %d\n", flag );
  printf( "Quantity: %d\n", quantity );
  printf( "Type: %d\n", type );
}


void shop_data_t::mapBytes()
{
  pricesUnused = read2Bytes( bytes, 0x00 );
  for (int i = 0; i < 0x10; i++)
  {
    item_indexes.push_back( read2Bytes( bytes, i * 2 + 2 ) );
  }
}

void shop_data_t::writeToBytes()
{
  write2Bytes( bytes, 0x00, pricesUnused );
  for (int i = 0; i < 0x10; i++)
  {
    write2Bytes( bytes, i * 2 + 2, item_indexes[ i ] );
  }
}

void shop_data_t::test() const
{
  bytes_mapper_t::test();
  std::cout << "Prices Unused: " << pricesUnused << std::endl;
  std::cout << "Item Indexes: " << std::endl;
  for (auto& item : item_indexes)
  {
    std::cout << item << " ";
  }
  std::cout << std::endl;
}

void rate_data_t::writeToBytes()
{
  write4Bytes( bytes, 0x00, rate );
}

void rate_data_t::test() const
{
  bytes_mapper_t::test();
  std::cout << "Rate: " << rate << std::endl;
}

void character_stats_t::mapBytes()
{
  name_offset = read2Bytes( bytes, 0x00 );
  name_key = read2Bytes( bytes, 0x02 );
  base_hp = read4Bytes( bytes, 0x04 );
  base_mp = read4Bytes( bytes, 0x08 );
  base_str = read1Byte( bytes, 0x0C );
  base_def = read1Byte( bytes, 0x0D );
  base_mag = read1Byte( bytes, 0x0E );
  base_mdef = read1Byte( bytes, 0x0F );
  base_agi = read1Byte( bytes, 0x10 );
  base_luck = read1Byte( bytes, 0x11 );
  base_eva = read1Byte( bytes, 0x12 );
  base_acc = read1Byte( bytes, 0x13 );
  unknown1 = read2Bytes( bytes, 0x14 );
  unknown2 = read2Bytes( bytes, 0x16 );
  current_ap = read4Bytes( bytes, 0x18 );
  current_hp = read4Bytes( bytes, 0x1C );
  current_mp = read4Bytes( bytes, 0x20 );
  max_hp = read4Bytes( bytes, 0x24 );
  max_mp = read4Bytes( bytes, 0x28 );
  flags = read1Byte( bytes, 0x2C );
  current_weapon_id = read1Byte( bytes, 0x2D );
  current_armor_id = read1Byte( bytes, 0x2E );
  str = read1Byte( bytes, 0x2F );
  def = read1Byte( bytes, 0x30 );
  mag = read1Byte( bytes, 0x31 );
  mdef = read1Byte( bytes, 0x32 );
  agi = read1Byte( bytes, 0x33 );
  luck = read1Byte( bytes, 0x34 );
  eva = read1Byte( bytes, 0x35 );
  acc = read1Byte( bytes, 0x36 );
  poison_damage = read1Byte( bytes, 0x37 );
  overdrive_mode = read1Byte( bytes, 0x38 );
  overdrive_current = read1Byte( bytes, 0x39 );
  overdrive_max = read1Byte( bytes, 0x3A );
  sphere_level = read1Byte( bytes, 0x3B );
  sphere_level_used = read1Byte( bytes, 0x3C );
  unknown3 = read1Byte( bytes, 0x3D );
  ability_field1 = read4Bytes( bytes, 0x3E );
  ability_field2 = read4Bytes( bytes, 0x42 );
  ability_field3 = read4Bytes( bytes, 0x46 );
  encounter_count = read4Bytes( bytes, 0x50 );
  kill_count = read4Bytes( bytes, 0x54 );
  unknown4 = read4Bytes( bytes, 0x58 );
  unknown5 = read4Bytes( bytes, 0x5C );
  overdrive_mode_counters = read2Bytes( bytes, 0x60 );
  overdrive_mode_flags = read4Bytes( bytes, 0x88 );
  unknown6 = read4Bytes( bytes, 0x8C );
  unknown7 = read4Bytes( bytes, 0x90 );
}

void character_stats_t::mapFlags()
{
  overdrive.bits.warrior = ( overdrive_mode_flags & 0x01 ) > 0;
  overdrive.bits.comrade = ( overdrive_mode_flags & 0x02 ) > 0;
  overdrive.bits.stoic = ( overdrive_mode_flags & 0x04 ) > 0;
  overdrive.bits.healer = ( overdrive_mode_flags & 0x8 ) > 0;
  overdrive.bits.tactician = ( overdrive_mode_flags & 0x10 ) > 0;
  overdrive.bits.victim = ( overdrive_mode_flags & 0x20 ) > 0;
  overdrive.bits.dancer = ( overdrive_mode_flags & 0x40 ) > 0;
  overdrive.bits.avenger = ( overdrive_mode_flags & 0x80 ) > 0;
  overdrive.bits.slayer = ( overdrive_mode_flags & 0x100 ) > 0;
  overdrive.bits.hero = ( overdrive_mode_flags & 0x200 ) > 0;
  overdrive.bits.rook = ( overdrive_mode_flags & 0x400 ) > 0;
  overdrive.bits.victor = ( overdrive_mode_flags & 0x800 ) > 0;
  overdrive.bits.coward = ( overdrive_mode_flags & 0x1000 ) > 0;
  overdrive.bits.ally = ( overdrive_mode_flags & 0x2000 ) > 0;
  overdrive.bits.sufferer = ( overdrive_mode_flags & 0x4000 ) > 0;
  overdrive.bits.daredevil = ( overdrive_mode_flags & 0x8000 ) > 0;
  overdrive.bits.loner = ( overdrive_mode_flags & 0x10000 ) > 0;
  overdrive.bits.unused1 = ( overdrive_mode_flags & 0x20000 ) > 0;
  overdrive.bits.unused2 = ( overdrive_mode_flags & 0x40000 ) > 0;
  overdrive.bits.aeon = ( overdrive_mode_flags & 0x80000 ) > 0;

  ability_flags1.bits.attack = ( ability_field1 & 0x01 ) > 0;
  ability_flags1.bits.item = ( ability_field1 & 0x02 ) > 0;
  ability_flags1.bits.switch_out = ( ability_field1 & 0x04 ) > 0;
  ability_flags1.bits.escape = ( ability_field1 & 0x08 ) > 0;
  ability_flags1.bits.change_weapon = ( ability_field1 & 0x10 ) > 0;
  ability_flags1.bits.change_armor = ( ability_field1 & 0x20 ) > 0;
  ability_flags1.bits.delay_attack = ( ability_field1 & 0x40 ) > 0;
  ability_flags1.bits.delay_buster = ( ability_field1 & 0x80 ) > 0;
  ability_flags1.bits.sleep_attack = ( ability_field1 & 0x100 ) > 0;
  ability_flags1.bits.silence_attack = ( ability_field1 & 0x200 ) > 0;
  ability_flags1.bits.dark_attack = ( ability_field1 & 0x400 ) > 0;
  ability_flags1.bits.zombie_attack = ( ability_field1 & 0x800 ) > 0;
  ability_flags1.bits.sleep_buster = ( ability_field1 & 0x1000 ) > 0;
  ability_flags1.bits.silence_buster = ( ability_field1 & 0x2000 ) > 0;
  ability_flags1.bits.dark_buster = ( ability_field1 & 0x4000 ) > 0;
  ability_flags1.bits.triple_foul = ( ability_field1 & 0x8000 ) > 0;
  ability_flags1.bits.power_break = ( ability_field1 & 0x10000 ) > 0;
  ability_flags1.bits.magic_break = ( ability_field1 & 0x20000 ) > 0;
  ability_flags1.bits.armor_break = ( ability_field1 & 0x40000 ) > 0;
  ability_flags1.bits.mental_break = ( ability_field1 & 0x80000 ) > 0;
  ability_flags1.bits.mug = ( ability_field1 & 0x100000 ) > 0;
  ability_flags1.bits.quick_hit = ( ability_field1 & 0x200000 ) > 0;
  ability_flags1.bits.steal = ( ability_field1 & 0x400000 ) > 0;
  ability_flags1.bits.use = ( ability_field1 & 0x800000 ) > 0;
  ability_flags1.bits.flee = ( ability_field1 & 0x1000000 ) > 0;
  ability_flags1.bits.pray = ( ability_field1 & 0x2000000 ) > 0;
  ability_flags1.bits.cheer = ( ability_field1 & 0x4000000 ) > 0;
  ability_flags1.bits.aim = ( ability_field1 & 0x8000000 ) > 0;
  ability_flags1.bits.focus = ( ability_field1 & 0x10000000 ) > 0;
  ability_flags1.bits.reflex = ( ability_field1 & 0x20000000 ) > 0;
  ability_flags1.bits.luck = ( ability_field1 & 0x40000000 ) > 0;
  ability_flags1.bits.jinx = ( ability_field1 & 0x80000000 ) > 0;

  ability_flags2.bits.lancet = ( ability_field2 & 0x01 ) > 0;
  ability_flags2.bits.unused1 = ( ability_field2 & 0x02 ) > 0;
  ability_flags2.bits.guard = ( ability_field2 & 0x04 ) > 0;
  ability_flags2.bits.sentinel = ( ability_field2 & 0x08 ) > 0;
  ability_flags2.bits.spare_change = ( ability_field2 & 0x10 ) > 0;
  ability_flags2.bits.threaten = ( ability_field2 & 0x20 ) > 0;
  ability_flags2.bits.provoke = ( ability_field2 & 0x40 ) > 0;
  ability_flags2.bits.entrust = ( ability_field2 & 0x80 ) > 0;
  ability_flags2.bits.copycat = ( ability_field2 & 0x100 ) > 0;
  ability_flags2.bits.doubelcast = ( ability_field2 & 0x200 ) > 0;
  ability_flags2.bits.bribe = ( ability_field2 & 0x400 ) > 0;
  ability_flags2.bits.cure = ( ability_field2 & 0x800 ) > 0;
  ability_flags2.bits.cura = ( ability_field2 & 0x1000 ) > 0;
  ability_flags2.bits.curaga = ( ability_field2 & 0x2000 ) > 0;
  ability_flags2.bits.null_frost = ( ability_field2 & 0x4000 ) > 0;
  ability_flags2.bits.null_blaze = ( ability_field2 & 0x8000 ) > 0;
  ability_flags2.bits.null_shock = ( ability_field2 & 0x10000 ) > 0;
  ability_flags2.bits.null_tide = ( ability_field2 & 0x20000 ) > 0;
  ability_flags2.bits.scan = ( ability_field2 & 0x40000 ) > 0;
  ability_flags2.bits.esuna = ( ability_field2 & 0x80000 ) > 0;
  ability_flags2.bits.life = ( ability_field2 & 0x100000 ) > 0;
  ability_flags2.bits.full_life = ( ability_field2 & 0x200000 ) > 0;
  ability_flags2.bits.haste = ( ability_field2 & 0x400000 ) > 0;
  ability_flags2.bits.hastega = ( ability_field2 & 0x800000 ) > 0;
  ability_flags2.bits.slow = ( ability_field2 & 0x1000000 ) > 0;
  ability_flags2.bits.slowga = ( ability_field2 & 0x2000000 ) > 0;
  ability_flags2.bits.shell = ( ability_field2 & 0x4000000 ) > 0;
  ability_flags2.bits.protect = ( ability_field2 & 0x8000000 ) > 0;
  ability_flags2.bits.reflect = ( ability_field2 & 0x10000000 ) > 0;
  ability_flags2.bits.dispel = ( ability_field2 & 0x20000000 ) > 0;
  ability_flags2.bits.regen = ( ability_field2 & 0x40000000 ) > 0;
  ability_flags2.bits.holy = ( ability_field2 & 0x80000000 ) > 0;

  ability_flags3.bits.auto_life = ( ability_field3 & 0x01 ) > 0;
  ability_flags3.bits.blizzard = ( ability_field3 & 0x02 ) > 0;
  ability_flags3.bits.fire = ( ability_field3 & 0x04 ) > 0;
  ability_flags3.bits.thunder = ( ability_field3 & 0x08 ) > 0;
  ability_flags3.bits.water = ( ability_field3 & 0x10 ) > 0;
  ability_flags3.bits.fira = ( ability_field3 & 0x20 ) > 0;
  ability_flags3.bits.blizzara = ( ability_field3 & 0x40 ) > 0;
  ability_flags3.bits.thundara = ( ability_field3 & 0x80 ) > 0;
  ability_flags3.bits.watera = ( ability_field3 & 0x100 ) > 0;
  ability_flags3.bits.firaga = ( ability_field3 & 0x200 ) > 0;
  ability_flags3.bits.blizzaga = ( ability_field3 & 0x400 ) > 0;
  ability_flags3.bits.thundaga = ( ability_field3 & 0x800 ) > 0;
  ability_flags3.bits.waterga = ( ability_field3 & 0x1000 ) > 0;
  ability_flags3.bits.bio = ( ability_field3 & 0x2000 ) > 0;
  ability_flags3.bits.demi = ( ability_field3 & 0x4000 ) > 0;
  ability_flags3.bits.death = ( ability_field3 & 0x8000 ) > 0;
  ability_flags3.bits.drain = ( ability_field3 & 0x10000 ) > 0;
  ability_flags3.bits.osmose = ( ability_field3 & 0x20000 ) > 0;
  ability_flags3.bits.flare = ( ability_field3 & 0x40000 ) > 0;
  ability_flags3.bits.ultima = ( ability_field3 & 0x80000 ) > 0;
  ability_flags3.bits.shield = ( ability_field3 & 0x100000 ) > 0;
  ability_flags3.bits.boost = ( ability_field3 & 0x200000 ) > 0;
  ability_flags3.bits.dismiss = ( ability_field3 & 0x400000 ) > 0;
  ability_flags3.bits.dismiss_yojimbo = ( ability_field3 & 0x800000 ) > 0;
  ability_flags3.bits.pilfer_gil = ( ability_field3 & 0x1000000 ) > 0;
  ability_flags3.bits.full_break = ( ability_field3 & 0x2000000 ) > 0;
  ability_flags3.bits.extract_power = ( ability_field3 & 0x4000000 ) > 0;
  ability_flags3.bits.extract_mana = ( ability_field3 & 0x8000000 ) > 0;
  ability_flags3.bits.extract_speed = ( ability_field3 & 0x10000000 ) > 0;
  ability_flags3.bits.extract_ability = ( ability_field3 & 0x20000000 ) > 0;
  ability_flags3.bits.nab_gil = ( ability_field3 & 0x40000000 ) > 0;
  ability_flags3.bits.quick_pockets = ( ability_field3 & 0x80000000 ) > 0;
}

void character_stats_t::writeToBytes()
{
  write2Bytes( bytes, 0x00, name_offset );
  write2Bytes( bytes, 0x02, name_key );
  write4Bytes( bytes, 0x04, base_hp );
  write4Bytes( bytes, 0x08, base_mp );
  write1Byte( bytes, 0x0C, base_str );
  write1Byte( bytes, 0x0D, base_def );
  write1Byte( bytes, 0x0E, base_mag );
  write1Byte( bytes, 0x0F, base_mdef );
  write1Byte( bytes, 0x10, base_agi );
  write1Byte( bytes, 0x11, base_luck );
  write1Byte( bytes, 0x12, base_eva );
  write1Byte( bytes, 0x13, base_acc );
  write2Bytes( bytes, 0x14, unknown1 );
  write2Bytes( bytes, 0x16, unknown2 );
  write4Bytes( bytes, 0x18, current_ap );
  write4Bytes( bytes, 0x1C, current_hp );
  write4Bytes( bytes, 0x20, current_mp );
  write4Bytes( bytes, 0x24, max_hp );
  write4Bytes( bytes, 0x28, max_mp );
  write1Byte( bytes, 0x2C, flags );
  write1Byte( bytes, 0x2D, current_weapon_id );
  write1Byte( bytes, 0x2E, current_armor_id );
  write1Byte( bytes, 0x2F, str );
  write1Byte( bytes, 0x30, def );
  write1Byte( bytes, 0x31, mag );
  write1Byte( bytes, 0x32, mdef );
  write1Byte( bytes, 0x33, agi );
  write1Byte( bytes, 0x34, luck );
  write1Byte( bytes, 0x35, eva );
  write1Byte( bytes, 0x36, acc );
  write1Byte( bytes, 0x37, poison_damage );
  write1Byte( bytes, 0x38, overdrive_mode );
  write1Byte( bytes, 0x39, overdrive_current );
  write1Byte( bytes, 0x3A, overdrive_max );
  write1Byte( bytes, 0x3B, sphere_level );
  write1Byte( bytes, 0x3C, sphere_level_used );
  write1Byte( bytes, 0x3D, unknown3 );
  write4Bytes( bytes, 0x3E, ability_field1 );
  write4Bytes( bytes, 0x42, ability_field2 );
  write4Bytes( bytes, 0x46, ability_field3 );
  write4Bytes( bytes, 0x50, encounter_count );
  write4Bytes( bytes, 0x54, kill_count );
  write4Bytes( bytes, 0x58, unknown4 );
  write4Bytes( bytes, 0x5C, unknown5 );
  write2Bytes( bytes, 0x60, overdrive_mode_counters );
  write4Bytes( bytes, 0x8C, unknown6 );
  write4Bytes( bytes, 0x90, unknown7 );

  overdrive_mode_flags = overdrive.bytes;
  write4Bytes( bytes, 0x88, overdrive_mode_flags );
  ability_field1 = ability_flags1.bytes;
  write4Bytes( bytes, 0x3E, ability_field1 );
  ability_field2 = ability_flags2.bytes;
  write4Bytes( bytes, 0x42, ability_field2 );
  ability_field3 = ability_flags3.bytes;
  write4Bytes( bytes, 0x46, ability_field3 );
}

void character_stats_t::test() const
{
  bytes_mapper_t::test();
  printf( "Name Offset: %d\n", name_offset );
  printf( "Name Key: %d\n", name_key );
  printf( "Base HP: %d\n", base_hp );
  printf( "Base MP: %d\n", base_mp );
  printf( "Base STR: %d\n", base_str );
  printf( "Base DEF: %d\n", base_def );
  printf( "Base MAG: %d\n", base_mag );
  printf( "Base MDEF: %d\n", base_mdef );
  printf( "Base AGI: %d\n", base_agi );
  printf( "Base LUCK: %d\n", base_luck );
  printf( "Base EVA: %d\n", base_eva );
  printf( "Base ACC: %d\n", base_acc );
  printf( "Unknown1: %d\n", unknown1 );
  printf( "Unknown2: %d\n", unknown2 );
  printf( "Current AP: %d\n", current_ap );
  printf( "Current HP: %d\n", current_hp );
  printf( "Current MP: %d\n", current_mp );
  printf( "Max HP: %d\n", max_hp );
  printf( "Max MP: %d\n", max_mp );
  printf( "Flags: %d\n", flags );
  printf( "Current Weapon ID: %d\n", current_weapon_id );
  printf( "Current Armor ID: %d\n", current_armor_id );
  printf( "STR: %d\n", str );
  printf( "DEF: %d\n", def );
  printf( "MAG: %d\n", mag );
  printf( "MDEF: %d\n", mdef );
  printf( "AGI: %d\n", agi );
  printf( "LUCK: %d\n", luck );
  printf( "EVA: %d\n", eva );
  printf( "ACC: %d\n", acc );
  printf( "Poison Damage: %d\n", poison_damage );
  printf( "Overdrive Mode: %d\n", overdrive_mode );
  printf( "Overdrive Current: %d\n", overdrive_current );
  printf( "Overdrive Max: %d\n", overdrive_max );
  printf( "Sphere Level: %d\n", sphere_level );
  printf( "Sphere Level Used: %d\n", sphere_level_used );
  printf( "Unknown3: %d\n", unknown3 );
  printf( "Ability Field 1: %d\n", ability_field1 );
  printf( "Abilities Learned:\n" );
  printf( "________________\n" );
  printf( "Attack: %d\n", ability_flags1.bits.attack );
  printf( "Item: %d\n", ability_flags1.bits.item );
  printf( "Switch Out: %d\n", ability_flags1.bits.switch_out );
  printf( "Escape: %d\n", ability_flags1.bits.escape );
  printf( "Change Weapon: %d\n", ability_flags1.bits.change_weapon );
  printf( "Change Armor: %d\n", ability_flags1.bits.change_armor );
  printf( "Delay Attack: %d\n", ability_flags1.bits.delay_attack );
  printf( "Delay Buster: %d\n", ability_flags1.bits.delay_buster );
  printf( "Sleep Attack: %d\n", ability_flags1.bits.sleep_attack );
  printf( "Silence Attack: %d\n", ability_flags1.bits.silence_attack );
  printf( "Dark Attack: %d\n", ability_flags1.bits.dark_attack );
  printf( "Zombie Attack: %d\n", ability_flags1.bits.zombie_attack );
  printf( "Sleep Buster: %d\n", ability_flags1.bits.sleep_buster );
  printf( "Silence Buster: %d\n", ability_flags1.bits.silence_buster );
  printf( "Dark Buster: %d\n", ability_flags1.bits.dark_buster );
  printf( "Triple Foul: %d\n", ability_flags1.bits.triple_foul );
  printf( "Power Break: %d\n", ability_flags1.bits.power_break );
  printf( "Magic Break: %d\n", ability_flags1.bits.magic_break );
  printf( "Armor Break: %d\n", ability_flags1.bits.armor_break );
  printf( "Mental Break: %d\n", ability_flags1.bits.mental_break );
  printf( "Mug: %d\n", ability_flags1.bits.mug );
  printf( "Quick Hit: %d\n", ability_flags1.bits.quick_hit );
  printf( "Steal: %d\n", ability_flags1.bits.steal );
  printf( "Use: %d\n", ability_flags1.bits.use );
  printf( "Flee: %d\n", ability_flags1.bits.flee );
  printf( "Pray: %d\n", ability_flags1.bits.pray );
  printf( "Cheer: %d\n", ability_flags1.bits.cheer );
  printf( "Aim: %d\n", ability_flags1.bits.aim );
  printf( "Focus: %d\n", ability_flags1.bits.focus );
  printf( "Reflex: %d\n", ability_flags1.bits.reflex );
  printf( "Luck: %d\n", ability_flags1.bits.luck );
  printf( "Jinx: %d\n", ability_flags1.bits.jinx );
  printf( "________________\n" );
  printf( "Ability Field 2: %d\n", ability_field2 );
  printf( "Abilities Learned:\n" );
  printf( "________________\n" );
  printf( "Lancet: %d\n", ability_flags2.bits.lancet );
  printf( "Unused1: %d\n", ability_flags2.bits.unused1 );
  printf( "Guard: %d\n", ability_flags2.bits.guard );
  printf( "Sentinel: %d\n", ability_flags2.bits.sentinel );
  printf( "Spare Change: %d\n", ability_flags2.bits.spare_change );
  printf( "Threaten: %d\n", ability_flags2.bits.threaten );
  printf( "Provoke: %d\n", ability_flags2.bits.provoke );
  printf( "Entrust: %d\n", ability_flags2.bits.entrust );
  printf( "Copycat: %d\n", ability_flags2.bits.copycat );
  printf( "Doublecast: %d\n", ability_flags2.bits.doubelcast );
  printf( "Bribe: %d\n", ability_flags2.bits.bribe );
  printf( "Cure: %d\n", ability_flags2.bits.cure );
  printf( "Cura: %d\n", ability_flags2.bits.cura );
  printf( "Curaga: %d\n", ability_flags2.bits.curaga );
  printf( "Null Frost: %d\n", ability_flags2.bits.null_frost );
  printf( "Null Blaze: %d\n", ability_flags2.bits.null_blaze );
  printf( "Null Shock: %d\n", ability_flags2.bits.null_shock );
  printf( "Null Tide: %d\n", ability_flags2.bits.null_tide );
  printf( "Scan: %d\n", ability_flags2.bits.scan );
  printf( "Esuna: %d\n", ability_flags2.bits.esuna );
  printf( "Life: %d\n", ability_flags2.bits.life );
  printf( "Full Life: %d\n", ability_flags2.bits.full_life );
  printf( "Haste: %d\n", ability_flags2.bits.haste );
  printf( "Hastega: %d\n", ability_flags2.bits.hastega );
  printf( "Slow: %d\n", ability_flags2.bits.slow );
  printf( "Slowga: %d\n", ability_flags2.bits.slowga );
  printf( "Shell: %d\n", ability_flags2.bits.shell );
  printf( "Protect: %d\n", ability_flags2.bits.protect );
  printf( "Reflect: %d\n", ability_flags2.bits.reflect );
  printf( "Dispel: %d\n", ability_flags2.bits.dispel );
  printf( "Regen: %d\n", ability_flags2.bits.regen );
  printf( "Holy: %d\n", ability_flags2.bits.holy );
  printf( "________________\n" );
  printf( "Ability Field 3: %d\n", ability_field3 );
  printf( "Abilities Learned:\n" );
  printf( "________________\n" );
  printf( "Auto Life: %d\n", ability_flags3.bits.auto_life );
  printf( "Blizzard: %d\n", ability_flags3.bits.blizzard );
  printf( "Fire: %d\n", ability_flags3.bits.fire );
  printf( "Thunder: %d\n", ability_flags3.bits.thunder );
  printf( "Water: %d\n", ability_flags3.bits.water );
  printf( "Fira: %d\n", ability_flags3.bits.fira );
  printf( "Blizzara: %d\n", ability_flags3.bits.blizzara );
  printf( "Thundara: %d\n", ability_flags3.bits.thundara );
  printf( "Watera: %d\n", ability_flags3.bits.watera );
  printf( "Firaga: %d\n", ability_flags3.bits.firaga );
  printf( "Blizzaga: %d\n", ability_flags3.bits.blizzaga );
  printf( "Thundaga: %d\n", ability_flags3.bits.thundaga );
  printf( "Waterga: %d\n", ability_flags3.bits.waterga );
  printf( "Bio: %d\n", ability_flags3.bits.bio );
  printf( "Demi: %d\n", ability_flags3.bits.demi );
  printf( "Death: %d\n", ability_flags3.bits.death );
  printf( "Drain: %d\n", ability_flags3.bits.drain );
  printf( "Osmose: %d\n", ability_flags3.bits.osmose );
  printf( "Flare: %d\n", ability_flags3.bits.flare );
  printf( "Ultima: %d\n", ability_flags3.bits.ultima );
  printf( "Shield: %d\n", ability_flags3.bits.shield );
  printf( "Boost: %d\n", ability_flags3.bits.boost );
  printf( "Dismiss: %d\n", ability_flags3.bits.dismiss );
  printf( "Dismiss Yojimbo: %d\n", ability_flags3.bits.dismiss_yojimbo );
  printf( "Pilfer Gil: %d\n", ability_flags3.bits.pilfer_gil );
  printf( "Full Break: %d\n", ability_flags3.bits.full_break );
  printf( "Extract Power: %d\n", ability_flags3.bits.extract_power );
  printf( "Extract Mana: %d\n", ability_flags3.bits.extract_mana );
  printf( "Extract Speed: %d\n", ability_flags3.bits.extract_speed );
  printf( "Extract Ability: %d\n", ability_flags3.bits.extract_ability );
  printf( "Nab Gil: %d\n", ability_flags3.bits.nab_gil );
  printf( "Quick Pockets: %d\n", ability_flags3.bits.quick_pockets );
  printf( "________________\n" );
  printf( "Encounter Count: %d\n", encounter_count );
  printf( "Kill Count: %d\n", kill_count );
  printf( "Unknown4: %d\n", unknown4 );
  printf( "Unknown5: %d\n", unknown5 );
  printf( "Overdrive Mode Counters: %d\n", overdrive_mode_counters );
  printf( "Overdrive Mode Flags: %d\n", overdrive_mode_flags );
  printf( "________________\n" );
  printf( "Overdrive Learned:\n" );
  printf( "Warrior: %d\n", overdrive.bits.warrior );
  printf( "Comrade: %d\n", overdrive.bits.comrade );
  printf( "Stoic: %d\n", overdrive.bits.stoic );
  printf( "Healer: %d\n", overdrive.bits.healer );
  printf( "Tactician: %d\n", overdrive.bits.tactician );
  printf( "Victim: %d\n", overdrive.bits.victim );
  printf( "Dancer: %d\n", overdrive.bits.dancer );
  printf( "Avenger: %d\n", overdrive.bits.avenger );
  printf( "Slayer: %d\n", overdrive.bits.slayer );
  printf( "Hero: %d\n", overdrive.bits.hero );
  printf( "Rook: %d\n", overdrive.bits.rook );
  printf( "Victor: %d\n", overdrive.bits.victor );
  printf( "Coward: %d\n", overdrive.bits.coward );
  printf( "Ally: %d\n", overdrive.bits.ally );
  printf( "Sufferer: %d\n", overdrive.bits.sufferer );
  printf( "Daredevil: %d\n", overdrive.bits.daredevil );
  printf( "Loner: %d\n", overdrive.bits.loner );
  printf( "Unused1: %d\n", overdrive.bits.unused1 );
  printf( "Unused2: %d\n", overdrive.bits.unused2 );
  printf( "Aeon: %d\n", overdrive.bits.aeon );
  printf( "________________\n" );
  printf( "Unknown6: %d\n", unknown6 );
  printf( "Unknown7: %d\n", unknown7 );
}

void aeon_scaling_data_t::mapBytes()
{
  genre_byte = read1Byte( bytes, 0x10 );
  ap_req_coef1 = read1Byte( bytes, 0x11 );
  ap_req_coef2 = read1Byte( bytes, 0x12 );
  ap_req_coef3 = read1Byte( bytes, 0x13 );
  ap_req_max = read4Bytes( bytes, 0x14 );
  hp_coef1 = read1Byte( bytes, 0x18 );
  hp_coef2 = read1Byte( bytes, 0x19 );
  mp_coef1 = read1Byte( bytes, 0x1A );
  mp_coef2 = read1Byte( bytes, 0x1B );
  str_coef1 = read1Byte( bytes, 0x1C );
  str_coef2 = read1Byte( bytes, 0x1D );
  def_coef1 = read1Byte( bytes, 0x1E );
  def_coef2 = read1Byte( bytes, 0x1F );
  mag_coef1 = read1Byte( bytes, 0x20 );
  mag_coef2 = read1Byte( bytes, 0x21 );
  mdef_coef1 = read1Byte( bytes, 0x22 );
  mdef_coef2 = read1Byte( bytes, 0x23 );
  agi_coef1 = read1Byte( bytes, 0x24 );
  agi_coef2 = read1Byte( bytes, 0x25 );
  eva_coef1 = read1Byte( bytes, 0x26 );
  eva_coef2 = read1Byte( bytes, 0x27 );
  acc_coef1 = read1Byte( bytes, 0x28 );
  acc_coef2 = read1Byte( bytes, 0x29 );
  unknown = read2Bytes( bytes, 0x2A );

  if (ap_req_coef1 == 0 && ap_req_coef2 == 0 && ap_req_coef3 == 0 && hp_coef1 > 0)
  {
    is_yuna_summon = true;
  }
}

void aeon_scaling_data_t::writeToBytes()
{
  write1Byte( bytes, 0x10, genre_byte );
  write1Byte( bytes, 0x11, ap_req_coef1 );
  write1Byte( bytes, 0x12, ap_req_coef2 );
  write1Byte( bytes, 0x13, ap_req_coef3 );
  write4Bytes( bytes, 0x14, ap_req_max );
  write1Byte( bytes, 0x18, hp_coef1 );
  write1Byte( bytes, 0x19, hp_coef2 );
  write1Byte( bytes, 0x1A, mp_coef1 );
  write1Byte( bytes, 0x1B, mp_coef2 );
  write1Byte( bytes, 0x1C, str_coef1 );
  write1Byte( bytes, 0x1D, str_coef2 );
  write1Byte( bytes, 0x1E, def_coef1 );
  write1Byte( bytes, 0x1F, def_coef2 );
  write1Byte( bytes, 0x20, mag_coef1 );
  write1Byte( bytes, 0x21, mag_coef2 );
  write1Byte( bytes, 0x22, mdef_coef1 );
  write1Byte( bytes, 0x23, mdef_coef2 );
  write1Byte( bytes, 0x24, agi_coef1 );
  write1Byte( bytes, 0x25, agi_coef2 );
  write1Byte( bytes, 0x26, eva_coef1 );
  write1Byte( bytes, 0x27, eva_coef2 );
  write1Byte( bytes, 0x28, acc_coef1 );
  write1Byte( bytes, 0x29, acc_coef2 );
  write2Bytes( bytes, 0x2A, unknown );
}

void aeon_scaling_data_t::test() const
{
  bytes_mapper_t::test();
  printf( "______________________\n" );
  printf( "Genre Byte: %d\n", genre_byte );
  printf( "AP Req Coef 1: %d\n", ap_req_coef1 );
  printf( "AP Req Coef 2: %d\n", ap_req_coef2 );
  printf( "AP Req Coef 3: %d\n", ap_req_coef3 );
  printf( "AP Req Max: %I32ud\n", ap_req_max );
  printf( "HP Coef 1: %d\n", hp_coef1 );
  printf( "HP Coef 2: %d\n", hp_coef2 );
  printf( "MP Coef 1: %d\n", mp_coef1 );
  printf( "MP Coef 2: %d\n", mp_coef2 );
  printf( "STR Coef 1: %d\n", str_coef1 );
  printf( "STR Coef 2: %d\n", str_coef2 );
  printf( "DEF Coef 1: %d\n", def_coef1 );
  printf( "DEF Coef 2: %d\n", def_coef2 );
  printf( "MAG Coef 1: %d\n", mag_coef1 );
  printf( "MAG Coef 2: %d\n", mag_coef2 );
  printf( "MDEF Coef 1: %d\n", mdef_coef1 );
  printf( "MDEF Coef 2: %d\n", mdef_coef2 );
  printf( "AGI Coef 1: %d\n", agi_coef1 );
  printf( "AGI Coef 2: %d\n", agi_coef2 );
  printf( "EVA Coef 1: %d\n", eva_coef1 );
  printf( "EVA Coef 2: %d\n", eva_coef2 );
  printf( "ACC Coef 1: %d\n", acc_coef1 );
  printf( "ACC Coef 2: %d\n", acc_coef2 );
  printf( "Unknown: %ld\n", unknown );
  printf( "______________________\n" );
}

void aeon_stat_data_t::mapBytes()
{
  hp = read2Bytes( bytes, 0x00 );
  mp = read2Bytes( bytes, 0x02 );
  str = read1Byte( bytes, 0x04 );
  def = read1Byte( bytes, 0x05 );
  mag = read1Byte( bytes, 0x06 );
  mdef = read1Byte( bytes, 0x07 );
  acc = read1Byte( bytes, 0x08 );
  eva = read1Byte( bytes, 0x09 );
  agi = read1Byte( bytes, 0x0A );
  luck = read1Byte( bytes, 0x0B );
}

void aeon_stat_data_t::writeToBytes()
{
  write2Bytes( bytes, 0x00, hp );
  write2Bytes( bytes, 0x02, mp );
  write1Byte( bytes, 0x04, str );
  write1Byte( bytes, 0x05, def );
  write1Byte( bytes, 0x06, mag );
  write1Byte( bytes, 0x07, mdef );
  write1Byte( bytes, 0x08, acc );
  write1Byte( bytes, 0x09, eva );
  write1Byte( bytes, 0x0A, agi );
  write1Byte( bytes, 0x0B, luck );
}

void aeon_stat_data_t::test() const
{
  bytes_mapper_t::test();
  printf( "______________________\n" );
  printf( "HP: %d\n", hp );
  printf( "MP: %d\n", mp );
  printf( "STR: %d\n", str );
  printf( "DEF: %d\n", def );
  printf( "MAG: %d\n", mag );
  printf( "MDEF: %d\n", mdef );
  printf( "ACC: %d\n", acc );
  printf( "EVA: %d\n", eva );
  printf( "AGI: %d\n", agi );
  printf( "LUCK: %d\n", luck );
}

void sphere_grid_node_data_t::mapBytes()
{
  uint16_t x_pos_raw = read2Bytes( bytes, 0x00 );
  if (( x_pos_raw & 0x8000 ) != 0)
    x_pos = x_pos_raw - 0x10000;
  else
    x_pos = x_pos_raw;
  uint16_t y_pos_raw = read2Bytes( bytes, 0x02 );
  if (( y_pos_raw & 0x8000 ) != 0)
    y_pos = y_pos_raw - 0x10000;
  else
    y_pos = y_pos_raw;

  unknown1 = read2Bytes( bytes, 0x04 );
  original_content = read1Byte( bytes, 0x06 );
  unknown2 = read1Byte( bytes, 0x07 );
  cluster = read2Bytes( bytes, 0x08 );
  unknown3 = read2Bytes( bytes, 0x0A );
}

void sphere_grid_node_data_t::writeToBytes()
{
  //write2Bytes( bytes, 0x00, ( ( x_pos + 0x10000 ) & 0x8000 ) == 0 ? x_pos + 0x10000 : x_pos );
  //write2Bytes( bytes, 0x02, ( ( y_pos + 0x10000 ) & 0x8000 ) == 0 ? y_pos + 0x10000 : y_pos );
  //write2Bytes( bytes, 0x04, unknown1 );
  write1Byte( bytes, 0x06, original_content );
  write1Byte( bytes, 0x07, unknown2 );
  write2Bytes( bytes, 0x08, cluster );
  write2Bytes( bytes, 0x0A, unknown2 );
}

void sphere_grid_node_data_t::test() const
{
  bytes_mapper_t::test();
  printf( "____________________Sphere Node Data______________________\n" );
  printf( "X Pos: %d\n", x_pos );
  printf( "Y Pos: %d\n", y_pos );
  printf( "Unknown1: %d\n", unknown1 );
  printf( "Original Content: %d\n", original_content );
  printf( "Cluster: %d\n", cluster );
  printf( "Unknown2: %d\n", unknown2 );
  printf( "Content: %d\n", content );
}

void sphere_grid_data_t::mapBytes()
{
  switch (type)
  {
    case sphere_grid_type_e::SPHERE_GRID_ORIGINAL:
      full_content_bytes = fileToBytes( INPUT_FOLDER + ABMAP_FOLDER + "dat09.dat" );
      break;
    case sphere_grid_type_e::SPHERE_GRID_STANDARD:
      full_content_bytes = fileToBytes( INPUT_FOLDER + ABMAP_FOLDER + "dat10.dat" );
      break;
    case sphere_grid_type_e::SPHERE_GRID_EXPERT:
      full_content_bytes = fileToBytes( INPUT_FOLDER + ABMAP_FOLDER + "dat11.dat" );
      break;
    default:
      break;
  }
  std::vector<char> temp_bytes = std::vector<char>( full_content_bytes.begin() + CONTENT_OFFSET, full_content_bytes.end() );

  for (size_t i = 0; i < temp_bytes.size(); i++)
  {
    uint8_t copy = read1Byte( temp_bytes, i );
    chunked_content_bytes.push_back( copy );
  }

  unknown1 = read2Bytes( bytes, 0x00 );
  cluster_count = read2Bytes( bytes, 0x02 );
  node_count = read2Bytes( bytes, 0x04 );
  link_count = read2Bytes( bytes, 0x06 );
  unknown2 = read2Bytes( bytes, 0x08 );
  unknown3 = read2Bytes( bytes, 0x0A );
  unknown4 = read2Bytes( bytes, 0x0C );
  unknown5 = read2Bytes( bytes, 0x0E );

  size_t cluster_end = 0x10 + cluster_count * CLUSTER_LENGTH;
  size_t node_end = cluster_end + node_count * NODE_LENGTH;
  for (int i = 0; i < node_count * NODE_LENGTH; i += NODE_LENGTH)
  {
    std::vector<char> copy( bytes.begin() + cluster_end + i, bytes.begin() + cluster_end + i + NODE_LENGTH );
    sphere_grid_node_data_t* node = new sphere_grid_node_data_t( copy );
    nodes.push_back( node );
  }

  for (size_t i = 0; i < chunked_content_bytes.size(); i++)
  {
    sphere_grid_node_data_t& node = *nodes[ i ];
    node.content = chunked_content_bytes[ i ];
  }
}

void sphere_grid_data_t::writeToBytes()
{
  //write2Bytes( bytes, 0x00, unknown1 );
  //write2Bytes( bytes, 0x02, cluster_count );
  //write2Bytes( bytes, 0x04, node_count );
  //write2Bytes( bytes, 0x06, link_count );
  //write2Bytes( bytes, 0x08, unknown2 );
  //write2Bytes( bytes, 0x0A, unknown3 );
  //write2Bytes( bytes, 0x0C, unknown4 );
  //write2Bytes( bytes, 0x0E, unknown5 );
  size_t cluster_end = 0x10 + cluster_count * CLUSTER_LENGTH;
  for (int i = 0; i < node_count; i++)
  {
    sphere_grid_node_data_t& node = *nodes[ i ];
    std::vector<char> copy = node.bytes;
    for (int j = 0; j < NODE_LENGTH; j++)
    {
      write1Byte( bytes, cluster_end + i + j, copy[ j ] );
    }
    write1Byte( full_content_bytes, i + CONTENT_OFFSET, node.content );
  }
}

void sphere_grid_data_t::test() const
{
  bytes_mapper_t::test();
  printf( "____________________Sphere Grid Data______________________\n" );
  printf( "Unknown1: %d\n", unknown1 );
  printf( "Cluster Count: %d\n", cluster_count );
  printf( "Node Count: %d\n", node_count );
  printf( "Link Count: %d\n", link_count );
  printf( "Unknown2: %d\n", unknown2 );
  printf( "Unknown3: %d\n", unknown3 );
  printf( "Unknown4: %d\n", unknown4 );
  printf( "Unknown5: %d\n", unknown5 );
  printf( "Nodes: \n" );
  for (auto& node : nodes)
  {
    node->test();
  }
}

// =======================
// Added destructors
// =======================

enemy_data_t::~enemy_data_t()
{
  delete loot_data;
  delete stats_data;
}

encounter_file_t::~encounter_file_t()
{
  delete formation;
}

field_group_data_t::~field_group_data_t()
{
  for (auto* f : formations) delete f;
}

field_encounter_data_t::~field_encounter_data_t()
{
  for (auto* g : groups) delete g;
}

btl_data_t::~btl_data_t()
{
  for (auto* f : field_battle_data) delete f;
}

sphere_grid_data_t::~sphere_grid_data_t()
{
  for (auto* n : nodes) delete n;
}