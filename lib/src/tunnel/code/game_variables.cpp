/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the ptb::game_variables class.
 * \author Julien Jorge
 */
#include "tunnel/game_variables.hpp"
#include "tunnel/defines.hpp"

#include "engine/game.hpp"
#include "engine/variable/variable.hpp"

/*----------------------------------------------------------------------------*/
/**
 * \brief A function that gets a game variable.
 * \param n The name of the variable.
 * \param def The default value to return if the variable is not set.
 */
template<typename T>
static T tunnel_game_variables_get_value( const std::string& n, const T& def )
{
  bear::engine::variable<T> var(n);

  if ( bear::engine::game::get_instance().game_variable_exists(var) )
    {
      bear::engine::game::get_instance().get_game_variable(var);
      return var.get_value();
    }
  else
    return def;
} // tunnel_game_variables_get_value()


/*----------------------------------------------------------------------------*/
/**
 * \brief Get port of a given player.
 */
unsigned int tunnel::game_variables::get_port()
{
  return tunnel_game_variables_get_value
    ( make_persistent_variable_name( "network/port" ), (unsigned int)2424 );
} // game_variables::get_port()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set port of a given player.
 * \param port The port.
 */
void tunnel::game_variables::set_port(unsigned int port)
{
  bear::engine::game::get_instance().set_game_variable
    ( bear::engine::variable<unsigned int>
      ( make_persistent_variable_name( "network/port" ), port ) );
} // game_variables::set_port()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell if a player is local.
 * \param p The index of the player.*/
bool tunnel::game_variables::is_local_player(unsigned int p)
{
  return tunnel_game_variables_get_value
    ( make_persistent_variable_name
      ( "network/" + make_player_specific_variable_name
        ( p, "local_player" ) ), true );
} // game_variables::is_local_player()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set if a player is local.
 * \param p The index of the player.
 * \param value The new value.
 */
void tunnel::game_variables::set_local_player(unsigned int p, bool value)
{
  bear::engine::game::get_instance().set_game_variable
    ( bear::engine::variable<bool>
      ( make_persistent_variable_name
	( "network/" + make_player_specific_variable_name
	  ( p, "local_player" ) ), value ) );
} // game_variables::set_local_player_index()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell if a the game is launched by editor.
 */
bool tunnel::game_variables::is_editor_running()
{
  return tunnel_game_variables_get_value( "editor_running", false );
} // game_variables::is_editor_running()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set if the game has launched by editor.
 * \param value The new value.
 */
void tunnel::game_variables::set_editor_running(bool value)
{
  bear::engine::game::get_instance().set_game_variable
    ( bear::engine::variable<bool>( "editor_running" , value ) );
} // game_variables::set_editor_running()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell if a the level is finished.
 */
bool tunnel::game_variables::is_level_finished()
{
  return tunnel_game_variables_get_value( "level_finished", false );
} // game_variables::is_level_finished()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set if the level is finished.
 * \param value The new value.
 */
void tunnel::game_variables::set_level_is_finished(bool value)
{
  bear::engine::game::get_instance().set_game_variable
    ( bear::engine::variable<bool>( "level_finished" , value ) );
} // game_variables::set_level_is_finished()
    
/*----------------------------------------------------------------------------*/
/**
 * \brief Get ip adddress of a given player.
 * \param p The index of the player.
 */
std::string tunnel::game_variables::get_ip(unsigned int p)
{
  std::string s("127.0.0.1");
  
  return tunnel_game_variables_get_value
    ( make_persistent_variable_name
      ( "network/" + make_player_specific_variable_name
        ( p, "network/ip" ) ), s );
} // game_variables::get_ip()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set ip address of a given player.
 * \param p The index of the player.
 * \param ip The ip adress.
 */
void  tunnel::game_variables::set_ip(unsigned int p, const std::string& ip)
{
  bear::engine::game::get_instance().set_game_variable
    ( bear::engine::variable<std::string>
      ( make_persistent_variable_name
        ( "network/" +
          make_player_specific_variable_name( p, "network/ip" )), ip ) );
} // game_variables::set_ip()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the name of the next level to load.
 */
std::string tunnel::game_variables::get_next_level_name()
{
  return tunnel_game_variables_get_value( "scenario/next_level", std::string() );
} // game_variables::get_next_level_name()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the name of the next level to load.
 * \param n The name of the level.
 */
void tunnel::game_variables::set_next_level_name( const std::string& n )
{
  bear::engine::game::get_instance().set_game_variable
    ( bear::engine::variable<std::string>( "scenario/next_level", n ) );
} // game_variables::set_next_level_name()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set a level precedence.
 * \param prec The filename of the level that preceeds the other.
 * \param next The filename of the level that suceeds the other.
 */
void tunnel::game_variables::set_level_precedence
( const std::string& prec, const std::string& next )
{
  bear::engine::game::get_instance().set_game_variable
    ( bear::engine::variable<std::string>
      ( make_persistent_variable_name(prec + "/continues_with"),
        next ) );
} // game_variables::set_level_precedence()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set if a level has been finished.
 * \param lvl The filename of the level.
 * \param b The new status.
 */
void tunnel::game_variables::set_finished_level( const std::string& lvl, bool b)
{
  bear::engine::game::get_instance().set_game_variable
    ( bear::engine::variable<bool>
      ( make_persistent_variable_name(lvl + "/is_finished"), b ) );
} // game_variables::set_finished_level()

/*----------------------------------------------------------------------------*/
/**
 * \brief Return if a given level has been finished.
 * \param lvl The filename of the level.
 */
bool tunnel::game_variables::level_is_finished(const std::string& lvl)
{
  return tunnel_game_variables_get_value
    ( make_persistent_variable_name(lvl + "/is_finished"), false);
} // game_variables::level_is_finished()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the name of a level according its filename.
 * \param filename The filename of the level.
 */
std::string tunnel::game_variables::get_level_name(const std::string& filename)
{
  return tunnel_game_variables_get_value
    ( make_persistent_variable_name(filename + "/name"), std::string() );
} // game_variables::get_level_name()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the name of a level.
 * \param filename The filename of the level.
 * \param name The name of the level.
 */
void tunnel::game_variables::set_level_name
( const std::string& filename, const std::string& name )
{
  bear::engine::game::get_instance().set_game_variable
    ( bear::engine::variable<std::string>
      ( make_persistent_variable_name(filename + "/name"), name ) );
} // game_variables::set_level_precedence()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the name of current main level.
 */
std::string tunnel::game_variables::get_main_level_name()
{
  return tunnel_game_variables_get_value
    ( "scenario/main_level_name", std::string() );
} // game_variables::get_main_level_name()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the name of current main level.
 * \param n The name of the current main level.
 */
void tunnel::game_variables::set_main_level_name
( const std::string& n )
{
  bear::engine::game::get_instance().set_game_variable
    ( bear::engine::variable<std::string>
      ( "scenario/main_level_name", n ) );
} // game_variables::set_main_level_name()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the variable of lives number of a given player.
 */
std::string tunnel::game_variables::get_lives_count_variable_name()
{
  return "lives";
} // game_variables::get_lives_count_variable_name()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the number of lives of a given player.
 */
unsigned int tunnel::game_variables::get_lives_count()
{
  return tunnel_game_variables_get_value
    ( get_lives_count_variable_name(), (unsigned int)0 );
} // game_variables::get_lives_count()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the number of lives of a given player.
 * \param c The number of lives.
 */
void tunnel::game_variables::set_lives_count(unsigned int c )
{
  bear::engine::game::get_instance().set_game_variable
    ( bear::engine::variable<unsigned int>
      ( get_lives_count_variable_name(), c ) );
} // game_variables::set_lives_count()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the persistent number of lives of a given player.
 */
unsigned int tunnel::game_variables::get_persistent_lives_count()
{
  return tunnel_game_variables_get_value
    ( make_persistent_variable_name( get_lives_count_variable_name()), 
      (unsigned int)0 );
} // game_variables::get_persistent_lives_count()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the persistent number of lives of a given player.
 * \param c The number of lives.
 */
void tunnel::game_variables::set_persistent_lives_count
( unsigned int c )
{
  bear::engine::game::get_instance().set_game_variable
    ( bear::engine::variable<unsigned int>
      ( make_persistent_variable_name(get_lives_count_variable_name()), c ) );
} // game_variables::set_persistent_lives_count()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the variable of energy.
 */
std::string tunnel::game_variables::get_energy_variable_name()
{
  return "energy" ;
} // game_variables::get_energy_variable_name()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the energy.
 */
unsigned int tunnel::game_variables::get_energy()
{
  return tunnel_game_variables_get_value
    ( get_energy_variable_name(), (unsigned int)5 );
} // game_variables::get_energy()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the energy.
 * \param e The energy.
 */
void tunnel::game_variables::set_energy( unsigned int e )
{
  bear::engine::game::get_instance().set_game_variable
    ( bear::engine::variable<unsigned int>
      ( get_energy_variable_name(), e ) );
} // game_variables::set_energy()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the variable of crystal_count.
 */
std::string tunnel::game_variables::get_crystal_count_variable_name()
{
  return "crystal_count" ;
} // game_variables::get_crystal_count_variable_name()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the crystal_count.
 */
unsigned int tunnel::game_variables::get_crystal_count()
{
  return tunnel_game_variables_get_value
    ( get_crystal_count_variable_name(), (unsigned int)0 );
} // game_variables::get_crystal_count()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the crystal_count.
 * \param nb The crystal_count.
 */
void tunnel::game_variables::set_crystal_count( unsigned int nb )
{
  bear::engine::game::get_instance().set_game_variable
    ( bear::engine::variable<unsigned int>
      ( get_crystal_count_variable_name(), nb ) );
} // game_variables::set_crystal_count()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the variable of founded_crystal_count.
 */
std::string tunnel::game_variables::get_founded_crystal_count_variable_name()
{
  return "founded_crystal_count" ;
} // game_variables::get_founded_crystal_count_variable_name()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the founded_crystal_count.
 */
unsigned int tunnel::game_variables::get_founded_crystal_count()
{
  return tunnel_game_variables_get_value
    ( get_founded_crystal_count_variable_name(), (unsigned int)0 );
} // game_variables::get_founded_crystal_count()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the founded_crystal_count.
 * \param nb The founded_crystal_count.
 */
void tunnel::game_variables::set_founded_crystal_count( unsigned int nb )
{
  bear::engine::game::get_instance().set_game_variable
    ( bear::engine::variable<unsigned int>
      ( get_founded_crystal_count_variable_name(), nb ) );
} // game_variables::set_founded_crystal_count()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the variable name for score of a given player.
 */
std::string tunnel::game_variables::get_score_variable_name()
{
  return "score";
} // game_variables::make_score_variable_name()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the score of a given player.
 */
unsigned int tunnel::game_variables::get_score()
{
  return tunnel_game_variables_get_value
    ( get_score_variable_name() , (unsigned int)0 );
} // game_variables::get_score()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the persistent score of a given player.
 */
unsigned int tunnel::game_variables::get_persistent_score()
{
  return tunnel_game_variables_get_value
    ( make_persistent_variable_name(get_score_variable_name()) ,
      (unsigned int)0 );
} // game_variables::get_persistent_score()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the score of a given player.
 * \param c The number of score.
 */
void tunnel::game_variables::set_score( unsigned int c )
{
  bear::engine::game::get_instance().set_game_variable
    ( bear::engine::variable<unsigned int>
      ( get_score_variable_name() , c ) );
} // game_variables::set_score()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the persistent score of a given player.
 * \param c The number of score.
 */
void tunnel::game_variables::set_persistent_score
( unsigned int c )
{
  bear::engine::game::get_instance().set_game_variable
    ( bear::engine::variable<unsigned int>
      ( make_persistent_variable_name(get_score_variable_name()) , c ) );
} // game_variables::set_persistent_score()

/*----------------------------------------------------------------------------*/
/**
 * \brief Add some points to the score of a given player.
 * \param c The number of points.
 */
void tunnel::game_variables::add_score( unsigned int c )
{
  set_score( get_score() + c );
} // game_variables::add_score()

/*----------------------------------------------------------------------------*/
/**
 * \brief Subtract some points to the score of a given player.
 * \param c The number of points.
 */
void tunnel::game_variables::sub_score( unsigned int c )
{
  if ( get_score() >= c )
    set_score( get_score() - c );
  else
    set_score( 0 );
} // game_variables::sub_score()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get a variable of type string, return the parameter if the variable
 *        does not exist.
 * \param n The name of the variable.
 */
std::string tunnel::game_variables::get_string_default( const std::string& n )
{
  return tunnel_game_variables_get_value( n, n );
} // game_variables::get_string_default()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get a variable name prefixed with the default variable name of a given
 *        player.
 * \param p The index of the player.
 * \param n The name of the variable.
 */
std::string tunnel::game_variables::make_player_specific_variable_name
( unsigned int p, const std::string& n )
{
  std::ostringstream oss;
  oss << "player_" << p << '/' << n;

  return oss.str();
} // game_variables::make_player_specific_variable_name()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get a variable name prefixed with persistent option prefix.
 * \param n The name of the variable.
 */
std::string tunnel::game_variables::make_persistent_variable_name
( const std::string& n )
{
  return TUNNEL_PERSISTENT_PREFIX + n;
} // game_variables::make_persistent_variable_name()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get a persistent level variable name for the current main level.
 * \param n The name of the variable.
 */
std::string tunnel::game_variables::make_persistent_level_variable_name
( const std::string& n )
{
  return make_persistent_variable_name( get_main_level_name() + "/" + n );
} // game_variables::make_persistent_level_variable_name()

/*----------------------------------------------------------------------------*/
/**
 * \brief Load player's variables.
 */
void tunnel::game_variables::load_player_variables()
{
  load_player_variables(1);
} // game_variables::load_player_variables()

/*----------------------------------------------------------------------------*/
/**
 * \brief Load player's variables.
 * \param p The index of the player.
 */
void tunnel::game_variables::load_player_variables(unsigned int p)
{
  set_score(get_persistent_score());
  set_lives_count(get_persistent_lives_count());
} // game_variables::load_player_variables()

/*----------------------------------------------------------------------------*/
/**
 * \brief Save player's variables. 
 */
void tunnel::game_variables::save_player_variables()
{
  save_player_variables(1);
} // game_variables::save_player_variables()

/*----------------------------------------------------------------------------*/
/**
 * \brief Save player's variables. 
 * \param p The index of the player.
 */
void tunnel::game_variables::save_player_variables(unsigned int p)
{
  set_persistent_score(get_score());
  set_persistent_lives_count(get_lives_count());
} // game_variables::save_player_variables()
