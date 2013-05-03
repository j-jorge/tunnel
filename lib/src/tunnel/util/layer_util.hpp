/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief Utility functions about the layers.
 * \author Julien Jorge
 */
#ifndef __TUNNEL_LAYER_UTIL_HPP__
#define __TUNNEL_LAYER_UTIL_HPP__

#include "engine/level.hpp"

namespace tunnel
{
  namespace util
  {
    void move_tag_after_all_tags( level& lvl, std::string tag );

  } // namespace util
} // namespace tunnel

#endif // __TUNNEL_LAYER_UTIL_HPP__
