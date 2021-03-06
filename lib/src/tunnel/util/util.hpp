/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Utility functions about tunnel.
 * \author Sébastien angibaud
 */
#ifndef __TUNNEL_UTIL_HPP__
#define __TUNNEL_UTIL_HPP__

#include "engine/base_item.hpp"

namespace tunnel
{
  /**
   * \brief Utility functions about tunnel.
   * \author S�bastien angibaud
   */
  namespace util
  {
    void send_start_level( const std::string& filename );
    void send_quit_level( const std::string& filename );
    void send_complete_level( const std::string& filename );
    void send_die_level( const std::string& filename );
    void send_version();
  } // namespace util

} // namespace tunnel

#endif // __TUNNEL_UTIL_HPP__
