/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the tunnel::status_layer class.
 * \author Julien Jorge
 */
#include "tunnel/layer/status_layer.hpp"

#include "tunnel/layer/status/energy_component.hpp"
#include "tunnel/layer/status/status_component.hpp"

#include "tunnel/game_variables.hpp"
#include "engine/game.hpp"
#include "engine/level.hpp"
#include "visual/bitmap_writing.hpp"
#include "visual/scene_sprite.hpp"
#include "visual/scene_writing.hpp"
#include <boost/bind.hpp>

/*----------------------------------------------------------------------------*/
const unsigned int tunnel::status_layer::s_margin = 5;

/*----------------------------------------------------------------------------*/
/**
 * \brief Destructor.
 */
tunnel::status_layer::status_layer()
{
} // status_layer::status_layer()

/*----------------------------------------------------------------------------*/
/**
 * \brief Destructor.
 */
tunnel::status_layer::~status_layer()
{
  component_list::iterator it2;
  for ( it2 = m_components.begin(); 
	it2 != m_components.end(); ++it2)
    delete *it2;
} // status_layer::~status_layer()

/*----------------------------------------------------------------------------*/
/**
 * \brief Initialize the layer.
 */
void tunnel::status_layer::build()
{
  super::build();
  
  create_components();
} // status_layer::build()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the players status and update local values.
 */
void tunnel::status_layer::progress( bear::universe::time_type elapsed_time )
{
  if ( ! get_level().is_paused() )
    {
      component_list::iterator it2;
      for ( it2 = m_components.begin(); 
            it2 != m_components.end(); ++it2)
        (*it2)->progress(elapsed_time);
    }
} // status_layer::progress()

/*----------------------------------------------------------------------------*/
/**
 * \brief Render the players status.
 * \param e (out) The scene elements.
 */
void tunnel::status_layer::render( scene_element_list& e ) const
{
  if ( ! get_level().is_paused() )
    {
      component_list::const_iterator it;
      for ( it = m_components.begin(); 
            it != m_components.end(); ++it)
        (*it)->render( e );
    }
} // status_layer::render()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create  components.
 */
void tunnel::status_layer::create_components()
{
  // ############## BOTTOM RIGHT #########################
  bear::visual::position_type pos_top( s_margin, get_size().y - s_margin );

  // score  
  energy_component* e = new energy_component
    (get_level_globals(), pos_top, bear::universe::zone::top_zone, 
     status_component::left_placement,
     status_component::top_placement,get_size(),
     200, false); 
  e->build();
  m_components.push_back(e);
  pos_top.y += - e->height() - s_margin;

  // lives
  /*
  pos_bottom.x = get_size().x - s_margin;
  status_component* l = new lives_component
    (get_level_globals(), pos_bottom, bear::universe::zone::bottom_zone, 
     status_component::right_placement,
     status_component::bottom_placement,get_size(),
     m_score_background.get_size().y, false); 
  l->build();
  m_components.push_back(l);
  */
} // status_layer::create_components()
