/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief Implementation of the main procedure.
 * \author Julien Jorge
 */
#include "launcher.hpp"

#ifdef __APPLE__
#include <SDL/SDL.h> // needed on OSX because there SDL needs to hijack 'main'
#endif

CLAW_APPLICATION_IMPLEMENT(tunnel::launcher)
