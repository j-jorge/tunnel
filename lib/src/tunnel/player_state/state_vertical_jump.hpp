/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief The class describing the state where the player prepare
 * a vertical jump.
 * \author Sebastien Angibaud
 */
#ifndef __TUNNEL_STATE_VERTICAL_JUMP_HPP__
#define __TUNNEL_STATE_VERTICAL_JUMP_HPP__

#include "tunnel/player_state/state_player.hpp"

namespace tunnel
{
  /**
   * \brief The class describing a state where the player jump vertically.
   * \author Sebastien Angibaud
   */
  class state_vertical_jump : public state_player
  {
  public:
    /** \brief The type of the parent class. */
    typedef state_player super;

  public:
    state_vertical_jump(const player_proxy& player);

    virtual std::string get_name() const;
    virtual void start();

    virtual void do_jump();
  }; // class state_vertical_jump
} // namespace tunnel

#endif // __TUNNEL_STATE_VERTICAL_JUMP_HPP__
