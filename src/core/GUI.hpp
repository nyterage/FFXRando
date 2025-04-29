#pragma once
#include <wx/wxprec.h>
#include <wx/grid.h>
#include <chrono>
#include "Randomizer.hpp"

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

enum
{
  ID_SEED = 1,
  ID_RANDOMIZE = 2,
  ID_RANDOMIZE_ENEMY_DROPS = 3,
  ID_RANDOMIZE_ENEMY_STEALS = 4,
  ID_RANDOMIZE_ENEMY_BRIBES = 5,
  ID_RANDOMIZE_ENEMY_GEAR_DROPS = 6,
  ID_RANDOMIZE_ENEMY_STATS = 7,
  ID_RANDOMIZE_ENEMY_STATS_DEFENSIVE = 8,
  ID_RANDOMIZE_ENEMY_STATS_SHUFFLE = 9,
  ID_RANDOMIZE_SHOPS = 10,
  ID_RANDOMIZE_SHOP_PRICES = 11,
  ID_RANDOMIZE_FIELD_ITEMS = 12,
  ID_RANDOMIZE_GEAR_ABILITIES = 13,
  ID_RANDOMIZE_KEY_ITEMS = 14,
  ID_KEEP_THINGS_SANE = 15,
  ID_RANDOMIZE_PLAYER_STATS = 16,
  ID_RANDOMIZE_AEON_STAT_SCALING = 17,
  ID_RANDOMIZE_PLAYER_STATS_SHUFFLE = 18,
  ID_RANDOMIZE_AEON_STAT_SCALING_SHUFFLE = 19,
  ID_POISON_IS_DEADLY = 20,
  ID_RANDOMIZE_AEON_BASE_STATS = 21,
  ID_SHUFFLE_AEON_BASE_STATS = 22,
  ID_RANDOMIZE_STARTING_OVERDRIVE_MODE = 23,
  ID_RANDOMIZE_ENEMY_ELEMENTAl_AFFINITIES = 24,
  ID_FAHRENHEIT = 25,
  ID_RANDOMIZE_CELESTIALS = 26,
  ID_RANDOMIZE_BROTHERHOOD = 27,
  ID_SHUFFLE_SPHERE_GRID = 28,
  ID_UPGRADE_SPHERE_NODES = 29,
  ID_DOWNGRADE_SPHERE_NODES = 30,
  ID_RANDOMIZE_SPHERE_GRID = 31,
  ID_EMPTY_GRID = 32,
  ID_FULL_GRID = 33,
  ID_REMOVE_LOCKS = 34,
};

struct gui_t : public wxApp
{
private:
  data_pack_t& dp;

public:
  gui_t( data_pack_t& data_pack ) : dp( data_pack ) {}

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
  bool keep_things_sane;
  bool randomize_celestials;
  bool randomize_brotherhood;
  wxButton* randomize_button;
  int32_t seed;
  wxTextCtrl* seed_text;

  bool fahrenheit;

public:
  frame_t( data_pack_t& data ) 
    : wxFrame( NULL, wxID_ANY, "FFX Randomizer", wxDefaultPosition, wxSize( 840, 720 ) ),
    randomize_enemy_drops( false ),
    randomize_enemy_steals( false ),
    randomize_enemy_bribes( false ),
    randomize_enemy_gear_drops( false ),
    randomize_enemy_stats( false ),
    randomize_enemy_stats_defensive( false ),
    randomize_enemy_stats_shuffle( false ),
    randomize_shops( false ),
    randomize_shop_prices( false ),
    randomize_field_items( false ),
    randomize_gear_abilities( false ),
    randomize_player_stats( false ),
    randomize_aeon_stat_scaling( false ),
    randomize_aeon_base_stats( false ),
    shuffle_player_stats( false ),
    shuffle_aeon_stat_scaling( false ),
    shuffle_aeon_base_stats( false ),
    poison_is_deadly( false ),
    randomize_starting_overdrive_mode( false ),
    randomize_enemy_elemental_affinities( false ),
    shuffle_sphere_grid( false ),
    randomize_sphere_grid( false ),
    empty_sphere_grid( false ),
    fill_sphere_grid( false ),
    remove_sphere_grid_locks( false ),
    upgrade_sphere_nodes( false ),
    downgrade_sphere_nodes( false ),
    randomize_key_items( false ),
    keep_things_sane( true ),
    randomizer( nullptr ),
    randomize_celestials( false ),
    randomize_brotherhood( false ),
    randomize_button( nullptr ),
    dp( data ),
    options( nullptr ),
    seed( std::chrono::system_clock::now().time_since_epoch().count() ),
    seed_text( nullptr ),
    fahrenheit( false )
  {
    initialize();
    SetSizeHints( GetBestSize(), GetMaxClientSize() );
  }

private:
  void initialize();
  void onSeedChange( wxCommandEvent& event );
  void onRandomize( wxCommandEvent& event );
  void onRandomizeEnemyDrops( wxCommandEvent& event );
  void onRandomizeEnemySteals( wxCommandEvent& event );
  void onRandomizeEnemyBribes( wxCommandEvent& event );
  void onRandomizeEnemyGearDrops( wxCommandEvent& event );
  void onRandomizeEnemyStats( wxCommandEvent& event );
  void onRandomizeEnemyStatsDefensive( wxCommandEvent& event );
  void onRandomizeEnemyStatsShuffle( wxCommandEvent& event );
  void onRandomizeShops( wxCommandEvent& event );
  void onRandomizeShopPrices( wxCommandEvent& event );
  void onRandomizeFieldItems( wxCommandEvent& event );
  void onRandomizeGearAbilities( wxCommandEvent& event );
  void onRandomizePlayerStats( wxCommandEvent& event );
  void onRandomizeAeonStatScaling( wxCommandEvent& event );
  void onRandomizeAeonBaseStats( wxCommandEvent& event );
  void onShufflePlayerStats( wxCommandEvent& event );
  void onShuffleAeonStatScaling( wxCommandEvent& event );
  void onShuffleAeonBaseStats( wxCommandEvent& event );
  void onPoisonIsDeadly( wxCommandEvent& event );
  void onRandomizeStartingOverdriveMode( wxCommandEvent& event );
  void onRandomizeEnemyElementalAffinities( wxCommandEvent& event );
  void onShuffleSphereGrid( wxCommandEvent& event );
  void onRandomizeSphereGrid( wxCommandEvent& event );
  void onEmptySphereGrid( wxCommandEvent& event );
  void onFillSphereGrid( wxCommandEvent& event );
  void onRemoveSphereGridLocks( wxCommandEvent& event );
  void onUpgradeSphereNodes( wxCommandEvent& event );
  void onDowngradeSphereNodes( wxCommandEvent& event );

  void onRandomizeKeyItems( wxCommandEvent& event );
  void onKeepThingsSane( wxCommandEvent& event );
  void onFahrenheit( wxCommandEvent& event );
  void onRandomizeCelestials( wxCommandEvent& event );
  void onRandomizeBrotherhood( wxCommandEvent& event );

  int32_t hash( char* str );
};

struct main_panel_t : public wxPanel
{
  wxCheckBox* poisonIsDeadlyCheckbox;

  wxCheckBox* randomizeEnemyDropsCheckbox;
  wxCheckBox* randomizeEnemyStealsCheckbox;
  wxCheckBox* randomizeEnemyBribesCheckbox;
  wxCheckBox* randomizeEnemyGearDropsCheckbox;
  wxCheckBox* randomizeEnemyElementalAffinitiesCheckbox;

  wxCheckBox* randomizeShopsCheckbox;
  wxCheckBox* randomizeShopPricesCheckbox;
  wxCheckBox* randomizeFieldItemsCheckbox;
  wxCheckBox* randomizeGearAbilitiesCheckbox;

  main_panel_t( frame_t* frame ) : wxPanel( frame, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_THEME ),
    poisonIsDeadlyCheckbox( nullptr ),
    randomizeEnemyDropsCheckbox( nullptr ),
    randomizeEnemyStealsCheckbox( nullptr ),
    randomizeEnemyBribesCheckbox( nullptr ),
    randomizeEnemyGearDropsCheckbox( nullptr ),
    randomizeEnemyElementalAffinitiesCheckbox( nullptr ),
    randomizeShopsCheckbox( nullptr ),
    randomizeShopPricesCheckbox( nullptr ),
    randomizeFieldItemsCheckbox( nullptr ),
    randomizeGearAbilitiesCheckbox( nullptr )
  {
    wxBoxSizer* sizer = new wxBoxSizer( wxVERTICAL );

    poisonIsDeadlyCheckbox = new wxCheckBox( this, ID_POISON_IS_DEADLY, _T( "Poison is Deadly" ), wxDefaultPosition, wxDefaultSize, 0 );
    poisonIsDeadlyCheckbox->SetToolTip( "If checked, poison will deal 50% of the players HP per tick instead of the default 25%." );

    randomizeEnemyDropsCheckbox = new wxCheckBox( this, ID_RANDOMIZE_ENEMY_DROPS, _T( "Randomize Enemy Drops" ), wxDefaultPosition, wxDefaultSize, 0 );
    randomizeEnemyStealsCheckbox = new wxCheckBox( this, ID_RANDOMIZE_ENEMY_STEALS, _T( "Randomize Enemy Steals" ), wxDefaultPosition, wxDefaultSize, 0 );
    randomizeEnemyBribesCheckbox = new wxCheckBox( this, ID_RANDOMIZE_ENEMY_BRIBES, _T( "Randomize Enemy Bribes" ), wxDefaultPosition, wxDefaultSize, 0 );
    randomizeEnemyGearDropsCheckbox = new wxCheckBox( this, ID_RANDOMIZE_ENEMY_GEAR_DROPS, _T( "Randomize Enemy Gear Drops" ), wxDefaultPosition, wxDefaultSize, 0 );
    randomizeEnemyElementalAffinitiesCheckbox = new wxCheckBox( this, ID_RANDOMIZE_ENEMY_ELEMENTAl_AFFINITIES, _T( "Randomize Enemy Elemental Affinities" ), wxDefaultPosition, wxDefaultSize, 0 );
    randomizeEnemyElementalAffinitiesCheckbox->SetToolTip( "If checked, enemy elemental affinities will be randomized. This includes:\n- Weaknesss \n- Resists \n- Immunities \n- Absorbs\n\nThis is slightly skewed in favor of giving an enemy a weakness if it gets an affinity." );

    randomizeShopsCheckbox = new wxCheckBox( this, ID_RANDOMIZE_SHOPS, _T( "Randomize Shops" ), wxDefaultPosition, wxDefaultSize, 0 );
    randomizeShopPricesCheckbox = new wxCheckBox( this, ID_RANDOMIZE_SHOP_PRICES, _T( "Randomize Shop Prices" ), wxDefaultPosition, wxDefaultSize, 0 );
    randomizeFieldItemsCheckbox = new wxCheckBox( this, ID_RANDOMIZE_FIELD_ITEMS, _T( "Randomize Field Items" ), wxDefaultPosition, wxDefaultSize, 0 );
    randomizeGearAbilitiesCheckbox = new wxCheckBox( this, ID_RANDOMIZE_GEAR_ABILITIES, _T( "Randomize Gear Abilities" ), wxDefaultPosition, wxDefaultSize, 0 );

    sizer->Add( poisonIsDeadlyCheckbox, 0, wxALIGN_LEFT | wxLEFT | wxRIGHT | wxTOP, FromDIP( 5 ) );

    sizer->Add( randomizeEnemyDropsCheckbox, 0, wxALIGN_LEFT | wxLEFT | wxRIGHT | wxTOP, FromDIP( 5 ) );
    sizer->Add( randomizeEnemyStealsCheckbox, 0, wxALIGN_LEFT | wxLEFT | wxRIGHT | wxTOP, FromDIP( 5 ) );
    sizer->Add( randomizeEnemyBribesCheckbox, 0, wxALIGN_LEFT | wxLEFT | wxRIGHT | wxTOP, FromDIP( 5 ) );
    sizer->Add( randomizeEnemyGearDropsCheckbox, 0, wxALIGN_LEFT | wxLEFT | wxRIGHT | wxTOP, FromDIP( 5 ) );
    sizer->Add( randomizeEnemyElementalAffinitiesCheckbox, 0, wxALIGN_LEFT | wxLEFT | wxRIGHT | wxTOP, FromDIP( 5 ) );

    sizer->Add( randomizeShopsCheckbox, 0, wxALIGN_LEFT | wxLEFT | wxRIGHT | wxTOP, FromDIP( 5 ) );
    sizer->Add( randomizeShopPricesCheckbox, 0, wxALIGN_LEFT | wxLEFT | wxRIGHT | wxTOP, FromDIP( 5 ) );
    sizer->Add( randomizeFieldItemsCheckbox, 0, wxALIGN_LEFT | wxLEFT | wxRIGHT | wxTOP, FromDIP( 5 ) );
    sizer->Add( randomizeGearAbilitiesCheckbox, 0, wxALIGN_LEFT | wxLEFT | wxRIGHT | wxTOP, FromDIP( 5 ) );
    sizer->InsertSpacer( sizer->GetItemCount(), FromDIP( 5 ) );

    SetSizer( sizer );
    SetMinSize( GetBestVirtualSize() );
  }
};

struct header_panel_t : public wxPanel
{
  wxCheckBox* randomizeKeyItemsCheckbox;
  wxCheckBox* keepThingsSaneCheckbox;
  wxCheckBox* fahrenheitCheckbox;
  wxCheckBox* randomizeCelestialsCheckbox;
  wxCheckBox* randomizeBrotherhoodCheckbox;

  header_panel_t( frame_t* frame ) : wxPanel( frame, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_THEME ),
    randomizeKeyItemsCheckbox( nullptr ),
    keepThingsSaneCheckbox( nullptr ),
    fahrenheitCheckbox( nullptr ),
    randomizeCelestialsCheckbox( nullptr ),
    randomizeBrotherhoodCheckbox( nullptr )
  {
    wxBoxSizer* sizer = new wxBoxSizer( wxVERTICAL );
    fahrenheitCheckbox = new wxCheckBox( this, ID_FAHRENHEIT, _T( "Fahrenheit" ), wxDefaultPosition, wxDefaultSize, 0 );
    fahrenheitCheckbox->SetToolTip( "Check this box to generate files in a format suitable for the Fahrenheit mod loader." );
    randomizeKeyItemsCheckbox = new wxCheckBox( this, ID_RANDOMIZE_KEY_ITEMS, _T( "Include Key Items in Pool?" ), wxDefaultPosition, wxDefaultSize, 0 );
    randomizeKeyItemsCheckbox->SetToolTip( "If checked, key items will be included in the randomization pool. This might break progression, use it with caution." );
    randomizeCelestialsCheckbox = new wxCheckBox( this, ID_RANDOMIZE_CELESTIALS, _T( "Randomize Celestial Weapons" ), wxDefaultPosition, wxDefaultSize, 0 );
    randomizeCelestialsCheckbox->SetToolTip( "If checked, celestial weapons abilities will be able to be randomized." );
    randomizeBrotherhoodCheckbox = new wxCheckBox( this, ID_RANDOMIZE_BROTHERHOOD, _T( "Randomize Brotherhood" ), wxDefaultPosition, wxDefaultSize, 0 );
    randomizeBrotherhoodCheckbox->SetToolTip( "If checked, Brotherhood abilities will be able to be randomized." );
    keepThingsSaneCheckbox = new wxCheckBox( this, ID_KEEP_THINGS_SANE, _T( "Keep Things Sane" ), wxDefaultPosition, wxDefaultSize, 0 );
    keepThingsSaneCheckbox->SetToolTip( "If checked, the randomizer will attempt to keep things close to vanilla values. IE, if you could ever only loot 1 of an item, the randomizer will keep it that way.\nAlso keeps constraints on gil, and AP to more reasonable values, within +-100% of their original values.\nThis will mean that some spheres will sell in shops for very little, as their data has them being sold for 2 gil." );
    keepThingsSaneCheckbox->SetValue( true );

    sizer->Add( fahrenheitCheckbox, 0, wxALIGN_LEFT | wxLEFT | wxRIGHT | wxTOP, FromDIP( 5 ) );
    sizer->Add( randomizeKeyItemsCheckbox, 0, wxALIGN_LEFT | wxLEFT | wxRIGHT | wxTOP, FromDIP( 5 ) );
    sizer->Add( randomizeCelestialsCheckbox, 0, wxALIGN_LEFT | wxLEFT | wxRIGHT | wxTOP, FromDIP( 5 ) );
    sizer->Add( randomizeBrotherhoodCheckbox, 0, wxALIGN_LEFT | wxLEFT | wxRIGHT | wxTOP, FromDIP( 5 ) );
    sizer->Add( keepThingsSaneCheckbox, 0, wxALIGN_LEFT | wxLEFT | wxRIGHT | wxTOP, FromDIP( 5 ) );
    sizer->InsertSpacer( sizer->GetItemCount(), FromDIP( 5 ) );
    SetSizer( sizer );

    SetMinSize( GetBestVirtualSize() );
  }
};

struct enemy_stats_panel_t : public wxPanel
{
  wxCheckBox* randomizeEnemyStatsCheckbox;
  wxCheckBox* randomizeEnemyStatsDefensiveCheckbox;
  wxCheckBox* randomizeEnemyStatsShuffleCheckbox;

  enemy_stats_panel_t( frame_t* frame ) : wxPanel( frame, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_THEME ),
    randomizeEnemyStatsCheckbox( nullptr ),
    randomizeEnemyStatsDefensiveCheckbox( nullptr ),
    randomizeEnemyStatsShuffleCheckbox( nullptr )
  {
    wxBoxSizer* sizer = new wxBoxSizer( wxVERTICAL );
    randomizeEnemyStatsCheckbox = new wxCheckBox( this, ID_RANDOMIZE_ENEMY_STATS, _T( "Randomize Enemy Stats - Normal Distribution" ), wxDefaultPosition, wxDefaultSize, 0 );
    randomizeEnemyStatsCheckbox->SetToolTip( "If checked, enemy stats will be randomized using a normal distribution, centered on their original values. This keeps things close to vanilla, with some spice on occasion" );
    randomizeEnemyStatsDefensiveCheckbox = new wxCheckBox( this, ID_RANDOMIZE_ENEMY_STATS_DEFENSIVE, _T( "Shuffle Enemy Stats + Normalize Defensives" ), wxDefaultPosition, wxDefaultSize, 0 );
    randomizeEnemyStatsDefensiveCheckbox->SetToolTip( "If checked, enemy defensive stats (def/magic def/evasion) will be randomly assigned to another enemies values, with some math magic to try to keep them from ending up too tanky.\n Non defensive stats are randomized with the same method as the Normal Distribution option." );
    randomizeEnemyStatsShuffleCheckbox = new wxCheckBox( this, ID_RANDOMIZE_ENEMY_STATS_SHUFFLE, _T( "Shuffle Enemy Stats" ), wxDefaultPosition, wxDefaultSize, 0 );
    randomizeEnemyStatsShuffleCheckbox->SetToolTip( "If checked, enemy defensive stats (def/magic def/evasion) will be shuffled to a different enemies defensive stats at random.\nYou may encounter a flan with penance's defensive stats" );
    sizer->Add( randomizeEnemyStatsCheckbox, 0, wxALIGN_LEFT | wxLEFT | wxRIGHT | wxTOP, FromDIP( 5 ) );
    sizer->Add( randomizeEnemyStatsDefensiveCheckbox, 0, wxALIGN_LEFT | wxLEFT | wxRIGHT | wxTOP, FromDIP( 5 ) );
    sizer->Add( randomizeEnemyStatsShuffleCheckbox, 0, wxALIGN_LEFT | wxLEFT | wxRIGHT | wxTOP, FromDIP( 5 ) );
    sizer->InsertSpacer( sizer->GetItemCount(), FromDIP( 5 ) );
    SetSizer( sizer );
    SetMinSize( GetBestVirtualSize() );
  }
};

struct player_stats_panel_t : public wxPanel
{
  wxCheckBox* randomizePlayerStatsCheckbox;
  wxCheckBox* shufflePlayerStatsCheckbox;
  wxCheckBox* randomizeStartingOverdriveModeCheckbox;

  player_stats_panel_t( wxPanel* panel ) : wxPanel( panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_THEME ),
    randomizePlayerStatsCheckbox( nullptr ),
    shufflePlayerStatsCheckbox( nullptr ),
    randomizeStartingOverdriveModeCheckbox( nullptr )
  {
    wxBoxSizer* sizer = new wxBoxSizer( wxVERTICAL );

    randomizePlayerStatsCheckbox = new wxCheckBox( this, ID_RANDOMIZE_PLAYER_STATS, _T( "Randomize Party Member Stats" ), wxDefaultPosition, wxDefaultSize, 0 );
    randomizePlayerStatsCheckbox->SetToolTip( "If checked, party member stats will be randomized using a normal distribution, centered on their original values. This keeps things close to vanilla, with some spice on occasion" );

    shufflePlayerStatsCheckbox = new wxCheckBox( this, ID_RANDOMIZE_PLAYER_STATS_SHUFFLE, _T( "Shuffle Party Member Stats" ), wxDefaultPosition, wxDefaultSize, 0 );
    shufflePlayerStatsCheckbox->SetToolTip( "If checked, party member stats will be shuffled to another party members stats at random." );

    randomizeStartingOverdriveModeCheckbox = new wxCheckBox( this, ID_RANDOMIZE_STARTING_OVERDRIVE_MODE, _T( "Randomize Starting Overdrive Mode" ), wxDefaultPosition, wxDefaultSize, 0 );
    randomizeStartingOverdriveModeCheckbox->SetToolTip( "If checked, the starting overdrive mode for playable characters will be random." );

    sizer->Add( randomizePlayerStatsCheckbox, 0, wxALIGN_LEFT | wxLEFT | wxRIGHT | wxTOP, FromDIP( 5 ) );
    sizer->Add( shufflePlayerStatsCheckbox, 0, wxALIGN_LEFT | wxLEFT | wxRIGHT | wxTOP, FromDIP( 5 ) );
    sizer->Add( randomizeStartingOverdriveModeCheckbox, 0, wxALIGN_LEFT | wxLEFT | wxRIGHT | wxTOP, FromDIP( 5 ) );
    sizer->InsertSpacer( sizer->GetItemCount(), FromDIP( 5 ) );
    SetSizer( sizer );
    SetMinSize( GetBestVirtualSize() );
  }
};

struct aeon_stats_panel_t : public wxPanel
{
  wxCheckBox* randomizeAeonStatScalingCheckbox;
  wxCheckBox* randomiseAeonBaseStatsCheckbox;
  wxCheckBox* shuffleAeonStatScalingCheckbox;
  wxCheckBox* shuffleAeonBaseStatsCheckbox;

  aeon_stats_panel_t( wxPanel* panel ) : wxPanel( panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_THEME ),
    randomizeAeonStatScalingCheckbox( nullptr ),
    randomiseAeonBaseStatsCheckbox( nullptr ),
    shuffleAeonStatScalingCheckbox( nullptr ),
    shuffleAeonBaseStatsCheckbox( nullptr )
  {
    wxBoxSizer* sizer = new wxBoxSizer( wxVERTICAL );

    randomizeAeonStatScalingCheckbox = new wxCheckBox( this, ID_RANDOMIZE_AEON_STAT_SCALING, _T( "Randomize Aeon Stat Scaling" ), wxDefaultPosition, wxDefaultSize, 0 );
    randomizeAeonStatScalingCheckbox->SetToolTip( "If checked, aeon stat scaling (with Yunas stats) will be randomized using a normal distribution, centered on their original values. This keeps things close to vanilla, with some spice on occasion" );
    randomiseAeonBaseStatsCheckbox = new wxCheckBox( this, ID_RANDOMIZE_AEON_BASE_STATS, _T( "Randomize Aeon Base Stats" ), wxDefaultPosition, wxDefaultSize, 0 );
    randomiseAeonBaseStatsCheckbox->SetToolTip( "If checked, aeon base stats will be randomized using a normal distribution, centered on their original values. This keeps things close to vanilla, with some spice on occasion" );

    shuffleAeonStatScalingCheckbox = new wxCheckBox( this, ID_RANDOMIZE_AEON_STAT_SCALING_SHUFFLE, _T( "Shuffle Aeon Stat Scaling" ), wxDefaultPosition, wxDefaultSize, 0 );
    shuffleAeonStatScalingCheckbox->SetToolTip( "If checked, aeon stat scaling (with Yunas stats) will be shuffled to another aeons stats at random." );
    shuffleAeonBaseStatsCheckbox = new wxCheckBox( this, ID_SHUFFLE_AEON_BASE_STATS, _T( "Shuffle Aeon Base Stats" ), wxDefaultPosition, wxDefaultSize, 0 );
    shuffleAeonBaseStatsCheckbox->SetToolTip( "If checked, aeon base stats will be shuffled to another aeons stats at random." );

    sizer->Add( randomiseAeonBaseStatsCheckbox, 0, wxALIGN_LEFT | wxLEFT | wxRIGHT | wxTOP, FromDIP( 5 ) );
    sizer->Add( randomizeAeonStatScalingCheckbox, 0, wxALIGN_LEFT | wxLEFT | wxRIGHT | wxTOP, FromDIP( 5 ) );
    sizer->Add( shuffleAeonStatScalingCheckbox, 0, wxALIGN_LEFT | wxLEFT | wxRIGHT | wxTOP, FromDIP( 5 ) );
    sizer->Add( shuffleAeonBaseStatsCheckbox, 0, wxALIGN_LEFT | wxLEFT | wxRIGHT | wxTOP, FromDIP( 5 ) );
    sizer->InsertSpacer( sizer->GetItemCount(), FromDIP( 5 ) );
    SetSizer( sizer );
    SetMinSize( GetBestVirtualSize() );
  }
};

struct sphere_grid_panel_t : public wxPanel
{
  wxCheckBox* shuffleSphereGridCheckbox;
  wxCheckBox* randomizeSphereGridCheckbox;
  wxCheckBox* emptySphereGridCheckbox;
  wxCheckBox* fillSphereGridCheckbox;
  wxCheckBox* removeSphereGridLocksCheckbox;
  wxCheckBox* upgradeSphereNodesCheckbox;
  wxCheckBox* downgradeSphereNodesCheckbox;

  sphere_grid_panel_t( wxPanel* panel ) : wxPanel( panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_THEME ),
    shuffleSphereGridCheckbox( nullptr ),
    randomizeSphereGridCheckbox( nullptr ),
    emptySphereGridCheckbox( nullptr ),
    fillSphereGridCheckbox( nullptr ),
    removeSphereGridLocksCheckbox( nullptr ),
    upgradeSphereNodesCheckbox( nullptr ),
    downgradeSphereNodesCheckbox( nullptr )
  {
    wxBoxSizer* sizer = new wxBoxSizer( wxVERTICAL );

    shuffleSphereGridCheckbox = new wxCheckBox( this, ID_SHUFFLE_SPHERE_GRID, _T( "Shuffle Sphere Grid" ), wxDefaultPosition, wxDefaultSize, 0 );
    shuffleSphereGridCheckbox->SetToolTip( "If checked, the sphere grid will be shuffled. This means that the nodes will be in a different order, but the same nodes will be present." );
    randomizeSphereGridCheckbox = new wxCheckBox( this, ID_RANDOMIZE_SPHERE_GRID, _T( "Randomize Sphere Grid" ), wxDefaultPosition, wxDefaultSize, 0 );
    randomizeSphereGridCheckbox->SetToolTip( "If checked, the sphere grid will be randomized. This means that there is no guarentee you will get all ability spheres, and there may be duplicate ability nodes." );
    emptySphereGridCheckbox = new wxCheckBox( this, ID_EMPTY_GRID, _T( "Empty Sphere Grid" ), wxDefaultPosition, wxDefaultSize, 0 );
    emptySphereGridCheckbox->SetToolTip( "If checked, the sphere grid will be empty aside from Ability nodes. You have to find all the spheres yourself." );
    fillSphereGridCheckbox = new wxCheckBox( this, ID_FULL_GRID, _T( "Full Sphere Grid" ), wxDefaultPosition, wxDefaultSize, 0 );
    fillSphereGridCheckbox->SetToolTip( "If checked, the sphere grid will have no empty nodes. Any slot that would be empty will be filled with a random stat node instead." );
    removeSphereGridLocksCheckbox = new wxCheckBox( this, ID_REMOVE_LOCKS, _T( "Remove Sphere Grid Locks" ), wxDefaultPosition, wxDefaultSize, 0 );
    removeSphereGridLocksCheckbox->SetToolTip( "If checked, the sphere grid will have no key nodes, giving you freedom to go anywhere and get anything." );
    upgradeSphereNodesCheckbox = new wxCheckBox( this, ID_UPGRADE_SPHERE_NODES, _T( "Upgrade Sphere Nodes" ), wxDefaultPosition, wxDefaultSize, 0 );
    upgradeSphereNodesCheckbox->SetToolTip( "If checked, all stat nodes in the sphere grid will be upgraded to their maximum value." );
    downgradeSphereNodesCheckbox = new wxCheckBox( this, ID_DOWNGRADE_SPHERE_NODES, _T( "Downgrade Sphere Nodes" ), wxDefaultPosition, wxDefaultSize, 0 );
    downgradeSphereNodesCheckbox->SetToolTip( "If checked, all stat nodes in the sphere grid will be downgraded to their minimum value." );

    sizer->Add( shuffleSphereGridCheckbox, 0, wxALIGN_LEFT | wxLEFT | wxRIGHT | wxTOP, FromDIP( 5 ) );
    sizer->Add( randomizeSphereGridCheckbox, 0, wxALIGN_LEFT | wxLEFT | wxRIGHT | wxTOP, FromDIP( 5 ) );
    sizer->Add( emptySphereGridCheckbox, 0, wxALIGN_LEFT | wxLEFT | wxRIGHT | wxTOP, FromDIP( 5 ) );
    sizer->Add( fillSphereGridCheckbox, 0, wxALIGN_LEFT | wxLEFT | wxRIGHT | wxTOP, FromDIP( 5 ) );
    sizer->Add( removeSphereGridLocksCheckbox, 0, wxALIGN_LEFT | wxLEFT | wxRIGHT | wxTOP, FromDIP( 5 ) );
    sizer->Add( upgradeSphereNodesCheckbox, 0, wxALIGN_LEFT | wxLEFT | wxRIGHT | wxTOP, FromDIP( 5 ) );
    sizer->Add( downgradeSphereNodesCheckbox, 0, wxALIGN_LEFT | wxLEFT | wxRIGHT | wxTOP, FromDIP( 5 ) );

    sizer->InsertSpacer( sizer->GetItemCount(), FromDIP( 5 ) );
    SetSizer( sizer );
    SetMinSize( GetBestVirtualSize() );
  }
};

struct new_game_panel_t : public wxPanel
{
  wxPanel* player_stats_panel;
  wxPanel* aeon_stats_panel;
  wxPanel* sphere_grid_panel;

  new_game_panel_t( frame_t* frame ) : wxPanel( frame, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE ),
    player_stats_panel( nullptr ),
    aeon_stats_panel( nullptr ),
    sphere_grid_panel( nullptr )
  {
    wxBoxSizer* main_sizer = new wxBoxSizer( wxVERTICAL );
    wxBoxSizer* main_horizontal_sizer = new wxBoxSizer( wxHORIZONTAL );
    wxBoxSizer* sphere_grid_sizer = new wxBoxSizer( wxVERTICAL );
    wxBoxSizer* vertical_sizer = new wxBoxSizer( wxVERTICAL );

    wxStaticText* sphere_grid_text = new wxStaticText( this, wxID_ANY, _T( "Sphere Grid Options" ), wxDefaultPosition, wxDefaultSize, 0 );
    sphere_grid_panel = new sphere_grid_panel_t( this );
    wxStaticText* aeon_stats_text = new wxStaticText( this, wxID_ANY, _T( "Aeon Stats Options" ), wxDefaultPosition, wxDefaultSize, 0 );
    aeon_stats_panel = new aeon_stats_panel_t( this );
    wxStaticText* player_stats_text = new wxStaticText( this, wxID_ANY, _T( "Player Stats Options" ), wxDefaultPosition, wxDefaultSize, 0 );
    player_stats_panel = new player_stats_panel_t( this );

    sphere_grid_text->SetFont( wxFont( 10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD ) );
    aeon_stats_text->SetFont( wxFont( 10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD ) );
    player_stats_text->SetFont( wxFont( 10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD ) );

    vertical_sizer->Add( aeon_stats_text, 0, wxALIGN_CENTER | wxLEFT | wxRIGHT | wxTOP, FromDIP( 5 ) );
    vertical_sizer->Add( aeon_stats_panel, 0, wxALIGN_CENTER | wxLEFT | wxRIGHT | wxTOP, FromDIP( 5 ) );
    vertical_sizer->Add( player_stats_text, 0, wxALIGN_CENTER | wxLEFT | wxRIGHT | wxTOP, FromDIP( 5 ) );
    vertical_sizer->Add( player_stats_panel, 0, wxALIGN_CENTER | wxLEFT | wxRIGHT | wxTOP, FromDIP( 5 ) );
    vertical_sizer->AddSpacer( FromDIP( 5 ) );

    sphere_grid_sizer->Add( sphere_grid_text, 0, wxALIGN_CENTER | wxLEFT | wxRIGHT | wxTOP, FromDIP( 5 ) );
    sphere_grid_sizer->Add( sphere_grid_panel, 0, wxALIGN_CENTER | wxLEFT | wxRIGHT | wxTOP, FromDIP( 5 ) );
    sphere_grid_sizer->AddSpacer( FromDIP( 5 ) );

    main_horizontal_sizer->Add( sphere_grid_sizer, 0, wxALIGN_TOP | wxLEFT | wxRIGHT | wxTOP, FromDIP( 5 ) );
    main_horizontal_sizer->Add( vertical_sizer, 0, wxALIGN_TOP | wxLEFT | wxRIGHT | wxTOP, FromDIP( 5 ) );
    main_horizontal_sizer->InsertSpacer( main_horizontal_sizer->GetItemCount(), FromDIP( 5 ) );

    main_sizer->Add( main_horizontal_sizer, 0, wxALIGN_CENTER | wxLEFT | wxRIGHT | wxTOP, FromDIP( 5 ) );
    main_sizer->InsertSpacer( main_sizer->GetItemCount(), FromDIP( 5 ) );

    SetSizer( main_sizer );
    SetMinSize( GetBestVirtualSize() );
  }
};

wxDECLARE_APP( gui_t );