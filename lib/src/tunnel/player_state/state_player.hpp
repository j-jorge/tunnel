/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Definition of the class describing a state of Player.
 * \author Sebastien Angibaud
 */
#ifndef __TUNNEL_STATE_PLAYER_HPP__
#define __TUNNEL_STATE_PLAYER_HPP__

#include "tunnel/player_proxy.hpp"

#include "engine/scene_visual.hpp"

#include <string>

namespace tunnel
{
  /**
   * \brief The class describing a state of the player (Player).
   * \author Julien Jorge
   */
  class state_player
  {
  public:
    state_player(const player_proxy& player_instance);
    virtual ~state_player() {};

  public:
    virtual std::string get_name() const { return "undefined state"; };
    virtual void start() {};
    virtual void stop() {};

    virtual void do_move_left();
    virtual void do_move_right();
    virtual void do_jump();
    virtual void do_continue_jump();
    virtual void do_slap();
    virtual void do_teleport();
    virtual void do_stop_teleport();
    virtual void do_stop_vertical_jump();
    virtual void do_look_upward();
    virtual void do_continue_look_upward();
    virtual void do_stop_look_upward();
    virtual void do_continue_crouch();
    virtual void do_crouch();
    virtual void do_stop_crouch();
    virtual void captive();
    virtual void release();
    virtual void do_start_throw();
    virtual void do_start_change_object();
    virtual void do_stop_throw();
    virtual void do_injured();
    virtual void do_finish_injured();

  protected:
    /** \brief The instance of Player. */
    const player_proxy m_player_instance;

  }; // class state_player
} // namespace tunnel

#endif // __TUNNEL_STATE_PLAYER_HPP__





