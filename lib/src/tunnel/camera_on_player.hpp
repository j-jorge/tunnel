/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief A camera shared among the player.
 * \author Sebastien Angibaud
 */
#ifndef __TUNNEL_CAMERA_ON_PLAYER_HPP__
#define __TUNNEL_CAMERA_ON_PLAYER_HPP__

#include "tunnel/player_proxy.hpp"

#include "communication/typed_message.hpp"
#include "engine/messageable_item.hpp"
#include "generic_items/camera.hpp"

#include "engine/export.hpp"

namespace tunnel
{
  /**
   * \brief A camera shared among the player.
   * \author Sebastien Angibaud
   */
  class camera_on_player:
    public bear::engine::messageable_item<bear::camera>
  {
    DECLARE_BASE_ITEM(camera_on_player);

  public:
    typedef bear::engine::messageable_item<bear::camera> super;

    /*----------------------------------------------------------------------*/
    /**
     * \brief The different placement modes for the camera.
     */
    enum placement_mode
      {
        /** \brief Centered on the player. */
        lock_player,

        /** \brief Don't move. */
        do_nothing
      }; // enum mode

    /*----------------------------------------------------------------------*/
    /**
     * \brief A message that set the placement mode of the camera.
     * \author Julien Jorge
     */
    class set_placement_message:
      public bear::communication::typed_message<camera_on_player>
    {
    public:
      set_placement_message( placement_mode mode );

      bool apply_to( camera_on_player& that );

    private:
      /** \brief The mode to set. */
      const placement_mode m_mode;

    }; // class set_placement_message

  private:
    /** \brief The type of the progress function. */
    typedef
    void (camera_on_player::*progress_type)( bear::universe::time_type );

    /*----------------------------------------------------------------------*/
  public:
    camera_on_player();
    camera_on_player( const camera_on_player& c );
    
    void progress( bear::universe::time_type elapsed_time );

    void set_mode( placement_mode mode );
    void set_proxy_player( player* p );

  private:
    void auto_position( bear::universe::time_type elapsed_time );

    void set_player( bear::universe::time_type elapsed_time );

  private:
    /** \brief Current placement mode. */
    placement_mode m_placement;

    /** \brief The first player. */
    player_proxy m_player;

  }; // class camera_on_player
} // namespace tunnel

#endif // __TUNNEL_CAMERA_ON_PLAYER_HPP__
