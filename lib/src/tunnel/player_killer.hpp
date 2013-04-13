/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief This item kill the player on collision.
 * \author Julien Jorge
 */
#ifndef __TUNNEL_PLAYER_KILLER_HPP__
#define __TUNNEL_PLAYER_KILLER_HPP__

#include "engine/base_item.hpp"

#include "engine/export.hpp"

namespace tunnel
{
  /**
   * \brief This item kill the player on collision.
   *
   * This class has no custom field.
   *
   * \author Julien Jorge
   */
  class player_killer:
    public bear::engine::base_item
  {
    DECLARE_BASE_ITEM(player_killer);

  public:
    typedef bear::engine::base_item super;

  private:
    void collision
    ( bear::engine::base_item& that, bear::universe::collision_info& info );

  }; // class player_killer
} // namespace tunnel

#endif // __TUNNEL_PLAYER_KILLER_HPP__
