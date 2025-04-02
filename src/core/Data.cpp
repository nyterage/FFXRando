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
  std::cout << "Is Buki Get: " << is_buki_get << std::endl;
  if (!is_buki_get)
  {
    std::cout << "Byte 00 Name ID Maybe: " << byte00_name_id_maybe << std::endl;
    std::cout << "Byte 01 Name ID Maybe: " << byte01_name_id_maybe << std::endl;
    std::cout << "Byte 02 Exists Maybe: " << byte02_exists_maybe << std::endl;
    std::cout << "Misc Flags: " << misc_flags << std::endl;
    std::cout << "Character ID: " << character_id << std::endl;
    std::cout << "Armor Byte: " << armor_byte << std::endl;
    std::cout << "Byte 06 Equipper Maybe: " << byte06_equipper_maybe << std::endl;
    std::cout << "Byte 07 Equipper Maybe: " << byte07_equipper_maybe << std::endl;
    std::cout << "Damage Calc: " << damage_calc << std::endl;
    std::cout << "Attack Power: " << attack_power << std::endl;
    std::cout << "Crit Bonus: " << crit_bonus << std::endl;
    std::cout << "Slots: " << slots << std::endl;
    std::cout << "Model ID: " << model_id << std::endl;
    std::cout << "Ability Slot 1: " << ability_slot1 << std::endl;
    std::cout << "Ability Slot 2: " << ability_slot2 << std::endl;
    std::cout << "Ability Slot 3: " << ability_slot3 << std::endl;
    std::cout << "Ability Slot 4: " << ability_slot4 << std::endl;
  }
  else
  {
    std::cout << "Misc Flags: " << misc_flags << std::endl;
    std::cout << "Character ID: " << character_id << std::endl;
    std::cout << "Armor Byte: " << armor_byte << std::endl;
    std::cout << "Byte 03 Constant Zero: " << byte03_constant_zero << std::endl;
    std::cout << "Damage Calc: " << damage_calc << std::endl;
    std::cout << "Attack Power: " << attack_power << std::endl;
    std::cout << "Crit Bonus: " << crit_bonus << std::endl;
    std::cout << "Slots: " << slots << std::endl;
    std::cout << "Ability Slot 1: " << ability_slot1 << std::endl;
    std::cout << "Ability Slot 2: " << ability_slot2 << std::endl;
    std::cout << "Ability Slot 3: " << ability_slot3 << std::endl;
    std::cout << "Ability Slot 4: " << ability_slot4 << std::endl;
  }
  std::cout << "Is Armor: " << is_armor << std::endl;
  std::cout << "Is Flag 1: " << is_flag1 << std::endl;
  std::cout << "Is Hidden in Menu: " << is_hidden_in_menu << std::endl;
  std::cout << "Is Celestial: " << is_celestial << std::endl;
  std::cout << "Is Brotherhood: " << is_brotherhood << std::endl;
  std::cout << "Is Unknown Flag: " << is_unknown_flag << std::endl;
}

void gear_data_t::mapAbilities( std::vector<uint16_t>& abilities )
{
  if (ability_slot1 != 0 && ability_slot1 != 255)
  {
    bool found = std::find( abilities.begin(), abilities.end(), ability_slot1 ) != abilities.end();
    if (!found)
      abilities.push_back( ability_slot1 );
  }
  if (ability_slot2 != 0 && ability_slot2 != 255)
  {
    bool found = std::find( abilities.begin(), abilities.end(), ability_slot2 ) != abilities.end();
    if (!found)
      abilities.push_back( ability_slot2 );
  }
  if (ability_slot3 != 0 && ability_slot3 != 255)
  {
    bool found = std::find( abilities.begin(), abilities.end(), ability_slot3 ) != abilities.end();
    if (!found)
      abilities.push_back( ability_slot3 );
  }
  if (ability_slot4 != 0 && ability_slot4 != 255)
  {
    bool found = std::find( abilities.begin(), abilities.end(), ability_slot4 ) != abilities.end();
    if (!found)
      abilities.push_back( ability_slot4 );
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
  std::cout << "Monster ID: " << monster_id << std::endl;
  std::cout << "Gil: " << gil << std::endl;
  std::cout << "AP: " << ap << std::endl;
  std::cout << "AP Overkill: " << ap_overkill << std::endl;
  std::cout << "Ronso Rage: " << ronso_rage << std::endl;
  std::cout << "Primary Drop Chance: " << primary_drop_chance << std::endl;
  std::cout << "Secondary Drop Chance: " << secondary_drop_chance << std::endl;
  std::cout << "Steal Chance: " << steal_chance << std::endl;
  std::cout << "Gear Drop Chance: " << gear_drop_chance << std::endl;
  std::cout << "Primary Normal Drop: " << primary_normal_drop << std::endl;
  std::cout << "Primary Normal Drop Rare: " << primary_normal_drop_rare << std::endl;
  std::cout << "Secondary Normal Drop: " << secondary_normal_drop << std::endl;
  std::cout << "Secondary Normal Drop Rare: " << secondary_normal_drop_rare << std::endl;
  std::cout << "N Primary Normal Drop: " << n_primary_normal_drop << std::endl;
  std::cout << "N Primary Normal Drop Rare: " << n_primary_normal_drop_rare << std::endl;
  std::cout << "N Secondary Normal Drop: " << n_secondary_normal_drop << std::endl;
  std::cout << "N Secondary Normal Drop Rare: " << n_secondary_normal_drop_rare << std::endl;
  std::cout << "Primary Normal Drop Overkill: " << primary_normal_drop_overkill << std::endl;
  std::cout << "Primary Normal Drop Overkill Rare: " << primary_normal_drop_overkill_rare << std::endl;
  std::cout << "Secondary Normal Drop Overkill: " << secondary_normal_drop_overkill << std::endl;
  std::cout << "Secondary Normal Drop Overkill Rare: " << secondary_normal_drop_overkill_rare << std::endl;
  std::cout << "N Primary Normal Drop Overkill: " << n_primary_normal_drop_overkill << std::endl;
  std::cout << "N Primary Normal Drop Overkill Rare: " << n_primary_normal_drop_overkill_rare << std::endl;
  std::cout << "N Secondary Normal Drop Overkill: " << n_secondary_normal_drop_overkill << std::endl;
  std::cout << "N Secondary Normal Drop Overkill Rare: " << n_secondary_normal_drop_overkill_rare << std::endl;
  std::cout << "Steal Item: " << steal_item << std::endl;
  std::cout << "Steal Item Rare: " << steal_item_rare << std::endl;
  std::cout << "N Steal Item: " << n_steal_item << std::endl;
  std::cout << "N Steal Item Rare: " << n_steal_item_rare << std::endl;
  std::cout << "Bribe Item: " << bribe_item << std::endl;
  std::cout << "N Bribe Item: " << n_bribe_item << std::endl;
  std::cout << "Gear Slot Count Byte: " << gear_slot_count_byte << std::endl;
  std::cout << "Gear Damage Calc: " << gear_damage_calc << std::endl;
  std::cout << "Gear Crit Bonus: " << gear_crit_bonus << std::endl;
  std::cout << "Gear Attack Power: " << gear_attack_power << std::endl;
  std::cout << "Gear Ability Count Byte: " << gear_ability_count_byte << std::endl;
  std::cout << "Weapon Abilities by Char: " << std::endl;
  for (int chr = 0; chr < 7; chr++)
  {
    std::cout << "Character " << chr << ": ";
    for (int i = 0; i < 8; i++)
    {
      std::cout << weapon_abilities_by_char.at( chr ) << " ";
    }
    std::cout << std::endl;
  }
  std::cout << "Gear Abilities by Char: " << std::endl;
  for (int chr = 0; chr < 7; chr++)
  {
    std::cout << "Character " << chr << ": ";
    for (int i = 0; i < 8; i++)
    {
      std::cout << gear_abilities_by_char.at( chr ) << " ";
    }
    std::cout << std::endl;
  }
  std::cout << "Zanmato Level Byte: " << zanmato_level_byte << std::endl;
  std::cout << "N Gil Steal: " << n_gil_steal << std::endl;
  std::cout << "Arena Price: " << arena_price << std::endl;
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
  //name = read4Bytes( bytes, 0x00 );
  //sensor_text = read4Bytes( bytes, 0x04 );
  //unused_str = read4Bytes( bytes, 0x08 );
  //scan_text = read4Bytes( bytes, 0x0C );
  //unused_str2 = read4Bytes( bytes, 0x10 );
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

//void enemy_stat_data_t::mapStrings( const std::string& localization )
//{
//  name.readAndSetLocalizedContent( localization, bytes, name_offset, name_key );
//  sensor_text.readAndSetLocalizedContent( localization, bytes, sensor_text_offset, sensor_text_key );
//  unused_str.readAndSetLocalizedContent( localization, bytes, unused_str_offset, unused_str_key );
//  scan_text.readAndSetLocalizedContent( localization, bytes, scan_text_offset, scan_text_key );
//  unused_str2.readAndSetLocalizedContent( localization, bytes, unused_str2_offset, unused_str2_key );
//}

//std::vector<KeyedString> enemy_stat_data_t::streamKeyedStrings( const std::string& localization ) const
//{
//  std::vector<KeyedString> result;
//  result.push_back( name.getLocalizedContent( localization ) );
//  result.push_back( sensor_text.getLocalizedContent( localization ) );
//  result.push_back( unused_str.getLocalizedContent( localization ) );
//  result.push_back( scan_text.getLocalizedContent( localization ) );
//  result.push_back( unused_str2.getLocalizedContent( localization ) );
//  return result;
//}

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
  write1Byte( bytes, 0x28, flag_map1 );
  write1Byte( bytes, 0x29, flag_map2 );
  write1Byte( bytes, 0x2A, poison_damage );
  write1Byte( bytes, 0x2B, element_absorb );
  write1Byte( bytes, 0x2C, element_immune );
  write1Byte( bytes, 0x2D, element_resist );
  write1Byte( bytes, 0x2E, element_weakness );
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
    write2Bytes( bytes, 0x50 + i * 2, abilities.at( i ) );
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

  flag1_byte.bits = { flags1.armored, flags1.immune_fractional_damage, flags1.immune_life, flags1.immune_sensor, flags1.unknown_flag, flags1.immune_physical_damage, flags1.immune_magic_damage, flags1.immune_all_damage };
  flag_map1 = flag1_byte.byte;

  flag2_byte.bits = { flags2.immune_delay, flags2.immune_slice, flags2.immune_bribe };
  flag_map2 = flag2_byte.byte;

  element_absorb_byte.bits = { element_absorb_flags.fire, element_absorb_flags.ice, element_absorb_flags.lightning, element_absorb_flags.water, element_absorb_flags.holy };
  element_absorb = element_absorb_byte.byte;

  element_immune_byte.bits = { element_immune_flags.fire, element_immune_flags.ice, element_immune_flags.lightning, element_immune_flags.water, element_immune_flags.holy };
  element_immune = element_immune_byte.byte;

  element_resist_byte.bits = { element_resist_flags.fire, element_resist_flags.ice, element_resist_flags.lightning, element_resist_flags.water, element_resist_flags.holy };
  element_resist = element_resist_byte.byte;

  element_weakness_byte.bits = { element_weakness_flags.fire, element_weakness_flags.ice, element_weakness_flags.lightning, element_weakness_flags.water, element_weakness_flags.holy };
  element_weakness = element_weakness_byte.byte;
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
  printf( "Flags: %d %d %d %d %d %d %d %d\n", flags1.armored, flags1.immune_fractional_damage, flags1.immune_life, flags1.immune_sensor, flags1.unknown_flag, flags1.immune_physical_damage, flags1.immune_magic_damage, flags1.immune_all_damage );
  printf( "Element Absorb Flags:\n" );
  printf( "Absorb Fire: %d\n", element_absorb_flags.fire );
  printf( "Absorb Ice: %d\n", element_absorb_flags.ice );
  printf( "Absorb Lightning: %d\n", element_absorb_flags.lightning );
  printf( "Absorb Water: %d\n", element_absorb_flags.water );
  printf( "Absorb Holy: %d\n", element_absorb_flags.holy );
  printf( "Element Immune Flags:\n" );
  printf( "Immune Fire: %d\n", element_immune_flags.fire );
  printf( "Immune Ice: %d\n", element_immune_flags.ice );
  printf( "Immune Lightning: %d\n", element_immune_flags.lightning );
  printf( "Immune Water: %d\n", element_immune_flags.water );
  printf( "Immune Holy: %d\n", element_immune_flags.holy );
  printf( "Element Resist Flags:\n" );
  printf( "Resist Fire: %d\n", element_resist_flags.fire );
  printf( "Resist Ice: %d\n", element_resist_flags.ice );
  printf( "Resist Lightning: %d\n", element_resist_flags.lightning );
  printf( "Resist Water: %d\n", element_resist_flags.water );
  printf( "Resist Holy: %d\n", element_resist_flags.holy );
  printf( "Element Weakness Flags:\n" );
  printf( "Weakness Fire: %d\n", element_weakness_flags.fire );
  printf( "Weakness Ice: %d\n", element_weakness_flags.ice );
  printf( "Weakness Lightning: %d\n", element_weakness_flags.lightning );
  printf( "Weakness Water: %d\n", element_weakness_flags.water );
  printf( "Weakness Holy: %d\n", element_weakness_flags.holy );
}

void enemy_stat_data_t::mapFlags()
{
  flags1.armored = ( flag_map1 & 0x01 ) > 0;
  flags1.immune_fractional_damage = ( flag_map1 & 0x02 ) > 0;
  flags1.immune_life = ( flag_map1 & 0x04 ) > 0;
  flags1.immune_sensor = ( flag_map1 & 0x08 ) > 0;
  flags1.unknown_flag = ( flag_map1 & 0x10 ) > 0;
  flags1.immune_physical_damage = ( flag_map1 & 0x20 ) > 0;
  flags1.immune_magic_damage = ( flag_map1 & 0x40 ) > 0;
  flags1.immune_all_damage = ( flag_map1 & 0x80 ) > 0;

  flags2.immune_delay = ( flag_map2 & 0x01 ) > 0;
  flags2.immune_slice = ( flag_map2 & 0x02 ) > 0;
  flags2.immune_bribe = ( flag_map2 & 0x04 ) > 0;

  element_absorb_flags.fire = ( element_absorb & 0x01 ) > 0;
  element_absorb_flags.ice = ( element_absorb & 0x02 ) > 0;
  element_absorb_flags.lightning = ( element_absorb & 0x04 ) > 0;
  element_absorb_flags.water = ( element_absorb & 0x08 ) > 0;
  element_absorb_flags.holy = ( element_absorb & 0x10 ) > 0;

  element_immune_flags.fire = ( element_immune & 0x01 ) > 0;
  element_immune_flags.ice = ( element_immune & 0x02 ) > 0;
  element_immune_flags.lightning = ( element_immune & 0x04 ) > 0;
  element_immune_flags.water = ( element_immune & 0x08 ) > 0;
  element_immune_flags.holy = ( element_immune & 0x10 ) > 0;

  element_resist_flags.fire = ( element_resist & 0x01 ) > 0;
  element_resist_flags.ice = ( element_resist & 0x02 ) > 0;
  element_resist_flags.lightning = ( element_resist & 0x04 ) > 0;
  element_resist_flags.water = ( element_resist & 0x08 ) > 0;
  element_resist_flags.holy = ( element_resist & 0x10 ) > 0;

  element_weakness_flags.fire = ( element_weakness & 0x01 ) > 0;
  element_weakness_flags.ice = ( element_weakness & 0x02 ) > 0;
  element_weakness_flags.lightning = ( element_weakness & 0x04 ) > 0;
  element_weakness_flags.water = ( element_weakness & 0x08 ) > 0;
  element_weakness_flags.holy = ( element_weakness & 0x10 ) > 0;
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
    bytes[ loot_data->initial_offset + i ] = loot_bytes[ i ];
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
  type = read1Byte( bytes, 0x02 ) + read1Byte( bytes, 0x03 ) * 0x100;
}

void field_data_t::writeToBytes()
{
  write1Byte( bytes, 0x00, flag );
  write1Byte( bytes, 0x01, quantity );
  write1Byte( bytes, 0x02, type & 0xFF );
  write1Byte( bytes, 0x03, ( type >> 8 ) & 0xFF00 );
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

void item_rate_t::writeToBytes()
{
  write4Bytes( bytes, 0x00, item_rate );
}

void item_rate_t::test() const
{
  bytes_mapper_t::test();
  std::cout << "Item Rate: " << item_rate << std::endl;
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
}

void character_stats_t::test() const
{
  bytes_mapper_t::test();
  printf( "Index: %d\n", index );
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
  printf( "Ability Field 2: %d\n", ability_field2 );
  printf( "Ability Field 3: %d\n", ability_field3 );
  printf( "Encounter Count: %d\n", encounter_count );
  printf( "Kill Count: %d\n", kill_count );
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
    aeon_scaling_data.push_back( this );
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
  printf( "Index: %d\n", index );
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