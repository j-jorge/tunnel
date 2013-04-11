/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief The class describing the state where the player sink.
 * \author Sebastien Angibaud
 */
#ifndef __TUNNEL_STATE_SINK_HPP__
#define __TUNNEL_STATE_SINK_HPP__

#include "tunnel/player_state/state_player.hpp"

namespace tunnel
{
  /**
   * \brief The class describing a state where the player swim.
   * \author Sebastien Angibaud
   */
  class state_sink : public tunnel::state_player
  {
  public:
    /** \brief The type of the parent class. */
    typedef tunnel::state_player super;

  public:
    state_sink(const player_proxy& player);

    virtual std::string get_name() const;

    virtual void do_look_upward();
    virtual void do_crouch();
    virtual void do_continue_look_upward();
    virtual void do_continue_crouch();
    virtual void do_jump();
    virtual void do_continue_jump();
  }; // class state_sink
} // namespace tunnel

#endif // __TUNNEL_STATE_SINK_HPP__
