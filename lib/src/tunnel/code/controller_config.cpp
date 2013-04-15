/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \brief Implementation of the tunnel::controller_config class.
 * \author Julien Jorge
 */
#include "tunnel/controller_config.hpp"

#include "tunnel/player_action.hpp"
#include "engine/game.hpp"
#include "engine/system/game_filesystem.hpp"

#include <claw/logger.hpp>
#include <sstream>
#include <fstream>

/*----------------------------------------------------------------------------*/
tunnel::controller_layout tunnel::controller_config::s_controller_layout[1];

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
tunnel::controller_config::controller_config()
  : m_base_layout_file_name("controller_layout")
{
  if ( s_controller_layout[0].empty() )
    default_controls_for_player_1();
} // controller_config::controller_config

/*----------------------------------------------------------------------------*/
/**
 * \brief Load the configuration.
 */
void tunnel::controller_config::load()
{
  load_controller_layout(1);
} // controller_config::save()

/*----------------------------------------------------------------------------*/
/**
 * \brief Save the configuration.
 */
void tunnel::controller_config::save() const
{
  save_controller_layout(1);
} // controller_config::save()

/*----------------------------------------------------------------------------*/
/**
 * \brief Save the layout of the controls for a player.
 * \param i Index of the player.
 * \pre \a i != 0
 */
void tunnel::controller_config::save_controller_layout( unsigned int i ) const
{
  CLAW_PRECOND( i!=0 );

  std::ostringstream oss;
  oss << m_base_layout_file_name << "_" << (int)i;

  const bear::engine::game& g( bear::engine::game::get_instance() );

  const std::string file_name
    ( g.get_game_filesystem().get_custom_config_file_name( oss.str() ) );
  std::ofstream f( file_name.c_str() );

  if ( !f )
    claw::logger << claw::log_warning << "Can't open controller's layout file '"
                 << oss.str() << "'." << std::endl;
  else
    {
      s_controller_layout[i-1].save(f);
      f.close();
    }
} // controller_config::save_controller_layout()

/*----------------------------------------------------------------------------*/
/**
 * \brief Load the layout of the controls for a player.
 * \param i Index of the player.
 * \pre \a i != 0 *
 */
void tunnel::controller_config::load_controller_layout( unsigned int i )
{
  CLAW_PRECOND( i!=0 );

  std::ostringstream oss;
  oss << m_base_layout_file_name << "_" << (int)i;

  const bear::engine::game& g( bear::engine::game::get_instance() );

  const std::string file_name
    ( g.get_game_filesystem().get_custom_config_file_name( oss.str() ) );
  std::ifstream f( file_name.c_str() );

  if ( !f )
    claw::logger << claw::log_warning << "Can't open controller's layout file '"
                 << oss.str() << "'." << std::endl;
  else
    {
      s_controller_layout[i-1].load(f);
      f.close();
    }
} // controller_config::load_controller_layout()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the controller layout of a given player.
 * \param i Index of the player.
 * \param lay The layout.
 * \pre \a i != 0
 */
void tunnel::controller_config::set_layout
( unsigned int i, const controller_layout& lay )
{
  CLAW_PRECOND( i!=0 );
  CLAW_PRECOND( i <= 2 );

  s_controller_layout[i-1] = lay;
} // controller_config::set_layout()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the controller layout of a given player.
 * \param i Index of the player.
 * \pre \a i != 0
 */
tunnel::controller_layout& tunnel::controller_config::get_layout( unsigned int i )
{
  CLAW_PRECOND( i != 0 );
  CLAW_PRECOND( i <= 2 );

  return s_controller_layout[i-1];
} // controller_config::get_layout()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the controller layout of a given player.
 * \param i Index of the player.
 * \pre \a i != 0
 */
const tunnel::controller_layout&
tunnel::controller_config::get_layout( unsigned int i ) const
{
  CLAW_PRECOND( i!=0 );
  CLAW_PRECOND( i <= 2 );

  return s_controller_layout[i-1];
} // controller_config::get_layout()

/*----------------------------------------------------------------------------*/
/**
 * \brief Define the default controls for the first player.
 */
void tunnel::controller_config::default_controls_for_player_1()
{
  s_controller_layout[0].set_action_key
    (bear::input::keyboard::kc_left, player_action::move_left);
  s_controller_layout[0].set_action_key
    (bear::input::keyboard::kc_right, player_action::move_right);
  s_controller_layout[0].set_action_key
    (bear::input::keyboard::kc_up, player_action::look_upward);
  s_controller_layout[0].set_action_key
    (bear::input::keyboard::kc_down, player_action::crouch);
  s_controller_layout[0].set_action_key
    (bear::input::keyboard::kc_f, player_action::slap); 
  s_controller_layout[0].set_action_key
    (bear::input::keyboard::kc_d, player_action::teleport);
  s_controller_layout[0].set_action_key
    (bear::input::keyboard::kc_space, player_action::jump);
  s_controller_layout[0].set_command_key
    (bear::input::keyboard::kc_pause, gui_command::pause);
} // controller_config::default_controls_for_player_1()

