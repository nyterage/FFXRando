#pragma once
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <chrono>
#include <sstream>
#include <string>
#include <vector>
#include <cstdint>
#include "BytesHelper.hpp"
// #include "/FFXDataParser/"
struct item_t
{
  uint16_t id;
  int min_quantity = 0;
  int max_quantity = 0;

  item_t( uint16_t& id, int& min_quantity, int& max_quantity ) : id( id ), min_quantity( min_quantity ), max_quantity( max_quantity ) {}

  int getMinQuantity() const { return this->min_quantity; }
  int getMaxQuantity() const { return this->max_quantity; }
  int getAverageQuantity() const { return ( this->min_quantity + this->max_quantity ) / 2; }
  int getStandardDeviation() const { return ( this->max_quantity - this->min_quantity ) / 2; }
  void setMinQuantity( int min_quantity ) { this->min_quantity = min_quantity; };
  void setMaxQuantity( int max_quantity ) { this->max_quantity = max_quantity; };
  void test()
  {
    std::cout << "Item ID: " << id << std::endl;
    std::cout << "Min Quantity: " << min_quantity << std::endl;
    std::cout << "Max Quantity: " << max_quantity << std::endl;
  }
};

struct gear_data_t final : public bytes_mapper_t
{
  bool is_buki_get;
  uint8_t byte00_name_id_maybe;
  uint8_t byte01_name_id_maybe;
  uint8_t byte02_exists_maybe;
  uint8_t byte03_constant_zero;
  uint16_t model_id;
  uint8_t misc_flags;
  uint8_t character_id;
  uint8_t armor_byte;
  uint8_t byte06_equipper_maybe;
  uint8_t byte07_equipper_maybe;
  uint8_t damage_calc;
  uint8_t attack_power;
  uint8_t crit_bonus;
  uint8_t slots;
  uint16_t ability_slot1;
  uint16_t ability_slot2;
  uint16_t ability_slot3;
  uint16_t ability_slot4;

  bool is_armor;
  bool is_flag1;
  bool is_hidden_in_menu;
  bool is_celestial;
  bool is_brotherhood;
  bool is_unknown_flag;

  gear_data_t( const std::vector<char>& bytes ) : bytes_mapper_t( bytes ) {
    is_buki_get = ( bytes.size() == 16 );
    if (is_buki_get)
      mapBytesBukiGet();
    else
      mapBytesNormal();
    mapFlags();
    // test();
  }

  void mapBytesNormal();
  void writeBytesNormal();
  void mapBytesBukiGet();
  void writeBytesBukiGet();
  void writeToBytes();
  void mapFlags();
  void test() const override;

  void mapAbilities( std::vector<uint16_t>& abilities );
};

struct enemy_loot_data_t final : public bytes_mapper_t
{
  static int const BYTE_LENGTH = 0x118;
  std::string monster_id;
  size_t initial_offset;
  size_t end_offset;
  uint16_t gil;
  uint16_t ap;
  uint16_t ap_overkill;
  uint16_t ronso_rage;
  int primary_drop_chance;
  int secondary_drop_chance;
  int steal_chance;
  int gear_drop_chance;
  uint16_t primary_normal_drop;
  uint16_t primary_normal_drop_rare;
  uint16_t secondary_normal_drop;
  uint16_t secondary_normal_drop_rare;
  int n_primary_normal_drop;
  int n_primary_normal_drop_rare;
  int n_secondary_normal_drop;
  int n_secondary_normal_drop_rare;
  uint16_t primary_normal_drop_overkill;
  uint16_t primary_normal_drop_overkill_rare;
  uint16_t secondary_normal_drop_overkill;
  uint16_t secondary_normal_drop_overkill_rare;
  int n_primary_normal_drop_overkill;
  int n_primary_normal_drop_overkill_rare;
  int n_secondary_normal_drop_overkill;
  int n_secondary_normal_drop_overkill_rare;
  uint16_t steal_item;
  uint16_t steal_item_rare;
  int n_steal_item;
  int n_steal_item_rare;
  uint16_t bribe_item;
  int n_bribe_item;
  int gear_slot_count_byte;
  int gear_damage_calc;
  int gear_crit_bonus;
  int gear_attack_power;
  int gear_ability_count_byte;
  std::unordered_map<int, uint16_t> weapon_abilities_by_char;
  std::unordered_map<int, uint16_t> gear_abilities_by_char;
  int zanmato_level_byte;
  int n_gil_steal;
  uint32_t arena_price;

  enemy_loot_data_t( const std::vector<char> bytes, size_t initial_offset, std::string monster_id ) : bytes_mapper_t( bytes ), initial_offset( initial_offset ), end_offset( initial_offset + BYTE_LENGTH ), monster_id( monster_id )
  {
    mapBytes();
    // test();
  }
  void mapBytes();
  void writeToBytes();
  void test() const override;
};

struct enemy_stat_data_t final : public bytes_mapper_t
{
  std::string monster_id;
  size_t initial_offset;
  int name_offset;
  int name_key;
  int sensor_text_offset;
  int sensor_text_key;
  int unused_str_offset;
  int unused_str_key;
  int scan_text_offset;
  int scan_text_key;
  int unused_str2_offset;
  int unused_str2_key;
  //int name;
  //int sensor_text;
  //int unused_str;
  //int scan_text;
  //int unused_str2;
  uint16_t hp;
  uint16_t mp;
  uint16_t overkill_threshold;
  int str;
  int def;
  int mag;
  int mdef;
  int agi;
  int luck;
  int eva;
  int acc;
  int unk1;
  int unk2;
  int poison_damage;
  int element_absorb;
  int element_immune;
  int element_resist;
  int element_weakness;
  int death_resist;
  int zombie_resist;
  int petrify_resist;
  int poison_resist;
  int pwr_break_resist;
  int mag_break_resist;
  int armor_break_resist;
  int mental_break_resist;
  int confuse_resist;
  int berserk_resist;
  int provoke_resist;
  int threaten_chance;
  int sleep_resist;
  int silence_resist;
  int darkness_resist;
  int shell_resist;
  int protect_resist;
  int reflect_resist;
  int nul_tide_resist;
  int nul_blaze_resist;
  int nul_shock_resist;
  int nul_frost_resist;
  int regen_resist;
  int haste_resist;
  int slow_resist;
  int auto_statuses;
  int auto_statuses_temporal;
  int auto_statuses_extra;
  int extra_status_immunities;
  std::unordered_map<int, uint16_t> abilities;
  int forced_action;
  int index;
  int model_id;
  int icon_type;
  int doom_count;
  int arena_id;
  int model_id_other;
  int always_zero1;
  int always_zero2;
  int always_zero3;
  int always_zero4;

  enemy_stat_data_t( const std::vector<char>& bytes, std::string locialization, size_t intial_offset, std::string monster_id ) : bytes_mapper_t( bytes ), initial_offset( intial_offset ), monster_id( monster_id )
  {
    mapBytes();
    // writeToBytes( locialization );
    // test();
  }

  void mapBytes();
  // void mapStrings( const std::string& localization );
  // std::vector<KeyedString> streamKeyedStrings( const std::string& localization ) const override;
  void writeToBytes( const std::string& localization );
  void test() const override;
};

struct enemy_data_t final : public bytes_mapper_t
{
  std::string monster_id;
  std::vector<char> script;
  std::vector<char> mapping_bytes;
  std::vector<char> stats_bytes;
  std::vector<char> chunk_3_bytes;  // Unknown
  std::vector<char> loot_bytes;
  std::vector<char> audio_bytes;
  std::vector<char> text_bytes;
  std::vector<chunk_t> chunks;
  enemy_loot_data_t* loot_data;
  enemy_stat_data_t* stats_data;

  enemy_data_t( std::string id, const std::vector<char>& bytes )
    : bytes_mapper_t( bytes ), monster_id( id ), chunks( bytesToChunks( bytes, read4Bytes( bytes, 0x00 ), 4 ) ), loot_data( nullptr ), stats_data( nullptr )
  {
    mapChunks();
    // test();
  }

  void mapChunks();
  void writeLootData( const enemy_loot_data_t& lootData );
  void test() const override;
};

struct field_data_t final : public bytes_mapper_t
{
  uint8_t flag;
  int quantity;
  uint16_t type;

  field_data_t( const std::vector<char>& bytes ) : bytes_mapper_t( bytes )
  {
    mapBytes();
    // test();
  }

  void mapBytes();
  void writeToBytes();
  void test() const override;
};

struct shop_data_t final : public bytes_mapper_t
{
  uint16_t pricesUnused;
  std::vector<uint16_t> item_indexes;
  bool is_gear_shop;

  shop_data_t( const std::vector<char>& bytes, bool gear ) : bytes_mapper_t( bytes ), is_gear_shop( gear )
  {
    mapBytes();
    // test();
  }
  void mapBytes();
  void writeToBytes();
  void test() const override;
};

// Constant values
static constexpr int ENEMY_COUNT = 360;
static const std::unordered_map<std::string, std::string> LOCALIZATIONS = {
  { "ch", "Chinese"},
  { "de", "German"},
  { "fr", "French"},
  { "it", "Italian"},
  { "jp", "Japanese"},
  { "kr", "Korean"},
  { "sp", "Spanish"},
  { "us", "English"}
};

// Path data
static const std::string INPUT_FOLDER = "input/";
static const std::string OUTPUT_FOLDER = "output/";
static const std::string FFX_FOLDER = "/ffx_ps2/ffx/";
static const std::string JPPC_FOLDER = FFX_FOLDER + "/master/jppc/";
static const std::string BATTLE_FOLDER = JPPC_FOLDER + "/battle/";
static const std::string BATTLE_KERNEL_FOLDER = BATTLE_FOLDER + "/kernel/";
static const std::string MONSTER_FOLDER = BATTLE_FOLDER + "/mon/";

// Dynamic data
static std::unordered_map<int, enemy_data_t*> enemy_data;
static std::unordered_map<int, field_data_t*> field_data;
static std::unordered_map<int, shop_data_t*> item_shop_data;
static std::unordered_map<int, shop_data_t*> gear_shop_data;
static std::unordered_map<int, gear_data_t*> buki_data;
static std::unordered_map<int, gear_data_t*> weapon_data;
static std::unordered_map<int, gear_data_t*> shop_arms_data;

// All Items Data, key is the item id, minimum and maximum quanities able to be obtained stored in the vector.
// This includes Key items obtained from chests! For non key items, use all_non_key_items.
static std::unordered_map<int, item_t*> all_items;
static std::unordered_map<int, item_t*> all_non_key_items;
