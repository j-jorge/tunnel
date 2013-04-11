/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief Implementation of the tunnel::state_start_cling class.
 * \author Sebastien Angibaud
 */
#include "tunnel/player_state/state_start_cling.hpp"

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
tunnel::state_start_cling::state_start_cling( const player_proxy& player_instance)
  : state_player(player_instance)
{
} // state_start_cling::state_start_cling()

/*----------------------------------------------------------------------------*/
/**
 * \brief Initialization of this state.
 */
void tunnel::state_start_cling::start()
{
  m_player_instance.set_offensive_phase(true);
} // state_start_cling::start()

/*----------------------------------------------------------------------------*/
/**
 * \brief The end of the action.
 */
void tunnel::state_start_cling::stop()
{
  m_player_instance.set_offensive_phase(false);
} // state_start_cling::stop()

/*----------------------------------------------------------------------------*/
/**
 * \brief Return the name of the state.
 */
std::string tunnel::state_start_cling::get_name() const
{
  return "start_cling";
} // state_start_cling::get_name()

/*----------------------------------------------------------------------------*/
/**
 * \brief Make the player doing slap.
 */
void tunnel::state_start_cling::do_slap()
{
} // state_start_cling::do_slap()
