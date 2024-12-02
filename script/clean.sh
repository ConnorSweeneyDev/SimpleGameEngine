#!/bin/bash

CLEAN_RESOURCE_SOURCE_FILES=0
FLAGS="-s -f make/main.mk CLEAN_RESOURCE_SOURCE_FILES=$CLEAN_RESOURCE_SOURCE_FILES"

CLEAN="clean $FLAGS"

if [ "$OS" == "Windows_NT" ]; then
  make $CLEAN
elif [ "$(uname)" == "Linux" ]; then
  make $CLEAN
else
  echo "Unsupported OS"
fi
