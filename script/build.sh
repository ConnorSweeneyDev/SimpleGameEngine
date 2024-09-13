#!/bin/bash

CPU_COUNT_MULTIPLIER=$(python3 -c 'import multiprocessing as mp; print(int(mp.cpu_count() * 1.5))')
FLAGS="-s -f make/main.mk -j $CPU_COUNT_MULTIPLIER DEBUG=1"

UTILITY="utility $FLAGS"
PREPARE="prepare $FLAGS"
BUILD="build $FLAGS"
make $PREPARE && make $BUILD
