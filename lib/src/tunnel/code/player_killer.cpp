/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the bear::player_killer class.
 * \author Julien Jorge
 */
#include "tunnel/player_killer.hpp"

#include "universe/collision_info.hpp"
#include "engine/export.hpp"
#include "tunnel/player_proxy.hpp"
#include "tunnel/player_action.hpp"

BASE_ITEM_EXPORT( player_killer, tunnel )

/*----------------------------------------------------------------------------*/
/**
 * \brief Kill \a that if it is a player.
 * \param that The other item of the collision.
 * \param info Some informations about the collision.
 */
void tunnel::player_killer::collision
( bear::engine::base_item& that, bear::universe::collision_info& info )
{
  player_proxy p(&that);

  if ( p != NULL )
    p.start_action( player_action::die );
} // player_killer::collision()
