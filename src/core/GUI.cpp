#include "GUI.hpp"
#include "Data.hpp"

bool gui_t::OnInit()
{
  SetAppearance( Appearance::System );
  SetAppName( "FFX Randomizer" );
  SetVendorName( "FFX Randomizer" );
  SetUseBestVisual( true, true );
  frame_t* frame = new frame_t( dp );
  frame->Show( true );
  return true;
}

void frame_t::initialize()
{
  wxBoxSizer* main_vertical_sizer = new wxBoxSizer( wxVERTICAL );

  notebook = new wxAuiNotebook( this, ID_NOTEBOOK, wxDefaultPosition, wxDefaultSize, wxNB_FIXEDWIDTH );
  notebook->SetAutoLayout( true );
  notebook->SetThemeEnabled( true );
  wxColor notebook_color = wxSystemSettings::GetColour( wxSYS_COLOUR_MENU );
  notebook->SetBackgroundColour( notebook_color );

  wxStaticText* header_text = new wxStaticText( this, wxID_ANY, _T( "FFX Randomizer" ), wxDefaultPosition, wxDefaultSize );
  header_text->SetFont( wxFont( 18, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD ) );

  wxStaticText* seed_header_text = new wxStaticText( this, wxID_ANY, _T( "RNG Seed" ), wxDefaultPosition, wxDefaultSize );
  seed_text = new wxTextCtrl( this, ID_SEED, std::to_string( seed ), wxDefaultPosition, wxDefaultSize );
  Bind( wxEVT_TEXT, &frame_t::onSeedChange, this, ID_SEED );

  wxStaticText* extra_text = new wxStaticText( this, wxID_ANY, _T( "Options that affect other aspects of the randomizer:" ), wxDefaultPosition, wxDefaultSize );
  extra_text->SetFont( wxFont( 10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD ) );
  header_panel_t* header_panel = new header_panel_t( this );
  Bind( wxEVT_CHECKBOX, &frame_t::onRandomizeKeyItems, this, ID_ALLOW_RANDOMIZE_KEY_ITEMS );

  Bind( wxEVT_CHECKBOX, &frame_t::onPoisonIsDeadly, this, ID_POISON_IS_DEADLY );
  Bind( wxEVT_CHECKBOX, &frame_t::onRandomizeEnemyDrops, this, ID_RANDOMIZE_ENEMY_DROPS );
  Bind( wxEVT_CHECKBOX, &frame_t::onRandomizeEnemySteals, this, ID_RANDOMIZE_ENEMY_STEALS );
  Bind( wxEVT_CHECKBOX, &frame_t::onRandomizeEnemyBribes, this, ID_RANDOMIZE_ENEMY_BRIBES );
  Bind( wxEVT_CHECKBOX, &frame_t::onRandomizeEnemyGearDrops, this, ID_RANDOMIZE_ENEMY_GEAR_DROPS );
  Bind( wxEVT_RADIOBUTTON, &frame_t::onRandomizeEnemyStatsNone, this, ID_RANDOMIZE_ENEMY_STATS_NONE );
  Bind( wxEVT_RADIOBUTTON, &frame_t::onRandomizeEnemyStats, this, ID_RANDOMIZE_ENEMY_STATS );
  Bind( wxEVT_RADIOBUTTON, &frame_t::onRandomizeEnemyStatsDefensive, this, ID_RANDOMIZE_ENEMY_STATS_DEFENSIVE );
  Bind( wxEVT_RADIOBUTTON, &frame_t::onRandomizeEnemyStatsShuffle, this, ID_RANDOMIZE_ENEMY_STATS_SHUFFLE );

  Bind( wxEVT_CHECKBOX, &frame_t::onRandomizeItemShops, this, ID_RANDOMIZE_ITEM_SHOPS );
  Bind( wxEVT_CHECKBOX, &frame_t::onRandomizeGearShops, this, ID_RANDOMIZE_GEAR_SHOPS );
  Bind( wxEVT_CHECKBOX, &frame_t::onRandomizeItemShopPrices, this, ID_RANDOMIZE_ITEM_SHOP_PRICES );
  Bind( wxEVT_CHECKBOX, &frame_t::onRandomizeGearShopPrices, this, ID_RANDOMIZE_GEAR_SHOP_PRICES );

  Bind( wxEVT_CHECKBOX, &frame_t::onRandomizeFieldItems, this, ID_RANDOMIZE_FIELD_ITEMS );

  Bind( wxEVT_CHECKBOX, &frame_t::onRandomizeGearAbilities, this, ID_RANDOMIZE_GEAR_ABILITIES );
  Bind( wxEVT_CHECKBOX, &frame_t::onRandomizeWeaponCrit, this, ID_RANDOMIZE_WEAPON_CRIT );
  Bind( wxEVT_CHECKBOX, &frame_t::onRandomizeWeaponAttackPower, this, ID_RANDOMIZE_WEAPON_ATTACK_POWER );
  Bind( wxEVT_CHECKBOX, &frame_t::onRandomizeWeaponDamageFormula, this, ID_RANDOMIZE_WEAPON_DAMAGE_FORMULA );

  Bind( wxEVT_RADIOBUTTON, &frame_t::onRandomizePlayerStatsNone, this, ID_RANDOMIZE_PLAYER_STATS_NONE );
  Bind( wxEVT_RADIOBUTTON, &frame_t::onRandomizePlayerStats, this, ID_RANDOMIZE_PLAYER_STATS );
  Bind( wxEVT_RADIOBUTTON, &frame_t::onShufflePlayerStats, this, ID_SHUFFLE_PLAYER_STATS );

  Bind( wxEVT_RADIOBUTTON, &frame_t::onRandomizeAeonStatScalingNone, this, ID_RANDOMIZE_AEON_STAT_SCALING_NONE );
  Bind( wxEVT_RADIOBUTTON, &frame_t::onRandomizeAeonStatScaling, this, ID_RANDOMIZE_AEON_STAT_SCALING );
  Bind( wxEVT_RADIOBUTTON, &frame_t::onShuffleAeonStatScaling, this, ID_SHUFFLE_AEON_STAT_SCALING );

  Bind( wxEVT_RADIOBUTTON, &frame_t::onRandomizeAeonBaseStatsNone, this, ID_RANDOMIZE_AEON_BASE_STATS_NONE );
  Bind( wxEVT_RADIOBUTTON, &frame_t::onRandomizeAeonBaseStats, this, ID_RANDOMIZE_AEON_BASE_STATS );
  Bind( wxEVT_RADIOBUTTON, &frame_t::onShuffleAeonBaseStats, this, ID_SHUFFLE_AEON_BASE_STATS );

  Bind( wxEVT_CHECKBOX, &frame_t::onRandomizeStartingOverdriveMode, this, ID_RANDOMIZE_STARTING_OVERDRIVE_MODE );
  Bind( wxEVT_CHECKBOX, &frame_t::onRandomizeEnemyElementalAffinities, this, ID_RANDOMIZE_ENEMY_ELEMENTAl_AFFINITIES );
  Bind( wxEVT_CHECKBOX, &frame_t::onRandomizeEncounters, this, ID_RANDOMIZE_ENCOUNTERS );

  Bind( wxEVT_CHECKBOX, &frame_t::onRemoveSphereGridLocks, this, ID_REMOVE_LOCKS );
  Bind( wxEVT_RADIOBUTTON, &frame_t::onRandomizeSphereGridNone, this, ID_SPHERE_GRID_NONE );
  Bind( wxEVT_RADIOBUTTON, &frame_t::onShuffleSphereGrid, this, ID_SHUFFLE_SPHERE_GRID );
  Bind( wxEVT_RADIOBUTTON, &frame_t::onRandomizeSphereGridTrue, this, ID_RANDOMIZE_SPHERE_GRID_TRUE );
  Bind( wxEVT_RADIOBUTTON, &frame_t::onRandomizeSphereGrid, this, ID_RANDOMIZE_SPHERE_GRID );
  Bind( wxEVT_RADIOBUTTON, &frame_t::onSphereNodesNone, this, ID_SPHERE_NODES_NONE );
  Bind( wxEVT_RADIOBUTTON, &frame_t::onEmptySphereGrid, this, ID_EMPTY_GRID );
  Bind( wxEVT_RADIOBUTTON, &frame_t::onFillSphereGrid, this, ID_FULL_GRID );
  Bind( wxEVT_RADIOBUTTON, &frame_t::onSphereGridNone, this, ID_NONE_GRID );
  Bind( wxEVT_RADIOBUTTON, &frame_t::onUpgradeSphereNodes, this, ID_UPGRADE_SPHERE_NODES );
  Bind( wxEVT_RADIOBUTTON, &frame_t::onDowngradeSphereNodes, this, ID_DOWNGRADE_SPHERE_NODES );

  Bind( wxEVT_RADIOBUTTON, &frame_t::onRandizedEncountersStatsNone, this, ID_RANDOM_ENCOUNTER_STATS_NONE );
  Bind( wxEVT_RADIOBUTTON, &frame_t::onSwapRandomEncounterStats, this, ID_SWAP_RANDOM_ENCOUNTER_STATS );
  Bind( wxEVT_RADIOBUTTON, &frame_t::onScaleEncounterStats, this, ID_SCALE_ECOUNTER_STATS );

  Bind( wxEVT_CHECKBOX, &frame_t::onKeepThingsSane, this, ID_KEEP_THINGS_SANE );
  Bind( wxEVT_CHECKBOX, &frame_t::onFahrenheit, this, ID_FAHRENHEIT );
  Bind( wxEVT_CHECKBOX, &frame_t::onRandomizeCelestials, this, ID_ALLOW_RANDOMIZE_CELESTIALS );
  Bind( wxEVT_CHECKBOX, &frame_t::onRandomizeBrotherhood, this, ID_ALLOW_RANDOMIZE_BROTHERHOOD );

  enemy_options_panel_t* panel = new enemy_options_panel_t( notebook );
  notebook->AddPage( panel, _T( "Enemy" ), true );

  gear_options_panel_t* gear_panel = new gear_options_panel_t( notebook );
  notebook->AddPage( gear_panel, _T( "Gear" ), false );

  item_options_panel_t* item_panel = new item_options_panel_t( notebook );
  notebook->AddPage( item_panel, _T( "Items" ), false );

  player_stats_panel_t* player_stats = new player_stats_panel_t( notebook );
  notebook->AddPage( player_stats, _T( "Player" ), false );

  aeon_stats_panel_t* aeon_stats = new aeon_stats_panel_t( notebook );
  notebook->AddPage( aeon_stats, _T( "Aeon" ), false );

  sphere_grid_panel_t* grid = new sphere_grid_panel_t( notebook );
  notebook->AddPage( grid, _T( "Sphere Grid" ), false );

  randomize_button = new wxButton( this, ID_RANDOMIZE, _T( "Randomize" ), wxDefaultPosition, wxDefaultSize, wxBU_ALIGN_MASK );
  randomize_button->SetToolTip( "Click this button to randomize the game!" );
  Bind( wxEVT_BUTTON, &frame_t::onRandomize, this, ID_RANDOMIZE );

  main_vertical_sizer->Add( header_text, 0, wxALIGN_CENTER | wxLEFT | wxRIGHT | wxTOP, FromDIP( 10 ) );
  main_vertical_sizer->Add( seed_header_text, 0, wxALIGN_CENTER | wxLEFT | wxRIGHT | wxTOP, FromDIP( 10 ) );
  main_vertical_sizer->Add( seed_text, 0, wxALIGN_CENTER | wxLEFT | wxRIGHT | wxTOP, FromDIP( 10 ) );
  main_vertical_sizer->Add( extra_text, 0, wxALIGN_CENTER | wxLEFT | wxRIGHT | wxTOP, FromDIP( 10 ) );
  main_vertical_sizer->Add( header_panel, 0, wxALIGN_CENTER | wxLEFT | wxRIGHT | wxTOP, FromDIP( 10 ) );
  main_vertical_sizer->Add( notebook, 0, wxALIGN_CENTER | wxLEFT | wxRIGHT | wxTOP, FromDIP( 10 ) );
  //main_vertical_sizer->Add( enemy_stats_text, 0, wxALIGN_CENTER | wxLEFT | wxRIGHT | wxTOP, FromDIP( 10 ) );
  //main_vertical_sizer->Add( stats_panel, 0, wxALIGN_CENTER | wxLEFT | wxRIGHT | wxTOP, FromDIP( 10 ) );
  main_vertical_sizer->Add( randomize_button, 0, wxALIGN_CENTER | wxLEFT | wxRIGHT | wxTOP, FromDIP( 10 ) );
  SetSizer( main_vertical_sizer );
  SetAutoLayout( true );
}

void frame_t::onRandomize( wxCommandEvent& event )
{
  options = new options_pack_t( randomize_enemy_drops,
                                randomize_enemy_steals,
                                randomize_enemy_bribes,
                                randomize_enemy_gear_drops,
                                randomize_enemy_stats,
                                randomize_enemy_stats_defensive,
                                randomize_enemy_stats_shuffle,
                                randomize_item_shops,
                                randomize_gear_shops,
                                randomize_item_shop_prices,
                                randomize_gear_shop_prices,
                                randomize_field_items,
                                randomize_gear_abilities,
                                randomize_weapon_crit,
                                randomize_weapon_attack_power,
                                randomize_weapon_damage_formula,
                                randomize_player_stats,
                                randomize_aeon_stat_scaling,
                                randomize_aeon_base_stats,
                                shuffle_player_stats,
                                shuffle_aeon_stat_scaling,
                                shuffle_aeon_base_stats,
                                poison_is_deadly,
                                randomize_starting_overdrive_mode,
                                randomize_enemy_elemental_affinities,
                                randomize_encounters,
                                shuffle_sphere_grid,
                                randomize_sphere_grid_true,
                                randomize_sphere_grid,
                                empty_sphere_grid,
                                fill_sphere_grid,
                                remove_sphere_grid_locks,
                                upgrade_sphere_nodes,
                                downgrade_sphere_nodes,
                                swap_random_stats,
                                scale_encounter_stats,
                                randomize_key_items,
                                randomize_celestials,
                                randomize_brotherhood,
                                keep_things_sane,
                                seed,
                                seed_text->GetValue().ToStdString(),
                                fahrenheit );

  wxLogMessage( "Finished Randomizing" );
  randomizer = new randomizer_t( *options, dp );
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

void frame_t::onRandomizeEnemyStatsNone( wxCommandEvent& event )
{
  randomize_enemy_stats = false;
  randomize_enemy_stats_defensive = false;
  randomize_enemy_stats_shuffle = false;
  printf( "Randomize Enemy Stats None: %d\n", randomize_enemy_stats );
}

void frame_t::onRandomizeEnemyStats( wxCommandEvent& event )
{
  randomize_enemy_stats = !randomize_enemy_stats;
  if (randomize_enemy_stats)
  {
    randomize_enemy_stats_defensive = false;
    randomize_enemy_stats_shuffle = false;
  }
  printf( "Randomize Enemy Stats Normal Distribution: %d\n", randomize_enemy_stats );
}

void frame_t::onRandomizeEnemyStatsDefensive( wxCommandEvent& event )
{
  randomize_enemy_stats_defensive = !randomize_enemy_stats_defensive;
  if (randomize_enemy_stats_defensive)
  {
    randomize_enemy_stats = false;
    randomize_enemy_stats_shuffle = false;
  }

  printf( "Randomize Enemy Stats Defensive: %d\n", randomize_enemy_stats_defensive );
}

void frame_t::onRandomizeEnemyStatsShuffle( wxCommandEvent& event )
{
  randomize_enemy_stats_shuffle = !randomize_enemy_stats_shuffle;
  if (randomize_enemy_stats_shuffle)
  {
    randomize_enemy_stats = false;
    randomize_enemy_stats_defensive = false;
  }
  printf( "Randomize Enemy Stats Shuffle: %d\n", randomize_enemy_stats_shuffle );
}

void frame_t::onRandomizeItemShops( wxCommandEvent& event )
{
  randomize_item_shops = !randomize_item_shops;
  printf( "Randomize Shops: %d\n", randomize_item_shops );
}

void frame_t::onRandomizeGearShops( wxCommandEvent& event )
{
  randomize_gear_shops = !randomize_gear_shops;
  printf( "Randomize Gear Shops: %d\n", randomize_gear_shops );
}

void frame_t::onRandomizeItemShopPrices( wxCommandEvent& event )
{
  randomize_item_shop_prices = !randomize_item_shop_prices;
  printf( "Randomize Shop Prices: %d\n", randomize_item_shop_prices );
}

void frame_t::onRandomizeGearShopPrices( wxCommandEvent& event )
{
  randomize_gear_shop_prices = !randomize_gear_shop_prices;
  printf( "Randomize Gear Shop Prices: %d\n", randomize_gear_shop_prices );
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

void frame_t::onRandomizeWeaponCrit( wxCommandEvent& event )
{
  randomize_weapon_crit = !randomize_weapon_crit;
  printf( "Randomize Weapon Crit Chance: %d\n", randomize_weapon_crit );
}

void frame_t::onRandomizeWeaponAttackPower( wxCommandEvent& event )
{
  randomize_weapon_attack_power = !randomize_weapon_attack_power;
  printf( "Randomize Weapon Attack Power: %d\n", randomize_weapon_attack_power );
}

void frame_t::onRandomizeWeaponDamageFormula( wxCommandEvent& event )
{
  randomize_weapon_damage_formula = !randomize_weapon_damage_formula;
  printf( "Randomize Weapon Damage Formula: %d\n", randomize_weapon_damage_formula );
}

void frame_t::onRandomizePlayerStatsNone( wxCommandEvent& event )
{
  randomize_player_stats = false;
  shuffle_player_stats = false;
  printf( "Randomize Player Stats None: %d\n", randomize_player_stats );
}

void frame_t::onRandomizePlayerStats( wxCommandEvent& event )
{
  randomize_player_stats = !randomize_player_stats;
  if (randomize_player_stats)
    shuffle_player_stats = false;
  printf( "Randomize Player Stats: %d\n", randomize_player_stats );
}

void frame_t::onShufflePlayerStats( wxCommandEvent& event )
{
  shuffle_player_stats = !shuffle_player_stats;
  if (shuffle_player_stats)
    randomize_player_stats = false;
  printf( "Shuffle Player Stats: %d\n", shuffle_player_stats );
}

void frame_t::onRandomizeAeonStatScalingNone( wxCommandEvent& event )
{
  randomize_aeon_stat_scaling = false;
  shuffle_aeon_stat_scaling = false;
  printf( "Randomize Aeon Stat Scaling None: %d\n", randomize_aeon_stat_scaling );
}

void frame_t::onShuffleAeonStatScaling( wxCommandEvent& event )
{
  shuffle_aeon_stat_scaling = !shuffle_aeon_stat_scaling;
  if (shuffle_aeon_stat_scaling)
    randomize_aeon_stat_scaling = false;
  printf( "Shuffle Aeon Stats: %d\n", shuffle_aeon_stat_scaling );
}

void frame_t::onRandomizeAeonStatScaling( wxCommandEvent& event )
{
  randomize_aeon_stat_scaling = !randomize_aeon_stat_scaling;
  if (randomize_aeon_stat_scaling)
    shuffle_aeon_stat_scaling = false;
  printf( "Randomize Aeon Stats: %d\n", randomize_aeon_stat_scaling );
}

void frame_t::onRandomizeAeonBaseStatsNone( wxCommandEvent& event )
{
  randomize_aeon_base_stats = false;
  shuffle_aeon_base_stats = false;
  printf( "Randomize Aeon Base Stats None: %d\n", randomize_aeon_base_stats );
}

void frame_t::onRandomizeAeonBaseStats( wxCommandEvent& event )
{
  randomize_aeon_base_stats = !randomize_aeon_base_stats;
  if (randomize_aeon_base_stats)
    shuffle_aeon_base_stats = false;
  printf( "Randomize Aeon Base Stats: %d\n", randomize_aeon_base_stats );
}

void frame_t::onShuffleAeonBaseStats( wxCommandEvent& event )
{
  shuffle_aeon_base_stats = !shuffle_aeon_base_stats;
  if (shuffle_aeon_base_stats)
    randomize_aeon_base_stats = false;
  printf( "Shuffle Aeon Base Stats: %d\n", shuffle_aeon_base_stats );
}

void frame_t::onRandomizeStartingOverdriveMode( wxCommandEvent& event )
{
  randomize_starting_overdrive_mode = !randomize_starting_overdrive_mode;
  printf( "Randomize Starting Overdrive Mode: %d\n", randomize_starting_overdrive_mode );
}

void frame_t::onRandomizeEnemyElementalAffinities( wxCommandEvent& event )
{
  randomize_enemy_elemental_affinities = !randomize_enemy_elemental_affinities;
  printf( "Randomize Enemy Elemental Affinities: %d\n", randomize_enemy_elemental_affinities );
}

void frame_t::onRandomizeEncounters( wxCommandEvent& event )
{
  randomize_encounters = !randomize_encounters;
  printf( "Randomize Encounters: %d\n", randomize_encounters );
}

void frame_t::onRandomizeSphereGridNone( wxCommandEvent& event )
{
  randomize_sphere_grid_true = false;
  shuffle_sphere_grid = false;
  printf( "Randomize Sphere Grid None: %d\n", randomize_sphere_grid_true );
}

void frame_t::onShuffleSphereGrid( wxCommandEvent& event )
{
  shuffle_sphere_grid = !shuffle_sphere_grid;
  if (shuffle_sphere_grid)
  {
    randomize_sphere_grid_true = false;
    randomize_sphere_grid = false;
  }
  printf( "Shuffle Sphere Grid: %d\n", shuffle_sphere_grid );
}

void frame_t::onRandomizeSphereGridTrue( wxCommandEvent& event )
{
  randomize_sphere_grid_true = !randomize_sphere_grid_true;
  if (randomize_sphere_grid_true)
  {
    randomize_sphere_grid = false;
    shuffle_sphere_grid = false;
  }
  printf( "Truly Randomize Sphere Grid: %d\n", randomize_sphere_grid_true );
}

void frame_t::onRandomizeSphereGrid( wxCommandEvent& event )
{
  randomize_sphere_grid = !randomize_sphere_grid;
  if (randomize_sphere_grid)
  {
    randomize_sphere_grid_true = false;
    shuffle_sphere_grid = false;
  }
  printf( "Randomize Sphere Grid: %d\n", randomize_sphere_grid );
}

void frame_t::onEmptySphereGrid( wxCommandEvent& event )
{
  empty_sphere_grid = !empty_sphere_grid;
  if (empty_sphere_grid)
    fill_sphere_grid = false;
  printf( "Empty Sphere Grid: %d\n", empty_sphere_grid );
}

void frame_t::onSphereGridNone( wxCommandEvent& event )
{
  empty_sphere_grid = false;
  fill_sphere_grid = false;
  printf( "Sphere Grid None: %d\n", empty_sphere_grid );
}

void frame_t::onFillSphereGrid( wxCommandEvent& event )
{
  fill_sphere_grid = !fill_sphere_grid;
  if (fill_sphere_grid)
    empty_sphere_grid = false;
  printf( "Fill Sphere Grid: %d\n", fill_sphere_grid );
}

void frame_t::onRemoveSphereGridLocks( wxCommandEvent& event )
{
  remove_sphere_grid_locks = !remove_sphere_grid_locks;
  printf( "Remove Sphere Grid Locks: %d\n", remove_sphere_grid_locks );
}

void frame_t::onSphereNodesNone( wxCommandEvent& event )
{
  upgrade_sphere_nodes = false;
  downgrade_sphere_nodes = false;
  printf( "Sphere Nodes None: %d\n", upgrade_sphere_nodes );
}

void frame_t::onUpgradeSphereNodes( wxCommandEvent& event )
{
  upgrade_sphere_nodes = !upgrade_sphere_nodes;
  if (upgrade_sphere_nodes)
    downgrade_sphere_nodes = false;
  printf( "Upgrade Sphere Nodes: %d\n", upgrade_sphere_nodes );
}

void frame_t::onDowngradeSphereNodes( wxCommandEvent& event )
{
  downgrade_sphere_nodes = !downgrade_sphere_nodes;
  if (downgrade_sphere_nodes)
    upgrade_sphere_nodes = false;
  printf( "Downgrade Sphere Nodes: %d\n", downgrade_sphere_nodes );
}

void frame_t::onRandizedEncountersStatsNone( wxCommandEvent& event )
{
  swap_random_stats = false;
  scale_encounter_stats = false;
  printf( "Randomized Encounters Stats None: %d\n", swap_random_stats );
}

void frame_t::onSwapRandomEncounterStats( wxCommandEvent& event )
{
  swap_random_stats = !swap_random_stats;
  if (swap_random_stats)
    scale_encounter_stats = false;

  printf( "Swap Random Encounter Stats: %d\n", swap_random_stats );
}

void frame_t::onScaleEncounterStats( wxCommandEvent& event )
{
  scale_encounter_stats = !scale_encounter_stats;
  if (scale_encounter_stats)
    swap_random_stats = false;
  printf( "Scale Encounter Stats: %d\n", scale_encounter_stats );
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

void frame_t::onFahrenheit( wxCommandEvent& event )
{
  fahrenheit = !fahrenheit;
  printf( "Fahrenheit: %d\n", fahrenheit );
}

void frame_t::onRandomizeCelestials( wxCommandEvent& event )
{
  randomize_celestials = !randomize_celestials;
  printf( "Randomize Celestial Weapons: %d\n", randomize_celestials );
}

void frame_t::onRandomizeBrotherhood( wxCommandEvent& event )
{
  randomize_brotherhood = !randomize_brotherhood;
  printf( "Randomize Brotherhood: %d\n", randomize_brotherhood );
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