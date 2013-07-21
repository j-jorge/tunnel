#!/bin/sh

rm -f CMakeCache.txt

. tunnel/build-scripts/version.sh

do_build() {

    CMAKE_ARGS="$@"
    . tunnel/build-scripts/windows-build.sh

    cp "$COMMON_LIBRARIES_DIR/"* "$INSTALL_PREFIX/bin/"
} # do_build

VERSION=${TUNNEL_VERSION}

do_build

cp tunnel/release/installer-files/* "$INSTALL_PREFIX"

makensis "$INSTALL_PREFIX/tunnel.nsi"
cp "$INSTALL_PREFIX"/tunnel.exe tunnel_$VERSION.exe

wine mingw32-make uninstall
rm -fr "$INSTALL_PREFIX"
