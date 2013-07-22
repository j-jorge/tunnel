/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \brief Implementation of the functions called at the begining of
 *        the game.
 * \author Sebastien Angibaud
 */
#include "tunnel/init.hpp"

#include "tunnel/defines.hpp"
#include "tunnel/controller_config.hpp"
#include "tunnel/game_variables.hpp"
#include "engine/game.hpp"
#include "engine/system/game_filesystem.hpp"
#include "engine/variable/variable.hpp"
#include "engine/resource_pool.hpp"
#include "engine/i18n/gettext_translator.hpp"
#include "engine/i18n/translator.hpp"

#include <locale>
#include <claw/logger.hpp>
#include <claw/string_algorithm.hpp>
#include <claw/configuration_file.hpp>
#include <sstream>
#include <boost/preprocessor/stringize.hpp>

/*----------------------------------------------------------------------------*/
/**
 * \brief Initialisation of the game.
 */
void init_tunnel()
{
  bear::engine::game::get_instance().set_translator
    ( bear::engine::gettext_translator( "tunnel" ) );

  srand( time(NULL) );

  tunnel::controller_config controller;
  controller.load();

  controller.save_controller_layout( 1 );
} // init_tunnel()
