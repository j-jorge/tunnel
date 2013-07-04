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
