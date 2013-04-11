/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief Implementation of the tunnel::state_run class.
 * \author Sebastien Angibaud
 */
#include "tunnel/player_state/state_run.hpp"

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
tunnel::state_run::state_run( const player_proxy& player_instance )
  : state_player(player_instance)
{

} // state_run::state_run()

/*----------------------------------------------------------------------------*/
/**
 * \brief Return the name of the state.
 */
std::string tunnel::state_run::get_name() const
{
  return "run";
} // state_run::get_name()

/*----------------------------------------------------------------------------*/
/**
 * \brief Make the player doing slap.
 */
void tunnel::state_run::do_slap()
{
  m_player_instance.start_action_model("slap_and_walk");
} // state_run::do_slap()

/*----------------------------------------------------------------------------*/
/**
 * \brief Player throw.
 */
void tunnel::state_run::do_start_throw()
{
  m_player_instance.start_action_model("maintain_and_walk");
} // state_run::do_start_throw()
