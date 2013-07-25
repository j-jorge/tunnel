/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Utility functions about roller painting.
 * \author Sébastien Angibaud
 */
#include "tunnel/util/util.hpp"

#include "tunnel/defines.hpp"
#include "tunnel/version.hpp"

#include "engine/level.hpp"
#include "engine/level_globals.hpp"
#include "engine/game.hpp"
#include "engine/system/game_filesystem.hpp"

/*----------------------------------------------------------------------------*/
/**
 * \brief Send statistic information when the player start a level.
 * \param filename The filename of the level.
 */
void tunnel::util::send_start_level( const std::string& filename )
{
  std::list<bear::engine::stat_variable> vars;
 
  vars.push_back
    ( bear::engine::stat_variable( "level", filename ) );

  bear::engine::game::get_instance().send_data( "start-level", vars );
} // util::send_start_level()

/*----------------------------------------------------------------------------*/
/**
 * \brief Send statistic information when the player quit a level.
 * \param filename The filename of the level.
 */
void tunnel::util::send_quit_level( const std::string& filename )
{
  std::list<bear::engine::stat_variable> vars;
 
  vars.push_back
    ( bear::engine::stat_variable( "level", filename ) );

  bear::engine::game::get_instance().send_data( "quit-level", vars );
} // util::send_quit_level()

/*----------------------------------------------------------------------------*/
/**
 * \brief Send statistic information when a level is complete.
 * \param filename The filename of the level.
 */
void tunnel::util::send_complete_level( const std::string& filename )
{
  std::list<bear::engine::stat_variable> vars;

  vars.push_back
    ( bear::engine::stat_variable( "level", filename ) );

  bear::engine::game::get_instance().send_data( "complete-level", vars );
} // util::send_complete_level()

/*----------------------------------------------------------------------------*/
/**
 * \brief Send statistic information when the player dies in a level.
 * \param filename The filename of the level.
 */
void tunnel::util::send_die_level( const std::string& filename )
{
  std::list<bear::engine::stat_variable> vars;

  vars.push_back
    ( bear::engine::stat_variable( "level", filename ) );

  bear::engine::game::get_instance().send_data( "die-level", vars );
} // util::send_die_level()

/*----------------------------------------------------------------------------*/
/**
 * \brief Send statistic information about version.
 */
void tunnel::util::send_version()
{
  std::list<bear::engine::stat_variable> vars;

  vars.push_back
    ( bear::engine::stat_variable( "major", TUNNEL_MAJOR_VERSION ) );
  vars.push_back( bear::engine::stat_variable
                  ( "minor", TUNNEL_MINOR_VERSION ) );
  vars.push_back
    ( bear::engine::stat_variable( "patch", TUNNEL_PATCH_NUMBER ) ); 

  bear::engine::game::get_instance().send_data( "version", vars );
} // util::send_version()
