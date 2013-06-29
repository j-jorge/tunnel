/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the tunnel::state_start_jump class.
 * \author Sebastien Angibaud
 */
#include "tunnel/player_state/state_start_jump.hpp"

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
tunnel::state_start_jump::state_start_jump( const player_proxy& player_instance)
  : state_player(player_instance)
{
} // state_start_jump::state_start_jump()

/*----------------------------------------------------------------------------*/
/**
 * \brief Return the name of the state.
 */
std::string tunnel::state_start_jump::get_name() const
{
  return "start_jump";
} // state_start_jump::get_name()

/*---------------------------------------------------------------------------*/
/**
 * \brief Progress the spot.
 */
void tunnel::state_start_jump::progress_spot()
{
  claw::math::coordinate_2d<int> gap(0, -5);
  m_player_instance.add_spot_gap(gap);
} // state_start_jump::progress_spot()

/*----------------------------------------------------------------------------*/
/**
 * \brief Player want an vertical jump.
 */
void tunnel::state_start_jump::do_stop_vertical_jump()
{
  if ( m_player_instance.has_bottom_contact() )
    m_player_instance.start_action_model("vertical_jump");
} // state_start_jump::do_stop_vertical_jump()

/*----------------------------------------------------------------------------*/
/**
 * \brief Move the player to the left.
 */
void tunnel::state_start_jump::do_move_left()
{
  // Player can't move on the left in this state
} // state_start_jump::do_move_left()

/*----------------------------------------------------------------------------*/
/**
 * \brief Move the player to the left.
 */
void tunnel::state_start_jump::do_move_right()
{
  // Player can't move on the right in this state
} // state_start_jump::do_move_right()

/*----------------------------------------------------------------------------*/
/**
 * \brief Stop an vertical jump.
 */
void tunnel::state_start_jump::do_stop_look_upward()
{
  m_player_instance.choose_idle_state();
} // state_start_jump::do_stop_look_upward()
