/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief The class describing the state where the player float.
 * \author Sebastien Angibaud
 */
#ifndef __TUNNEL_STATE_FLOAT_HPP__
#define __TUNNEL_STATE_FLOAT_HPP__

#include "tunnel/player_state/state_player.hpp"

namespace tunnel
{
  /**
   * \brief The class describing a state where the player float.
   * \author Sebastien Angibaud
   */
  class state_float : public tunnel::state_player
  {
  public:
    /** \brief The type of the parent class. */
    typedef tunnel::state_player super;

  public:
    state_float(const player_proxy& player);

    virtual std::string get_name() const;
    virtual void start();
    virtual void stop();
    virtual void do_jump();
    virtual void do_crouch();
    virtual void do_continue_crouch();

  private:
    /** \brief The density of the player. */
    double m_density;
  }; // class state_float
} // namespace tunnel

#endif // __TUNNEL_STATE_FLOAT_HPP__
