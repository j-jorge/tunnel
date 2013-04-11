/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief A message sent to get the instance of a player.
 * \author Julien Jorge
 */
#ifndef __TUNNEL_GET_PLAYER_INSTANCE_HPP__
#define __TUNNEL_GET_PLAYER_INSTANCE_HPP__

#include "communication/typed_message.hpp"

#include "tunnel/player.hpp" // must be included, not predeclared.

namespace tunnel
{
  /**
   * \brief A message sent to get the instance of a player.
   * \author Julien Jorge
   */
  class get_player_instance:
    public bear::communication::typed_message<player>
  {
  public:
    get_player_instance();

    bool apply_to( player& that );

    player* get_instance() const;

  private:
    /** \brief The instance of the player. */
    player* m_player;

  }; // class get_player_instance
} // namespace tunnel

#endif // __TUNNEL_GET_PLAYER_INSTANCE_HPP__
