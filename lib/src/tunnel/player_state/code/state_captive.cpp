/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief Implementation of the tunnel::state_captive class.
 * \author Sebastien Angibaud
 */
#include "tunnel/player_state/state_captive.hpp"

#include <limits>

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
tunnel::state_captive::state_captive( const player_proxy& player_instance )
  : state_player(player_instance)
{

} // state_captive::state_captive()

/*----------------------------------------------------------------------------*/
/**
 * \brief Return the name of the state.
 */
std::string tunnel::state_captive::get_name() const
{
  return "captive";
} // state_captive::get_name()

/*----------------------------------------------------------------------------*/
/**
 * \brief Initialization of this state.
 */
void tunnel::state_captive::start()
{
  m_mass = m_player_instance.get_mass();

  m_player_instance.set_mass( std::numeric_limits<double>::infinity() );
} // state_captive::start()

/*----------------------------------------------------------------------------*/
/**
 * \brief The end of the action.
 */
void tunnel::state_captive::stop()
{
  m_player_instance.set_mass(m_mass);
} // state_captive::stop()

/*----------------------------------------------------------------------------*/
/**
 * \brief Move the player to the left.
 */
void tunnel::state_captive::do_move_left()
{
  // we can't move in this state
} // state_captive::do_move_left()

/*----------------------------------------------------------------------------*/
/**
 * \brief Move the player to the left.
 */
void tunnel::state_captive::do_move_right()
{
   // we can't move in this state
} // state_captive::do_move_right()

/*----------------------------------------------------------------------------*/
/**
 * \brief Do a jump.
 */
void tunnel::state_captive::do_jump()
{
   // we can't jump in this state
} // state_captive::do_jump()

/*----------------------------------------------------------------------------*/
/**
 * \brief Make the player doing slap.
 */
void tunnel::state_captive::do_slap()
{
   // we can't slap in this state
} // state_captive::do_slap()

/*----------------------------------------------------------------------------*/
/**
 * \brief To unchain Player.
 */
void tunnel::state_captive::unchain()
{
  m_player_instance.choose_idle_state();
} // state_captive::unchain()

/*----------------------------------------------------------------------------*/
/**
 * \brief To chain Player.
 */
void tunnel::state_captive::chain()
{
  // Player is already captive
} // state_captive::chain()

/*----------------------------------------------------------------------------*/
/**
 * \brief Player throw a stone
 */
void tunnel::state_captive::do_start_throw()
{
 // we can't throw in this state
} // state_captive::start_throw

/*----------------------------------------------------------------------------*/
/**
 * \brief Player drop a power.
 */
void tunnel::state_captive::do_start_drop()
{
 // we can't drop in this state
} // state_captive::do_start_drop()

/*----------------------------------------------------------------------------*/
/**
 * \brief Player is injured.
 */
void tunnel::state_captive::do_injured()
{
  // do_nothong
} // state_captive::do_injured()
