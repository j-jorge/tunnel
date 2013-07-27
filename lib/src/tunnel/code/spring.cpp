/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the tunnel::spring class.
 * \author Sebastien Angibaud
 */
#include "tunnel/spring.hpp"

#include "engine/level_globals.hpp"

BASE_ITEM_EXPORT( spring, tunnel )

/*----------------------------------------------------------------------------*/
/**
 * \brief Loads the resources used by this item.
 */
void tunnel::spring::pre_cache()
{
  super::pre_cache();

  get_level_globals().load_sound( "sound/boing.ogg" );
} // spring::pre_cache()

/*----------------------------------------------------------------------------*/
/**
 * \brief Initialize the item.
 */
void tunnel::spring::build()
{
  super::build();

  set_bounce_sound( get_level_globals().new_sample( "sound/boing.ogg" ) );
} // spring::build()
