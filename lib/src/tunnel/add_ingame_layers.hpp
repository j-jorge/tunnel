/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief This class adds the layers for the graphical user interface in the
 *        current level.
 * \author Julien Jorge
 */
#ifndef __TUNNEL_ADD_INGAME_LAYERS_HPP__
#define __TUNNEL_ADD_INGAME_LAYERS_HPP__

#include "engine/base_item.hpp"
#include "engine/layer/gui_layer.hpp"
#include "engine/export.hpp"
#include "generic_items/timer.hpp"

namespace tunnel
{
  /**
   * \brief This class adds the layers for the graphical user interface in the
   *        current level.
   *
   * The custom fields of this class are
   * - show_introduction (boolean) tell if we must show the introduction of
   *   the level (with the level name and the act number) (default=true),
   *
   * \author Julien Jorge
   */
  class add_ingame_layers:
    public bear::engine::base_item
  {
    DECLARE_BASE_ITEM(add_ingame_layers);

  public:
    /** \brief The type of the parent class. */
    typedef bear::engine::base_item super;

  public:
    add_ingame_layers();

    void pre_cache();
    void build();

    void set_level_timer(const bear::timer* level_timer);
  }; // class add_ingame_layers
} // namespace tunnel

#endif // __TUNNEL_ADD_INGAME_LAYERS_HPP__
