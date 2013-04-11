/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief Implementation of the tunnel::state_hang class.
 * \author Sebastien Angibaud
 */
#include "tunnel/player_state/state_hang.hpp"

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
tunnel::state_hang::state_hang( const player_proxy& player_instance)
  : state_player(player_instance)
{
} // state_hang::state_hang()

/*----------------------------------------------------------------------------*/
/**
 * \brief Return the name of the state.
 */
std::string tunnel::state_hang::get_name() const
{
  return "hang";
} // state_hang::get_name()

/*----------------------------------------------------------------------------*/
/**
 * \brief Make the player doing slap.
 */
void tunnel::state_hang::do_slap()
{
} // state_hang::do_slap()

/*----------------------------------------------------------------------------*/
/**
 * \brief Move the player to the left.
 */
void tunnel::state_hang::do_move_left()
{
} // state_hang::do_move_left()

/*----------------------------------------------------------------------------*/
/**
 * \brief Move the player to the left.
 */
void tunnel::state_hang::do_move_right()
{
} // state_hang::do_move_right()

/*----------------------------------------------------------------------------*/
/**
 * \brief Player want start throw.
 */
void tunnel::state_hang::do_start_throw()
{
} // state_hang::do_start_throw()
