#!/bin/bash
#

source $STEAMLINK_HOME/setenv.sh

qmake
make $MAKE_J || exit 2
make install INSTALL_ROOT=$PWD/build

