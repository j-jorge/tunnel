/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief The class describing the state where the player roar.
 * \author Sebastien Angibaud
 */
#ifndef __TUNNEL_STATE_ROAR_HPP__
#define __TUNNEL_STATE_ROAR_HPP__

#include "tunnel/player_state/state_player.hpp"

namespace tunnel
{
  /**
   * \brief The class describing a state where the player roar.
   * \author Sebastien Angibaud
   */
  class state_roar : public tunnel::state_player
  {
  public:
    /** \brief The type of the parent class. */
    typedef tunnel::state_player super;

  public:
    state_roar(const player_proxy& player);

    virtual std::string get_name() const;

    virtual void do_move_left();
    virtual void do_move_right();
    virtual void do_jump();
    virtual void do_slap();
    virtual void do_start_drop();
    virtual void do_start_throw();
  }; // class state_roar
} // namespace tunnel

#endif // __TUNNEL_STATE_ROAR_HPP__
