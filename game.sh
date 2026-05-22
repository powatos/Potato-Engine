#!/bin/bash

LIB_TARGET=libPotatoEngine.a
GAME_TARGET=Program

OBJDIR=Binaries/
LOGDIR=logs/debug.log

case "$1" in
    "build"|"b")
        make
        echo "Build complete"
        ;;
    "run"|"r")
        if  [[ -f $GAME_TARGET ]]; then
            ./$GAME_TARGET
        else
            echo "Invalid game target"
            exit 1
        fi
        ;;
    "clean"|"-c")
        rm -rf $OBJDIR $LIB_TARGET $GAME_TARGET
        echo "Cleaned up binaries"
        ;;
    "flush"|"-f")
        > $LOGDIR
	    echo "Flushed $LOGDIR"
        ;;
    *)
        echo "Invalid argument"
        exit 1
        ;;

esac