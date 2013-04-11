/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief The class describing the state where the player do a clung jump.
 * \author Sebastien Angibaud
 */
#ifndef __TUNNEL_STATE_CLUNG_JUMP_HPP__
#define __TUNNEL_STATE_CLUNG_JUMP_HPP__

#include "tunnel/player_state/state_player.hpp"

namespace tunnel
{
  /**
   * \brief The class describing a state where the player do a clung jump.
   * \author Sebastien Angibaud
   */
  class state_clung_jump : public tunnel::state_player
  {
  public:
    /** \brief The type of the parent class. */
    typedef tunnel::state_player super;

  public:
    state_clung_jump(const player_proxy& player);

    virtual std::string get_name() const;

    virtual void do_jump();
  }; // class state_clung_jump
} // namespace tunnel

#endif // __TUNNEL_STATE_CLUNG_JUMP_HPP__
