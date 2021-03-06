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
#include "tunnel/crystal.hpp"

#include "tunnel/game_variables.hpp"
#include "tunnel/player.hpp"

#include "generic_items/decorative_item.hpp"
#include "universe/forced_movement/forced_rotation.hpp"

BASE_ITEM_EXPORT( crystal, tunnel )

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
tunnel::crystal::crystal()
: m_given (false)
{
  set_can_move_items(false);
} // crystal::crystal()

/*----------------------------------------------------------------------------*/
/**
 * \brief Build the item. This method is called automatically by the owner.
 */
void tunnel::crystal::build()
{
  super::build();
  
  m_level_started =
    get_level().on_started
    ( boost::bind( &crystal::on_level_started, this ) );

  bear::visual::sprite sprite
    ( get_level_globals().auto_sprite( "gfx/effect/light-star.png", "star" ) );
  sprite.set_size( 2 * get_size() );

  bear::decorative_item* item = new bear::decorative_item;
  item->set_sprite( sprite );
  item->set_z_position( get_z_position() - 10 );
  item->set_center_of_mass( get_center_of_mass() );
  item->set_system_angle_as_visual_angle( true );

  new_item(*item);

  bear::universe::forced_rotation mvt;
  mvt.set_radius(0);
  mvt.set_reference_point_on_center( *this );
  mvt.set_total_time( 20 );
  mvt.set_acceleration_time( 0 );
  mvt.set_angle_application( bear::universe::forced_rotation::apply_force );

  item->set_forced_movement( mvt );

  kill_when_dying( *item );
} // crystal::build()

/*----------------------------------------------------------------------------*/
/**
 * \brief Call collision_check_and_align().
 * \param that The other item of the collision.
 * \param info Some informations about the collision.
 */
void tunnel::crystal::collision
( bear::engine::base_item& that, bear::universe::collision_info& info )
{
  if ( ! m_given )
    {
      player* other = dynamic_cast<player*>(&that);
      
      if (other != NULL)
        {
          m_given = true;
          game_variables::set_founded_crystal_count
            ( game_variables::get_founded_crystal_count() + 1 );
          
          kill();
        }
    }
} // crystal::collision()

/*----------------------------------------------------------------------------*/
/**
 * \brief The level start.
 */
void tunnel::crystal::on_level_started()
{
  game_variables::set_crystal_count( game_variables::get_crystal_count() + 1 );

  m_level_started.disconnect();
} // crystal::on_level_started()
