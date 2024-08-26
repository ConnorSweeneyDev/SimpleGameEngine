#!/bin/bash

CPU_COUNT_MULTIPLIER=$(python3 -c 'import multiprocessing as mp; print(int(mp.cpu_count() * 1.5))')
DEBUG=1

FILE="-f make/main.mk"
FLAGS="-j $CPU_COUNT_MULTIPLIER DEBUG=$DEBUG"
UTILITY="$FILE utility $FLAGS"
PREPARE="$FILE prepare $FLAGS"
BUILD="$FILE build $FLAGS"

make $PREPARE && make $BUILD
