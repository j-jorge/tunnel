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
#include "tunnel/layer/status/crystal_component.hpp"

#include "tunnel/game_variables.hpp"

#include "engine/game.hpp"
#include "visual/scene_sprite.hpp"
#include "visual/bitmap_writing.hpp"
#include "visual/scene_writing.hpp"

#include <boost/bind.hpp>
#include <claw/tween/tweener_sequence.hpp>
#include <claw/tween/single_tweener.hpp>
#include <claw/tween/easing/easing_elastic.hpp>
#include <claw/tween/easing/easing_linear.hpp>
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
tunnel::crystal_component::crystal_component
( bear::engine::level_globals& glob,
  const bear::visual::position_type& active_position, 
  bear::universe::zone::position side,
  x_placement x_p, y_placement y_p,
  const bear::universe::size_box_type& layer_size,
  const bear::universe::coordinate_type& hide_height, bool flip )
  : super(glob,active_position,side, x_p, y_p, layer_size, hide_height, flip),
    m_font(glob.get_font("font/Hand Drawn Shapes.ttf",202))
{

} // crystal_component::crystal_component()

/*----------------------------------------------------------------------------*/
/**
 * \brief Initialize the component.
 */
void tunnel::crystal_component::build()
{
  std::ostringstream oss1;
  oss1 << "0";
  m_crystal.create(m_font, oss1.str());
  m_crystal->set_intensity(1, 0, 0);

  std::ostringstream oss2;
  oss2 << "/" << game_variables::get_crystal_count();
  m_required_crystal.create(m_font, oss2.str());
  m_required_crystal->set_intensity(0, 1, 0);
  
  m_crystal_sprite =
    get_level_globals().auto_sprite( "gfx/status/status.png", "heart" );
  m_crystal_sprite.set_intensity(1, 0, 0);

  super::build();
} // crystal_component::build()

/*----------------------------------------------------------------------------*/
/**
 * \brief Render the component.
 * \param e (out) The scene elements.
 */
void tunnel::crystal_component::render( scene_element_list& e ) const
{
  bear::visual::scene_sprite s1
    ( get_render_position().x, 
      get_render_position().y, m_crystal_sprite );
  
  const double f
    ( (m_crystal_sprite.height() - s_margin) / m_crystal.get_height() );
  bear::visual::scene_writing s2
    ( get_render_position().x + m_crystal_sprite.get_size().x + 
      s_margin + 5, get_render_position().y + 5
      + (m_crystal_sprite.height() - m_crystal_sprite.height() ) / 2,
      m_crystal);
  s2.set_scale_factor( 1.2 * f, 1.2 * f );
  
  bear::visual::scene_writing s3
    ( get_render_position().x + m_crystal_sprite.get_size().x + 
      s_margin + m_crystal.get_width() * 1.2 * f, get_render_position().y
      + (m_crystal_sprite.height() - m_crystal_sprite.height() ) / 2,
      m_required_crystal );
  s3.set_scale_factor( f, f );
  
  e.push_back( s1 );
  e.push_back( s2 );
  e.push_back( s3 );
} // crystal_component::render()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the visual width of the bar.
 */
unsigned int tunnel::crystal_component::width() const
{
  const double f
    ( (m_crystal_sprite.height() - s_margin) / m_crystal.get_height() );
  return m_crystal_sprite.width() + s_margin + m_crystal.get_width() * f + 
    + m_required_crystal.get_width() * f * 0.5;
} // crystal_component::width()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the visual height of the bar.
 */
unsigned int tunnel::crystal_component::height() const
{
  return m_crystal_sprite.height() * 1.2;
} // crystal_component::height()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set all signals to listen.
 */
void tunnel::crystal_component::init_signals()
{
  super::init_signals();

  add_signal
    ( bear::engine::game::get_instance().listen_uint_variable_change
      ( game_variables::get_crystal_count_variable_name(),
        boost::bind
        (&tunnel::crystal_component::on_crystal_changed,
         this, _1) ) );

  add_signal
    ( bear::engine::game::get_instance().listen_uint_variable_change
      ( game_variables::get_founded_crystal_count_variable_name(),
        boost::bind
        (&tunnel::crystal_component::on_crystal_changed,
         this, _1) ) );
} // crystal_component::init_signals()

/*----------------------------------------------------------------------------*/
/**
 * \brief The fonction called when number of crystal changes.
 * \param number The new crystal number.
 */
void tunnel::crystal_component::on_crystal_changed(unsigned int number)
{
  std::ostringstream oss;
  oss << game_variables::get_founded_crystal_count();
  m_crystal.create(m_font, oss.str());

  if ( number >= game_variables::get_crystal_count() )
    m_crystal->set_intensity(0, 1, 0);
  else
    m_crystal->set_intensity(1, 0, 0);
} // crystal_component::on_crystal_changed()

