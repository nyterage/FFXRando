#include "Randomizer.hpp"

void randomizer_t::reconstructSphereGridData()
{
  for (auto& grid : data_pack.sphere_grid_data)
  {
    //std::string name = "dat0" + std::to_string( grid->type + 1 ) + ".dat";
    //std::string string = "Reconstructing " + name + "...";
    //std::cout << string << std::endl;
    //std::string path = INPUT_FOLDER + ABMAP_FOLDER + name;
    std::string output_path = OUTPUT_FOLDER + prefix + ABMAP_FOLDER;
    std::filesystem::create_directories( output_path );
    //std::string file = output_path + name;
    //bytes_mapper_t::writeBytesToNewFile( grid->bytes, file );

    std::string content_name;

    switch (grid->type)
    {
      case SPHERE_GRID_ORIGINAL:
        content_name = "dat09.dat";
        break;
      case SPHERE_GRID_STANDARD:
        content_name = "dat10.dat";
        break;
      case SPHERE_GRID_EXPERT:
        content_name = "dat11.dat";
        break;
      default:
        break;
    }
    std::string content_string = "Reconstructing " + content_name + "...";
    std::cout << content_string << std::endl;
    std::string content_path = INPUT_FOLDER + ABMAP_FOLDER + content_name;
    std::vector<char> content_bytes;
    content_bytes.insert( content_bytes.end(), grid->full_content_bytes.begin(), grid->full_content_bytes.end() );
    std::string content_file = output_path + content_name;
    bytes_mapper_t::writeBytesToNewFile( content_bytes, content_file );
  }
}


void randomizer_t::getSphereGridNodeIds()
{
  for (auto& grid : data_pack.sphere_grid_data)
  {
    for (auto& node : grid->nodes)
    {
      switch (grid->type)
      {
        case SPHERE_GRID_ORIGINAL:
          original_sphere_grid_node_ids.push_back( node->original_content );
          break;
        case SPHERE_GRID_STANDARD:
          standard_sphere_grid_node_ids.push_back( node->original_content );
          break;
        case SPHERE_GRID_EXPERT:
          expert_sphere_grid_node_ids.push_back( node->original_content );
          break;
        default:
          std::cerr << "Unknown sphere grid type: " << grid->type << std::endl;
          break;
      }
    }
  }
}

void randomizer_t::setRequiredAbilities()
{
  // Force abilities used by tutorials to be learned to prevent softlocks
  character_stats_t& riku_stats = *data_pack.player_stats_data[ ply_save_e::CHARACTER_RIKU ];
  riku_stats.ability_flags1.bits.use = 1;
  riku_stats.ability_flags1.bits.steal = 1;
  riku_stats.writeToBytes();

  character_stats_t& kimari_stats = *data_pack.player_stats_data[ ply_save_e::CHARACTER_KIMAHRI ];
  kimari_stats.ability_flags2.bits.lancet = 1;
  kimari_stats.writeToBytes();

  character_stats_t& wakka_stats = *data_pack.player_stats_data[ ply_save_e::CHARACTER_WAKKA ];
  wakka_stats.ability_flags1.bits.dark_attack = 1;
  wakka_stats.writeToBytes();

  character_stats_t& lulu_stats = *data_pack.player_stats_data[ ply_save_e::CHARACTER_LULU ];
  lulu_stats.ability_flags3.bits.thunder = 1;
  lulu_stats.writeToBytes();
}

void randomizer_t::shuffleSphereGridNodes()
{
  setRequiredAbilities();

  for (auto& grid : data_pack.sphere_grid_data)
  {
    switch (grid->type)
    {
      case sphere_grid_type_e::SPHERE_GRID_ORIGINAL:
        shuffled_original_sphere_grid_node_ids = original_sphere_grid_node_ids;
        std::shuffle( shuffled_original_sphere_grid_node_ids.begin(), shuffled_original_sphere_grid_node_ids.end(), rng );
        break;
      case sphere_grid_type_e::SPHERE_GRID_STANDARD:
        shuffled_standard_sphere_grid_node_ids = standard_sphere_grid_node_ids;
        std::shuffle( shuffled_standard_sphere_grid_node_ids.begin(), shuffled_standard_sphere_grid_node_ids.end(), rng );
        break;
      case sphere_grid_type_e::SPHERE_GRID_EXPERT:
        shuffled_expert_sphere_grid_node_ids = expert_sphere_grid_node_ids;
        std::shuffle( shuffled_expert_sphere_grid_node_ids.begin(), shuffled_expert_sphere_grid_node_ids.end(), rng );
        break;
      default:
        break;
    }

    for (size_t i = 0; i < grid->nodes.size(); i++)
    {
      sphere_grid_node_data_t& node = *grid->nodes[ i ];
      if (node.original_content == NODE_NULL)
        continue; // Skip null nodes

      switch (grid->type)
      {
        case sphere_grid_type_e::SPHERE_GRID_ORIGINAL:
          node.content = shuffled_original_sphere_grid_node_ids[ i ];
          node.writeToBytes();
          break;
        case sphere_grid_type_e::SPHERE_GRID_STANDARD:
          node.content = shuffled_standard_sphere_grid_node_ids[ i ];
          node.writeToBytes();
          break;
        case sphere_grid_type_e::SPHERE_GRID_EXPERT:
          node.content = shuffled_expert_sphere_grid_node_ids[ i ];
          node.writeToBytes();
          break;
        default:
          break;
      }
    }

    grid->writeToBytes();
  }
}

void randomizer_t::randomizeSphereGridTrue()
{
  setRequiredAbilities();

  for (auto& grid : data_pack.sphere_grid_data)
  {
    sphere_grid_data_t& sphere_grid = *grid;
    for (auto& node_data : sphere_grid.nodes)
    {
      sphere_grid_node_data_t& node = *node_data;
      uint8_t new_content = uniform<uint8_t>( 0, 0x7F );
      node.content = new_content;
      node.writeToBytes();
    }
    sphere_grid.writeToBytes();
  }
}

void randomizer_t::randomizeSphereGrid()
{
  setRequiredAbilities();

  for (auto& grid : data_pack.sphere_grid_data)
  {
    std::vector<uint8_t> abilities;
    abilities.reserve( 84 );
    for (int i = 0x2A; i <= 0x7E; i++)
      abilities.push_back( i );

    std::vector<sphere_grid_node_data_t*> already_used_nodes;
    already_used_nodes.reserve( abilities.size() );
    sphere_grid_data_t& sphere_grid = *grid;

    for (int i = 0; i < abilities.size(); i++)
    {
      uint8_t new_content = abilities[ i ];
      int random_node_index = uniform<int>( 0, sphere_grid.nodes.size() - 1 );
      sphere_grid_node_data_t* node = sphere_grid.nodes[ random_node_index ];
      node->content = new_content;
      node->writeToBytes();
      already_used_nodes.push_back( node );
    }

    for (auto& node_data : sphere_grid.nodes)
    {
      bool found = std::find( already_used_nodes.begin(), already_used_nodes.end(), node_data ) != already_used_nodes.end();
      if (found)
        continue;
      sphere_grid_node_data_t& node = *node_data;
      uint8_t new_content = uniform<uint8_t>( 0, options_pack.remove_sphere_grid_locks ? 0x26 : 0x29 );
      node.content = new_content;
      node.writeToBytes();
    }
    sphere_grid.writeToBytes();
  }
}

void randomizer_t::emptySphereGrid()
{
  for (auto& grid : data_pack.sphere_grid_data)
  {
    sphere_grid_data_t& sphere_grid = *grid;
    for (auto& node_data : sphere_grid.nodes)
    {
      sphere_grid_node_data_t& node = *node_data;
      std::vector<uint16_t> blacklist = { 0xFF };
      if (std::find( blacklist.begin(), blacklist.end(), node.original_content ) != blacklist.end())
        continue;
      if (node.content <= 0x29)
        node.content = 0x01;
      node.writeToBytes();
    }
    sphere_grid.writeToBytes();
  }
}

void randomizer_t::fillSphereGrid()
{
  for (auto& grid : data_pack.sphere_grid_data)
  {
    sphere_grid_data_t& sphere_grid = *grid;
    for (auto& node_data : sphere_grid.nodes)
    {
      sphere_grid_node_data_t& node = *node_data;
      if (node.content != 0x01)
        continue;
      uint8_t new_content = uniform<uint8_t>( 1, 0x26 );
      node.content = new_content;
      node.writeToBytes();
    }
    sphere_grid.writeToBytes();
  }
}

void randomizer_t::removeSphereGridLocks()
{
  for (auto& grid : data_pack.sphere_grid_data)
  {
    sphere_grid_data_t& sphere_grid = *grid;
    for (auto& node_data : sphere_grid.nodes)
    {
      sphere_grid_node_data_t& node = *node_data;
      std::vector<uint16_t> whitelist = { 0x00, 0x27, 0x28, 0x29 };
      if (std::find( whitelist.begin(), whitelist.end(), node.content ) != whitelist.end())
        node.content = 0x01;
      node.writeToBytes();
    }
    sphere_grid.writeToBytes();
  }
}

void randomizer_t::upgradeSphereGridNodes()
{
  for (auto& grid : data_pack.sphere_grid_data)
  {
    sphere_grid_data_t& grid_data = *grid;
    for (auto& grid_node : grid_data.nodes)
    {
      sphere_grid_node_data_t& node = *grid_node;
      switch (node.content)
      {
        case NODE_STRENGTH_1:
        case NODE_STRENGTH_2:
        case NODE_STRENGTH_3:
          node.content = NODE_STRENGTH_4;
          break;
        case NODE_DEFENSE_1:
        case NODE_DEFENSE_2:
        case NODE_DEFENSE_3:
          node.content = NODE_DEFENSE_4;
          break;
        case NODE_MAGIC_1:
        case NODE_MAGIC_2:
        case NODE_MAGIC_3:
          node.content = NODE_MAGIC_4;
          break;
        case NODE_MAGIC_DEFENSE_1:
        case NODE_MAGIC_DEFENSE_2:
        case NODE_MAGIC_DEFENSE_3:
          node.content = NODE_MAGIC_DEFENSE_4;
          break;
        case NODE_AGILITY_1:
        case NODE_AGILITY_2:
        case NODE_AGILITY_3:
          node.content = NODE_AGILITY_4;
          break;
        case NODE_LUCK_1:
        case NODE_LUCK_2:
        case NODE_LUCK_3:
          node.content = NODE_LUCK_4;
          break;
        case NODE_EVASION_1:
        case NODE_EVASION_2:
        case NODE_EVASION_3:
          node.content = NODE_EVASION_4;
          break;
        case NODE_ACCURACY_1:
        case NODE_ACCURACY_2:
        case NODE_ACCURACY_3:
          node.content = NODE_ACCURACY_4;
          break;
        case NODE_HP_200:
          node.content = NODE_HP_300;
          break;
        case NODE_MP_10:
        case NODE_MP_20:
          node.content = NODE_MP_40;
          break;
        default:
          break;
      }
      node.writeToBytes();
    }
    grid_data.writeToBytes();
  }
}

void randomizer_t::downgradeSphereGridNodes()
{
  for (auto& grid : data_pack.sphere_grid_data)
  {
    sphere_grid_data_t& grid_data = *grid;
    for (auto& grid_node : grid_data.nodes)
    {
      sphere_grid_node_data_t& node = *grid_node;
      switch (node.content)
      {
        case NODE_STRENGTH_2:
        case NODE_STRENGTH_3:
        case NODE_STRENGTH_4:
          node.content = NODE_STRENGTH_1;
          break;
        case NODE_DEFENSE_2:
        case NODE_DEFENSE_3:
        case NODE_DEFENSE_4:
          node.content = NODE_DEFENSE_1;
          break;
        case NODE_MAGIC_2:
        case NODE_MAGIC_3:
        case NODE_MAGIC_4:
          node.content = NODE_MAGIC_1;
          break;
        case NODE_MAGIC_DEFENSE_2:
        case NODE_MAGIC_DEFENSE_3:
        case NODE_MAGIC_DEFENSE_4:
          node.content = NODE_MAGIC_DEFENSE_1;
          break;
        case NODE_AGILITY_2:
        case NODE_AGILITY_3:
        case NODE_AGILITY_4:
          node.content = NODE_AGILITY_1;
          break;
        case NODE_LUCK_2:
        case NODE_LUCK_3:
        case NODE_LUCK_4:
          node.content = NODE_LUCK_1;
          break;
        case NODE_EVASION_2:
        case NODE_EVASION_3:
        case NODE_EVASION_4:
          node.content = NODE_EVASION_1;
          break;
        case NODE_ACCURACY_2:
        case NODE_ACCURACY_3:
        case NODE_ACCURACY_4:
          node.content = NODE_ACCURACY_1;
          break;
        case NODE_HP_300:
          node.content = NODE_HP_200;
          break;
        case NODE_MP_10:
        case NODE_MP_20:
          node.content = NODE_MP_40;
          break;
        default:
          break;
      }
      node.writeToBytes();
    }
    grid_data.writeToBytes();
  }
}

void randomizer_t::doSphereGridRandomization()
{
  if (!options_pack.shuffle_sphere_grid && !options_pack.randomize_sphere_grid_true && !options_pack.randomize_sphere_grid &&
       !options_pack.empty_sphere_grid && !options_pack.fill_sphere_grid && !options_pack.upgrade_sphere_nodes &&
       !options_pack.downgrade_sphere_nodes && !options_pack.remove_sphere_grid_locks)
    return;

  if (options_pack.shuffle_sphere_grid)
  {
    printf( "Shuffling Sphere Grid...\n" );
    shuffleSphereGridNodes();
  }

  if (options_pack.randomize_sphere_grid_true)
  {
    printf( "Randomizing Sphere Grid...\n" );
    randomizeSphereGridTrue();
  }

  if (options_pack.randomize_sphere_grid)
  {
    printf( "Randomizing Sphere Grid...\n" );
    randomizeSphereGrid();
  }

  if (options_pack.remove_sphere_grid_locks)
  {
    printf( "Removing Sphere Grid Locks...\n" );
    removeSphereGridLocks();
  }

  if (options_pack.empty_sphere_grid)
  {
    printf( "Emptying Sphere Grid...\n" );
    emptySphereGrid();
  }

  if (options_pack.fill_sphere_grid)
  {
    printf( "Filling Sphere Grid...\n" );
    fillSphereGrid();
  }

  if (options_pack.upgrade_sphere_nodes)
  {
    printf( "Upgrading Sphere Grid Nodes...\n" );
    upgradeSphereGridNodes();
  }

  if (options_pack.downgrade_sphere_nodes)
  {
    printf( "Downgrading Sphere Grid Nodes...\n" );
    downgradeSphereGridNodes();
  }

  reconstructSphereGridData();
}