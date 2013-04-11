/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief Implementation of the tunnel::state_jump class.
 * \author Sebastien Angibaud
 */
#include "tunnel/player_state/state_jump.hpp"


/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
tunnel::state_jump::state_jump( const player_proxy& player_instance  )
  : state_player(player_instance)
{

} // state_jump::state_jump()

/*----------------------------------------------------------------------------*/
/**
 * \brief Return the name of the state.
 */
std::string tunnel::state_jump::get_name() const
{
  return "jump";
} // state_jump::get_name()

/*----------------------------------------------------------------------------*/
/**
 * \brief Do a jump.
 */
void tunnel::state_jump::do_jump()
{
  // we can't jump in this state.
} // state_jump::do_jump()

/*----------------------------------------------------------------------------*/
/**
 * \brief Continue to jump.
 */
void tunnel::state_jump::do_continue_jump()
{
  m_player_instance.apply_continue_jump();
} // state_jump::do_continue_jump()

/*----------------------------------------------------------------------------*/
/**
 * \brief Player throw.
 */
void tunnel::state_jump::do_start_throw()
{
  m_player_instance.start_action_model("maintain_and_fall");
} // state_jump::do_start_throw()
