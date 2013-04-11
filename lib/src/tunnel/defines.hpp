/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief Game definess.
 * \author Julien Jorge
 */
#ifndef __TUNNEL_DEFINES_HPP__
#define __TUNNEL_DEFINES_HPP__

/** \brief The name of the level displayed when loading a level. */
#define TUNNEL_LOADING_LEVEL_NAME "level/loading.cl"

/** \brief The maximum number of points a player can receive at once. */
#define TUNNEL_MAX_POINTS_AT_ONCE 50000

/** \brief The number of points over which the player wins a new try. */
#define TUNNEL_ONE_UP_POINTS_COUNT 50000

/** \brief The maximum energy that a player can have. */
#define TUNNEL_MAXIMUM_ENERGY 200

/** \brief The name of the layer displaying the transition effects. */
#define TUNNEL_TRANSITION_EFFECT_DEFAULT_TARGET_NAME "transition_effect_layer"

/** \brief The name of the layer displaying the transition effects. */
#define TUNNEL_SCRIPT_EFFECT_DEFAULT_TARGET_NAME "script_effect_layer"

/** \brief The name of the layer displaying the balloons. */
#define TUNNEL_BALLOON_LAYER_DEFAULT_TARGET_NAME "balloon_layer"

/** \brief The name of the layer displaying the frames during the game. */
#define TUNNEL_WINDOWS_LAYER_DEFAULT_TARGET_NAME "windows_layer"

/** \brief The name of the layer displaying the informations about the
    players. */
#define TUNNEL_STATUS_LAYER_DEFAULT_TARGET_NAME "status_layer"

/** \brief The default orange color, used in gui layers. */
#define TUNNEL_ORANGE_PIXEL bear::visual::color_type(254, 160, 0, 255)

/** \brief The prefix for game variable to save. */
#define TUNNEL_PERSISTENT_PREFIX "persistent/"

/** \brief The filename for one player save. */
#define TUNNEL_SAVE_ONE_PLAYER_FILENAME "1p-game-variables.sav"

/** \brief The filename for one player save. */
#define TUNNEL_SAVE_TWO_PLAYERS_FILENAME "2p-game-variables.sav"

/** \brief The filename for one player save. */
#define TUNNEL_DEFAULT_EXIT_NAME "default"

/** \brief The name of service that dispatches first player's controls. */
#define TUNNEL_PLAYER_ACTIONS_SERVICE "player_actions"

/** \brief The color of the aura of god */
#define TUNNEL_GOD_AURA_COLOR bear::visual::color_type(255, 255, 133, 255)

/** \brief The color of the border of the aura of god */
#define TUNNEL_GOD_AURA_BORDER_COLOR bear::visual::color_type(192, 192, 100, 255)

#endif // __TUNNEL_DEFINES_HPP__
