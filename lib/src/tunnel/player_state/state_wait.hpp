/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief The class describing the state where the player wait.
 * \author Sebastien Angibaud
 */
#ifndef __TUNNEL_STATE_WAIT_HPP__
#define __TUNNEL_STATE_WAIT_HPP__

#include "tunnel/player_state/state_player.hpp"

namespace tunnel
{
  /**
   * \brief The class describing a state where the player wait.
   * \author Sebastien Angibaud
   */
  class state_wait : public tunnel::state_player
  {
  public:
    /** \brief The type of the parent class. */
    typedef state_player super;

  public:
    state_wait(const player_proxy& player);

    virtual std::string get_name() const;

    virtual void do_move_left();
    virtual void do_move_right();
    virtual void do_look_upward();
    virtual void do_crouch();

  }; // class state_wait
} // namespace tunnel

#endif // __TUNNEL_STATE_WAIT_HPP__
