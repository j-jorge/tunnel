/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the tunnel::door class.
 * \author Sebastien Angibaud
 */
#include "tunnel/door.hpp"

BASE_ITEM_EXPORT( door, tunnel )


/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
tunnel::door::door()
: m_opened(false)
{

} // door::door()

/*----------------------------------------------------------------------------*/
/**
 * \brief Load the media required by this class.
 */
void tunnel::door::pre_cache()
{
  super::pre_cache();

  get_level_globals().load_model("model/door.cm");
} // door::pre_cache()

/*----------------------------------------------------------------------------*/
/**
 * \brief Do post creation actions.
 */
void tunnel::door::on_enters_layer()
{
  super::on_enters_layer();

  set_model_actor( get_level_globals().get_model("model/door.cm") );
  
  if ( m_opened )
    start_model_action("opened");
  else
    start_model_action("closed");
} // door::on_enters_layer()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell if the item is correctly initialized.
 */
bool tunnel::door::is_valid() const
{
  return ! m_tag.empty();
} // door::is_valid()


/*----------------------------------------------------------------------------*/
/**
 * \brief Set a field of type bool.
 * \param name The name of the field.
 * \param value The new value of the field.
 * \return false if the field "name" is unknow, true otherwise.
 */
bool tunnel::door::set_bool_field( const std::string& name, bool value )
{
  bool result = false;

  if ( name == "door.opened" )
    m_opened = value;
  else
    result = super::set_bool_field( name, value );

  return result;
} // door::set_bool_field()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set a field of type string.
 * \param name The name of the field.
 * \param value The new value of the field.
 * \return false if the field "name" is unknow, true otherwise.
 */
bool tunnel::door::set_string_field
( const std::string& name, const std::string& value )
{
  bool result = false;

  if ( name == "door.tag" )
    m_tag = value;
  else
    result = super::set_string_field( name, value );

  return result;
} // door::set_string_field()

/*----------------------------------------------------------------------------*/
/**
 * \brief Return the tag of the door.
 */
std::string tunnel::door::get_tag() const
{
  return m_tag;
} // door::get_tag()

/*----------------------------------------------------------------------------*/
/**
 * \brief Switch the door.
 */
void tunnel::door::switch_door()
{
  if ( get_current_action_name() == "closed" ||
       get_current_action_name() == "close" )
    start_model_action("open");
  else
    start_model_action("close");
} // door::switch_door()

/*----------------------------------------------------------------------------*/
/**
 * \brief Process a collision with the door.
 * \param mark The mark on which the collision occurred.
 * \param that The other item of the collision.
 * \param info Some informations about the collision.
 */
void tunnel::door::on_door_collision
( bear::engine::base_item& mark, bear::engine::base_item& that,
  bear::universe::collision_info& info )
{
  default_collision(info);
} // door::on_door_collision()

/*----------------------------------------------------------------------------*/
/**
 * \brief Export the methods of the class.
 */
void tunnel::door::init_exported_methods()
{
  TEXT_INTERFACE_CONNECT_METHOD_3
    ( door, on_door_collision, void, bear::engine::base_item&,
      bear::engine::base_item&, bear::universe::collision_info& );
} // door::init_exported_methods()

/*----------------------------------------------------------------------------*/
TEXT_INTERFACE_IMPLEMENT_METHOD_LIST( tunnel::door )
