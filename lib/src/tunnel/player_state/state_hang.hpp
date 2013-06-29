/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief The class describing the state where the player is hanged.
 * \author Sebastien Angibaud
 */
#ifndef __TUNNEL_STATE_HANG_HPP__
#define __TUNNEL_STATE_HANG_HPP__

#include "tunnel/player_state/state_player.hpp"

namespace tunnel
{
  /**
   * \brief The class describing a state where the player is hanged.
   * \author Sebastien Angibaud
   */
  class state_hang : public state_player
  {
  public:
    /** \brief The type of the parent class. */
    typedef state_player super;

  public:
    state_hang(const player_proxy& player);

    virtual std::string get_name() const;

    virtual void do_slap();
    virtual void do_move_right();
    virtual void do_move_left();
    virtual void do_start_throw();
  }; // class state_hang
} // namespace tunnel

#endif // __TUNNEL_STATE_HANG_HPP__
