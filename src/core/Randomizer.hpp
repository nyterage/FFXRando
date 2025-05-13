#pragma once
#include "BytesHelper.hpp"
#include "Data.hpp"
#include "json.hpp"
#include <random>
#include <filesystem>
#include <thread>
#include <vector>

using json = nlohmann::json;

struct randomizer_t
{
private:
  std::mt19937 rng;

  // Static data
  const data_pack_t& data_pack;
  const options_pack_t& options_pack;

  // Dynamically populated data
  std::unordered_map<int, item_t*> all_items;
  std::unordered_map<int, item_t*> all_non_key_items;
  std::unordered_map<int, item_t*> all_key_items;
  std::vector<gear_data_t*> all_armor;
  std::vector<gear_data_t*> all_weapons;
  std::vector<uint16_t> abilities;
  std::vector<uint8_t> weapon_formulas;
  std::vector<uint8_t> def_pool;
  std::vector<uint8_t> mdef_pool;
  std::vector<uint8_t> eva_pool;
  std::vector<uint8_t> original_sphere_grid_node_ids;
  std::vector<uint8_t> standard_sphere_grid_node_ids;
  std::vector<uint8_t> expert_sphere_grid_node_ids;
  std::vector<uint16_t> random_monster_encounter_ids;

  // Shuffled vectors
  std::vector<character_stats_t*> shuffled_player_stats_data;
  std::vector<aeon_scaling_data_t*> shuffled_aeon_scaling_data;
  std::vector<aeon_stat_data_t*> shuffled_aeon_stat_data;
  std::vector<uint8_t> shuffled_original_sphere_grid_node_ids;
  std::vector<uint8_t> shuffled_standard_sphere_grid_node_ids;
  std::vector<uint8_t> shuffled_expert_sphere_grid_node_ids;
  std::vector<uint16_t> shuffled_random_monster_encounter_ids;
  std::unordered_map<uint16_t, uint16_t> paired_mosnter_ids;

  // Lists
  const std::vector<uint16_t> enemy_id_whitelist{ 91, 92, 93, 94, 96, 97, 97, 48, 49, 195, 196, 225, 226, 227, 228, 222, 43, 241, 245, 246, 247, 42, 51, 53, 58, 68, 69, 70, 71, 72, 73, 74, 75, 76, 211 };
  const std::vector<uint16_t> boss_id_whitelist{ 153, 103, 229 };
  std::vector<uint16_t> randomized_monsters{};

public:
  std::string prefix;
  std::string btl_kernel_input;
  std::string btl_kernel_output;

  json json_data;

  randomizer_t( const options_pack_t& options_pack,
                const data_pack_t& data_pack )
    :
    data_pack( data_pack ),
    options_pack( options_pack ),
    all_items(),
    all_non_key_items(),
    all_key_items(),
    all_armor(),
    all_weapons(),
    abilities(),
    def_pool(),
    mdef_pool(),
    eva_pool(),
    original_sphere_grid_node_ids(),
    standard_sphere_grid_node_ids(),
    expert_sphere_grid_node_ids(),
    random_monster_encounter_ids(),
    shuffled_player_stats_data(),
    shuffled_aeon_scaling_data(),
    shuffled_aeon_stat_data(),
    shuffled_original_sphere_grid_node_ids(),
    shuffled_standard_sphere_grid_node_ids(),
    shuffled_expert_sphere_grid_node_ids(),
    shuffled_random_monster_encounter_ids(),
    prefix( options_pack.fahrenheit ? FAHRENHEIT_PREFIX : "" ),
    btl_kernel_input( INPUT_FOLDER + BATTLE_KERNEL_FOLDER ),
    btl_kernel_output( OUTPUT_FOLDER + prefix + BATTLE_KERNEL_FOLDER ),
    json_data()
  {
    rng.seed( options_pack.seed );

    json_data = {
      { "Name", NAME },
      { "Desc", DESCRIPTION },
      { "Authors", AUTHOR },
      { "Link", "https://github.com/nyterage/FFXRando" },
      { "DllList", json::array() },
      { "Dependencies", json::array() },
      { "LoadAfter", json::array() },
      { "Version", VERSION },
      { "Seed", options_pack.seed_text }
    };

    getFieldItems();
    getShopItems();
    getMonsterItems();
    getRandomEncounterIDs();

    if (options_pack.shuffle_sphere_grid)
      getSphereGridNodeIds();

    poplateGearLists();
    populateAbilityData();
    populateWeaponFormulas();
    randomize();
  }

  template <typename T>
  T uniform( T min, T max ) {
    static_assert( std::is_integral<T>::value, "Only integral types are supported" );

    using DistType = typename std::conditional<sizeof( T ) <= 2, uint32_t, T>::type;

    std::uniform_int_distribution<DistType> dist( min, max );
    return static_cast< T >( dist( rng ) );
  }

  template <typename T>
  T normal( T mean, T stddev, T min, T max ) {
    static_assert( std::is_integral<T>::value, "Only integral types are supported" );
    if (mean == 0)
      return 0;

    if (stddev == 0)
      return mean;

    std::normal_distribution<double> dist( static_cast< double >( mean ), static_cast< double >( stddev ) );
    T number;
    do
    {
      double sampled = dist( rng );
      number = static_cast< T >( std::round( sampled ) );
    }
    while (number < min || number > max);

    return number;
  }

  void writeJson( json& j )
  {
    if (!options_pack.fahrenheit)
      return;

    std::cout << std::setw( 4 ) << j << std::endl;
    std::ofstream file( OUTPUT_FOLDER + "FFXRando/FFXRando.manifest.json" );
    file.write( j.dump( 4 ).c_str(), j.dump( 4 ).size() );
  }

  template <typename T>
  void genericReconstructor( const std::string& input_path, const std::string& output_path, const std::string& filename, std::vector<T*>& vector, bool has_header = false )
  {
    std::vector<char> reconstructed_bytes;
    std::string full_path = input_path + filename;
    std::vector<char> bytes = bytes_mapper_t::fileToBytes( full_path );

    if (has_header)
      bytes = std::vector<char>( bytes.begin(), bytes.begin() + 20 );

    reconstructed_bytes.insert( reconstructed_bytes.end(), bytes.begin(), bytes.end() );

    for (auto& element : vector)
    {
      std::vector<char> element_bytes = element->bytes;
      reconstructed_bytes.insert( reconstructed_bytes.end(), element_bytes.begin(), element_bytes.end() );
    }

    std::filesystem::create_directories( output_path );
    std::string file = output_path + filename;
    bytes_mapper_t::writeBytesToNewFile( reconstructed_bytes, file );
  }

  // Sphere Grid
  void reconstructSphereGridData();
  void getSphereGridNodeIds();
  void setRequiredAbilities();
  void shuffleSphereGridNodes();
  void randomizeSphereGridTrue();
  void randomizeSphereGrid();
  void emptySphereGrid();
  void fillSphereGrid();
  void removeSphereGridLocks();
  void upgradeSphereGridNodes();
  void downgradeSphereGridNodes();
  void doSphereGridRandomization();

  // Items
  void reconstructTakaraData();
  void checkItemList( uint16_t& id, uint8_t& quantity, bool key = false );
  void getFieldItems();
  void getMonsterItems();
  void getShopItems();
  item_t* getRandomItem();
  item_t* getRandomKeyItem();
  int getRandomItemQuantity( item_t* item, bool is_monster = true );
  void randomizeFieldItems();
  void doFieldRandomization();

  // Gear
  void reconstructBukiData();
  void reconstructWeaponData();
  void reconstructShopArmsData();
  void poplateGearLists();
  uint16_t getRandomAbility();
  void populateAbilityData();
  uint8_t getRandomFormula();
  void populateWeaponFormulas();
  void writeGearData( gear_data_t& gear );
  void randomizeShopArmsAbilities();
  void randomizeBukiAbilities();
  void randomizeWeaponsAbilities();
  void randomizeWeaponCrit();
  void randomizeWeaponAttackPower();
  void randomizeWeaponDamageFormula();
  void doGearRandomization();

  // Enemy Data
  void randomizeEnemyDrops( enemy_data_t* enemy );
  void randomizeEnemySteal( enemy_data_t* enemy );
  void randomizeEnemyBribe( enemy_data_t* enemy );
  void randomizeEnemyStatsNormal( enemy_data_t* enemy );
  void addEnemyDefenses( enemy_data_t* enemy );
  void randomizeEnemyStatsDefensiveNormalization( enemy_data_t* enemy );
  void shuffleEnemyStats( enemy_data_t* enemy );
  void randomizeEnemyElementalAffinities( enemy_data_t* enemy );
  void randomizeEnemyGearDrops( enemy_data_t* enemy );
  void doEnemyRandomization();

  // Random Encounters
  void getRandomEncounterIDs();
  void adjustStats();
  void randomizeEncounters( encounter_file_t& encounter );
  void doRandomEcnounterRandomization();

  // Player Characters & Aeons
  void reconstructPlayerStatsData();
  void reconstructAeonScalingData();
  void reconstructAeonStatData();
  void randomizePlayerStats();
  void shuffleCharacterStats();
  void randomizeAeonStatScaling();
  void randomizeAeonBaseStats();
  void shuffleAeonStatScaling();
  void shuffleAeonBaseStats();
  void doPlayerStatRandomization();

  // Shops
  void reconstructItemShopData();
  void reconstructArmsShopData();
  void reconstructArmsRateData();
  void reconstructItemRateData();
  void randomizeArmsPrices();
  void randomizeItemPrices();
  void randomizeItemShops();
  int getRandomShopArmsIndex();
  void randomizeGearShops();
  void doShopRandomization();
  void doPriceRandomization();


  void randomize()
  {
    printf( "Starting Randomizer...\n" );

    // Clean the output folder to prevent any issues
    std::filesystem::remove_all( OUTPUT_FOLDER );

    std::thread enemy_thread( &randomizer_t::doEnemyRandomization, this );
    std::thread shop_thread( &randomizer_t::doShopRandomization, this );
    std::thread price_thread( &randomizer_t::doPriceRandomization, this );
    std::thread field_thread( &randomizer_t::doFieldRandomization, this );
    std::thread gear_thread( &randomizer_t::doGearRandomization, this );
    // Dont Thread these to prevent a race condition.
    // TODO: Refactor so the race condition isnt possible
    // Since Player stats write the data to the file, make sure sphere grid is randomized first
    // as this sets the flags for Use and Lancet on Khimari and Riku if necessaray.
    doSphereGridRandomization();
    doPlayerStatRandomization();

    enemy_thread.join();
    shop_thread.join();
    price_thread.join();
    field_thread.join();
    gear_thread.join();

    writeJson( json_data );
  }
};