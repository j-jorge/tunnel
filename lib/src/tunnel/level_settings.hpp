/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief An item to set parameters of level.
 * \author Angibaud Sebastien
 */
#ifndef __TUNNEL_LEVEL_SETTINGS_HPP__
#define __TUNNEL_LEVEL_SETTINGS_HPP__

#include "generic_items/level_settings.hpp"
#include "engine/export.hpp"

namespace tunnel
{
  /**
   * \brief An item to set parameters of level.
   *
   * The valid fields for this item are
   *  - any field supported by the parent classes.
   *
   * \author Sebastien Angibaud
   */
  class level_settings:
    public bear::level_settings
  {
    DECLARE_BASE_ITEM(level_settings);

  public:
    /** \brief The type of the parent class. */
    typedef bear::level_settings super;

  public:
    level_settings();

    void build();
  }; // class level_settings
} // namespace tunnel

#endif // __TUNNEL_LEVEL_SETTINGS_HPP__
