/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief The component to display the energy bonus state.
 * \author Sebastien Angibaud
 */
#ifndef __TUNNEL_ENERGY_COMPONENT_HPP__
#define __TUNNEL_ENERGY_COMPONENT_HPP__

#include "tunnel/layer/status/status_component.hpp"

#include "visual/animation.hpp"

namespace tunnel
{
  /**
   * \brief The component to display the energy bonus state.
   * \author Sebastien Angibaud
   */
  class energy_component :
    public status_component
  {
  public:
    /** \brief The type of the parent class. */
    typedef status_component super;

  public:
    energy_component
    ( bear::engine::level_globals& glob, 
      const bear::visual::position_type& active_position,
      bear::universe::zone::position side,
      x_placement x_p, y_placement y_p,
      const bear::universe::size_box_type& layer_size,
      const bear::universe::coordinate_type& hide_height, bool flip);

    void build();
    void render( scene_element_list& e ) const;
    unsigned int width() const;
    unsigned int height() const;

  protected:
    void init_signals();

  private:
    void on_energy_changed(unsigned int value);      

  private:
    /** \brief The current sprite of energy. */
    bear::visual::sprite m_sprite;

  }; // class energy_component
} // namespace tunnel

#endif // __TUNNEL_ENERGY_COMPONENT_HPP__
