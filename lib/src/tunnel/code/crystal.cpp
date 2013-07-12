/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the tunnel::crystal class.
 * \author Sebastien Angibaud
 */
#include "tunnel/crystal.hpp"

BASE_ITEM_EXPORT( crystal, tunnel )

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
tunnel::crystal::crystal()
{
  set_can_move_items(false);
} // door::door()
