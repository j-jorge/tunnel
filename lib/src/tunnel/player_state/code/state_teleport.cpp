/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief Implementation of the tunnel::state_teleport class.
 * \author Sebastien Angibaud
 */
#include "tunnel/player_state/state_teleport.hpp"

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
tunnel::state_teleport::state_teleport( const player_proxy& player_instance )
  : state_player(player_instance)
{

} // state_teleport::state_teleport()

/*----------------------------------------------------------------------------*/
/**
 * \brief Return the name of the state.
 */
std::string tunnel::state_teleport::get_name() const
{
  return "teleport";
} // state_teleport::get_name()

/*----------------------------------------------------------------------------*/
/**
 * \brief Start the action.
 */
void tunnel::state_teleport::start()
{
} // state_teleport::stop()

/*----------------------------------------------------------------------------*/
/**
 * \brief The end of the action.
 */
void tunnel::state_teleport::stop()
{
} // state_teleport::stop()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell that the action is finished.
 */
void tunnel::state_teleport::do_stop_teleport()
{
  std::cout << "stop teleport" << std::endl;
  m_player_instance.start_action_model("idle");
} // state_teleport::do_stop_teleport()

/*----------------------------------------------------------------------------*/
/**
 * \brief Make the player doing teleport.
 */
void tunnel::state_teleport::do_teleport()
{
  // Player can't do a new teleport.
} // state_teleport::do_teleport()
