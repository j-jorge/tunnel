/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief The class describing the state where the player want to clutch.
 * \author Sebastien Angibaud
 */
#ifndef __TUNNEL_STATE_START_CLING_HPP__
#define __TUNNEL_STATE_START_CLING_HPP__

#include "tunnel/player_state/state_player.hpp"

namespace tunnel
{
  /**
   * \brief The class describing a state where the player want to cling.
   * \author Sebastien Angibaud
   */
  class state_start_cling : public state_player
  {
  public:
    /** \brief The type of the parent class. */
    typedef state_player super;

  public:
    state_start_cling(const player_proxy& player);

    virtual std::string get_name() const;
    virtual void start();
    virtual void stop();

    virtual void do_slap();

  private:
    /* \brief The initial value of normal_defensive_power. */
    bool m_initial_normal_defensive_power;
  }; // class state_start_cling
} // namespace tunnel

#endif // __TUNNEL_STATE_START_CLING_HPP__
