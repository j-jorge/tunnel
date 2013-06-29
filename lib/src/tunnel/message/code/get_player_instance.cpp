/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the tunnel::get_player_instance class.
 * \author Julien Jorge
 */
#include "tunnel/message/get_player_instance.hpp"

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
tunnel::get_player_instance::get_player_instance()
  : m_player(NULL)
{

} // get_player_instance::get_player_instance()

/*----------------------------------------------------------------------------*/
/**
 * \brief Apply the message to a player.
 * \param that The player to which the message is applied.
 */
bool tunnel::get_player_instance::apply_to( player& that )
{
  m_player = &that;
  return true;
} // get_player_instance::apply_to()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the instance of the player.
 */
tunnel::player* tunnel::get_player_instance::get_instance() const
{
  return m_player;
} // get_player_instance::get_instance()
