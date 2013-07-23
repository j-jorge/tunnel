/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the tunnel::level_exit class.
 * \author Sebastien Angibaud
 */
#include "tunnel/level_exit.hpp"

#include "tunnel/defines.hpp"
#include "tunnel/game_variables.hpp"
#include "tunnel/player.hpp"

#include "generic_items/delayed_level_loading.hpp"

BASE_ITEM_EXPORT( level_exit, tunnel )

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
tunnel::level_exit::level_exit()
: m_opened (false)
{
  set_can_move_items(false);
} // level_exit::level_exit()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell if the item is correctly initialized.
 */
bool tunnel::level_exit::is_valid() const
{
  return ! m_level_filename.empty();
} // level_exit::is_valid()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set a field of type string.
 * \param name The name of the field.
 * \param value The new value of the field.
 * \return false if the field "name" is unknow, true otherwise.
 */
bool tunnel::level_exit::set_string_field
( const std::string& name, const std::string& value )
{
  bool result = true;

  if ( name == "level_exit.next_level" )
    m_level_filename = value;
  else
    result = super::set_string_field( name, value );

  return result;
} // level_exit::set_string_field()

/*---------------------------------------------------------------------------*/
/**
 * \brief Do one iteration in the progression of the item.
 * \param elapsed_time Elapsed time since the last call.
 */
void tunnel::level_exit::progress( bear::universe::time_type elapsed_time )
{
  super::progress( elapsed_time );

  if ( game_variables::get_founded_crystal_count() < 
       game_variables::get_crystal_count() )
    get_rendering_attributes().set_color( bear::visual::color_type("#FF0000") );
  else
    get_rendering_attributes().set_color( bear::visual::color_type("#00FF00") );
} // level_exit::progress()

/*----------------------------------------------------------------------------*/
/**
 * \brief Call collision_check_and_align().
 * \param that The other item of the collision.
 * \param info Some informations about the collision.
 */
void tunnel::level_exit::collision
( bear::engine::base_item& that, bear::universe::collision_info& info )
{
  if ( ! m_opened && 
       game_variables::get_founded_crystal_count() >= 
       game_variables::get_crystal_count() )
    {
      player* other = dynamic_cast<player*>(&that);
      
      if (other != NULL)
        {
          m_opened = true;
          game_variables::set_level_is_finished(true);

          bear::delayed_level_loading* item = new bear::delayed_level_loading
            ( m_level_filename, 2, false, 2, 
              TUNNEL_TRANSITION_EFFECT_DEFAULT_TARGET_NAME);
          new_item(*item);
          item->set_global(true);
          item->set_center_of_mass(get_center_of_mass());

          kill();
        }
    }
} // level_exit::collision()
