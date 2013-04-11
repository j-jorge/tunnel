/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief Implementation of the tunnel::state_game_over class.
 * \author Sebastien Angibaud
 */
#include "tunnel/player_state/state_game_over.hpp"

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
tunnel::state_game_over::state_game_over( const player_proxy& player_instance )
  : state_player(player_instance)
{
} // state_game_over::state_game_over()


/*----------------------------------------------------------------------------*/
/**
 * \brief Return the name of the state.
 */
std::string tunnel::state_game_over::get_name() const
{
  return "game_over";
} // state_game_over::get_name()

/*----------------------------------------------------------------------------*/
/**
 * \brief Move the player to the left.
 */
void tunnel::state_game_over::do_move_left()
{
  // do nothing
} // state_game_over::do_move_left()

/*----------------------------------------------------------------------------*/
/**
 * \brief Move the player to the left.
 */
void tunnel::state_game_over::do_move_right()
{
  // do nothing
} // state_game_over::do_move_right()

/*----------------------------------------------------------------------------*/
/**
 * \brief Do a jump.
 */
void tunnel::state_game_over::do_jump()
{
  // do nothing
} // state_game_over::do_jump()

/*----------------------------------------------------------------------------*/
/**
 * \brief Make the player doing slap.
 */
void tunnel::state_game_over::do_slap()
{
  // do nothing
} // state_game_over::do_slap()

/*----------------------------------------------------------------------------*/
/**
 * \brief Player throw.
 */
void tunnel::state_game_over::do_start_throw()
{
  // do nothing
} // state_game_over::do_start_throw()

/*----------------------------------------------------------------------------*/
/**
 * \brief Player drop a power.
 */
void tunnel::state_game_over::do_start_drop()
{
  // do nothing
} // state_game_over::do_start_drop()

/*----------------------------------------------------------------------------*/
/**
 * \brief Player is injured.
 */
void tunnel::state_game_over::do_injured()
{
  // do nothing
} // state_game_over::do_injured()
