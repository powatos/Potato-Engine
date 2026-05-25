#!/bin/bash

GAME_TARGET=Program

OBJDIR=build/
LOGDIR=logs/debug.log

SCRIPT=$(basename "$0")
CBTYPE=${2:-Debug}

case "$1" in
    "conf")
        rm -rf $OBJDIR
        cmake -B $OBJDIR -DCMAKE_BUILD_TYPE=$CBTYPE
        echo "Rebuild complete"
        ;;
    "build"|"b")
        cmake --build $OBJDIR
        echo "Build complete"
        ;;
    "run"|"r")
        if  [[ -f $OBJDIR/$GAME_TARGET ]]; then
            ./$OBJDIR/$GAME_TARGET
        else
            echo "Invalid game target"
            exit 1
        fi
        ;;
    "clean"|"-c")
        rm -rf $OBJDIR
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