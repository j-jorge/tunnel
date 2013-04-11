/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief Implementation of the tunnel::state_wait class.
 * \author Sebastien Angibaud
 */
#include "tunnel/player_state/state_wait.hpp"

#include <stdlib.h>
#include <time.h>

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
tunnel::state_wait::state_wait( const player_proxy& player_instance )
  : state_player(player_instance)
{

} // state_wait::state_wait()

/*----------------------------------------------------------------------------*/
/**
 * \brief Return the name of the state.
 */
std::string tunnel::state_wait::get_name() const
{
  return "wait";
} // state_wait::get_name()

/*----------------------------------------------------------------------------*/
/**
 * \brief Move the player to the left.
 */
void tunnel::state_wait::do_move_left()
{
  super::do_move_left();
  m_player_instance.choose_walk_state();
} // state_wait::do_move_left()

/*----------------------------------------------------------------------------*/
/**
 * \brief Move the player to the left.
 */
void tunnel::state_wait::do_move_right()
{
  super::do_move_right();
  m_player_instance.choose_walk_state();
} // state_wait::do_move_right()

/*----------------------------------------------------------------------------*/
/**
 * \brief Make the player look up.
 */
void tunnel::state_wait::do_look_upward()
{
  m_player_instance.start_action_model("look_upward");
} // state_wait::do_look_upward()

/*----------------------------------------------------------------------------*/
/**
 * \brief Make the player crouch.
 */
void tunnel::state_wait::do_crouch()
{
  m_player_instance.start_action_model("crouch");
} // state_wait::do_crouch()
