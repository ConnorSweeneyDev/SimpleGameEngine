#!/bin/bash

LEVEL=0
RESOURCES=0

if [ $LEVEL == 0 ]; then
  rm -rf build/SimpleGameEngine.dir
elif [ $LEVEL == 1 ]; then
  rm -rf build/SimpleGameEngine.dir
  rm -rf build/external
elif [ $LEVEL == 2 ]; then
  rm -rf build
fi

if [ $RESOURCES == 1 ]; then
  rm -f program/source/resource.cpp
  rm -f program/include/resource.hpp
fi
