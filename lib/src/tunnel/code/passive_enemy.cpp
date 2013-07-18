/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the tunnel::passive_enemy class.
 * \author Sébastien Angibaud
 */
#include "tunnel/passive_enemy.hpp"
#include "tunnel/player.hpp"

#include "universe/collision_info.hpp"

#include "engine/export.hpp"

BASE_ITEM_EXPORT( passive_enemy, tunnel )

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
tunnel::passive_enemy::passive_enemy()
  : m_right_side_type(inactive_type), m_left_side_type(inactive_type),
    m_top_side_type(inactive_type), m_bottom_side_type(inactive_type)
{
  set_can_move_items(true);
} // passive_enemy::passive_enemy()

/*----------------------------------------------------------------------------*/
/**
 * \brief Call collision_check_and_align().
 * \param that The other item of the collision.
 * \param info Some informations about the collision.
 */
void tunnel::passive_enemy::collision
( bear::engine::base_item& that, bear::universe::collision_info& info )
{
  side_type t = inactive_type;

  switch( info.get_collision_side() )
    {
    case bear::universe::zone::top_zone:
      t = m_top_side_type; break;
    case bear::universe::zone::bottom_zone:
      t = m_bottom_side_type; break;
    case bear::universe::zone::middle_left_zone:
      t = m_left_side_type; break;
    case bear::universe::zone::middle_right_zone:
      t = m_right_side_type; break;
    default:
      { }
    }

  if ( t == attack_type )
    {
      if ( collision_and_attack(that, info) )
        collision_check_and_align(that, info);
    }
  else
    collision_check_and_align(that, info);
} // passive_enemy::collision()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set a field of type \c string.
 * \param name The name of the field.
 * \param value The new value of the field.
 * \return false if the field "name" is unknow, true otherwise.
 */
bool tunnel::passive_enemy::set_string_field
( const std::string& name, const std::string& value )
{
  bool result = true;

  if ( name == "passive_enemy.type_right_side" )
    result = set_side_type(m_right_side_type, value);
  else if ( name == "passive_enemy.type_left_side" )
    result = set_side_type(m_left_side_type, value);
  else if ( name == "passive_enemy.type_top_side" )
    result = set_side_type(m_top_side_type, value);
  else if ( name == "passive_enemy.type_bottom_side" )
    result = set_side_type(m_bottom_side_type, value);
  else
    result = super::set_string_field(name, value);

  return result;
} // passive_enemy::set_string_field()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the type of a given side.
 * \param side The considered side.
 * \param value The new type of the side.
 * \return false if the value is unknow, true otherwise.
 */
bool tunnel::passive_enemy::set_side_type
(side_type& side, const std::string& value)
{
  bool result = true;

  if ( value == "inactive" )
    side = inactive_type;
  else if ( value == "attack" )
    side = attack_type;
  else
    result = false;

  return result;
} // passive_enemy::set_side()

/*----------------------------------------------------------------------------*/
/**
 * \brief Process a collision and attack.
 * \param that The other item of the collision.
 * \param info Some informations about the collision.
 */
bool tunnel::passive_enemy::collision_and_attack
( bear::engine::base_item& that, bear::universe::collision_info& info )
{
  if ( attack(that, info.get_collision_side()) )
    return true;
  else
    {
      super::collision(that, info);
      return false;
    }
} // passive_enemy::collision_and_attack()

/*----------------------------------------------------------------------------*/
/**
 * \brief Attack an other item.
 * \param that The item to attack.
 */
bool tunnel::passive_enemy::attack( bear::engine::base_item& that )
{
  return attack
    ( that,
      bear::universe::zone::find
      ( that.get_bounding_box(), this->get_bounding_box() ) );
} // passive_enemy::attack()

/*----------------------------------------------------------------------------*/
/**
 * \brief Attack an other item.
 * \param that The item to attack.
 * \param side The side of this with which the attack is done.
 */
bool tunnel::passive_enemy::attack
( bear::engine::base_item& that, bear::universe::zone::position side )
{
  bool result = false;

  player* other = dynamic_cast<player*>(&that);
  
  if (other != NULL)
    result = other->receive_an_attack(*this);

  return result;
} // passive_enemy::attack()
