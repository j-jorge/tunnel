/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the tunnel::energy class.
 * \author Sebastien Angibaud
 */
#include "tunnel/layer/status/energy_component.hpp"

#include "tunnel/game_variables.hpp"

#include "engine/game.hpp"
#include "visual/scene_sprite.hpp"
#include "visual/bitmap_writing.hpp"
#include "visual/scene_writing.hpp"

#include <boost/bind.hpp>
#include <claw/tween/tweener_sequence.hpp>
#include <claw/tween/single_tweener.hpp>
#include <claw/tween/easing/easing_elastic.hpp>
#include <claw/tween/easing/easing_back.hpp>

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 * \param glob Level globals in which we take the resources.
 * \param active_position the position in active state.
 * \param side Indicates the side on which the component appears.
 * \param x_p The placement on x-coordinate.
 * \param y_p The placement on y-coordinate.
 * \param layer_size The size of the layer in which the component is displayed.
 * \param flip Indicates if picture must be flipped.
 */
tunnel::energy_component::energy_component
( bear::engine::level_globals& glob,
  const bear::visual::position_type& active_position, 
  bear::universe::zone::position side,
  x_placement x_p, y_placement y_p,
  const bear::universe::size_box_type& layer_size,
  const bear::universe::coordinate_type& hide_height, bool flip )
  : super(glob,active_position,side, x_p, y_p, layer_size, hide_height, flip)
{
} // energy_component::energy_component()

/*----------------------------------------------------------------------------*/
/**
 * \brief Initialize the component.
 */
void tunnel::energy_component::build()
{
  m_sprite =
    get_level_globals().auto_sprite( "gfx/status/status.png", "hearth" );

  super::build();
} // energy_component::build()

/*----------------------------------------------------------------------------*/
/**
 * \brief Render the component.
 * \param e (out) The scene elements.
 */
void tunnel::energy_component::render( scene_element_list& e ) const
{
  unsigned int nb = game_variables::get_energy();
  
  bear::visual::scene_sprite s1
    ( get_render_position().x + 2, get_render_position().y, m_sprite);
  if ( nb == 0 )
    s1.get_rendering_attributes().set_intensity(0,0,0);
  e.push_back( s1 ); 
  
  bear::visual::scene_sprite s2
    ( get_render_position().x + m_sprite.width() + 8, 
      get_render_position().y, m_sprite);
  if ( nb <= 1 )
    s2.get_rendering_attributes().set_intensity(0,0,0);
  e.push_back( s2 ); 
  
  bear::visual::scene_sprite s3
    ( get_render_position().x + m_sprite.width()/2 + 5, 
      get_render_position().y + m_sprite.height() + 4, m_sprite);
  if ( nb <= 2 )
    s3.get_rendering_attributes().set_intensity(0,0,0);
  e.push_back( s3 ); 
} // energy_component::render()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the visual width of the bar.
 */
unsigned int tunnel::energy_component::width() const
{
  return m_sprite.width() * 2 + 6;
} // energy_component::width()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the visual height of the bar.
 */
unsigned int tunnel::energy_component::height() const
{
  return m_sprite.height() * 2 + 4;
} // energy_component::height()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set all signals to listen.
 */
void tunnel::energy_component::init_signals()
{
  super::init_signals();

  add_signal
    ( bear::engine::game::get_instance().listen_uint_variable_change
      ( game_variables::get_energy_variable_name(),
        boost::bind
        (&tunnel::energy_component::on_energy_changed,
         this, _1) ) );
} // energy_component::init_signals()

/*----------------------------------------------------------------------------*/
/**
 * \brief The fonction called when number of energy changes.
 * \param value The new energy state.
 */
void tunnel::energy_component::on_energy_changed(unsigned int value)
{
  // do nothing ? animation ?
} // energy_component::on_energy_changed()
