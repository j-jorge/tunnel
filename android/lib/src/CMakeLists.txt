cmake_minimum_required(VERSION 2.6)
project(tunnel-android-launcher)

set( TUNNEL_ANDROID_LAUNCHER_TARGET_NAME libtunnel.so )

include_directories( . ${BEAR_ENGINE_INCLUDE_DIRECTORY} )

add_custom_command(
  OUTPUT ${TUNNEL_ANDROID_LAUNCHER_TARGET_NAME}
  COMMAND sh make.sh
  DEPENDS tunnel
  )
