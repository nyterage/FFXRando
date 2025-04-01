#include "GUI.hpp"
#include "Data.hpp"

bool gui_t::OnInit()
{
  SetAppearance( Appearance::System );
  frame_t* frame = new frame_t( enemy_data, field_data, item_shop_data, gear_shop_data,
                                buki_data, weapon_data, arms_shop_data, item_rate_data, 
                                player_stats_data, aeon_scaling_data, aeon_stat_data );
  frame->Show( true );
  return true;
}

void frame_t::initialize()
{
  wxBoxSizer* sizer = new wxBoxSizer( wxVERTICAL );

  wxStaticText* header_text = new wxStaticText( this, wxID_ANY, _T( "FFX Randomizer" ), wxDefaultPosition, wxDefaultSize, 0 );
  header_text->SetFont( wxFont( 18, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD ) );

  wxStaticText* seed_header_text = new wxStaticText( this, wxID_ANY, _T( "RNG Seed" ), wxDefaultPosition, wxDefaultSize, 0 );
  seed_text = new wxTextCtrl( this, ID_SEED, std::to_string( seed ), wxDefaultPosition, wxDefaultSize, 0 );
  Bind( wxEVT_TEXT, &frame_t::onSeedChange, this, ID_SEED );

  wxStaticText* extra_text = new wxStaticText( this, wxID_ANY, _T( "Options that affect other aspects of the randomizer:" ), wxDefaultPosition, wxDefaultSize, 0 );
  header_panel_t* header_panel = new header_panel_t( this );
  Bind( wxEVT_CHECKBOX, &frame_t::onRandomizeKeyItems, this, ID_RANDOMIZE_KEY_ITEMS );

  wxStaticText* main_text = new wxStaticText( this, wxID_ANY, _T( "Main Options:" ), wxDefaultPosition, wxDefaultSize, 0 );

  Bind( wxEVT_CHECKBOX, &frame_t::onPoisonIsDeadly, this, ID_POISON_IS_DEADLY );
  Bind( wxEVT_CHECKBOX, &frame_t::onRandomizeEnemyDrops, this, ID_RANDOMIZE_ENEMY_DROPS );
  Bind( wxEVT_CHECKBOX, &frame_t::onRandomizeEnemySteals, this, ID_RANDOMIZE_ENEMY_STEALS );
  Bind( wxEVT_CHECKBOX, &frame_t::onRandomizeEnemyBribes, this, ID_RANDOMIZE_ENEMY_BRIBES );
  Bind( wxEVT_CHECKBOX, &frame_t::onRandomizeEnemyGearDrops, this, ID_RANDOMIZE_ENEMY_GEAR_DROPS );
  Bind( wxEVT_CHECKBOX, &frame_t::onRandomizeEnemyStats, this, ID_RANDOMIZE_ENEMY_STATS );
  Bind( wxEVT_CHECKBOX, &frame_t::onRandomizeEnemyStatsDefensive, this, ID_RANDOMIZE_ENEMY_STATS_DEFENSIVE );
  Bind( wxEVT_CHECKBOX, &frame_t::onRandomizeEnemyStatsShuffle, this, ID_RANDOMIZE_ENEMY_STATS_SHUFFLE );
  Bind( wxEVT_CHECKBOX, &frame_t::onRandomizeShops, this, ID_RANDOMIZE_SHOPS );
  Bind( wxEVT_CHECKBOX, &frame_t::onRandomizeShopPrices, this, ID_RANDOMIZE_SHOP_PRICES );
  Bind( wxEVT_CHECKBOX, &frame_t::onRandomizeFieldItems, this, ID_RANDOMIZE_FIELD_ITEMS );
  Bind( wxEVT_CHECKBOX, &frame_t::onRandomizeGearAbilities, this, ID_RANDOMIZE_GEAR_ABILITIES );
  Bind( wxEVT_CHECKBOX, &frame_t::onRandomizePlayerStats, this, ID_RANDOMIZE_PLAYER_STATS );
  Bind( wxEVT_CHECKBOX, &frame_t::onRandomizeAeonStatScaling, this, ID_RANDOMIZE_AEON_STAT_SCALING );
  Bind( wxEVT_CHECKBOX, &frame_t::onRandomizeAeonBaseStats, this, ID_RANDOMIZE_AEON_BASE_STATS );
  Bind( wxEVT_CHECKBOX, &frame_t::onShufflePlayerStats, this, ID_RANDOMIZE_PLAYER_STATS_SHUFFLE );
  Bind( wxEVT_CHECKBOX, &frame_t::onShuffleAeonStatScaling, this, ID_RANDOMIZE_AEON_STAT_SCALING_SHUFFLE );
  Bind( wxEVT_CHECKBOX, &frame_t::onShuffleAeonBaseStats, this, ID_SHUFFLE_AEON_BASE_STATS );
  Bind( wxEVT_CHECKBOX, &frame_t::onRandomizeStartingOverdriveMode, this, ID_RANDOMIZE_STARTING_OVERDRIVE_MODE );

  Bind( wxEVT_CHECKBOX, &frame_t::onKeepThingsSane, this, ID_KEEP_THINGS_SANE );

  main_panel_t* panel = new main_panel_t( this );

  wxStaticText* player_stats_text = new wxStaticText( this, wxID_ANY, _T( "These Options only affect new save files!" ), wxDefaultPosition, wxDefaultSize, 0 );
  player_stats_panel_t* player_stats_panel = new player_stats_panel_t( this );

  wxStaticText* enemy_stats_text = new wxStaticText( this, wxID_ANY, _T( "These Options are mutually exclusive, only pick one." ), wxDefaultPosition, wxDefaultSize, 0 );
  enemy_stats_panel_t* stats_panel = new enemy_stats_panel_t( this );

  randomize_button = new wxButton( this, ID_RANDOMIZE, _T( "Randomize" ), wxDefaultPosition, wxDefaultSize, 0 );
  Bind( wxEVT_BUTTON, &frame_t::onRandomize, this, ID_RANDOMIZE );

  sizer->Add( header_text, 0, wxALIGN_CENTER | wxLEFT | wxRIGHT | wxTOP, FromDIP( 10 ) );
  sizer->Add( seed_header_text, 0, wxALIGN_CENTER | wxLEFT | wxRIGHT | wxTOP, FromDIP( 10 ) );
  sizer->Add( seed_text, 0, wxALIGN_CENTER | wxLEFT | wxRIGHT | wxTOP, FromDIP( 10 ) );
  sizer->Add( extra_text, 0, wxALIGN_CENTER | wxLEFT | wxRIGHT | wxTOP, FromDIP( 10 ) );
  sizer->Add( header_panel, 0, wxALIGN_CENTER | wxLEFT | wxRIGHT | wxTOP, FromDIP( 10 ) );
  sizer->Add( main_text, 0, wxALIGN_CENTER | wxLEFT | wxRIGHT | wxTOP, FromDIP( 15 ) );
  sizer->Add( panel, 0, wxALIGN_CENTER | wxLEFT | wxRIGHT | wxTOP, FromDIP( 5 ) );
  sizer->Add( player_stats_text, 0, wxALIGN_CENTER | wxLEFT | wxRIGHT | wxTOP, FromDIP( 5 ) );
  sizer->Add( player_stats_panel, 0, wxALIGN_CENTER | wxLEFT | wxRIGHT | wxTOP, FromDIP( 5 ) );
  sizer->Add( enemy_stats_text, 0, wxALIGN_CENTER | wxLEFT | wxRIGHT | wxTOP, FromDIP( 5 ) );
  sizer->Add( stats_panel, 0, wxALIGN_CENTER | wxLEFT | wxRIGHT | wxTOP, FromDIP( 5 ) );
  sizer->Add( randomize_button, 0, wxALIGN_CENTER | wxLEFT | wxRIGHT | wxTOP, FromDIP( 10 ) );
  SetSizer( sizer );
}

void frame_t::onRandomize( wxCommandEvent& event )
{
  if (randomize_enemy_stats && randomize_enemy_stats_defensive || randomize_enemy_stats && randomize_enemy_stats_shuffle || randomize_enemy_stats_shuffle && randomize_enemy_stats_defensive )
  {
    wxLogMessage( "You can only pick one of the enemy stat randomization options" );
    return;
  }

  if (randomize_player_stats && shuffle_player_stats || randomize_aeon_base_stats && shuffle_aeon_base_stats || randomize_aeon_stat_scaling && shuffle_aeon_stat_scaling)
  {
    wxLogMessage( "You can only pick one of the player or aeon stat randomization options at a time!\nFor Aeons, base and scaling can both be picked though!" );
    return;
  }

  wxLogMessage( "Finished Randomizing" );
  randomizer = new randomizer_t( seed, 
                                 enemy_data, 
                                 field_data, 
                                 item_shop_data, 
                                 gear_shop_data,
                                 buki_data, 
                                 weapon_data,
                                 shop_arms_data, 
                                 item_rate_data,
                                 player_stats_data, 
                                 aeon_scaling_data,
                                 aeon_stat_data,
                                 randomize_enemy_drops,
                                 randomize_enemy_steals, 
                                 randomize_enemy_bribes, 
                                 randomize_enemy_gear_drops, 
                                 randomize_enemy_stats,
                                 randomize_enemy_stats_defensive, 
                                 randomize_enemy_stats_shuffle,
                                 randomize_shops,
                                 randomize_shop_prices,
                                 randomize_field_items, 
                                 randomize_gear_abilities,
                                 randomize_player_stats,
                                 randomize_aeon_stat_scaling, 
                                 randomize_aeon_base_stats,
                                 shuffle_player_stats, 
                                 shuffle_aeon_stat_scaling,
                                 shuffle_aeon_base_stats,
                                 poison_is_deadly,
                                 randomize_starting_overdrive_mode,
                                 randomize_key_items, 
                                 keep_things_sane );
}

void frame_t::onPoisonIsDeadly( wxCommandEvent& event )
{
  poison_is_deadly = !poison_is_deadly;
  printf( "Poison is Deadly: %d\n", poison_is_deadly );
}

void frame_t::onRandomizeEnemyDrops( wxCommandEvent& event )
{
  randomize_enemy_drops = !randomize_enemy_drops;
  printf( "Randomize Enemy Drops: %d\n", randomize_enemy_drops );
}

void frame_t::onRandomizeEnemySteals( wxCommandEvent& event )
{
  randomize_enemy_steals = !randomize_enemy_steals;
  printf( "Randomize Enemy Steals: %d\n", randomize_enemy_steals );
}

void frame_t::onRandomizeEnemyBribes( wxCommandEvent& event )
{
  randomize_enemy_bribes = !randomize_enemy_bribes;
  printf( "Randomize Enemy Bribes: %d\n", randomize_enemy_bribes );
}

void frame_t::onRandomizeEnemyGearDrops( wxCommandEvent& event )
{
  randomize_enemy_gear_drops = !randomize_enemy_gear_drops;
  printf( "Randomize Enemy Gear Drops: %d\n", randomize_enemy_gear_drops );
}

void frame_t::onRandomizeEnemyStats( wxCommandEvent& event )
{
  randomize_enemy_stats = !randomize_enemy_stats;
  printf( "Randomize Enemy Stats Normal Distribution: %d\n", randomize_enemy_stats );
}

void frame_t::onRandomizeEnemyStatsDefensive( wxCommandEvent& event )
{
  randomize_enemy_stats_defensive = !randomize_enemy_stats_defensive;
  printf( "Randomize Enemy Stats Defensive: %d\n", randomize_enemy_stats_defensive );
}

void frame_t::onRandomizeEnemyStatsShuffle( wxCommandEvent& event )
{
  randomize_enemy_stats_shuffle = !randomize_enemy_stats_shuffle;
  printf( "Randomize Enemy Stats Shuffle: %d\n", randomize_enemy_stats_shuffle );
}

void frame_t::onRandomizeShops( wxCommandEvent& event )
{
  randomize_shops = !randomize_shops;
  printf( "Randomize Shops: %d\n", randomize_shops );
}

void frame_t::onRandomizeShopPrices( wxCommandEvent& event )
{
  randomize_shop_prices = !randomize_shop_prices;
  printf( "Randomize Shop Prices: %d\n", randomize_shop_prices );
}

void frame_t::onRandomizeFieldItems( wxCommandEvent& event )
{
  randomize_field_items = !randomize_field_items;
  printf( "Randomize Field Items: %d\n", randomize_field_items );
}

void frame_t::onRandomizeGearAbilities( wxCommandEvent& event )
{
  randomize_gear_abilities = !randomize_gear_abilities;
  printf( "Randomize Gear Abilities: %d\n", randomize_gear_abilities );
}

void frame_t::onRandomizePlayerStats( wxCommandEvent& event )
{
  randomize_player_stats = !randomize_player_stats;
  printf( "Randomize Player Stats: %d\n", randomize_player_stats );
}

void frame_t::onRandomizeAeonStatScaling( wxCommandEvent& event )
{
  randomize_aeon_stat_scaling = !randomize_aeon_stat_scaling;
  printf( "Randomize Aeon Stats: %d\n", randomize_aeon_stat_scaling );
}

void frame_t::onRandomizeAeonBaseStats( wxCommandEvent& event )
{
  randomize_aeon_base_stats = !randomize_aeon_base_stats;
  printf( "Randomize Aeon Base Stats: %d\n", randomize_aeon_base_stats );
}

void frame_t::onShufflePlayerStats( wxCommandEvent& event )
{
  shuffle_player_stats = !shuffle_player_stats;
  printf( "Shuffle Player Stats: %d\n", shuffle_player_stats );
}

void frame_t::onShuffleAeonStatScaling( wxCommandEvent& event )
{
  shuffle_aeon_stat_scaling = !shuffle_aeon_stat_scaling;
  printf( "Shuffle Aeon Stats: %d\n", shuffle_aeon_stat_scaling );
}

void frame_t::onShuffleAeonBaseStats( wxCommandEvent& event )
{
  shuffle_aeon_base_stats = !shuffle_aeon_base_stats;
  printf( "Shuffle Aeon Base Stats: %d\n", shuffle_aeon_base_stats );
}

void frame_t::onRandomizeStartingOverdriveMode( wxCommandEvent& event )
{
  randomize_starting_overdrive_mode = !randomize_starting_overdrive_mode;
  printf( "Randomize Starting Overdrive Mode: %d\n", randomize_starting_overdrive_mode );
}

void frame_t::onRandomizeKeyItems( wxCommandEvent& event )
{
  randomize_key_items = !randomize_key_items;
  printf( "Randomize Key Items: %d\n", randomize_key_items );
}

void frame_t::onKeepThingsSane( wxCommandEvent& event )
{
  keep_things_sane = !keep_things_sane;
  printf( "Keep Things Sane: %d\n", keep_things_sane );
}

int32_t frame_t::hash( char* str )
{
  unsigned int h;
  unsigned char* p;

  h = 0;
  for (p = ( unsigned char* ) str; *p != '\0'; p++)
    h = 37 * h + *p;
  return h; // or, h % ARRAY_SIZE;
}

void frame_t::onSeedChange( wxCommandEvent& event )
{
  if (seed_text->GetValue().IsEmpty())
    return;

  std::string seed_str = seed_text->GetValue().ToStdString();
  int32_t this_seed = 0;
  for (char& c : seed_str)
  {
    int32_t character = hash( &c );
    this_seed += character;
  }

  seed = this_seed;
  printf( "Seed: %ld\n", seed );
}