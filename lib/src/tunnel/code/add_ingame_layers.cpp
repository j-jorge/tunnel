/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the tunnel::add_ingame_layers class.
 * \author Julien Jorge
 */
#include "tunnel/add_ingame_layers.hpp"
#include "tunnel/defines.hpp"
#include "tunnel/game_variables.hpp"
#include "tunnel/tunnel_gettext.hpp" 

#include "engine/comic/layer/balloon_layer.hpp"
#include "engine/layer/transition_layer.hpp"
#include "engine/export.hpp"
#include "engine/level.hpp"
#include "engine/level_globals.hpp"
#include "engine/world.hpp"

#include "tunnel/layer/misc_layer.hpp"
#include "tunnel/layer/status_layer.hpp"

#ifndef NDEBUG
#include "generic_items/layer/item_information_layer.hpp"
#include "generic_items/layer/physics_layer.hpp"
#include "generic_items/layer/link_layer.hpp"
#include "generic_items/layer/recent_path_layer.hpp"
#include "generic_items/layer/wireframe_layer.hpp"
#endif

BASE_ITEM_EXPORT( add_ingame_layers, tunnel )

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
tunnel::add_ingame_layers::add_ingame_layers()
: m_add_status_layer(true)
{

} // add_ingame_layers::add_ingame_layers()

/*----------------------------------------------------------------------------*/
/**
 * \brief Load the media required by this class.
 */
void tunnel::add_ingame_layers::pre_cache()
{
  super::pre_cache();

  get_level_globals().load_font("font/hand-drawn-shapes.ttf");
} // add_ingame_layers::pre_cache()

/*----------------------------------------------------------------------------*/
/**
 * \brief Initialize the item.
 */
void tunnel::add_ingame_layers::build()
{
  bear::engine::transition_layer* transition
    ( new bear::engine::transition_layer
      (TUNNEL_TRANSITION_EFFECT_DEFAULT_TARGET_NAME) );
  
  get_level().push_layer( transition );
  get_level().push_layer( new misc_layer() );   
  if ( m_add_status_layer ) 
    get_level().push_layer( new status_layer() );  
  
#ifndef NDEBUG
  get_level().push_layer( new bear::item_information_layer );
  get_level().push_layer( new bear::link_layer );
  get_level().push_layer( new bear::physics_layer );
  get_level().push_layer( new bear::wireframe_layer );
  get_level().push_layer( new bear::recent_path_layer );
#endif

  kill();
} // add_ingame_layers::build()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set a field of type \c boolean.
 * \param name The name of the field.
 * \param value The value of the field.
 */
bool 
tunnel::add_ingame_layers::set_bool_field( const std::string& name, bool value )
{
  bool result(true);

  if ( name == "add_ingame_layers.add_status_layer" )
    m_add_status_layer = value;
  else
    result = super::set_bool_field(name, value);

  return result;
} // add_ingame_layers::set_bool_field()
