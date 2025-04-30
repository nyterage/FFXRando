#pragma once
#include <iostream>
#include <string>
#include <cstdint>
#include "BytesHelper.hpp"
// #define NDEBUG
#include <cassert>

// Use (void) to silence unused warnings.
#define assertm(exp, msg) assert((void(msg), exp));

enum sphere_grid_type_t
{
  SPHERE_GRID_ORIGINAL,
  SPHERE_GRID_STANDARD,
  SPHERE_GRID_EXPERT
};

struct item_t
{
  uint16_t id;
  uint8_t min_quantity = 0;
  uint8_t max_quantity = 0;

  item_t( uint16_t id, uint8_t min_quantity, uint8_t max_quantity ) : id( id ), min_quantity( min_quantity ), max_quantity( max_quantity ) {
    //test();
  }

  uint8_t getMinQuantity() const { return min_quantity; }
  uint8_t getMaxQuantity() const { return max_quantity; }
  uint8_t getAverageQuantity() const { return ( min_quantity + max_quantity ) / 2; }
  uint8_t getStandardDeviation() const { return ( max_quantity - min_quantity ) / 2; }
  void setMinQuantity( uint8_t min ) { min_quantity = min; };
  void setMaxQuantity( uint8_t max ) { max_quantity = max; };
  void test()
  {
    printf( "Item ID: %d\n", id );
    printf( "Min Quantity: %d\n", min_quantity );
    printf( "Max Quantity: %d\n", max_quantity );
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

  gear_data_t( chunk_t& data ) : bytes_mapper_t( data.data ) {
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
  uint8_t primary_drop_chance;
  uint8_t secondary_drop_chance;
  uint8_t steal_chance;
  uint8_t gear_drop_chance;
  uint16_t primary_normal_drop;
  uint16_t primary_normal_drop_rare;
  uint16_t secondary_normal_drop;
  uint16_t secondary_normal_drop_rare;
  uint8_t n_primary_normal_drop;
  uint8_t n_primary_normal_drop_rare;
  uint8_t n_secondary_normal_drop;
  uint8_t n_secondary_normal_drop_rare;
  uint16_t primary_normal_drop_overkill;
  uint16_t primary_normal_drop_overkill_rare;
  uint16_t secondary_normal_drop_overkill;
  uint16_t secondary_normal_drop_overkill_rare;
  uint8_t n_primary_normal_drop_overkill;
  uint8_t n_primary_normal_drop_overkill_rare;
  uint8_t n_secondary_normal_drop_overkill;
  uint8_t n_secondary_normal_drop_overkill_rare;
  uint16_t steal_item;
  uint16_t steal_item_rare;
  uint8_t n_steal_item;
  uint8_t n_steal_item_rare;
  uint16_t bribe_item;
  uint8_t n_bribe_item;
  uint8_t gear_slot_count_byte;
  uint8_t gear_damage_calc;
  uint8_t gear_crit_bonus;
  uint8_t gear_attack_power;
  uint8_t gear_ability_count_byte;
  std::unordered_map<int, uint16_t> weapon_abilities_by_char;
  std::unordered_map<int, uint16_t> gear_abilities_by_char;
  uint8_t zanmato_level_byte;
  uint8_t n_gil_steal;
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
  static int const BYTE_LENGTH = 0x80;
  std::string monster_id;
  size_t initial_offset;
  uint16_t name_offset;
  uint16_t name_key;
  uint16_t sensor_text_offset;
  uint16_t sensor_text_key;
  uint16_t unused_str_offset;
  uint16_t unused_str_key;
  uint16_t scan_text_offset;
  uint16_t scan_text_key;
  uint16_t unused_str2_offset;
  uint16_t unused_str2_key;
  uint32_t hp;
  uint32_t mp;
  uint32_t overkill_threshold;
  uint8_t str;
  uint8_t def;
  uint8_t mag;
  uint8_t mdef;
  uint8_t agi;
  uint8_t luck;
  uint8_t eva;
  uint8_t acc;
  uint8_t flag_map1;
  uint8_t flag_map2;
  uint8_t poison_damage;
  uint8_t element_absorb;
  uint8_t element_immune;
  uint8_t element_resist;
  uint8_t element_weakness;
  uint8_t death_resist;
  uint8_t zombie_resist;
  uint8_t petrify_resist;
  uint8_t poison_resist;
  uint8_t pwr_break_resist;
  uint8_t mag_break_resist;
  uint8_t armor_break_resist;
  uint8_t mental_break_resist;
  uint8_t confuse_resist;
  uint8_t berserk_resist;
  uint8_t provoke_resist;
  uint8_t threaten_chance;
  uint8_t sleep_resist;
  uint8_t silence_resist;
  uint8_t darkness_resist;
  uint8_t shell_resist;
  uint8_t protect_resist;
  uint8_t reflect_resist;
  uint8_t nul_tide_resist;
  uint8_t nul_blaze_resist;
  uint8_t nul_shock_resist;
  uint8_t nul_frost_resist;
  uint8_t regen_resist;
  uint8_t haste_resist;
  uint8_t slow_resist;
  uint16_t auto_statuses;
  uint16_t auto_statuses_temporal;
  uint16_t auto_statuses_extra;
  uint16_t extra_status_immunities;
  std::unordered_map<int, uint16_t> abilities;
  uint16_t forced_action;
  uint16_t index;
  uint16_t model_id;
  uint8_t icon_type;
  uint8_t doom_count;
  uint16_t arena_id;
  uint16_t model_id_other;
  uint8_t always_zero1;
  uint8_t always_zero2;
  uint8_t always_zero3;
  uint8_t always_zero4;

  struct flags1_t
  {
    unsigned int armored : 1;
    unsigned int immune_fractional_damage : 1;
    unsigned int immune_life : 1;
    unsigned int immune_sensor : 1;
    unsigned int unknown_flag : 1;
    unsigned int immune_physical_damage : 1;
    unsigned int immune_magic_damage : 1;
    unsigned int immune_all_damage : 1;
  } flags1;

  struct flags2_t
  {
    unsigned int immune_delay : 1;
    unsigned int immune_slice : 1;
    unsigned int immune_bribe : 1;
  } flags2;

  struct elemement_absorb_flags_t
  {
    unsigned int fire : 1;
    unsigned int ice : 1;
    unsigned int lightning : 1;
    unsigned int water : 1;
    unsigned int holy : 1;
  } element_absorb_flags;

  struct element_immune_flags_t
  {
    unsigned int fire : 1;
    unsigned int ice : 1;
    unsigned int lightning : 1;
    unsigned int water : 1;
    unsigned int holy : 1;
  } element_immune_flags;

  struct element_resist_flags_t
  {
    unsigned int fire : 1;
    unsigned int ice : 1;
    unsigned int lightning : 1;
    unsigned int water : 1;
    unsigned int holy : 1;
  } element_resist_flags;

  struct element_weakness_flags_t
  {
    unsigned int fire : 1;
    unsigned int ice : 1;
    unsigned int lightning : 1;
    unsigned int water : 1;
    unsigned int holy : 1;
  } element_weakness_flags;
  
  union flag1_byte_t
  {
    uint8_t byte;
    struct flags1_t bits;
  } flag1_byte;

  union flag2_byte_t
  {
    uint8_t byte;
    struct flags2_t bits;
  } flag2_byte;

  union element_absorb_byte_t
  {
    uint8_t byte;
    struct elemement_absorb_flags_t bits;
  } element_absorb_byte;

  union element_immune_byte_t
  {
    uint8_t byte;
    struct element_immune_flags_t bits;
  } element_immune_byte;

  union element_resist_byte_t
  {
    uint8_t byte;
    struct element_resist_flags_t bits;
  } element_resist_byte;

  union element_weakness_byte_t
  {
    uint8_t byte;
    struct element_weakness_flags_t bits;
  } element_weakness_byte;

  enemy_stat_data_t( const std::vector<char>& bytes, size_t intial_offset, std::string monster_id ) : bytes_mapper_t( bytes ), initial_offset( intial_offset ), monster_id( monster_id )
  {
    mapBytes();
    mapFlags();
    // writeToBytes( locialization );
    // test();
  }

  void mapBytes();
  void mapFlags();
  void writeToBytes();
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
  void writeStatsData( const enemy_stat_data_t& statsData );
  void test() const override;
};

struct field_data_t final : public bytes_mapper_t
{
  int index;
  uint8_t flag;
  uint8_t quantity;
  uint16_t type;

  field_data_t( chunk_t& data ) : bytes_mapper_t( data.data ), index( data.index )
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

  shop_data_t( chunk_t& data ) : bytes_mapper_t( data.data ), is_gear_shop( data.is_gear_shop_chunk )
  {
    mapBytes();
    // test();
  }
  void mapBytes();
  void writeToBytes();
  void test() const override;
};

struct item_rate_t : public bytes_mapper_t
{
  uint32_t item_rate;

  item_rate_t( chunk_t& data ) : bytes_mapper_t( data.data ), item_rate( read4Bytes( bytes, 0x00 ) )
  {
    // test();
  }

  void writeToBytes();
  void test() const override;
};

struct character_stats_t : public bytes_mapper_t
{
  uint16_t name_offset;
  uint16_t name_key;
  uint32_t base_hp;
  uint32_t base_mp;
  uint8_t base_str;
  uint8_t base_def;
  uint8_t base_mag;
  uint8_t base_mdef;
  uint8_t base_agi;
  uint8_t base_luck;
  uint8_t base_eva;
  uint8_t base_acc;
  uint32_t current_ap;
  uint32_t current_hp;
  uint32_t current_mp;
  uint32_t max_hp;
  uint32_t max_mp;
  uint16_t unknown1;
  uint16_t unknown2;
  uint8_t flags;
  uint8_t current_weapon_id;
  uint8_t current_armor_id;
  uint8_t str;
  uint8_t def;
  uint8_t mag;
  uint8_t mdef;
  uint8_t agi;
  uint8_t luck;
  uint8_t eva;
  uint8_t acc;
  uint8_t poison_damage;
  uint8_t overdrive_mode;
  uint8_t overdrive_current;
  uint8_t overdrive_max;
  uint8_t sphere_level;
  uint8_t sphere_level_used;
  uint8_t unknown3;
  uint32_t ability_field1;
  uint32_t ability_field2;
  uint32_t ability_field3;
  uint32_t encounter_count;
  uint32_t kill_count;
  uint32_t unknown4;
  uint32_t unknown5;
  uint16_t overdrive_mode_counters;
  uint32_t overdrive_mode_flags;
  uint32_t unknown6;
  uint32_t unknown7;

  struct overdrive_flags_t
  {
    unsigned int warrior : 1;
    unsigned int comrade : 1;
    unsigned int stoic : 1;
    unsigned int healer : 1;
    unsigned int tactician : 1;
    unsigned int victim : 1;
    unsigned int dancer : 1;
    unsigned int avenger : 1;
    unsigned int slayer : 1;
    unsigned int hero : 1;
    unsigned int rook : 1;
    unsigned int victor : 1;
    unsigned int coward : 1;
    unsigned int ally : 1;
    unsigned int sufferer : 1;
    unsigned int daredevil : 1;
    unsigned int loner : 1;
    unsigned int unused1 : 1;
    unsigned int unused2 : 1;
    unsigned int aeon : 1;
  } overdrive_learned;

  union overdrive_bytes_t
  {
    uint32_t bytes;
    struct overdrive_flags_t bits;
  } overdrive_bytes;

  character_stats_t( chunk_t& data ) : bytes_mapper_t( data.data )
  {
    mapBytes();
    mapFlags();
    // test();
  }

  void mapBytes();
  void mapFlags();
  void writeToBytes();
  void test() const override;
};

struct aeon_scaling_data_t : public bytes_mapper_t
{
  uint8_t genre_byte;
  uint8_t ap_req_coef1;
  uint8_t ap_req_coef2;
  uint8_t ap_req_coef3;
  uint32_t ap_req_max;
  uint8_t hp_coef1;
  uint8_t hp_coef2;
  uint8_t mp_coef1;
  uint8_t mp_coef2;
  uint8_t str_coef1;
  uint8_t str_coef2;
  uint8_t def_coef1;
  uint8_t def_coef2;
  uint8_t mag_coef1;
  uint8_t mag_coef2;
  uint8_t mdef_coef1;
  uint8_t mdef_coef2;
  uint8_t agi_coef1;
  uint8_t agi_coef2;
  uint8_t eva_coef1;
  uint8_t eva_coef2;
  uint8_t acc_coef1;
  uint8_t acc_coef2;
  uint16_t unknown;

  aeon_scaling_data_t( chunk_t& data ) : bytes_mapper_t( data.data )
  {
    mapBytes();
    //test();
  }

  void mapBytes();
  void writeToBytes();
  void test() const override;
};

struct aeon_stat_data_t : public bytes_mapper_t
{
  uint16_t hp;
  uint16_t mp;
  uint8_t str;
  uint8_t def;
  uint8_t mag;
  uint8_t mdef;
  uint8_t agi;
  uint8_t eva;
  uint8_t acc;
  uint8_t luck;

  aeon_stat_data_t( chunk_t& data ) : bytes_mapper_t( data.data )
  {
    mapBytes();
    // test();
  }

  void mapBytes();
  void writeToBytes();
  void test() const override;
};

struct sphere_grid_node_data_t : public bytes_mapper_t
{
  int16_t x_pos;
  int16_t y_pos;
  uint16_t unknown1;
  uint16_t original_content;
  uint16_t cluster;
  uint16_t unknown2;

  uint8_t content;

  sphere_grid_node_data_t( const std::vector<char>& bytes ) : bytes_mapper_t( bytes )
  {
    mapBytes();
    // test();
  }

  void mapBytes();
  void writeToBytes();
  void test() const override;
};

struct sphere_grid_data_t : public bytes_mapper_t
{
  const int CLUSTER_LENGTH = 16;
  const int NODE_LENGTH = 12;
  const int LINK_LENGTH = 8;
  const int CONTENT_OFFSET = 8;

  sphere_grid_type_t type;
  std::vector<char> full_content_bytes;
  std::vector<uint8_t> chunked_content_bytes;

  uint16_t unknown1;
  uint16_t cluster_count;
  uint16_t node_count;
  uint16_t link_count;
  uint16_t unknown2;
  uint16_t unknown3;
  uint16_t unknown4;
  uint16_t unknown5;

  std::vector<sphere_grid_node_data_t*> nodes;

  sphere_grid_data_t( const std::vector<char>& bytes, sphere_grid_type_t type ) : bytes_mapper_t( bytes ), type( type )
  {
    mapBytes();
    // test();
  }

  void mapBytes();
  void writeToBytes();
  void test() const override;
};

struct data_pack_t
{
  std::vector<enemy_data_t*>& enemy_data;
  std::vector<field_data_t*>& field_data;
  std::vector<shop_data_t*>& item_shop_data;
  std::vector<shop_data_t*>& gear_shop_data;
  std::vector<gear_data_t*>& buki_data;
  std::vector<gear_data_t*>& weapon_data;
  std::vector<gear_data_t*>& shop_arms_data;
  std::vector<item_rate_t*>& item_rate_data;
  std::vector<character_stats_t*>& player_stats_data;
  std::vector<aeon_scaling_data_t*>& aeon_scaling_data;
  std::vector<aeon_stat_data_t*>& aeon_stat_data;
  std::vector<sphere_grid_data_t*>& sphere_grid_data;

  data_pack_t() = default;

  data_pack_t(
    std::vector<enemy_data_t*>& enemy_data,
    std::vector<field_data_t*>& field_data,
    std::vector<shop_data_t*>& item_shop_data,
    std::vector<shop_data_t*>& gear_shop_data,
    std::vector<gear_data_t*>& buki_data,
    std::vector<gear_data_t*>& weapon_data,
    std::vector<gear_data_t*>& shop_arms_data,
    std::vector<item_rate_t*>& item_rate_data,
    std::vector<character_stats_t*>& player_stats_data,
    std::vector<aeon_scaling_data_t*>& aeon_scaling_data,
    std::vector<aeon_stat_data_t*>& aeon_stat_data,
    std::vector<sphere_grid_data_t*>& sphere_grid_data
  ) :
    enemy_data( enemy_data ),
    field_data( field_data ),
    item_shop_data( item_shop_data ),
    gear_shop_data( gear_shop_data ),
    buki_data( buki_data ),
    weapon_data( weapon_data ),
    shop_arms_data( shop_arms_data ),
    item_rate_data( item_rate_data ),
    player_stats_data( player_stats_data ),
    aeon_scaling_data( aeon_scaling_data ),
    aeon_stat_data( aeon_stat_data ),
    sphere_grid_data( sphere_grid_data )
  {}
};

struct options_pack_t
{
  bool randomize_enemy_drops;
  bool randomize_enemy_steals;
  bool randomize_enemy_bribes;
  bool randomize_enemy_gear_drops;
  bool randomize_enemy_stats;
  bool randomize_enemy_stats_defensive;
  bool randomize_enemy_stats_shuffle;
  bool randomize_shops;
  bool randomize_shop_prices;
  bool randomize_field_items;
  bool randomize_gear_abilities;
  bool randomize_player_stats;
  bool randomize_aeon_stat_scaling;
  bool randomize_aeon_base_stats;
  bool shuffle_player_stats;
  bool shuffle_aeon_stat_scaling;
  bool shuffle_aeon_base_stats;
  bool poison_is_deadly;
  bool randomize_starting_overdrive_mode;
  bool randomize_enemy_elemental_affinities;

  bool shuffle_sphere_grid;
  bool randomize_sphere_grid;
  bool empty_sphere_grid;
  bool fill_sphere_grid;
  bool remove_sphere_grid_locks;
  bool upgrade_sphere_nodes;
  bool downgrade_sphere_nodes;

  bool randomize_key_items;
  bool randomize_celestials;
  bool randomize_brotherhood;
  bool keep_things_sane;
  int32_t seed;
  std::string seed_text;

  bool fahrenheit;

  options_pack_t(
    bool randomize_enemy_drops,
    bool randomize_enemy_steals,
    bool randomize_enemy_bribes,
    bool randomize_enemy_gear_drops,
    bool randomize_enemy_stats,
    bool randomize_enemy_stats_defensive,
    bool randomize_enemy_stats_shuffle,
    bool randomize_shops,
    bool randomize_shop_prices,
    bool randomize_field_items,
    bool randomize_gear_abilities,
    bool randomize_player_stats,
    bool randomize_aeon_stat_scaling,
    bool randomize_aeon_base_stats,
    bool shuffle_player_stats,
    bool shuffle_aeon_stat_scaling,
    bool shuffle_aeon_base_stats,
    bool poison_is_deadly,
    bool randomize_starting_overdrive_mode,
    bool randomize_enemy_elemental_affinities,
    bool shuffle_sphere_grid,
    bool randomize_sphere_grid,
    bool empty_sphere_grid,
    bool fill_sphere_grid,
    bool remove_sphere_grid_locks,
    bool upgrade_sphere_nodes,
    bool downgrade_sphere_nodes,
    bool randomize_key_items,
    bool randomize_celestials,
    bool randomize_brotherhood,
    bool keep_things_sane,
    int32_t seed,
    std::string seed_text,
    bool fahrenheit
  ) :
  randomize_enemy_drops( randomize_enemy_drops ),
    randomize_enemy_steals( randomize_enemy_steals ),
    randomize_enemy_bribes( randomize_enemy_bribes ),
    randomize_enemy_gear_drops( randomize_enemy_gear_drops ),
    randomize_enemy_stats( randomize_enemy_stats ),
    randomize_enemy_stats_defensive( randomize_enemy_stats_defensive ),
    randomize_enemy_stats_shuffle( randomize_enemy_stats_shuffle ),
    randomize_shops( randomize_shops ),
    randomize_shop_prices( randomize_shop_prices ),
    randomize_field_items( randomize_field_items ),
    randomize_gear_abilities( randomize_gear_abilities ),
    randomize_player_stats( randomize_player_stats ),
    randomize_aeon_stat_scaling( randomize_aeon_stat_scaling ),
    randomize_aeon_base_stats( randomize_aeon_base_stats ),
    shuffle_player_stats( shuffle_player_stats ),
    shuffle_aeon_stat_scaling( shuffle_aeon_stat_scaling ),
    shuffle_aeon_base_stats( shuffle_aeon_base_stats ),
    poison_is_deadly( poison_is_deadly ),
    randomize_starting_overdrive_mode( randomize_starting_overdrive_mode ),
    randomize_enemy_elemental_affinities( randomize_enemy_elemental_affinities ),
    shuffle_sphere_grid( shuffle_sphere_grid ),
    randomize_sphere_grid( randomize_sphere_grid ),
    empty_sphere_grid( empty_sphere_grid ),
    fill_sphere_grid( fill_sphere_grid ),
    remove_sphere_grid_locks( remove_sphere_grid_locks ),
    upgrade_sphere_nodes( upgrade_sphere_nodes ),
    downgrade_sphere_nodes( downgrade_sphere_nodes ),
    randomize_key_items( randomize_key_items ),
    randomize_celestials( randomize_celestials ),
    randomize_brotherhood( randomize_brotherhood ),
    keep_things_sane( keep_things_sane ),
    seed( seed ),
    seed_text( seed_text ),
    fahrenheit( fahrenheit )
  {}
};

// Constant values
static constexpr int ENEMY_COUNT = 360;
// Versioning
static constexpr int MAJOR_VERSION = 1;
static constexpr int MINOR_VERSION = 1;
static constexpr int PATCH_VERSION = 1;
// Information
static const std::string VERSION = "v" + std::to_string( MAJOR_VERSION ) + "." + std::to_string( MINOR_VERSION ) + "." + std::to_string( PATCH_VERSION );
static const std::string AUTHOR = "Taeznak";
static const std::string NAME = "FFXRando";
static const std::string DESCRIPTION = "A randomizer for Final Fantasy X";

// Path data
static const std::string INPUT_FOLDER = "input/";
static const std::string OUTPUT_FOLDER = "output/";
static const std::string FAHRENHEIT_PREFIX = "FFXRando/efl/x/";
static const std::string FFX_FOLDER = "/ffx_ps2/ffx/";
static const std::string JPPC_FOLDER = FFX_FOLDER + "/master/jppc/";
static const std::string USPC_FOLDER = FFX_FOLDER + "/master/new_uspc/";
static const std::string USPC_BTL_KERN_FOLDER = USPC_FOLDER + "/battle/kernel/";
static const std::string CHPC_FOLDER = FFX_FOLDER + "/master/new_chpc/";
static const std::string CHPC_BTL_KERN_FOLDER = CHPC_FOLDER + "/battle/kernel/";
static const std::string DEPC_FOLDER = FFX_FOLDER + "/master/new_depc/";
static const std::string DEPC_BTL_KERN_FOLDER = DEPC_FOLDER + "/battle/kernel/";
static const std::string FRPC_FOLDER = FFX_FOLDER + "/master/new_frpc/";
static const std::string FRPC_BTL_KERN_FOLDER = FRPC_FOLDER + "/battle/kernel/";
static const std::string ITPC_FOLDER = FFX_FOLDER + "/master/new_itpc/";
static const std::string ITPC_BTL_KERN_FOLDER = ITPC_FOLDER + "/battle/kernel/";
static const std::string NEW_JPPC_FOLDER = FFX_FOLDER + "/master/new_jppc/";
static const std::string NEW_JPPC_BTL_KERN_FOLDER = NEW_JPPC_FOLDER + "/battle/kernel/";
static const std::string KRPC_FOLDER = FFX_FOLDER + "/master/new_krpc/";
static const std::string KRPC_BTL_KERN_FOLDER = KRPC_FOLDER + "/battle/kernel/";
static const std::string SPPC_FOLDER = FFX_FOLDER + "/master/new_sppc/";
static const std::string SPPC_BTL_KERN_FOLDER = SPPC_FOLDER + "/battle/kernel/";
static const std::string BATTLE_FOLDER = JPPC_FOLDER + "/battle/";
static const std::string BATTLE_KERNEL_FOLDER = BATTLE_FOLDER + "/kernel/";
static const std::string MONSTER_FOLDER = BATTLE_FOLDER + "/mon/";
static const std::string ABMAP_FOLDER = JPPC_FOLDER + "/menu/abmap/";

static const std::unordered_map<std::string, std::string> LOCALIZATIONS = {
  { "ch", CHPC_BTL_KERN_FOLDER},
  { "de", DEPC_BTL_KERN_FOLDER},
  { "fr", FRPC_BTL_KERN_FOLDER},
  { "it", ITPC_BTL_KERN_FOLDER},
  { "jp", NEW_JPPC_BTL_KERN_FOLDER},
  { "kr", KRPC_BTL_KERN_FOLDER},
  { "sp", SPPC_BTL_KERN_FOLDER},
  { "us", USPC_BTL_KERN_FOLDER}
};