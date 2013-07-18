/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief The component to display the crystal.
 * \author Sebastien Angibaud
 */
#ifndef __TUNNEL_CRYSTAL_COMPONENT_HPP__
#define __TUNNEL_CRYSTAL_COMPONENT_HPP__

#include "tunnel/layer/status/status_component.hpp"

#include "visual/animation.hpp"
#include "visual/writing.hpp"

namespace tunnel
{
  /**
   * \brief The component to display the crystal.
   * \author Sebastien Angibaud
   */
  class crystal_component :
    public status_component
  {
  public:
    /** \brief The type of the parent class. */
    typedef status_component super;

  public:
    crystal_component
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
    void on_crystal_changed(unsigned int number); 

  private:
    /** \brief The font for text. */
    bear::visual::font m_font;
    
    /** \brief The number of crystals. */
    bear::visual::writing m_crystal;

     /** \brief The number of required crystal. */
    bear::visual::writing m_required_crystal;

    /** \brief The current animation of crystal. */
    bear::visual::sprite m_crystal_sprite;

  }; // class crystal_component
} // namespace tunnel

#endif // __TUNNEL_CRYSTAL_COMPONENT_HPP__
