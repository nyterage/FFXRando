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
  ID_RANDOMIZE_AEON_STATS = 17,
  ID_RANDOMIZE_PLAYER_STATS_SHUFFLE = 18,
  ID_RANDOMIZE_AEON_STATS_SHUFFLE = 19,
  ID_POISON_IS_DEADLY = 20,
};

struct gui_t : public wxApp
{
private:
  std::unordered_map<int, enemy_data_t*> enemy_data;
  std::unordered_map<int, field_data_t*> field_data;
  std::unordered_map<int, shop_data_t*> item_shop_data;
  std::unordered_map<int, shop_data_t*> gear_shop_data;
  std::unordered_map<int, gear_data_t*> buki_data;
  std::unordered_map<int, gear_data_t*> weapon_data;
  std::unordered_map<int, gear_data_t*> arms_shop_data;
  std::vector<item_rate_t*> item_rate_data;
  std::vector<character_stats_t*> player_stats_data;
  std::vector<aeon_scaling_data_t*> aeon_scaling_data;

public:
  gui_t( std::unordered_map<int, enemy_data_t*> ed,
         std::unordered_map<int, field_data_t*> fd,
         std::unordered_map<int, shop_data_t*> isd,
         std::unordered_map<int, shop_data_t*> gsd,
         std::unordered_map<int, gear_data_t*> bd,
         std::unordered_map<int, gear_data_t*> wd,
         std::unordered_map<int, gear_data_t*> asd,
         std::vector < item_rate_t*> ird,
         std::vector < character_stats_t*> psd,
         std::vector < aeon_scaling_data_t*> aesd
  ) :
    enemy_data( ed ), field_data( fd ), item_shop_data( isd ),
    gear_shop_data( gsd ), buki_data( bd ), weapon_data( wd ),
    arms_shop_data( asd ), item_rate_data( ird ), player_stats_data( psd ),
    aeon_scaling_data( aesd )
  {}

  virtual bool OnInit();
};

class frame_t : public wxFrame
{
private:
  std::unordered_map<int, enemy_data_t*> enemy_data;
  std::unordered_map<int, field_data_t*> field_data;
  std::unordered_map<int, shop_data_t*> item_shop_data;
  std::unordered_map<int, shop_data_t*> gear_shop_data;
  std::unordered_map<int, gear_data_t*> buki_data;
  std::unordered_map<int, gear_data_t*> weapon_data;
  std::unordered_map<int, gear_data_t*> shop_arms_data;
  std::vector<item_rate_t*> item_rate_data;
  std::vector<character_stats_t*> player_stats_data;
  std::vector<aeon_scaling_data_t*> aeon_scaling_data;

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
  bool randomize_aeon_stats;
  bool shuffle_player_stats;
  bool shuffle_aeon_stats;
  bool poison_is_deadly;

  bool randomize_key_items;
  bool keep_things_sane;
  wxButton* randomize_button;
  int32_t seed;
  wxTextCtrl* seed_text;

public:
  frame_t( std::unordered_map<int, enemy_data_t*> ed,
           std::unordered_map<int, field_data_t*> fd,
           std::unordered_map<int, shop_data_t*> isd,
           std::unordered_map<int, shop_data_t*> gsd,
           std::unordered_map<int, gear_data_t*> bd,
           std::unordered_map<int, gear_data_t*> wd,
           std::unordered_map<int, gear_data_t*> asd,
           std::vector <item_rate_t*> ird,
           std::vector<character_stats_t*> psd,
           std::vector<aeon_scaling_data_t*> aesd
  ) : wxFrame( NULL, wxID_ANY, "FFX Randomizer", wxDefaultPosition, wxSize( 350, 700 ) ),
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
    randomize_aeon_stats( false ),
    shuffle_player_stats( false ),
    shuffle_aeon_stats( false ),
    poison_is_deadly( false ),
    randomize_key_items( false ),
    keep_things_sane( true ),
    randomizer( nullptr ),
    randomize_button( nullptr ),
    enemy_data( ed ),
    field_data( fd ),
    item_shop_data( isd ),
    gear_shop_data( gsd ),
    buki_data( bd ),
    weapon_data( wd ),
    shop_arms_data( asd ),
    item_rate_data( ird ),
    player_stats_data( psd ),
    aeon_scaling_data( aesd ),
    seed( std::chrono::system_clock::now().time_since_epoch().count() ),
    seed_text( nullptr )
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
  void onRandomizeAeonStats( wxCommandEvent& event );
  void onShufflePlayerStats( wxCommandEvent& event );
  void onShuffleAeonStats( wxCommandEvent& event );
  void onPoisonIsDeadly( wxCommandEvent& event );

  void onRandomizeKeyItems( wxCommandEvent& event );
  void onKeepThingsSane( wxCommandEvent& event );

  int32_t hash( char* str );
};

struct main_panel_t : public wxPanel
{
  wxCheckBox* poisonIsDeadlyCheckbox;
  wxCheckBox* randomizeEnemyDropsCheckbox;
  wxCheckBox* randomizeEnemyStealsCheckbox;
  wxCheckBox* randomizeEnemyBribesCheckbox;
  wxCheckBox* randomizeEnemyGearDropsCheckbox;
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
    randomizeShopsCheckbox = new wxCheckBox( this, ID_RANDOMIZE_SHOPS, _T( "Randomize Shops" ), wxDefaultPosition, wxDefaultSize, 0 );
    randomizeShopPricesCheckbox = new wxCheckBox( this, ID_RANDOMIZE_SHOP_PRICES, _T( "Randomize Shop Prices" ), wxDefaultPosition, wxDefaultSize, 0 );
    randomizeFieldItemsCheckbox = new wxCheckBox( this, ID_RANDOMIZE_FIELD_ITEMS, _T( "Randomize Field Items" ), wxDefaultPosition, wxDefaultSize, 0 );
    randomizeGearAbilitiesCheckbox = new wxCheckBox( this, ID_RANDOMIZE_GEAR_ABILITIES, _T( "Randomize Gear Abilities" ), wxDefaultPosition, wxDefaultSize, 0 );

    sizer->Add( poisonIsDeadlyCheckbox, 0, wxALIGN_LEFT | wxLEFT | wxRIGHT | wxTOP, FromDIP( 5 ) );
    sizer->Add( randomizeEnemyDropsCheckbox, 0, wxALIGN_LEFT | wxLEFT | wxRIGHT | wxTOP, FromDIP( 5 ) );
    sizer->Add( randomizeEnemyStealsCheckbox, 0, wxALIGN_LEFT | wxLEFT | wxRIGHT | wxTOP, FromDIP( 5 ) );
    sizer->Add( randomizeEnemyBribesCheckbox, 0, wxALIGN_LEFT | wxLEFT | wxRIGHT | wxTOP, FromDIP( 5 ) );
    sizer->Add( randomizeEnemyGearDropsCheckbox, 0, wxALIGN_LEFT | wxLEFT | wxRIGHT | wxTOP, FromDIP( 5 ) );
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

  header_panel_t( frame_t* frame ) : wxPanel( frame, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_THEME ),
    randomizeKeyItemsCheckbox( nullptr ),
    keepThingsSaneCheckbox( nullptr )
  {
    wxBoxSizer* sizer = new wxBoxSizer( wxVERTICAL );
    randomizeKeyItemsCheckbox = new wxCheckBox( this, ID_RANDOMIZE_KEY_ITEMS, _T( "Include Key Items in Pool?" ), wxDefaultPosition, wxDefaultSize, 0 );
    randomizeKeyItemsCheckbox->SetToolTip( "If checked, key items will be included in the randomization pool. This might break progression, use it with caution." );
    keepThingsSaneCheckbox = new wxCheckBox( this, ID_KEEP_THINGS_SANE, _T( "Keep Things Sane" ), wxDefaultPosition, wxDefaultSize, 0 );
    keepThingsSaneCheckbox->SetToolTip( "If checked, the randomizer will attempt to keep things close to vanilla values. IE, if you could ever only loot 1 of an item, the randomizer will keep it that way.\nAlso keeps constraints on gil, and AP to more reasonable values, within +-100% of their original values.\nThis will mean that some spheres will sell in shops for very little, as their data has them being sold for 2 gil." );
    keepThingsSaneCheckbox->SetValue( true );

    sizer->Add( randomizeKeyItemsCheckbox, 0, wxALIGN_LEFT | wxLEFT | wxRIGHT | wxTOP, FromDIP( 5 ) );
    sizer->Add( keepThingsSaneCheckbox, 0, wxALIGN_LEFT | wxLEFT | wxRIGHT | wxTOP, FromDIP( 5 ) );
    sizer->InsertSpacer( sizer->GetItemCount(), FromDIP( 5 ) );
    SetSizer( sizer );

    SetMinSize( GetBestVirtualSize() );
  }
};

struct player_stats_panel_t : public wxPanel
{
  wxCheckBox* randomizePlayerStatsCheckbox;
  wxCheckBox* randomizeAeonStatsCheckbox;
  wxCheckBox* shufflePlayerStatsCheckbox;
  wxCheckBox* shuffleAeonStatsCheckbox;

  player_stats_panel_t( frame_t* frame ) : wxPanel( frame, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_THEME ),
    randomizePlayerStatsCheckbox( nullptr ),
    randomizeAeonStatsCheckbox( nullptr ),
    shufflePlayerStatsCheckbox( nullptr ),
    shuffleAeonStatsCheckbox( nullptr )
  {
    wxBoxSizer* sizer = new wxBoxSizer( wxVERTICAL );
    randomizePlayerStatsCheckbox = new wxCheckBox( this, ID_RANDOMIZE_PLAYER_STATS, _T( "Randomize Party Member Stats" ), wxDefaultPosition, wxDefaultSize, 0 );
    randomizePlayerStatsCheckbox->SetToolTip( "If checked, party member stats will be randomized using a normal distribution, centered on their original values. This keeps things close to vanilla, with some spice on occasion" );
    randomizeAeonStatsCheckbox = new wxCheckBox( this, ID_RANDOMIZE_AEON_STATS, _T( "Randomize Aeon Stat Scaling" ), wxDefaultPosition, wxDefaultSize, 0 );
    randomizeAeonStatsCheckbox->SetToolTip( "If checked, aeon stats will be randomized using a normal distribution, centered on their original values. This keeps things close to vanilla, with some spice on occasion" );
    shufflePlayerStatsCheckbox = new wxCheckBox( this, ID_RANDOMIZE_PLAYER_STATS_SHUFFLE, _T( "Shuffle Party Member Stats" ), wxDefaultPosition, wxDefaultSize, 0 );
    shufflePlayerStatsCheckbox->SetToolTip( "If checked, party member stats will be shuffled to another party members stats at random." );
    shuffleAeonStatsCheckbox = new wxCheckBox( this, ID_RANDOMIZE_AEON_STATS_SHUFFLE, _T( "Shuffle Aeon Stat Scaling" ), wxDefaultPosition, wxDefaultSize, 0 );
    shuffleAeonStatsCheckbox->SetToolTip( "If checked, aeon stats will be shuffled to another aeons stats at random." );

    sizer->Add( randomizePlayerStatsCheckbox, 0, wxALIGN_LEFT | wxLEFT | wxRIGHT | wxTOP, FromDIP( 5 ) );
    sizer->Add( randomizeAeonStatsCheckbox, 0, wxALIGN_LEFT | wxLEFT | wxRIGHT | wxTOP, FromDIP( 5 ) );
    sizer->Add( shufflePlayerStatsCheckbox, 0, wxALIGN_LEFT | wxLEFT | wxRIGHT | wxTOP, FromDIP( 5 ) );
    sizer->Add( shuffleAeonStatsCheckbox, 0, wxALIGN_LEFT | wxLEFT | wxRIGHT | wxTOP, FromDIP( 5 ) );
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

wxDECLARE_APP( gui_t );