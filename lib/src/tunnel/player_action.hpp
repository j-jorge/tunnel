/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Code values of the player's actions.
 * \author Julien Jorge
 */
#ifndef __TUNNEL_PLAYER_ACTION_HPP__
#define __TUNNEL_PLAYER_ACTION_HPP__

#include <string>

namespace tunnel
{
  /**
   * \brief Code values of the player's actions.
   * \author Julien Jorge
   */
  struct player_action
  {
  public:
    /** \brief The type of the codes for the actions. */
    typedef unsigned int value_type;

  public:
    static std::string to_string( value_type a );
    static value_type from_string( const std::string& s );

  public:
    /** \brief Bad action code. */
    static const value_type action_null = 0;

    /** \brief Action code dying. */
    static const value_type die = action_null + 1;

    /** \brief Minimal value of the valid actions. */
    static const value_type min_value = die;

    /** \brief Action code: Idle. */
    static const value_type idle = die + 1;

    /** \brief Action code: Move to the left. */
    static const value_type move_left = idle + 1;

    /** \brief Action code: Move to the right. */
    static const value_type move_right = move_left + 1;

    /** \brief Action code: Jump. */
    static const value_type jump = move_right + 1;

    /** \brief Action code: Look up. */
    static const value_type look_upward = jump + 1;

    /** \brief Action code: Crouch. */
    static const value_type crouch = look_upward + 1;

    /** \brief Action code: Slap. */
    static const value_type slap = crouch + 1;

    /** \brief Action code: Create a ground. */
    static const value_type create_ground = slap + 1;

    /** \brief Action code: Create a ground. */
    static const value_type create_seed = create_ground + 1;

    /** \brief Action code: teleport. */
    static const value_type teleport = create_seed + 1;

    /** \brief Action code: captive the player. */
    static const value_type captive = teleport + 1;

    /** \brief Action code: Release player. */
    static const value_type release = captive + 1;

    /** \brief Action code: The player roar. */
    static const value_type roar = release + 1;

    /** \brief Action code: The player disappear. */
    static const value_type disappear = roar + 1;

    /** \brief Action code: The player wait. */
    static const value_type wait = disappear + 1;

    /** \brief Maximal value of the valid actions. */
    static const value_type max_value = wait;

  }; // struct player_action
} // namespace tunnel

#endif // __TUNNEL_PLAYER_ACTION_HPP__
