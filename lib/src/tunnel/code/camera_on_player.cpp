/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief Implementation of the tunnel::camera_on_player class.
 * \author Sébastien Angibaud
 */
#include "tunnel/camera_on_player.hpp"

#include "tunnel/util/player_util.hpp"

BASE_ITEM_EXPORT( camera_on_player, tunnel )

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 * \param mode The mode to se the camera to.
 */
tunnel::camera_on_player::set_placement_message::set_placement_message
( placement_mode mode )
  : m_mode(mode)
{

} // set_placement_message::set_placement_message()

/*----------------------------------------------------------------------------*/
/**
 * \brief Apply the message to a camera.
 * \param that The camera to apply the message to.
 */
bool tunnel::camera_on_player::set_placement_message::apply_to( camera_on_player& that )
{
  that.set_mode( m_mode );
  return true;
} // set_placement_message::apply_to()




/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
tunnel::camera_on_player::camera_on_player()
  : m_placement(lock_player), m_progress(&camera_on_player::progress_no_player)
{
  set_active_on_build();
} // camera_on_player::camera_on_player()

/*----------------------------------------------------------------------------*/
/**
 * \brief Initialize the item.
 */
void tunnel::camera_on_player::build()
{
  super::build();
} // camera_on_player::build()

/*----------------------------------------------------------------------------*/
/**
 * \brief Do one step in the progression of the item.
 * \param elapsed_time Elapsed time since the last call.
 */
void tunnel::camera_on_player::progress( bear::universe::time_type elapsed_time )
{
  (this->*m_progress)(elapsed_time);
} // camera_on_player::progress()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the placement mode.
 * \param mode The new mode.
 */
void tunnel::camera_on_player::set_mode( placement_mode mode )
{
  m_placement = mode;
} // camera_on_player::set_mode()

/*----------------------------------------------------------------------------*/
/**
 * \brief Compute the position of the camera.
 * \param elapsed_time Elapsed time since the last call.
 */
void tunnel::camera_on_player::auto_position
( bear::universe::time_type elapsed_time )
{
  switch(m_placement)
    {
    case lock_player: set_player(elapsed_time); break;
    case do_nothing: break;
    }
} // camera_on_player::auto_position()

/*----------------------------------------------------------------------------*/
/**
 * \brief Center the camera on the player.
 * \param elapsed_time Elapsed time since the last call.
 */
void
tunnel::camera_on_player::set_player( bear::universe::time_type elapsed_time )
{
  if ( m_player != NULL )
    adjust_position( m_player.hot_spot(), elapsed_time );
  else
    m_placement = do_nothing;
} // camera_on_player::set_player()

/*----------------------------------------------------------------------------*/
/**
 * \brief Search players.
 */
void tunnel::camera_on_player::search_player()
{
  if ( m_player == NULL )
    m_player = util::find_player( get_level_globals(), 1 );
} // camera_on_player::search_player()

/*----------------------------------------------------------------------------*/
/**
 * \brief Search the players and update the position of the camera.
 * \param elapsed_time Elapsed time since the last call.
 */
void tunnel::camera_on_player::progress_no_player
( bear::universe::time_type elapsed_time )
{
  search_player();

  if ( m_player!=NULL )
    {
      m_progress = &camera_on_player::progress_with_player;

      teleport( m_player.hot_spot() );
    }
  else
    progress_zoom(elapsed_time);
} // camera_on_player::progress_no_player()

/*----------------------------------------------------------------------------*/
/**
 * \brief Update the position of the camera.
 * \param elapsed_time Elapsed time since the last call.
 */
void tunnel::camera_on_player::progress_with_player
( bear::universe::time_type elapsed_time )
{
  progress_zoom(elapsed_time);
  auto_position(elapsed_time);
} // camera_on_player::progress_with_player()
