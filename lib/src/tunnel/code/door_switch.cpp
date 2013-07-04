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
  bool result = false;

  if ( name == "door_switch.tag" )
    m_tag = value;
  else
    result = super::set_string_field( name, value );

  return result;
} // door_switch::set_string_field()

