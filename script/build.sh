#!/bin/bash

BUILD_TYPE=Release
if [ ! -d "build" ]; then
  cmake -S . -B build -DCMAKE_BUILD_TYPE=$BUILD_TYPE
fi
cmake --build build --config $BUILD_TYPE
