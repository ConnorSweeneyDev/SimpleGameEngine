#!/bin/bash

CPU_COUNT_MULTIPLIER=$(nproc)
FLAGS="-s -f make/main.mk -j$CPU_COUNT_MULTIPLIER DEBUG=1"
UTILITY="utility $FLAGS"
PREPARE="prepare $FLAGS"
BUILD="build $FLAGS"

make $PREPARE && make $BUILD
