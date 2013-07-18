cmake_minimum_required(VERSION 2.6)
project(tunnel-library)

set( LIBTUNNEL_TARGET_NAME tunnel )

include_directories( ..
  ${BEAR_ENGINE_INCLUDE_DIRECTORY}
  ${BEAR_GENERIC_ITEMS_INCLUDE_DIRECTORY}
  )

#-------------------------------------------------------------------------------
set( LIBTUNNEL_SOURCE_FILES
  code/add_ingame_layers.cpp
  code/block.cpp
  code/camera_on_player.cpp
  code/clingable.cpp
  code/controller_config.cpp
  code/controller_layout.cpp
  code/crystal.cpp
  code/door.cpp
  code/door_switch.cpp
  code/game_variables.cpp
  code/gui_command.cpp
  code/init.cpp
  code/item_picking_filter.cpp
  code/layer_border.cpp
  code/level_settings.cpp
  code/passive_enemy.cpp
  code/player.cpp
  code/player_action.cpp
  code/player_killer.cpp
  code/player_pending_action.cpp
  code/player_proxy.cpp
  code/player_stop_block.cpp
  code/spring.cpp

  layer/code/misc_layer.cpp
  layer/code/status_layer.cpp
  layer/status/code/crystal_component.cpp
  layer/status/code/energy_component.cpp
  layer/status/code/status_component.cpp

  message/code/get_player_instance.cpp

  network/message/code/player_action_message.cpp

  player_state/code/state_captive.cpp  
  player_state/code/state_cling.cpp
  player_state/code/state_clung_jump.cpp
  player_state/code/state_crouch.cpp
  player_state/code/state_dead.cpp
  player_state/code/state_fall.cpp
  player_state/code/state_float.cpp
  player_state/code/state_hang.cpp
  player_state/code/state_game_over.cpp
  player_state/code/state_idle.cpp
  player_state/code/state_injured.cpp
  player_state/code/state_jump.cpp
  player_state/code/state_look_upward.cpp
  player_state/code/state_paralyze.cpp
  player_state/code/state_player.cpp
  player_state/code/state_roar.cpp 
  player_state/code/state_run.cpp
  player_state/code/state_slap.cpp
  player_state/code/state_start_cling.cpp
  player_state/code/state_start_hang.cpp
  player_state/code/state_start_jump.cpp
  player_state/code/state_sink.cpp
  player_state/code/state_swimming.cpp
  player_state/code/state_teleport.cpp
  player_state/code/state_vertical_jump.cpp
  player_state/code/state_wait.cpp
  player_state/code/state_walk.cpp

  util/code/layer_util.cpp
  util/code/player_util.cpp
)

add_library( ${LIBTUNNEL_TARGET_NAME} SHARED ${LIBTUNNEL_SOURCE_FILES} )

set_target_properties(
  ${LIBTUNNEL_TARGET_NAME}
  PROPERTIES
  INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/${TUNNEL_INSTALL_CUSTOM_LIBRARY_DIR}"
  )

if( NOT WIN32 )
  set_target_properties(
    ${LIBTUNNEL_TARGET_NAME}
    PROPERTIES
    COMPILE_DEFINITIONS "TUNNEL_TEXT_DOMAIN_PATH=${CMAKE_INSTALL_PREFIX}/${TRANSLATIONS_INSTALL_DIR}"
    )
endif( NOT WIN32 )

if( TUNNEL_CAN_RESTART_LEVEL )
  set_target_properties(
    ${LIBTUNNEL_TARGET_NAME}
    PROPERTIES
    COMPILE_DEFINITIONS "TUNNEL_CAN_RESTART_LEVEL=1"
    )
endif( TUNNEL_CAN_RESTART_LEVEL )

install(
  TARGETS ${LIBTUNNEL_TARGET_NAME}
  DESTINATION ${TUNNEL_INSTALL_CUSTOM_LIBRARY_DIR}
  )

set(
  LIBTUNNEL_LINK_LIBRARIES
  bear_engine
  bear_generic_items
  bear_gui
  ${CLAW_CONFIGURATION_FILE_LIBRARIES}
  ${Boost_SIGNALS_LIBRARY}
  )

if(WIN32 OR APPLE)
  set(
    LIBTUNNEL_LINK_LIBRARIES
    ${LIBTUNNEL_LINK_LIBRARIES}
    intl )
endif(WIN32 OR APPLE)

target_link_libraries(
  ${LIBTUNNEL_TARGET_NAME}
  ${LIBTUNNEL_LINK_LIBRARIES}
  )
