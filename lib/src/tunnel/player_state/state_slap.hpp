/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief The class describing the state where the player slap.
 * \author Sebastien Angibaud
 */
#ifndef __TUNNEL_STATE_SLAP_HPP__
#define __TUNNEL_STATE_SLAP_HPP__

#include "tunnel/player_state/state_player.hpp"

namespace tunnel
{
  /**
   * \brief The class describing a state where the player slap.
   * \author Sebastien Angibaud
   */
  class state_slap : public state_player
  {
  public:
    /** \brief The type of the parent class. */
    typedef tunnel::state_player super;

  public:
    state_slap(const player_proxy& player);

    virtual std::string get_name() const;
    virtual void start();
    virtual void stop();

    virtual void do_slap();

  private:
    /* \brief The initial value of normal_defensive_power. */
    bool m_initial_normal_defensive_power;
  }; // class state_slap
} // namespace tunnel

#endif // __TUNNEL_STATE_SLAP_HPP__
