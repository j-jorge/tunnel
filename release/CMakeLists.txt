if( WIN32 )
  install(
    FILES tunnel.ico ReadMe.txt
    DESTINATION ${CMAKE_INSTALL_PREFIX}
    PERMISSIONS OWNER_READ OWNER_WRITE
    GROUP_READ
    WORLD_READ
    )
endif()
