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
  unk1 = read1Byte( bytes, 0x28 );
  unk2 = read1Byte( bytes, 0x29 );
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

void enemy_stat_data_t::writeToBytes( const std::string& localization )
{
  std::vector<char> newBytes;
  write2Bytes( newBytes, 0x00, name_offset );
  write2Bytes( newBytes, 0x02, name_key );
  write2Bytes( newBytes, 0x04, sensor_text_offset );
  write2Bytes( newBytes, 0x06, sensor_text_key );
  write2Bytes( newBytes, 0x08, unused_str_offset );
  write2Bytes( newBytes, 0x0A, unused_str_key );
  write2Bytes( newBytes, 0x0C, scan_text_offset );
  write2Bytes( newBytes, 0x0E, scan_text_key );
  write2Bytes( newBytes, 0x10, unused_str2_offset );
  write2Bytes( newBytes, 0x12, unused_str2_key );
  write4Bytes( newBytes, 0x14, hp );
  write4Bytes( newBytes, 0x18, mp );
  write4Bytes( newBytes, 0x1C, overkill_threshold );
  write1Byte( newBytes, 0x20, str );
  write1Byte( newBytes, 0x21, def );
  write1Byte( newBytes, 0x22, mag );
  write1Byte( newBytes, 0x23, mdef );
  write1Byte( newBytes, 0x24, agi );
  write1Byte( newBytes, 0x25, luck );
  write1Byte( newBytes, 0x26, eva );
  write1Byte( newBytes, 0x27, acc );
  write1Byte( newBytes, 0x28, unk1 );
  write1Byte( newBytes, 0x29, unk2 );
  write1Byte( newBytes, 0x2A, poison_damage );
  write1Byte( newBytes, 0x2B, element_absorb );
  write1Byte( newBytes, 0x2C, element_immune );
  write1Byte( newBytes, 0x2D, element_resist );
  write1Byte( newBytes, 0x2E, element_weakness );
  write1Byte( newBytes, 0x2F, death_resist );
  write1Byte( newBytes, 0x30, zombie_resist );
  write1Byte( newBytes, 0x31, petrify_resist );
  write1Byte( newBytes, 0x32, poison_resist );
  write1Byte( newBytes, 0x33, pwr_break_resist );
  write1Byte( newBytes, 0x34, mag_break_resist );
  write1Byte( newBytes, 0x35, armor_break_resist );
  write1Byte( newBytes, 0x36, mental_break_resist );
  write1Byte( newBytes, 0x37, confuse_resist );
  write1Byte( newBytes, 0x38, berserk_resist );
  write1Byte( newBytes, 0x39, provoke_resist );
  write1Byte( newBytes, 0x3A, threaten_chance );
  write1Byte( newBytes, 0x3B, sleep_resist );
  write1Byte( newBytes, 0x3C, silence_resist );
  write1Byte( newBytes, 0x3D, darkness_resist );
  write1Byte( newBytes, 0x3E, shell_resist );
  write1Byte( newBytes, 0x3F, protect_resist );
  write1Byte( newBytes, 0x40, reflect_resist );
  write1Byte( newBytes, 0x41, nul_tide_resist );
  write1Byte( newBytes, 0x42, nul_blaze_resist );
  write1Byte( newBytes, 0x43, nul_shock_resist );
  write1Byte( newBytes, 0x44, nul_frost_resist );
  write1Byte( newBytes, 0x45, regen_resist );
  write1Byte( newBytes, 0x46, haste_resist );
  write1Byte( newBytes, 0x47, slow_resist );
  write2Bytes( newBytes, 0x48, auto_statuses );
  write2Bytes( newBytes, 0x4A, auto_statuses_temporal );
  write2Bytes( newBytes, 0x4C, auto_statuses_extra );
  write2Bytes( newBytes, 0x4E, extra_status_immunities );

  for (int i = 0; i < 0x10; i++)
  {
    write2Bytes( newBytes, 0x50 + i * 2, abilities.at( i ) );
  }

  write2Bytes( newBytes, 0x70, forced_action );
  write2Bytes( newBytes, 0x72, index );
  write2Bytes( newBytes, 0x74, model_id );
  write1Byte( newBytes, 0x76, icon_type );
  write1Byte( newBytes, 0x77, doom_count );
  write2Bytes( newBytes, 0x78, arena_id );
  write2Bytes( newBytes, 0x7A, model_id_other );
  write1Byte( newBytes, 0x7C, always_zero1 );
  write1Byte( newBytes, 0x7D, always_zero2 );
  write1Byte( newBytes, 0x7E, always_zero3 );
  write1Byte( newBytes, 0x7F, always_zero4 );
  printf( "New bytes size: %zu\n", newBytes.size() );
}

void enemy_stat_data_t::test() const
{
  bytes_mapper_t::test();
  std::cout << "Name Offset: " << name_offset << std::endl;
  std::cout << "Name Key: " << name_key << std::endl;
  std::cout << "Sensor Text Offset: " << sensor_text_offset << std::endl;
  std::cout << "Sensor Text Key: " << sensor_text_key << std::endl;
  std::cout << "Unused Str Offset: " << unused_str_offset << std::endl;
  std::cout << "Unused Str Key: " << unused_str_key << std::endl;
  std::cout << "Scan Text Offset: " << scan_text_offset << std::endl;
  std::cout << "Scan Text Key: " << scan_text_key << std::endl;
  std::cout << "Unused Str2 Offset: " << unused_str2_offset << std::endl;
  std::cout << "Unused Str2 Key: " << unused_str2_key << std::endl;
  std::cout << "HP: " << hp << std::endl;
  std::cout << "MP: " << mp << std::endl;
  std::cout << "Overkill Threshold: " << overkill_threshold << std::endl;
  std::cout << "STR: " << str << std::endl;
  std::cout << "DEF: " << def << std::endl;
  std::cout << "MAG: " << mag << std::endl;
  std::cout << "MDEF: " << mdef << std::endl;
  std::cout << "AGI: " << agi << std::endl;
  std::cout << "LUCK: " << luck << std::endl;
  std::cout << "EVA: " << eva << std::endl;
  std::cout << "ACC: " << acc << std::endl;
  std::cout << "Unk1: " << unk1 << std::endl;
  std::cout << "Unk2: " << unk2 << std::endl;
  std::cout << "Poison Damage: " << poison_damage << std::endl;
  std::cout << "Element Absorb: " << element_absorb << std::endl;
  std::cout << "Element Immune: " << element_immune << std::endl;
  std::cout << "Element Resist: " << element_resist << std::endl;
  std::cout << "Element Weakness: " << element_weakness << std::endl;
  std::cout << "Death Resist: " << death_resist << std::endl;
  std::cout << "Zombie Resist: " << zombie_resist << std::endl;
  std::cout << "Petrify Resist: " << petrify_resist << std::endl;
  std::cout << "Poison Resist: " << poison_resist << std::endl;
  std::cout << "Pwr Break Resist: " << pwr_break_resist << std::endl;
  std::cout << "Mag Break Resist: " << mag_break_resist << std::endl;
  std::cout << "Armor Break Resist: " << armor_break_resist << std::endl;
  std::cout << "Mental Break Resist: " << mental_break_resist << std::endl;
  std::cout << "Confuse Resist: " << confuse_resist << std::endl;
  std::cout << "Berserk Resist: " << berserk_resist << std::endl;
  std::cout << "Provoke Resist: " << provoke_resist << std::endl;
  std::cout << "Threaten Chance: " << threaten_chance << std::endl;
  std::cout << "Sleep Resist: " << sleep_resist << std::endl;
  std::cout << "Silence Resist: " << silence_resist << std::endl;
  std::cout << "Darkness Resist: " << darkness_resist << std::endl;
  std::cout << "Shell Resist: " << shell_resist << std::endl;
  std::cout << "Protect Resist: " << protect_resist << std::endl;
  std::cout << "Reflect Resist: " << reflect_resist << std::endl;
  std::cout << "Nul Tide Resist: " << nul_tide_resist << std::endl;
  std::cout << "Nul Blaze Resist: " << nul_blaze_resist << std::endl;
  std::cout << "Nul Shock Resist: " << nul_shock_resist << std::endl;
  std::cout << "Nul Frost Resist: " << nul_frost_resist << std::endl;
  std::cout << "Regen Resist: " << regen_resist << std::endl;
  std::cout << "Haste Resist: " << haste_resist << std::endl;
  std::cout << "Slow Resist: " << slow_resist << std::endl;
  std::cout << "Auto Statuses: " << auto_statuses << std::endl;
  std::cout << "Auto Statuses Temporal: " << auto_statuses_temporal << std::endl;
  std::cout << "Auto Statuses Extra: " << auto_statuses_extra << std::endl;
  std::cout << "Extra Status Immunities: " << extra_status_immunities << std::endl;
  std::cout << "Abilities: " << std::endl;
  for (int i = 0; i < 0x10; i++)
  {
    std::cout << abilities.at( i ) << " ";
  }
  std::cout << std::endl;
  std::cout << "Forced Action: " << forced_action << std::endl;
  std::cout << "Index: " << index << std::endl;
  std::cout << "Model ID: " << model_id << std::endl;
  std::cout << "Icon Type: " << icon_type << std::endl;
  std::cout << "Doom Count: " << doom_count << std::endl;
  std::cout << "Arena ID: " << arena_id << std::endl;
  std::cout << "Model ID Other: " << model_id_other << std::endl;
  std::cout << "Always Zero 1: " << always_zero1 << std::endl;
  std::cout << "Always Zero 2: " << always_zero2 << std::endl;
  std::cout << "Always Zero 3: " << always_zero3 << std::endl;
  std::cout << "Always Zero 4: " << always_zero4 << std::endl;
}

void enemy_data_t::mapChunks() {
  script = chunks.at( 0 ).data;
  mapping_bytes = chunks.at( 1 ).data;
  stats_bytes = chunks.at( 2 ).data;
  chunk_3_bytes = chunks.at( 3 ).data;
  loot_bytes = chunks.at( 4 ).data;
  audio_bytes = chunks.at( 5 ).data;
  text_bytes = chunks.at( 6 ).data;

  stats_data = new enemy_stat_data_t( stats_bytes, "en", chunks.at( 2 ).initial_offset, monster_id );
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
  std::cout << "Flag: " << flag << std::endl;
  std::cout << "Quantity: " << quantity << std::endl;
  std::cout << "Type: " << type << std::endl;
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