/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the tunnel::state_float class.
 * \author Sebastien Angibaud
 */
#include "tunnel/player_state/state_float.hpp"

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
tunnel::state_float::state_float( const player_proxy& player_instance  )
  : state_player(player_instance)
{

} // state_float::state_float()

/*----------------------------------------------------------------------------*/
/**
 * \brief Return the name of the state.
 */
std::string tunnel::state_float::get_name() const
{
  return "float";
} // state_float::get_name()

/*----------------------------------------------------------------------------*/
/**
 * \brief Initialization of this state.
 */
void tunnel::state_float::start()
{
  m_density = m_player_instance.get_density();
  m_player_instance.set_density(0.85);
  m_player_instance.set_system_angle(0);
} // state_float::start()

/*----------------------------------------------------------------------------*/
/**
 * \brief Stop this state.
 */
void tunnel::state_float::stop()
{
  m_player_instance.set_density(m_density);
} // state_float::stop()

/*----------------------------------------------------------------------------*/
/**
 * \brief Do a jump.
 */
void tunnel::state_float::do_jump()
{
  // the bottom_contact is not required
  if ( m_player_instance.get_current_action_name() == "float" )
    m_player_instance.apply_impulse_jump();
} // state_float::do_jump()

/*----------------------------------------------------------------------------*/
/**
 * \brief Make the player crouch.
 */
void tunnel::state_float::do_crouch()
{
  m_player_instance.apply_dive();
} // state_float::do_crouch()

/*----------------------------------------------------------------------------*/
/**
 * \brief Make the player continue to crouch.
 */
void tunnel::state_float::do_continue_crouch()
{
  m_player_instance.apply_dive();
} // state_float::do_continue_crouch()
