/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the tunnel::state_teleport class.
 * \author Sebastien Angibaud
 */
#include "tunnel/player_state/state_teleport.hpp"

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
tunnel::state_teleport::state_teleport( const player_proxy& player_instance )
  : state_player(player_instance)
{

} // state_teleport::state_teleport()

/*----------------------------------------------------------------------------*/
/**
 * \brief Return the name of the state.
 */
std::string tunnel::state_teleport::get_name() const
{
  return "teleport";
} // state_teleport::get_name()

/*----------------------------------------------------------------------------*/
/**
 * \brief Start the action.
 */
void tunnel::state_teleport::start()
{
} // state_teleport::stop()

/*----------------------------------------------------------------------------*/
/**
 * \brief The end of the action.
 */
void tunnel::state_teleport::stop()
{
} // state_teleport::stop()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell that the action is finished.
 */
void tunnel::state_teleport::do_stop_teleport()
{
  m_player_instance.apply_abort_tunnel();
} // state_teleport::do_stop_teleport()

/*----------------------------------------------------------------------------*/
/**
 * \brief Make the player doing teleport.
 */
void tunnel::state_teleport::do_teleport()
{
  // Player can't do a new teleport.
} // state_teleport::do_teleport()

/*----------------------------------------------------------------------------*/
/**
 * \brief Move the player to the left.
 */
void tunnel::state_teleport::do_move_left()
{
  // we can't move in this state
} // state_teleport::do_move_left()

/*----------------------------------------------------------------------------*/
/**
 * \brief Move the player to the left.
 */
void tunnel::state_teleport::do_move_right()
{
   // we can't move in this state
} // state_teleport::do_move_right()

/*----------------------------------------------------------------------------*/
/**
 * \brief Do a jump.
 */
void tunnel::state_teleport::do_jump()
{
   // we can't jump in this state
} // state_teleport::do_jump()

/*----------------------------------------------------------------------------*/
/**
 * \brief Make the player doing slap.
 */
void tunnel::state_teleport::do_slap()
{
   // we can't slap in this state
} // state_teleport::do_slap()

