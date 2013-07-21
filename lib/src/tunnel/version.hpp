/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Version of Tunnel
 * \author Julien Jorge
 */
#ifndef __TUNNEL_VERSION_HPP__
#define __TUNNEL_VERSION_HPP__

#define TUNNEL_TO_STR_BIS(v) # v
#define TUNNEL_TO_STR(v) TUNNEL_TO_STR_BIS(v)

#define TUNNEL_MAJOR_VERSION 0
#define TUNNEL_MINOR_VERSION 1
#define TUNNEL_PATCH_NUMBER 0
#define TUNNEL_VERSION_STRING "Tunnel " \
  TUNNEL_TO_STR(TUNNEL_MAJOR_VERSION) "." \
  TUNNEL_TO_STR(TUNNEL_MINOR_VERSION) "." TUNNEL_TO_STR(TUNNEL_PATCH_NUMBER)

#endif // __TUNNEL_VERSION_HPP__
