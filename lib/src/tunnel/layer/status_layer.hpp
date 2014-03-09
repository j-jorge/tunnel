/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief The status layer contains the area where are displayed the
 *        informations about the player.
 * \author Julien Jorge
 */
#ifndef __TUNNEL_STATUS_LAYER_HPP__
#define __TUNNEL_STATUS_LAYER_HPP__

#include "engine/layer/gui_layer.hpp"
#include "visual/sprite.hpp"
#include "visual/writing.hpp"

#include <boost/signals2.hpp>
#include <claw/tween/tweener_group.hpp>

namespace tunnel
{
  class cart;
  class status_component;

  /**
   * \brief The status layer contains the area where are displayed the
   *        informations about the player.
   */
  class status_layer:
    public bear::engine::gui_layer
  {
  public:
    /** \brief The type of a list of scene elements retrieved from the layer. */
    typedef bear::engine::gui_layer::scene_element_list scene_element_list;

    typedef bear::engine::gui_layer super;

    /** The A list of status component. */
    typedef std::list<status_component*> component_list;

  public:
    status_layer();
    virtual ~status_layer();

    void build();
    void progress( bear::universe::time_type elapsed_time );
    void render( scene_element_list& e ) const;

  private:
    void create_components();

  private:
    /** \brief The component that display components. */
    component_list m_components;

    /** \brief The sprite of score background. */
    bear::visual::sprite m_score_background;

    /** \brief The margin around the sprites. */
    static const unsigned int s_margin;
  }; // class status_layer
} // namespace tunnel

#endif // __TUNNEL_STATUS_LAYER_HPP__
