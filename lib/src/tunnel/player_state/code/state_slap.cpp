/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief Implementation of the tunnel::state_slap class.
 * \author Sebastien Angibaud
 */
#include "tunnel/player_state/state_slap.hpp"

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
tunnel::state_slap::state_slap( const player_proxy& player_instance )
  : state_player(player_instance)
{

} // state_slap::state_slap()

/*----------------------------------------------------------------------------*/
/**
 * \brief Return the name of the state.
 */
std::string tunnel::state_slap::get_name() const
{
  return "slap";
} // state_slap::get_name()

/*----------------------------------------------------------------------------*/
/**
 * \brief Start the action.
 */
void tunnel::state_slap::start()
{
} // state_slap::stop()

/*----------------------------------------------------------------------------*/
/**
 * \brief The end of the action.
 */
void tunnel::state_slap::stop()
{
  m_player_instance.set_offensive_phase(false);
} // state_slap::stop()

/*----------------------------------------------------------------------------*/
/**
 * \brief Make the player doing slap.
 */
void tunnel::state_slap::do_slap()
{
  // Player can't do a new slap.
} // state_slap::do_slap()
