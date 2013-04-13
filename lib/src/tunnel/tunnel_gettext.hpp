/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief Macro to call gettext on the roller painting text domain.
 * \author Julien Jorge
 */
#ifndef __TUNNEL_GETTEXT_HPP__
#define __TUNNEL_GETTEXT_HPP__

#include <libintl.h>

#define tunnel_gettext(s) dgettext( "tunnel", (s) )

#endif // __TUNNEL_GETTEXT_HPP__
