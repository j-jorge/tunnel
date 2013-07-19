/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the tunnel::state_plee class.
 * \author Sebastien Angibaud
 */
#include "tunnel/player_state/state_player.hpp"

#include "tunnel/game_variables.hpp"

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
tunnel::state_player::state_player( const player_proxy& player_instance )
  : m_player_instance(player_instance)
{

} // state_player::state_player()

/*----------------------------------------------------------------------------*/
/**
 * \brief Move the player to the left.
 */
void tunnel::state_player::do_move_left()
{
  m_player_instance.apply_move_left();
} // state_player::do_move_left()

/*----------------------------------------------------------------------------*/
/**
 * \brief Move the player to the left.
 */
void tunnel::state_player::do_move_right()
{
  m_player_instance.apply_move_right();
} // state_player::do_move_right()

/*----------------------------------------------------------------------------*/
/**
 * \brief Do a jump.
 */
void tunnel::state_player::do_jump()
{
  if ( m_player_instance.has_bottom_contact() )
    m_player_instance.start_action_model("jump");
} // state_player::do_jump()

/*----------------------------------------------------------------------------*/
/**
 * \brief Continue to jump.
 */
void tunnel::state_player::do_continue_jump()
{
  // do nothing
} // state_player::do_continue_jump()

/*----------------------------------------------------------------------------*/
/**
 * \brief Stop a vertical jump.
 */
void tunnel::state_player::do_stop_vertical_jump()
{
} // state_player::do_stop_vertical_jump()

/*----------------------------------------------------------------------------*/
/**
 * \brief Make the player doing slap.
 */
void tunnel::state_player::do_slap()
{
  if (m_player_instance.has_bottom_contact() )
    m_player_instance.start_action_model("slap");
  else
    m_player_instance.start_action_model("start_cling");
} // state_player::do_slap()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell that the teleport is stopped.
 */
void tunnel::state_player::do_stop_teleport()
{
} // state_player::do_stop_teleport()

/*----------------------------------------------------------------------------*/
/**
 * \brief Make the player doing teleport.
 */
void tunnel::state_player::do_teleport()
{
  m_player_instance.apply_open_tunnel();
} // state_player::do_teleport()

/*----------------------------------------------------------------------------*/
/**
 * \brief Make the player look upward.
 */
void tunnel::state_player::do_look_upward()
{

} // state_player::do_look_upward()

/*----------------------------------------------------------------------------*/
/**
 * \brief Stop to look up.
 */
void tunnel::state_player::do_stop_look_upward()
{

} // state_player::do_stop_look_upward()

/*----------------------------------------------------------------------------*/
/**
 * \brief Continue to look up.
 */
void tunnel::state_player::do_continue_look_upward()
{

} // state_player::do_continue_look_upward()

/*----------------------------------------------------------------------------*/
/**
 * \brief Make the player crouch.
 */
void tunnel::state_player::do_crouch()
{

} // state_player::do_crouch()

/*----------------------------------------------------------------------------*/
/**
 * \brief Make the player continue to crouch.
 */
void tunnel::state_player::do_continue_crouch()
{

} // state_player::do_continue_crouch()

/*----------------------------------------------------------------------------*/
/**
 * \brief Stop to crouch.
 */
void tunnel::state_player::do_stop_crouch()
{

} // state_player::do_stop_crouch()

/*----------------------------------------------------------------------------*/
/**
 * \brief To captive Player.
 */
void tunnel::state_player::captive()
{
  m_player_instance.start_action_model("captive");
} // state_player::captive()

/*----------------------------------------------------------------------------*/
/**
 * \brief To release player.
 */
void tunnel::state_player::release()
{
  m_player_instance.start_action_model("idle");
} // state_player::release()

/*----------------------------------------------------------------------------*/
/**
 * \brief Player throw.
 */
void tunnel::state_player::do_start_throw()
{
  m_player_instance.start_action_model("maintain");
} // state_player::do_start_throw()

/*----------------------------------------------------------------------------*/
/**
 * \brief Change the current object.
 */
void tunnel::state_player::do_start_change_object()
{
} // state_player::do_start_change_object()

/*----------------------------------------------------------------------------*/
/**
 * \brief Player want throw.
 */
void tunnel::state_player::do_stop_throw()
{

} // state_player::do_stop_throw()

/*----------------------------------------------------------------------------*/
/**
 * \brief Player is injured.
 */
void tunnel::state_player::do_injured()
{
  m_player_instance.start_action_model("injured");
} // state_player::do_injured()

/*----------------------------------------------------------------------------*/
/**
 * \brief Player is not injured now.
 */
void tunnel::state_player::do_finish_injured()
{
  // do nothing
} // state_player::do_finish_injured()
