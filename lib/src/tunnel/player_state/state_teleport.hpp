/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief The class describing the state where the player teleport.
 * \author Sebastien Angibaud
 */
#ifndef __TUNNEL_STATE_TELEPORT_HPP__
#define __TUNNEL_STATE_TELEPORT_HPP__

#include "tunnel/player_state/state_player.hpp"

namespace tunnel
{
  /**
   * \brief The class describing a state where the player teleport.
   * \author Sebastien Angibaud
   */
  class state_teleport : public state_player
  {
  public:
    /** \brief The type of the parent class. */
    typedef tunnel::state_player super;

  public:
    state_teleport(const player_proxy& player);

    virtual std::string get_name() const;
    virtual void start();
    virtual void stop();

    virtual void do_stop_teleport();
    virtual void do_teleport();

  private:
    /* \brief The initial value of normal_defensive_power. */
    bool m_initial_normal_defensive_power;
  }; // class state_teleport
} // namespace tunnel

#endif // __TUNNEL_STATE_TELEPORT_HPP__
