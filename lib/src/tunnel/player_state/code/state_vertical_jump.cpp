/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief Implementation of the tunnel::state_vertical_jump class.
 * \author Sebastien Angibaud
 */
#include "tunnel/player_state/state_vertical_jump.hpp"

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
tunnel::state_vertical_jump::state_vertical_jump
( const player_proxy& player_instance  )
  : state_player(player_instance)
{

} // state_vertical_jump::state_vertical_jump()

/*----------------------------------------------------------------------------*/
/**
 * \brief Return the name of the state.
 */
std::string tunnel::state_vertical_jump::get_name() const
{
  return "vertical_jump";
} // state_vertical_jump::get_name()

/*----------------------------------------------------------------------------*/
/**
 * \brief Initialization of this state.
 */
void tunnel::state_vertical_jump::start()
{
  double force = m_player_instance.get_vertical_jump_force() *
    m_player_instance.get_jump_time_ratio();

  m_player_instance.add_external_force( bear::universe::force_type(0, force));
  m_player_instance.add_internal_force( bear::universe::force_type(0, force));
} // state_vertical_jump::start()

/*----------------------------------------------------------------------------*/
/**
 * \brief Do a jump.
 */
void tunnel::state_vertical_jump::do_jump()
{
  // Player can't jump
} // state_vertical_jump::do_jump()
