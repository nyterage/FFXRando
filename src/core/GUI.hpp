#pragma once
#include <wx/wxprec.h>
#include <wx/grid.h>
#include <wx/aui/auibook.h>
#include <wx/aui/aui.h>
#include <chrono>
#include "Randomizer.hpp"

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

enum
{
  ID_SEED = 1,
  ID_KEEP_THINGS_SANE,
  ID_FAHRENHEIT,
  ID_RANDOMIZE,
  ID_ALLOW_RANDOMIZE_KEY_ITEMS,
  ID_ALLOW_RANDOMIZE_CELESTIALS,
  ID_ALLOW_RANDOMIZE_BROTHERHOOD,
  ID_POISON_IS_DEADLY,
  ID_RANDOMIZE_ENEMY_DROPS,
  ID_RANDOMIZE_ENEMY_STEALS,
  ID_RANDOMIZE_ENEMY_BRIBES,
  ID_RANDOMIZE_ENEMY_GEAR_DROPS,
  ID_RANDOMIZE_ENEMY_STATS_NONE,
  ID_RANDOMIZE_ENEMY_STATS,
  ID_RANDOMIZE_ENEMY_STATS_DEFENSIVE,
  ID_RANDOMIZE_ENEMY_STATS_SHUFFLE,
  ID_RANDOMIZE_ENEMY_ELEMENTAl_AFFINITIES,
  ID_RANDOMIZE_ENCOUNTERS,
  ID_RANDOMIZE_ITEM_SHOPS,
  ID_RANDOMIZE_ITEM_SHOP_PRICES,
  ID_ENSURE_SHOPS_SELL_SPHERES,
  ID_RANDOMIZE_FIELD_ITEMS,
  ID_RANDOMIZE_GEAR_SHOPS,
  ID_RANDOMIZE_GEAR_SHOP_PRICES,
  ID_RANDOMIZE_GEAR_ABILITIES,
  ID_RANDOMIZE_WEAPON_CRIT,
  ID_RANDOMIZE_WEAPON_ATTACK_POWER,
  ID_RANDOMIZE_WEAPON_DAMAGE_FORMULA,
  ID_RANDOMIZE_PLAYER_STATS_NONE,
  ID_RANDOMIZE_PLAYER_STATS,
  ID_SHUFFLE_PLAYER_STATS,
  ID_RANDOMIZE_STARTING_OVERDRIVE_MODE,
  ID_RANDOMIZE_AEON_STAT_SCALING_NONE,
  ID_SHUFFLE_AEON_STAT_SCALING,
  ID_RANDOMIZE_AEON_STAT_SCALING,
  ID_RANDOMIZE_AEON_BASE_STATS_NONE,
  ID_SHUFFLE_AEON_BASE_STATS,
  ID_RANDOMIZE_AEON_BASE_STATS,
  ID_SPHERE_GRID_NONE,
  ID_SHUFFLE_SPHERE_GRID,
  ID_RANDOMIZE_SPHERE_GRID,
  ID_RANDOMIZE_SPHERE_GRID_TRUE,
  ID_SPHERE_NODES_NONE,
  ID_UPGRADE_SPHERE_NODES,
  ID_DOWNGRADE_SPHERE_NODES,
  ID_NONE_GRID,
  ID_EMPTY_GRID,
  ID_FULL_GRID,
  ID_REMOVE_LOCKS,
  ID_RANDOM_ENCOUNTER_STATS_NONE,
  ID_SWAP_RANDOM_ENCOUNTER_STATS,
  ID_SCALE_ECOUNTER_STATS,
  ID_RANDOMIZE_CUSTOMIZATION_ITEMS,
  ID_RANDOMIZE_AEON_STAT_ITEMS,
  ID_BASE_WINDOW = 1000,
  ID_NOTEBOOK,
};

struct gui_t : public wxApp
{
private:
  data_pack_t& dp;
  wxFrame* frame;

public:
  gui_t( data_pack_t& data_pack ) : dp( data_pack ), frame( nullptr ) {}

  virtual bool OnInit();
};

class frame_t : public wxFrame
{
private:
  data_pack_t& dp;
  options_pack_t* options;

  randomizer_t* randomizer;

  bool randomize_enemy_drops;
  bool randomize_enemy_steals;
  bool randomize_enemy_bribes;
  bool randomize_enemy_gear_drops;
  bool randomize_enemy_stats;
  bool randomize_enemy_stats_defensive;
  bool randomize_enemy_stats_shuffle;
  bool randomize_item_shops;
  bool randomize_gear_shops;
  bool randomize_item_shop_prices;
  bool randomize_gear_shop_prices;
  bool ensure_shops_sell_spheres;
  bool randomize_field_items;
  bool randomize_gear_abilities;
  bool randomize_weapon_crit;
  bool randomize_weapon_attack_power;
  bool randomize_weapon_damage_formula;
  bool randomize_player_stats;
  bool randomize_aeon_stat_scaling;
  bool randomize_aeon_base_stats;
  bool shuffle_player_stats;
  bool shuffle_aeon_stat_scaling;
  bool shuffle_aeon_base_stats;
  bool poison_is_deadly;
  bool randomize_starting_overdrive_mode;
  bool randomize_enemy_elemental_affinities;
  bool randomize_encounters;

  bool shuffle_sphere_grid;
  bool randomize_sphere_grid_true;
  bool randomize_sphere_grid;
  bool empty_sphere_grid;
  bool fill_sphere_grid;
  bool remove_sphere_grid_locks;
  bool upgrade_sphere_nodes;
  bool downgrade_sphere_nodes;

  bool swap_random_stats;
  bool scale_encounter_stats;

  bool randomize_key_items;
  bool keep_things_sane;
  bool randomize_celestials;
  bool randomize_brotherhood;
  bool randomize_customization_items;
  bool randomize_aeon_stat_items;

  wxButton* randomize_button;
  int32_t seed;
  wxTextCtrl* seed_text;

  bool fahrenheit;

  wxAuiNotebook* notebook;

public:
  frame_t( data_pack_t& data )
    : wxFrame( NULL, ID_BASE_WINDOW, "FFX Randomizer", wxDefaultPosition, wxSize( 840, 720 ) ),
    dp( data ),
    options( nullptr ),
    randomizer( nullptr ),
    randomize_enemy_drops( false ),
    randomize_enemy_steals( false ),
    randomize_enemy_bribes( false ),
    randomize_enemy_gear_drops( false ),
    randomize_enemy_stats( false ),
    randomize_enemy_stats_defensive( false ),
    randomize_enemy_stats_shuffle( false ),
    randomize_item_shops( false ),
    randomize_gear_shops( false ),
    randomize_item_shop_prices( false ),
    randomize_gear_shop_prices( false ),
    ensure_shops_sell_spheres( false ),
    randomize_field_items( false ),
    randomize_gear_abilities( false ),
    randomize_weapon_crit( false ),
    randomize_weapon_attack_power( false ),
    randomize_weapon_damage_formula( false ),
    randomize_player_stats( false ),
    randomize_aeon_stat_scaling( false ),
    randomize_aeon_base_stats( false ),
    shuffle_player_stats( false ),
    shuffle_aeon_stat_scaling( false ),
    shuffle_aeon_base_stats( false ),
    poison_is_deadly( false ),
    randomize_starting_overdrive_mode( false ),
    randomize_enemy_elemental_affinities( false ),
    randomize_encounters( false ),
    shuffle_sphere_grid( false ),
    randomize_sphere_grid_true( false ),
    randomize_sphere_grid( false ),
    empty_sphere_grid( false ),
    fill_sphere_grid( false ),
    remove_sphere_grid_locks( false ),
    upgrade_sphere_nodes( false ),
    downgrade_sphere_nodes( false ),
    swap_random_stats( false ),
    scale_encounter_stats( false ),
    randomize_key_items( false ),
    keep_things_sane( true ),
    randomize_celestials( false ),
    randomize_brotherhood( false ),
    randomize_customization_items( false ),
    randomize_aeon_stat_items( false ),
    randomize_button( nullptr ),
    seed( std::chrono::system_clock::now().time_since_epoch().count() ),
    seed_text( nullptr ),
    fahrenheit( false ),
    notebook( nullptr )
  {
    initialize();
    SetSizeHints( GetBestSize(), GetMaxClientSize() );
    SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOW ) );
    wxSize size = GetBestSize();
    size.SetHeight( size.GetHeight() + 10 );
    size.SetWidth( size.GetWidth() );
    SetSize( size );
  }

private:
  void initialize();
  void onSeedChange( wxCommandEvent& event );
  void onRandomize( wxCommandEvent& event );
  void onPoisonIsDeadly( wxCommandEvent& event );
  void onRandomizeEnemyDrops( wxCommandEvent& event );
  void onRandomizeEnemySteals( wxCommandEvent& event );
  void onRandomizeEnemyBribes( wxCommandEvent& event );
  void onRandomizeEnemyGearDrops( wxCommandEvent& event );
  void onRandomizeEnemyStatsNone( wxCommandEvent& event );
  void onRandomizeEnemyStats( wxCommandEvent& event );
  void onRandomizeEnemyStatsDefensive( wxCommandEvent& event );
  void onRandomizeEnemyStatsShuffle( wxCommandEvent& event );
  void onRandomizeEnemyElementalAffinities( wxCommandEvent& event );

  void onRandomizeItemShops( wxCommandEvent& event );
  void onRandomizeGearShops( wxCommandEvent& event );
  void onRandomizeItemShopPrices( wxCommandEvent& event );
  void onRandomizeGearShopPrices( wxCommandEvent& event );
  void onEnsureShopsSellSpheres( wxCommandEvent& event );

  void onRandomizeFieldItems( wxCommandEvent& event );

  void onRandomizeGearAbilities( wxCommandEvent& event );
  void onRandomizeWeaponCrit( wxCommandEvent& event );
  void onRandomizeWeaponAttackPower( wxCommandEvent& event );
  void onRandomizeWeaponDamageFormula( wxCommandEvent& event );
  void onRandomizeCustomizationItems( wxCommandEvent& event );

  void onRandomizeStartingOverdriveMode( wxCommandEvent& event );

  void onRandomizePlayerStatsNone( wxCommandEvent& event );
  void onRandomizePlayerStats( wxCommandEvent& event );
  void onShufflePlayerStats( wxCommandEvent& event );

  void onRandomizeAeonStatScalingNone( wxCommandEvent& event );
  void onRandomizeAeonStatScaling( wxCommandEvent& event );
  void onShuffleAeonStatScaling( wxCommandEvent& event );

  void onRandomizeAeonBaseStatsNone( wxCommandEvent& event );
  void onRandomizeAeonBaseStats( wxCommandEvent& event );
  void onShuffleAeonBaseStats( wxCommandEvent& event );

  void onRandomizeAeonStatItems( wxCommandEvent& event );

  void onRandomizeEncounters( wxCommandEvent& event );
  void onRandizedEncountersStatsNone( wxCommandEvent& event );
  void onSwapRandomEncounterStats( wxCommandEvent& event );
  void onScaleEncounterStats( wxCommandEvent& event );

  void onRemoveSphereGridLocks( wxCommandEvent& event );
  void onRandomizeSphereGridNone( wxCommandEvent& event );
  void onShuffleSphereGrid( wxCommandEvent& event );
  void onRandomizeSphereGridTrue( wxCommandEvent& event );
  void onRandomizeSphereGrid( wxCommandEvent& event );
  void onSphereNodesNone( wxCommandEvent& event );
  void onEmptySphereGrid( wxCommandEvent& event );
  void onFillSphereGrid( wxCommandEvent& event );
  void onSphereGridNone( wxCommandEvent& event );
  void onUpgradeSphereNodes( wxCommandEvent& event );
  void onDowngradeSphereNodes( wxCommandEvent& event );

  void onRandomizeKeyItems( wxCommandEvent& event );
  void onKeepThingsSane( wxCommandEvent& event );
  void onFahrenheit( wxCommandEvent& event );
  void onRandomizeCelestials( wxCommandEvent& event );
  void onRandomizeBrotherhood( wxCommandEvent& event );

  int32_t hash( char* str );
};

struct enemy_options_panel_t : public wxPanel
{
  wxCheckBox* poisonIsDeadlyCheckbox;

  wxCheckBox* randomizeEnemyDropsCheckbox;
  wxCheckBox* randomizeEnemyStealsCheckbox;
  wxCheckBox* randomizeEnemyBribesCheckbox;
  wxCheckBox* randomizeEnemyGearDropsCheckbox;
  wxCheckBox* randomizeEnemyElementalAffinitiesCheckbox;
  wxCheckBox* randomizeEncountersCheckbox;

  enemy_options_panel_t( wxAuiNotebook* frame ) : wxPanel( frame, wxID_ANY, wxDefaultPosition, wxSize( 335, 350 ), wxBORDER_NONE),
    poisonIsDeadlyCheckbox( nullptr ),
    randomizeEnemyDropsCheckbox( nullptr ),
    randomizeEnemyStealsCheckbox( nullptr ),
    randomizeEnemyBribesCheckbox( nullptr ),
    randomizeEnemyGearDropsCheckbox( nullptr ),
    randomizeEnemyElementalAffinitiesCheckbox( nullptr ),
    randomizeEncountersCheckbox( nullptr )
  {
    wxBoxSizer* sizer = new wxBoxSizer( wxVERTICAL );

    poisonIsDeadlyCheckbox = new wxCheckBox( this, ID_POISON_IS_DEADLY, _T( "Enemy Poison is Deadly" ), wxDefaultPosition, wxDefaultSize, 0 );
    poisonIsDeadlyCheckbox->SetToolTip( "If checked, poison will deal 50% of the player's HP per tick instead of the default 25%." );

    randomizeEnemyDropsCheckbox = new wxCheckBox( this, ID_RANDOMIZE_ENEMY_DROPS, _T( "Randomize Enemy Drops" ), wxDefaultPosition, wxDefaultSize, 0 );
    randomizeEnemyStealsCheckbox = new wxCheckBox( this, ID_RANDOMIZE_ENEMY_STEALS, _T( "Randomize Enemy Steals" ), wxDefaultPosition, wxDefaultSize, 0 );
    randomizeEnemyBribesCheckbox = new wxCheckBox( this, ID_RANDOMIZE_ENEMY_BRIBES, _T( "Randomize Enemy Bribes" ), wxDefaultPosition, wxDefaultSize, 0 );
    randomizeEnemyGearDropsCheckbox = new wxCheckBox( this, ID_RANDOMIZE_ENEMY_GEAR_DROPS, _T( "Randomize Enemy Gear Drops" ), wxDefaultPosition, wxDefaultSize, 0 );
    randomizeEnemyElementalAffinitiesCheckbox = new wxCheckBox( this, ID_RANDOMIZE_ENEMY_ELEMENTAl_AFFINITIES, _T( "Randomize Enemy Elemental Affinities" ), wxDefaultPosition, wxDefaultSize, 0 );
    randomizeEnemyElementalAffinitiesCheckbox->SetToolTip( "If checked, enemy elemental affinities will be randomized. This includes:\n- Weaknesss \n- Resists \n- Immunities \n- Absorbs\n\nThis is slightly skewed in favor of giving an enemy a weakness if it gets an affinity." );
    randomizeEncountersCheckbox = new wxCheckBox( this, ID_RANDOMIZE_ENCOUNTERS, _T( "Randomize Random Encounters" ), wxDefaultPosition, wxDefaultSize, 0 );
    randomizeEncountersCheckbox->SetToolTip( "If checked, random encounters will be randomized." );

    wxStaticText* random_encounter_text = new wxStaticText( this, wxID_ANY, _T( "Random Encounter Stat Options" ), wxDefaultPosition, wxDefaultSize, 0 );
    random_encounter_text->SetFont( wxFont( 9, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD ) );

    wxRadioButton* swapRandomizedEncounterStatsNoneRadioBox = new wxRadioButton( this, ID_RANDOM_ENCOUNTER_STATS_NONE, _T( "None" ), wxDefaultPosition, wxDefaultSize, wxRB_GROUP );
    swapRandomizedEncounterStatsNoneRadioBox->SetToolTip( "If checked, randomized encounters will have their original stats" );
    wxRadioButton* swapRandomizedEncounterStatsRadioButton = new wxRadioButton( this, ID_SWAP_RANDOM_ENCOUNTER_STATS, _T( "Swap Randomized Encounter Stats" ), wxDefaultPosition, wxDefaultSize, 0 );
    swapRandomizedEncounterStatsRadioButton->SetToolTip( "If checked, randomized encounters will get the stats of their original enemy." );
    wxRadioButton* scaleEncounterStatsRadioButton = new wxRadioButton( this, ID_SCALE_ECOUNTER_STATS, _T( "Normalize Encounter Stats" ), wxDefaultPosition, wxDefaultSize, 0 );
    scaleEncounterStatsRadioButton->SetToolTip( "If checked, randomized encounters will have their stats scaled based on the difference between the original and new enemies stats." );

    wxStaticText* enemy_stats_text = new wxStaticText( this, wxID_ANY, _T( "Enemy Stat Randomization Options" ), wxDefaultPosition, wxDefaultSize, 0 );
    enemy_stats_text->SetFont( wxFont( 9, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD ) );

    wxRadioButton* noRandomizeEnemyStats = new wxRadioButton( this, ID_RANDOMIZE_ENEMY_STATS_NONE, _T( "No Randomization" ), wxDefaultPosition, wxDefaultSize, wxRB_GROUP );
    noRandomizeEnemyStats->SetToolTip( "If checked, enemy stats will not be randomized." );
    wxRadioButton* randomizeEnemyStatsRadioButton = new wxRadioButton( this, ID_RANDOMIZE_ENEMY_STATS, _T( "Randomize Enemy Stats" ), wxDefaultPosition, wxDefaultSize, 0 );
    randomizeEnemyStatsRadioButton->SetToolTip( "If checked, enemy stats will be randomized using a normal distribution, centered on their original values. This keeps things close to vanilla, with some spice on occasion" );
    wxRadioButton* randomizeEnemyStatsDefensiveRadioButton = new wxRadioButton( this, ID_RANDOMIZE_ENEMY_STATS_DEFENSIVE, _T( "Shuffle Enemy Stats + Normalize Defensives" ), wxDefaultPosition, wxDefaultSize, 0 );
    randomizeEnemyStatsDefensiveRadioButton->SetToolTip( "If checked, enemy defensive stats (def/magic def/evasion) will be randomly assigned to another enemies values, with some math magic to try to keep them from ending up too tanky.\n Non defensive stats are randomized with the same method as the Normal Distribution option." );
    wxRadioButton* randomizeEnemyStatsShuffleRadioButton = new wxRadioButton( this, ID_RANDOMIZE_ENEMY_STATS_SHUFFLE, _T( "Shuffle Enemy Stats" ), wxDefaultPosition, wxDefaultSize, 0 );
    randomizeEnemyStatsShuffleRadioButton->SetToolTip( "If checked, enemy defensive stats (def/magic def/evasion) will be shuffled to a different enemies defensive stats at random.\nYou may encounter a flan with penance's defensive stats" );

    sizer->Add( poisonIsDeadlyCheckbox, 0, wxALIGN_LEFT | wxLEFT | wxRIGHT | wxTOP, FromDIP( 5 ) );

    sizer->Add( randomizeEnemyDropsCheckbox, 0, wxALIGN_LEFT | wxLEFT | wxRIGHT | wxTOP, FromDIP( 5 ) );
    sizer->Add( randomizeEnemyStealsCheckbox, 0, wxALIGN_LEFT | wxLEFT | wxRIGHT | wxTOP, FromDIP( 5 ) );
    sizer->Add( randomizeEnemyBribesCheckbox, 0, wxALIGN_LEFT | wxLEFT | wxRIGHT | wxTOP, FromDIP( 5 ) );
    sizer->Add( randomizeEnemyGearDropsCheckbox, 0, wxALIGN_LEFT | wxLEFT | wxRIGHT | wxTOP, FromDIP( 5 ) );
    sizer->Add( randomizeEnemyElementalAffinitiesCheckbox, 0, wxALIGN_LEFT | wxLEFT | wxRIGHT | wxTOP, FromDIP( 5 ) );
    sizer->Add( randomizeEncountersCheckbox, 0, wxALIGN_LEFT | wxLEFT | wxRIGHT | wxTOP, FromDIP( 5 ) );

    sizer->InsertSpacer( sizer->GetItemCount(), FromDIP( 10 ) );
    sizer->Add( random_encounter_text, 0, wxALIGN_LEFT | wxLEFT | wxRIGHT | wxTOP, FromDIP( 5 ) );
    sizer->Add( swapRandomizedEncounterStatsNoneRadioBox, 0, wxALIGN_LEFT | wxLEFT | wxRIGHT | wxTOP, FromDIP( 5 ) );
    sizer->Add( swapRandomizedEncounterStatsRadioButton, 0, wxALIGN_LEFT | wxLEFT | wxRIGHT | wxTOP, FromDIP( 5 ) );
    sizer->Add( scaleEncounterStatsRadioButton, 0, wxALIGN_LEFT | wxLEFT | wxRIGHT | wxTOP, FromDIP( 5 ) );

    sizer->InsertSpacer( sizer->GetItemCount(), FromDIP( 10 ) );

    sizer->Add( enemy_stats_text, 0, wxALIGN_LEFT | wxLEFT | wxRIGHT | wxTOP, FromDIP( 5 ) );
    sizer->Add( noRandomizeEnemyStats, 0, wxALIGN_LEFT | wxLEFT | wxRIGHT | wxTOP, FromDIP( 5 ) );
    sizer->Add( randomizeEnemyStatsRadioButton, 0, wxALIGN_LEFT | wxLEFT | wxRIGHT | wxTOP, FromDIP( 5 ) );
    sizer->Add( randomizeEnemyStatsDefensiveRadioButton, 0, wxALIGN_LEFT | wxLEFT | wxRIGHT | wxTOP, FromDIP( 5 ) );
    sizer->Add( randomizeEnemyStatsShuffleRadioButton, 0, wxALIGN_LEFT | wxLEFT | wxRIGHT | wxTOP, FromDIP( 5 ) );

    sizer->InsertSpacer( sizer->GetItemCount(), FromDIP( 5 ) );

    SetSizer( sizer );
  }
};

struct header_panel_t : public wxPanel
{
  wxCheckBox* keepThingsSaneCheckbox;
  wxCheckBox* fahrenheitCheckbox;

  header_panel_t( frame_t* frame ) : wxPanel( frame, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_THEME ),

    keepThingsSaneCheckbox( nullptr ),
    fahrenheitCheckbox( nullptr )
  {
    wxBoxSizer* sizer = new wxBoxSizer( wxVERTICAL );
    fahrenheitCheckbox = new wxCheckBox( this, ID_FAHRENHEIT, _T( "Fahrenheit" ), wxDefaultPosition, wxDefaultSize, 0 );
    fahrenheitCheckbox->SetToolTip( "Check this box to generate files in a format suitable for the Fahrenheit mod loader." );
    keepThingsSaneCheckbox = new wxCheckBox( this, ID_KEEP_THINGS_SANE, _T( "Keep Things Sane" ), wxDefaultPosition, wxDefaultSize, 0 );
    keepThingsSaneCheckbox->SetToolTip( "If checked, the randomizer will attempt to keep things close to vanilla values. IE, if you could ever only loot 1 of an item, the randomizer will keep it that way.\nAlso keeps constraints on gil, and AP to more reasonable values, within +-100% of their original values.\nThis will mean that some spheres will sell in shops for very little, as their data has them being sold for 2 gil." );
    keepThingsSaneCheckbox->SetValue( true );

    sizer->Add( fahrenheitCheckbox, 0, wxALIGN_LEFT | wxLEFT | wxRIGHT | wxTOP, FromDIP( 5 ) );
    sizer->Add( keepThingsSaneCheckbox, 0, wxALIGN_LEFT | wxLEFT | wxRIGHT | wxTOP, FromDIP( 5 ) );
    sizer->InsertSpacer( sizer->GetItemCount(), FromDIP( 5 ) );
    SetSizer( sizer );

    SetMinSize( GetBestVirtualSize() );
  }
};

struct gear_options_panel_t : public wxPanel
{
  wxCheckBox* randomizeCelestialsCheckbox;
  wxCheckBox* randomizeBrotherhoodCheckbox;
  wxCheckBox* randomizeGearAbilitiesCheckbox;
  wxCheckBox* randomizeWeaponCritCheckbox;
  wxCheckBox* randomizeWeaponAttackPowerCheckbox;
  wxCheckBox* randomizeWeaponDamageFormulaCheckbox;
  wxCheckBox* randomizeGearShopsCheckbox;
  wxCheckBox* randomizeGearPricesCheckbox;
  wxCheckBox* randomizeCustomizationItemsCheckbox;

  gear_options_panel_t( wxAuiNotebook* book ) : wxPanel( book, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE ),
    randomizeCelestialsCheckbox( nullptr ),
    randomizeBrotherhoodCheckbox( nullptr ),
    randomizeGearAbilitiesCheckbox( nullptr ),
    randomizeWeaponCritCheckbox( nullptr ),
    randomizeWeaponAttackPowerCheckbox( nullptr ),
    randomizeWeaponDamageFormulaCheckbox( nullptr ),
    randomizeGearShopsCheckbox( nullptr ),
    randomizeGearPricesCheckbox( nullptr ),
    randomizeCustomizationItemsCheckbox( nullptr )
  {
    wxBoxSizer* sizer = new wxBoxSizer( wxVERTICAL );
    randomizeCelestialsCheckbox = new wxCheckBox( this, ID_ALLOW_RANDOMIZE_CELESTIALS, _T( "Include Celestial Items in Pool" ), wxDefaultPosition, wxDefaultSize, 0 );
    randomizeCelestialsCheckbox->SetToolTip( "If checked, celestial weapons abilities will be able to be randomized." );

    randomizeBrotherhoodCheckbox = new wxCheckBox( this, ID_ALLOW_RANDOMIZE_BROTHERHOOD, _T( "Include Brotherhood in Pool" ), wxDefaultPosition, wxDefaultSize, 0 );
    randomizeBrotherhoodCheckbox->SetToolTip( "If checked, Brotherhood abilities will be able to be randomized." );

    randomizeGearAbilitiesCheckbox = new wxCheckBox( this, ID_RANDOMIZE_GEAR_ABILITIES, _T( "Randomize Gear Abilities" ), wxDefaultPosition, wxDefaultSize, 0 );
    randomizeGearAbilitiesCheckbox->SetToolTip( "If checked, gear abilities will be randomized. This includes:\n- Armor\n- Weapons" );

    randomizeWeaponCritCheckbox = new wxCheckBox( this, ID_RANDOMIZE_WEAPON_CRIT, _T( "Randomize Weapon Crit Chance" ), wxDefaultPosition, wxDefaultSize, 0 );
    randomizeWeaponCritCheckbox->SetToolTip( "If checked, weapon crit chance will be randomized." );

    randomizeWeaponAttackPowerCheckbox = new wxCheckBox( this, ID_RANDOMIZE_WEAPON_ATTACK_POWER, _T( "Randomize Weapon Attack Power" ), wxDefaultPosition, wxDefaultSize, 0 );
    randomizeWeaponAttackPowerCheckbox->SetToolTip( "If checked, weapon attack power will be randomized." );

    randomizeWeaponDamageFormulaCheckbox = new wxCheckBox( this, ID_RANDOMIZE_WEAPON_DAMAGE_FORMULA, _T( "Randomize Weapon Damage Formula" ), wxDefaultPosition, wxDefaultSize, 0 );
    randomizeWeaponDamageFormulaCheckbox->SetToolTip( "If checked, weapon damage formula will be randomized." );

    randomizeGearShopsCheckbox = new wxCheckBox( this, ID_RANDOMIZE_GEAR_SHOPS, _T( "Randomize Gear Shops" ), wxDefaultPosition, wxDefaultSize, 0 );
    randomizeGearShopsCheckbox->SetToolTip( "If checked, gear shops will be randomized. Including the number of items offered." );

    randomizeGearPricesCheckbox = new wxCheckBox( this, ID_RANDOMIZE_GEAR_SHOP_PRICES, _T( "Randomize Gear Shop Prices" ), wxDefaultPosition, wxDefaultSize, 0 );
    randomizeGearPricesCheckbox->SetToolTip( "If checked, gear shop prices will be randomized." );

    randomizeCustomizationItemsCheckbox = new wxCheckBox( this, ID_RANDOMIZE_CUSTOMIZATION_ITEMS, _T( "Randomize Customization Items" ), wxDefaultPosition, wxDefaultSize, 0 );
    randomizeCustomizationItemsCheckbox->SetToolTip( "If checked, customization items will be randomized. This includes:\n- The item required to apply an auto ability to an item\n- The number of items required" );

    sizer->Add( randomizeCelestialsCheckbox, 0, wxALIGN_LEFT | wxLEFT | wxRIGHT | wxTOP, FromDIP( 5 ) );
    sizer->Add( randomizeBrotherhoodCheckbox, 0, wxALIGN_LEFT | wxLEFT | wxRIGHT | wxTOP, FromDIP( 5 ) );
    sizer->Add( randomizeGearAbilitiesCheckbox, 0, wxALIGN_LEFT | wxLEFT | wxRIGHT | wxTOP, FromDIP( 5 ) );
    sizer->Add( randomizeWeaponCritCheckbox, 0, wxALIGN_LEFT | wxLEFT | wxRIGHT | wxTOP, FromDIP( 5 ) );
    sizer->Add( randomizeWeaponAttackPowerCheckbox, 0, wxALIGN_LEFT | wxLEFT | wxRIGHT | wxTOP, FromDIP( 5 ) );
    sizer->Add( randomizeWeaponDamageFormulaCheckbox, 0, wxALIGN_LEFT | wxLEFT | wxRIGHT | wxTOP, FromDIP( 5 ) );
    sizer->Add( randomizeGearShopsCheckbox, 0, wxALIGN_LEFT | wxLEFT | wxRIGHT | wxTOP, FromDIP( 5 ) );
    sizer->Add( randomizeGearPricesCheckbox, 0, wxALIGN_LEFT | wxLEFT | wxRIGHT | wxTOP, FromDIP( 5 ) );
    sizer->Add( randomizeCustomizationItemsCheckbox, 0, wxALIGN_LEFT | wxLEFT | wxRIGHT | wxTOP, FromDIP( 5 ) );
    sizer->InsertSpacer( sizer->GetItemCount(), FromDIP( 5 ) );
    SetSizer( sizer );

    SetMinSize( GetBestVirtualSize() );
  }
};

struct item_options_panel_t : wxPanel
{
  wxCheckBox* randomizeKeyItemsCheckbox;
  wxCheckBox* randomizeShopsCheckbox;
  wxCheckBox* randomizeShopPricesCheckbox;
  wxCheckBox* randomizeFieldItemsCheckbox;
  wxCheckBox* ensureShopsSellSpheresCheckbox;

  item_options_panel_t( wxAuiNotebook* book ) : wxPanel( book, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE ),
    randomizeKeyItemsCheckbox( nullptr ),
    randomizeShopsCheckbox( nullptr ),
    randomizeShopPricesCheckbox( nullptr ),
    randomizeFieldItemsCheckbox( nullptr )
  {
    wxBoxSizer* sizer = new wxBoxSizer( wxVERTICAL );

    randomizeKeyItemsCheckbox = new wxCheckBox( this, ID_ALLOW_RANDOMIZE_KEY_ITEMS, _T( "Include Key Items in Pool" ), wxDefaultPosition, wxDefaultSize, 0 );
    randomizeKeyItemsCheckbox->SetToolTip( "If checked, key items will be included in the randomization pool. This might break progression, use it with caution." );


    randomizeShopsCheckbox = new wxCheckBox( this, ID_RANDOMIZE_ITEM_SHOPS, _T( "Randomize Shops" ), wxDefaultPosition, wxDefaultSize, 0 );
    randomizeShopsCheckbox->SetToolTip( "If checked, shops will be randomized. This includes:\n- The number of items offered\n- The items offered" );
    ensureShopsSellSpheresCheckbox = new wxCheckBox( this, ID_ENSURE_SHOPS_SELL_SPHERES, _T( "Ensure Randomized Shops Sell Spheres" ), wxDefaultPosition, wxDefaultSize, 0 );
    ensureShopsSellSpheresCheckbox->SetToolTip( "If checked, randomized shops will always sell the basic types of spheres. This includes:\n- Power Spheres \n- Mana Spheres \n- Agility Spheres \n- Ability Spheres " );
    randomizeShopPricesCheckbox = new wxCheckBox( this, ID_RANDOMIZE_ITEM_SHOP_PRICES, _T( "Randomize Shop Prices" ), wxDefaultPosition, wxDefaultSize, 0 );
    randomizeShopPricesCheckbox->SetToolTip( "If checked, shop prices will be randomized. This includes:\n- The prices of the items" );
    randomizeFieldItemsCheckbox = new wxCheckBox( this, ID_RANDOMIZE_FIELD_ITEMS, _T( "Randomize Field Items" ), wxDefaultPosition, wxDefaultSize, 0 );
    randomizeFieldItemsCheckbox->SetToolTip( "If checked, field items will be randomized. This includes:\n- Treasure Chests \n- Items gifted \n- Event Rewards" );

    sizer->Add( randomizeKeyItemsCheckbox, 0, wxALIGN_LEFT | wxLEFT | wxRIGHT | wxTOP, FromDIP( 5 ) );
    sizer->Add( randomizeShopsCheckbox, 0, wxALIGN_LEFT | wxLEFT | wxRIGHT | wxTOP, FromDIP( 5 ) );
    sizer->Add( ensureShopsSellSpheresCheckbox, 0, wxALIGN_LEFT | wxLEFT | wxRIGHT | wxTOP, FromDIP( 5 ) );
    sizer->Add( randomizeShopPricesCheckbox, 0, wxALIGN_LEFT | wxLEFT | wxRIGHT | wxTOP, FromDIP( 5 ) );
    sizer->Add( randomizeFieldItemsCheckbox, 0, wxALIGN_LEFT | wxLEFT | wxRIGHT | wxTOP, FromDIP( 5 ) );
    sizer->InsertSpacer( sizer->GetItemCount(), FromDIP( 5 ) );
    SetSizer( sizer );
    SetMinSize( GetBestVirtualSize() );
  }
};

struct player_stats_panel_t : public wxPanel
{
  wxCheckBox* randomizeStartingOverdriveModeCheckbox;

  player_stats_panel_t( wxAuiNotebook* panel ) : wxPanel( panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE ),
    randomizeStartingOverdriveModeCheckbox( nullptr )
  {
    wxBoxSizer* sizer = new wxBoxSizer( wxVERTICAL );

    wxStaticText* new_game_text = new wxStaticText( this, wxID_ANY, _T( "These Options only affect new save files!" ), wxDefaultPosition, wxDefaultSize, 0 );
    new_game_text->SetFont( wxFont( 12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD ) );

    wxRadioButton* RandomizePlayerStatsNoneRadioButton = new wxRadioButton( this, ID_RANDOMIZE_PLAYER_STATS_NONE, _T( "No Randomization" ), wxDefaultPosition, wxDefaultSize, wxRB_GROUP );
    RandomizePlayerStatsNoneRadioButton->SetToolTip( "If checked, player stats will not be randomized." );
    wxRadioButton* RandomizePlayerStatsRadioButton = new wxRadioButton( this, ID_RANDOMIZE_PLAYER_STATS, _T( "Randomize Player Stats" ), wxDefaultPosition, wxDefaultSize, 0 );
    RandomizePlayerStatsRadioButton->SetToolTip( "If checked, player stats will be randomized using a normal distribution, centered on their original values. This keeps things close to vanilla, with some spice on occasion" );
    wxRadioButton* ShufflePlayerStatsRadioButton = new wxRadioButton( this, ID_SHUFFLE_PLAYER_STATS, _T( "Shuffle Player Stats" ), wxDefaultPosition, wxDefaultSize, 0 );
    ShufflePlayerStatsRadioButton->SetToolTip( "If checked, player stats will be shuffled to another party members stats at random." );

    randomizeStartingOverdriveModeCheckbox = new wxCheckBox( this, ID_RANDOMIZE_STARTING_OVERDRIVE_MODE, _T( "Randomize Starting Overdrive Mode" ), wxDefaultPosition, wxDefaultSize, 0 );
    randomizeStartingOverdriveModeCheckbox->SetToolTip( "If checked, the starting overdrive mode for playable characters will be random." );

    wxStaticText* exclusive_text = new wxStaticText( this, wxID_ANY, _T( "Player Stat Options" ), wxDefaultPosition, wxDefaultSize, 0 );
    exclusive_text->SetFont( wxFont( 10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD ) );


    sizer->Add( new_game_text, 0, wxALIGN_CENTER | wxLEFT | wxRIGHT | wxTOP, FromDIP( 5 ) );
    sizer->Add( randomizeStartingOverdriveModeCheckbox, 0, wxALIGN_LEFT | wxLEFT | wxRIGHT | wxTOP, FromDIP( 5 ) );
    sizer->InsertSpacer( sizer->GetItemCount(), FromDIP( 10 ) );

    sizer->Add( exclusive_text, 0, wxALIGN_LEFT | wxLEFT | wxRIGHT | wxTOP, FromDIP( 5 ) );
    sizer->Add( RandomizePlayerStatsNoneRadioButton, 0, wxALIGN_LEFT | wxLEFT | wxRIGHT | wxTOP, FromDIP( 5 ) );
    sizer->Add( RandomizePlayerStatsRadioButton, 0, wxALIGN_LEFT | wxLEFT | wxRIGHT | wxTOP, FromDIP( 5 ) );
    sizer->Add( ShufflePlayerStatsRadioButton, 0, wxALIGN_LEFT | wxLEFT | wxRIGHT | wxTOP, FromDIP( 5 ) );
    sizer->InsertSpacer( sizer->GetItemCount(), FromDIP( 5 ) );
    SetSizer( sizer );
    SetMinSize( GetBestVirtualSize() );
  }
};

struct aeon_stats_panel_t : public wxPanel
{
  wxCheckBox* randomizeAeonStatCustomizationItemsCheckbox;

  aeon_stats_panel_t( wxAuiNotebook* panel ) : wxPanel( panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE ),
    randomizeAeonStatCustomizationItemsCheckbox( nullptr )
  {
    wxBoxSizer* sizer = new wxBoxSizer( wxVERTICAL );

    wxStaticText* new_game_text = new wxStaticText( this, wxID_ANY, _T( "These Options only affect new save files!" ), wxDefaultPosition, wxDefaultSize, 0 );
    new_game_text->SetFont( wxFont( 12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD ) );

    randomizeAeonStatCustomizationItemsCheckbox = new wxCheckBox( this, ID_RANDOMIZE_AEON_STAT_ITEMS, _T( "Randomize Customization Items" ), wxDefaultPosition, wxDefaultSize, 0 );
    randomizeAeonStatCustomizationItemsCheckbox->SetToolTip( "If checked, items to increase aeon stats, and teach new abilities will be randomized. This includes:\n- The item required \n- The number of items required" );

    wxRadioButton* randomizeAeonBaseStatsNoneRadioButton = new wxRadioButton( this, ID_RANDOMIZE_AEON_BASE_STATS_NONE, _T( "None" ), wxDefaultPosition, wxDefaultSize, wxRB_GROUP );
    randomizeAeonBaseStatsNoneRadioButton->SetToolTip( "If checked, aeon base stats will not be randomized." );
    wxRadioButton* randomizeAeonBaseStatsRadioButton = new wxRadioButton( this, ID_RANDOMIZE_AEON_BASE_STATS, _T( "Randomize Aeon Base Stats" ), wxDefaultPosition, wxDefaultSize, 0 );
    randomizeAeonBaseStatsRadioButton->SetToolTip( "If checked, aeon base stats will be randomized using a normal distribution, centered on their original values. This keeps things close to vanilla, with some spice on occasion" );
    wxRadioButton* shuffleAeonBaseStatsRadioButton = new wxRadioButton( this, ID_SHUFFLE_AEON_BASE_STATS, _T( "Shuffle Aeon Base Stats" ), wxDefaultPosition, wxDefaultSize, 0 );
    shuffleAeonBaseStatsRadioButton->SetToolTip( "If checked, aeon base stats will be shuffled to another aeons stats at random." );

    wxRadioButton* randomizeAeonStatScalingNoneRadioButton = new wxRadioButton( this, ID_RANDOMIZE_AEON_STAT_SCALING_NONE, _T( "None" ), wxDefaultPosition, wxDefaultSize, wxRB_GROUP );
    randomizeAeonStatScalingNoneRadioButton->SetToolTip( "If checked, aeon stat scaling will not be randomized." );
    wxRadioButton* randomizeAeonStatScalingRadioButton = new wxRadioButton( this, ID_RANDOMIZE_AEON_STAT_SCALING, _T( "Randomize Aeon Stat Scaling" ), wxDefaultPosition, wxDefaultSize, 0 );
    randomizeAeonStatScalingRadioButton->SetToolTip( "If checked, aeon stat scaling (with Yunas stats) will be randomized using a normal distribution, centered on their original values. This keeps things close to vanilla, with some spice on occasion" );
    wxRadioButton* shuffleAeonStatScalingRadioButton = new wxRadioButton( this, ID_SHUFFLE_AEON_STAT_SCALING, _T( "Shuffle Aeon Stat Scaling" ), wxDefaultPosition, wxDefaultSize, 0 );
    shuffleAeonStatScalingRadioButton->SetToolTip( "If checked, aeon stat scaling (with Yunas stats) will be shuffled to another aeons stats at random." );

    wxStaticText* scaling_text = new wxStaticText( this, wxID_ANY, _T( "Aeon Stat Scaling Options" ), wxDefaultPosition, wxDefaultSize, 0 );
    scaling_text->SetFont( wxFont( 9, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD ) );

    wxStaticText* stats = new wxStaticText( this, wxID_ANY, _T( "Aeon Base Stat Options" ), wxDefaultPosition, wxDefaultSize, 0 );
    stats->SetFont( wxFont( 9, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD ) );

    sizer->Add( new_game_text, 0, wxALIGN_CENTER | wxLEFT | wxRIGHT | wxTOP, FromDIP( 5 ) );
    sizer->Add( randomizeAeonStatCustomizationItemsCheckbox, 0, wxALIGN_LEFT | wxLEFT | wxRIGHT | wxTOP, FromDIP( 5 ) );

    sizer->InsertSpacer( sizer->GetItemCount(), FromDIP( 10 ) );

    sizer->Add( stats, 0, wxALIGN_LEFT | wxLEFT | wxRIGHT | wxTOP, FromDIP( 5 ) );
    sizer->Add( randomizeAeonBaseStatsNoneRadioButton, 0, wxALIGN_LEFT | wxLEFT | wxRIGHT | wxTOP, FromDIP( 5 ) );
    sizer->Add( randomizeAeonBaseStatsRadioButton, 0, wxALIGN_LEFT | wxLEFT | wxRIGHT | wxTOP, FromDIP( 5 ) );
    sizer->Add( shuffleAeonBaseStatsRadioButton, 0, wxALIGN_LEFT | wxLEFT | wxRIGHT | wxTOP, FromDIP( 5 ) );

    sizer->InsertSpacer( sizer->GetItemCount(), FromDIP( 10 ) );

    sizer->Add( scaling_text, 0, wxALIGN_LEFT | wxLEFT | wxRIGHT | wxTOP, FromDIP( 5 ) );
    sizer->Add( randomizeAeonStatScalingNoneRadioButton, 0, wxALIGN_LEFT | wxLEFT | wxRIGHT | wxTOP, FromDIP( 5 ) );
    sizer->Add( randomizeAeonStatScalingRadioButton, 0, wxALIGN_LEFT | wxLEFT | wxRIGHT | wxTOP, FromDIP( 5 ) );
    sizer->Add( shuffleAeonStatScalingRadioButton, 0, wxALIGN_LEFT | wxLEFT | wxRIGHT | wxTOP, FromDIP( 5 ) );

    sizer->InsertSpacer( sizer->GetItemCount(), FromDIP( 5 ) );
    SetSizer( sizer );
    SetMinSize( GetBestVirtualSize() );
  }
};

struct sphere_grid_panel_t : public wxPanel
{
  wxCheckBox* removeSphereGridLocksCheckbox;

  sphere_grid_panel_t( wxAuiNotebook* panel ) : wxPanel( panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE ),
    removeSphereGridLocksCheckbox( nullptr )
  {
    wxBoxSizer* sizer = new wxBoxSizer( wxVERTICAL );

    wxStaticText* new_game_text = new wxStaticText( this, wxID_ANY, _T( "These Options only affect new save files!" ), wxDefaultPosition, wxDefaultSize, 0 );
    new_game_text->SetFont( wxFont( 12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD ) );

    wxRadioButton* RandomizeSphereGridNoneRadioButton = new wxRadioButton( this, ID_SPHERE_GRID_NONE, _T( "No Randomization" ), wxDefaultPosition, wxDefaultSize, wxRB_GROUP );
    RandomizeSphereGridNoneRadioButton->SetToolTip( "If checked, sphere grid will not be randomized." );
    wxRadioButton* ShuffleSphereGridRadioButton = new wxRadioButton( this, ID_SHUFFLE_SPHERE_GRID, _T( "Shuffle Sphere Grid" ), wxDefaultPosition, wxDefaultSize, 0 );
    ShuffleSphereGridRadioButton->SetToolTip( "If checked, sphere grid will be shuffled. This means that the nodes will be in a different order, but the same nodes will be present." );
    wxRadioButton* RandomizeSphereGridRadioButton = new wxRadioButton( this, ID_RANDOMIZE_SPHERE_GRID_TRUE, _T( "Randomize Sphere Grid - True Randomization" ), wxDefaultPosition, wxDefaultSize, 0 );
    RandomizeSphereGridRadioButton->SetToolTip( "If checked, sphere grid will be truly randomized. This means that there is no guarentee you will get all ability nodes, and there may be duplicate ability nodes." );
    wxRadioButton* RandomizeSphereGridRadioButton2 = new wxRadioButton( this, ID_RANDOMIZE_SPHERE_GRID, _T( "Randomize Sphere Grid - Controlled Randomization" ), wxDefaultPosition, wxDefaultSize, 0 );
    RandomizeSphereGridRadioButton2->SetToolTip( "If checked, every node in the sphere grid will be replaced by a random node, not constrained by what was present originally, but will be guarenteed to have 1 of every ability node." );

    wxRadioButton* sphereNodesNoneRadioButton = new wxRadioButton( this, ID_SPHERE_NODES_NONE, _T( "None" ), wxDefaultPosition, wxDefaultSize, wxRB_GROUP );
    sphereNodesNoneRadioButton->SetToolTip( "If checked, sphere nodes will not be scaled up or down" );
    wxRadioButton* upgradeSphereNodesRadioButton = new wxRadioButton( this, ID_UPGRADE_SPHERE_NODES, _T( "Upgrade Sphere Nodes" ), wxDefaultPosition, wxDefaultSize, 0 );
    upgradeSphereNodesRadioButton->SetToolTip( "If checked, sphere nodes will be upgraded to their maximum value." );
    wxRadioButton* downgradeSphereNodesRadioButton = new wxRadioButton( this, ID_DOWNGRADE_SPHERE_NODES, _T( "Downgrade Sphere Nodes" ), wxDefaultPosition, wxDefaultSize, 0 );
    downgradeSphereNodesRadioButton->SetToolTip( "If checked, sphere nodes will be downgraded to their minimum value." );

    wxRadioButton* sphereGridNoneRadioButton = new wxRadioButton( this, ID_NONE_GRID, _T( "None" ), wxDefaultPosition, wxDefaultSize, wxRB_GROUP );
    sphereGridNoneRadioButton->SetToolTip( "If checked, the sphere grid nodes will be the same as normal." );
    wxRadioButton* emptySphereGridRadioButton = new wxRadioButton( this, ID_EMPTY_GRID, _T( "Empty Sphere Grid" ), wxDefaultPosition, wxDefaultSize, 0 );
    emptySphereGridRadioButton->SetToolTip( "If checked, the sphere grid will be empty aside from Ability nodes. You have to find all the spheres yourself." );
    wxRadioButton* fillSphereGridRadioButton = new wxRadioButton( this, ID_FULL_GRID, _T( "Full Sphere Grid" ), wxDefaultPosition, wxDefaultSize, 0 );
    fillSphereGridRadioButton->SetToolTip( "If checked, the sphere grid will have no empty nodes. Any slot that would be empty will be filled with a random stat node instead." );

    removeSphereGridLocksCheckbox = new wxCheckBox( this, ID_REMOVE_LOCKS, _T( "Remove Sphere Grid Locks" ), wxDefaultPosition, wxDefaultSize, 0 );
    removeSphereGridLocksCheckbox->SetToolTip( "If checked, the sphere grid will have no key nodes, giving you freedom to go anywhere and get anything." );

    wxStaticText* sphere_grid_text = new wxStaticText( this, wxID_ANY, _T( "Sphere Grid Randomization Options" ), wxDefaultPosition, wxDefaultSize, 0 );
    sphere_grid_text->SetFont( wxFont( 9, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD ) );

    wxStaticText* node_text = new wxStaticText( this, wxID_ANY, _T( "Sphere Grid Node Options" ), wxDefaultPosition, wxDefaultSize, 0 );
    node_text->SetFont( wxFont( 9, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD ) );

    wxStaticText* grid_text = new wxStaticText( this, wxID_ANY, _T( "Sphere Grid Modifier Options" ), wxDefaultPosition, wxDefaultSize, 0 );
    grid_text->SetFont( wxFont( 9, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD ) );

    sizer->Add( new_game_text, 0, wxALIGN_CENTER | wxLEFT | wxRIGHT | wxTOP, FromDIP( 5 ) );
    sizer->Add( removeSphereGridLocksCheckbox, 0, wxALIGN_LEFT | wxLEFT | wxRIGHT | wxTOP, FromDIP( 5 ) );
    sizer->InsertSpacer( sizer->GetItemCount(), FromDIP( 5 ) );

    sizer->Add( sphere_grid_text, 0, wxALIGN_LEFT | wxLEFT | wxRIGHT | wxTOP, FromDIP( 5 ) );
    sizer->Add( RandomizeSphereGridNoneRadioButton, 0, wxALIGN_LEFT | wxLEFT | wxRIGHT | wxTOP, FromDIP( 5 ) );
    sizer->Add( ShuffleSphereGridRadioButton, 0, wxALIGN_LEFT | wxLEFT | wxRIGHT | wxTOP, FromDIP( 5 ) );
    sizer->Add( RandomizeSphereGridRadioButton, 0, wxALIGN_LEFT | wxLEFT | wxRIGHT | wxTOP, FromDIP( 5 ) );
    sizer->Add( RandomizeSphereGridRadioButton2, 0, wxALIGN_LEFT | wxLEFT | wxRIGHT | wxTOP, FromDIP( 5 ) );

    sizer->InsertSpacer( sizer->GetItemCount(), FromDIP( 10 ) );

    sizer->Add( node_text, 0, wxALIGN_LEFT | wxLEFT | wxRIGHT | wxTOP, FromDIP( 5 ) );
    sizer->Add( sphereNodesNoneRadioButton, 0, wxALIGN_LEFT | wxLEFT | wxRIGHT | wxTOP, FromDIP( 5 ) );
    sizer->Add( upgradeSphereNodesRadioButton, 0, wxALIGN_LEFT | wxLEFT | wxRIGHT | wxTOP, FromDIP( 5 ) );
    sizer->Add( downgradeSphereNodesRadioButton, 0, wxALIGN_LEFT | wxLEFT | wxRIGHT | wxTOP, FromDIP( 5 ) );

    sizer->InsertSpacer( sizer->GetItemCount(), FromDIP( 10 ) );

    sizer->Add( grid_text, 0, wxALIGN_LEFT | wxLEFT | wxRIGHT | wxTOP, FromDIP( 5 ) );
    sizer->Add( sphereGridNoneRadioButton, 0, wxALIGN_LEFT | wxLEFT | wxRIGHT | wxTOP, FromDIP( 5 ) );
    sizer->Add( emptySphereGridRadioButton, 0, wxALIGN_LEFT | wxLEFT | wxRIGHT | wxTOP, FromDIP( 5 ) );
    sizer->Add( fillSphereGridRadioButton, 0, wxALIGN_LEFT | wxLEFT | wxRIGHT | wxTOP, FromDIP( 5 ) );

    sizer->InsertSpacer( sizer->GetItemCount(), FromDIP( 5 ) );
    SetSizer( sizer );
    SetMinSize( GetBestVirtualSize() );
  }
};

wxDECLARE_APP( gui_t );