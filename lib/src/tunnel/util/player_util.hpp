/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Utility functions about the players.
 * \author Julien Jorge
 */
#ifndef __TUNNEL_PLAYER_UTIL_HPP__
#define __TUNNEL_PLAYER_UTIL_HPP__

#include "engine/level_globals.hpp"
#include "tunnel/player_proxy.hpp"

namespace tunnel
{
  namespace util
  {
    std::string get_player_name( unsigned int player_index );

    player_proxy find_player
    ( const bear::engine::level_globals& glob, unsigned int player_index );

  } // namespace util
} // namespace tunnel

#endif // __TUNNEL_PLAYER_UTIL_HPP__
