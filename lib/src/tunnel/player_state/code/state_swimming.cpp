/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief Implementation of the tunnel::state_swimming class.
 * \author Sebastien Angibaud
 */
#include "tunnel/player_state/state_swimming.hpp"


/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
tunnel::state_swimming::state_swimming( const player_proxy& player_instance  )
  : state_player(player_instance)
{

} // state_swimming::state_swimming()

/*----------------------------------------------------------------------------*/
/**
 * \brief Return the name of the state.
 */
std::string tunnel::state_swimming::get_name() const
{
  return "swimming";
} // state_swimming::get_name()

/*----------------------------------------------------------------------------*/
/**
 * \brief Make the player look up.
 */
void tunnel::state_swimming::do_look_upward()
{
  m_player_instance.apply_swim_up();
} // state_swimming::do_look_upward()

/*----------------------------------------------------------------------------*/
/**
 * \brief Make the player continue to look_upward.
 */
void tunnel::state_swimming::do_continue_look_upward()
{
  m_player_instance.apply_swim_up();
} // state_swimming::do_continue_look_upward()

/*----------------------------------------------------------------------------*/
/**
 * \brief Make the player crouch.
 */
void tunnel::state_swimming::do_crouch()
{
  m_player_instance.apply_swim_down();
} // state_swimming::do_crouch()

/*----------------------------------------------------------------------------*/
/**
 * \brief Make the player continue to crouch.
 */
void tunnel::state_swimming::do_continue_crouch()
{

  m_player_instance.apply_swim_down();
} // state_swimming::do_continue_crouch()

/*----------------------------------------------------------------------------*/
/**
 * \brief Do a jump.
 */
void tunnel::state_swimming::do_jump()
{
  // Do nothing
} // state_swimming::do_jump()
