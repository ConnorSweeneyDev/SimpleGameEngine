#!/bin/bash

CPU_COUNT_MULTIPLIER=$(python3 -c 'import multiprocessing as mp; print(int(mp.cpu_count() * 1.5))')

make -f make/main.mk prepare -j $CPU_COUNT_MULTIPLIER && make -f make/main.mk build -j $CPU_COUNT_MULTIPLIER
