cmake_minimum_required(VERSION 2.6)
project(tunnel-launcher)

set( TUNNEL_LAUNCHER_TARGET_NAME tunnel-launcher )

include_directories( . ${BEAR_ENGINE_INCLUDE_DIRECTORY} )

#-------------------------------------------------------------------------------
set( TUNNEL_LAUNCHER_SOURCE_FILES
  code/launcher.cpp
  code/main.cpp
  )

add_executable( ${TUNNEL_LAUNCHER_TARGET_NAME} ${TUNNEL_LAUNCHER_SOURCE_FILES} )

set_target_properties(
  ${TUNNEL_LAUNCHER_TARGET_NAME}
  PROPERTIES
  INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/${TUNNEL_INSTALL_CUSTOM_LIBRARY_DIR}"
  )

#-------------------------------------------------------------------------------
# Get the name of a given library on the system
macro( make_library_system_name ROOT_NAME RESULT )

  if( WIN32 )
    set( ${RESULT} "lib${ROOT_NAME}.dll" )
  else()
    set( ${RESULT} "lib${ROOT_NAME}.so" )
  endif()

endmacro()

#-------------------------------------------------------------------------------

make_library_system_name(
  "bear_generic_items" GENERIC_ITEM_LIBRARY_SYSTEM_NAME
)

make_library_system_name(
  "tunnel" TUNNEL_LIBRARY_SYSTEM_NAME
  )

if( NOT CMAKE_BUILD_TYPE STREQUAL "release" )
  set(
    TUNNEL_COMPILE_DEFINITIONS
    "GENERIC_ITEMS_LIBRARY_DEBUG_PATH=${BEAR_ENGINE_LIBRARY_DIRECTORY}/${GENERIC_ITEM_LIBRARY_SYSTEM_NAME}"
    "TUNNEL_LIBRARY_DEBUG_PATH=${TUNNEL_EXECUTABLE_OUTPUT_PATH}/${TUNNEL_LIBRARY_SYSTEM_NAME}"
    "TUNNEL_DATA_DEBUG_DIRECTORY=${CMAKE_CURRENT_SOURCE_DIR}/../../data"
    )
endif()

if( TUNNEL_TEXT_DOMAIN_PATH )
  set( TUNNEL_TEXT_DOMAIN_PATH_DEF "TUNNEL_TEXT_DOMAIN_PATH=${TUNNEL_TEXT_DOMAIN_PATH}" )
endif()

if( BEAR_TEXT_DOMAIN_PATH )
  set(
    BEAR_TEXT_DOMAIN_PATH_DEF
    "BEAR_TEXT_DOMAIN_PATH=${BEAR_TEXT_DOMAIN_PATH}"
    )
endif()

if( WIN32 )
  set(
    TUNNEL_COMPILE_DEFINITIONS
    "${TUNNEL_COMPILE_DEFINITIONS}"
    "GENERIC_ITEMS_LIBRARY_PATH=${GENERIC_ITEM_LIBRARY_SYSTEM_NAME}"
    "TUNNEL_LIBRARY_PATH=${TUNNEL_LIBRARY_SYSTEM_NAME}"
    "TUNNEL_DATA_DIRECTORY=../${TUNNEL_INSTALL_DATA_DIR}"
    
    "BEAR_TEXT_DOMAIN_PATH=${CMAKE_INSTALL_PREFIX}/${TRANSLATIONS_INSTALL_DIR}"
    )
else()
  set(
    TUNNEL_COMPILE_DEFINITIONS
    "${TUNNEL_COMPILE_DEFINITIONS}"
    "GENERIC_ITEMS_LIBRARY_PATH=${CMAKE_INSTALL_PREFIX}/${BEAR_ENGINE_INSTALL_LIBRARY_DIR}/${GENERIC_ITEM_LIBRARY_SYSTEM_NAME}"
    "TUNNEL_LIBRARY_PATH=${CMAKE_INSTALL_PREFIX}/${BEAR_ENGINE_INSTALL_LIBRARY_DIR}/${TUNNEL_LIBRARY_SYSTEM_NAME}"
    "TUNNEL_DATA_DIRECTORY=${CMAKE_INSTALL_PREFIX}/${TUNNEL_INSTALL_DATA_DIR}"

    ${BEAR_TEXT_DOMAIN_PATH_DEF}
    ${TUNNEL_TEXT_DOMAIN_PATH_DEF}
    )
endif()

set_target_properties(
  ${TUNNEL_LAUNCHER_TARGET_NAME}
  PROPERTIES
  COMPILE_DEFINITIONS
  "${TUNNEL_COMPILE_DEFINITIONS}"
  )

#-------------------------------------------------------------------------------
install(
  TARGETS ${TUNNEL_LAUNCHER_TARGET_NAME}
  DESTINATION ${BEAR_ENGINE_INSTALL_EXECUTABLE_DIR}
  )

set(
  TUNNEL_LAUNCHER_LINK_LIBRARIES
  bear_engine
  ${CLAW_APPLICATION_LIBRARIES}
  )

if(WIN32)
  set(
    TUNNEL_LAUNCHER_LINK_LIBRARIES
    ${TUNNEL_LAUNCHER_LINK_LIBRARIES}
    ${SDL_LIBRARY}
    intl )
endif(WIN32)

# FIXME: it would be even better to use "sdl-config"
if(APPLE)
  set(
    TUNNEL_LAUNCHER_LINK_LIBRARIES
    ${TUNNEL_LAUNCHER_LINK_LIBRARIES}
    ${SDL_LIBRARY}
    SDLmain
    intl )
endif(APPLE)

target_link_libraries(
  ${TUNNEL_LAUNCHER_TARGET_NAME}
  ${TUNNEL_LAUNCHER_LINK_LIBRARIES}
  )
