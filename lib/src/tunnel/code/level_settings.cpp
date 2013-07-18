/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the tunnel::level_settings class.
 * \author Sebastien Angibaud
 */
#include "tunnel/level_settings.hpp"

#include "tunnel/game_variables.hpp"

BASE_ITEM_EXPORT( level_settings, tunnel )

/*----------------------------------------------------------------------------*/
/**
 * \brief Contructor.
 */
tunnel::level_settings::level_settings()
{
} // level_settings::level_settings()

/*----------------------------------------------------------------------------*/
/**
 * \brief Initialize the item.
 */
void tunnel::level_settings::build()
{
  super::build();

  game_variables::set_crystal_count(0);

  kill();
} // level_settings::build()
