/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the tunnel::door_switch class.
 * \author Sebastien Angibaud
 */
#include "tunnel/door_switch.hpp"
#include "tunnel/door.hpp"

#include "universe/collision_info.hpp"
#include "engine/world.hpp"
#include "engine/level.hpp"

BASE_ITEM_EXPORT( door_switch, tunnel )

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
tunnel::door_switch::door_switch()
{

} // door_switch::door_switch()

/*----------------------------------------------------------------------------*/
/**
 * \brief Load the media required by this class.
 */
void tunnel::door_switch::pre_cache()
{
  super::pre_cache();

  get_level_globals().load_model("model/door_switch.cm");
} // door_switch::pre_cache()

/*----------------------------------------------------------------------------*/
/**
 * \brief Do post creation actions.
 */
void tunnel::door_switch::on_enters_layer()
{
  super::on_enters_layer();

  set_model_actor( get_level_globals().get_model("model/door_switch.cm") );
  
  start_model_action("state_1");
} // door_switch::on_enters_layer()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell if the item is correctly initialized.
 */
bool tunnel::door_switch::is_valid() const
{
  return ! m_tag.empty();
} // door_switch::is_valid()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set a field of type string.
 * \param name The name of the field.
 * \param value The new value of the field.
 * \return false if the field "name" is unknow, true otherwise.
 */
bool tunnel::door_switch::set_string_field
( const std::string& name, const std::string& value )
{
  bool result = true;

  if ( name == "door_switch.tag" )
    m_tag = value;
  else
    result = super::set_string_field( name, value );

  return result;
} // door_switch::set_string_field()

/*----------------------------------------------------------------------------*/
/**
 * \brief Process a collision with the base.
 * \param mark The mark on which the collision occurred.
 * \param that The other item of the collision.
 * \param info Some informations about the collision.
 */
void tunnel::door_switch::on_base_collision
( bear::engine::base_item& mark, bear::engine::base_item& that,
  bear::universe::collision_info& info )
{
} // door_switch::on_base_collision()

/*----------------------------------------------------------------------------*/
/**
 * \brief Process a collision with the button 1.
 * \param mark The mark on which the collision occurred.
 * \param that The other item of the collision.
 * \param info Some informations about the collision.
 */
void tunnel::door_switch::on_button_1_collision
( bear::engine::base_item& mark, bear::engine::base_item& that,
  bear::universe::collision_info& info )
{
  if ( info.get_collision_side() == bear::universe::zone::top_zone )
    {
      if ( get_current_action_name() == "state_1" )
        {
          start_model_action("state_2");
          switch_door();
        }

      mark.default_collision(info);
    }
} // door_switch::on_button_1_collision()

/*----------------------------------------------------------------------------*/
/**
 * \brief Process a collision with the button 2.
 * \param mark The mark on which the collision occurred.
 * \param that The other item of the collision.
 * \param info Some informations about the collision.
 */
void tunnel::door_switch::on_button_2_collision
( bear::engine::base_item& mark, bear::engine::base_item& that,
  bear::universe::collision_info& info )
{
  if ( info.get_collision_side() == bear::universe::zone::top_zone ) 
    {
      if ( get_current_action_name() == "state_2" )
        {
          start_model_action("state_1");
          switch_door();
        }

      mark.default_collision(info);
    }
} // door_switch::on_button_2_collision()

/*----------------------------------------------------------------------------*/
/**
 * \brief Switch the door.
 */
void tunnel::door_switch::switch_door()
{
  bear::engine::world::item_list::iterator it;
  bear::engine::world::item_list items;
  bear::universe::rectangle_type r
    ( get_level().get_camera()->get_bounding_box() );

  get_world().pick_items_in_rectangle(items, r);

  for ( it = items.begin(); it != items.end(); ++it )
    {
      door* d = dynamic_cast<door*>(*it);
      
      if ( d != NULL )
        if ( d->has_tag(m_tag) )
          d->switch_door();
    }
} // door_switch::switch_door()

/*----------------------------------------------------------------------------*/
/**
 * \brief Export the methods of the class.
 */
void tunnel::door_switch::init_exported_methods()
{
  TEXT_INTERFACE_CONNECT_METHOD_3
    ( door_switch, on_base_collision, void, bear::engine::base_item&,
      bear::engine::base_item&, bear::universe::collision_info& );  
  TEXT_INTERFACE_CONNECT_METHOD_3
    ( door_switch, on_button_1_collision, void, bear::engine::base_item&,
      bear::engine::base_item&, bear::universe::collision_info& );  
  TEXT_INTERFACE_CONNECT_METHOD_3
    ( door_switch, on_button_2_collision, void, bear::engine::base_item&,
      bear::engine::base_item&, bear::universe::collision_info& );
} // door::init_exported_methods()

/*----------------------------------------------------------------------------*/
TEXT_INTERFACE_IMPLEMENT_METHOD_LIST( tunnel::door_switch )
