#!/bin/bash

CPU_COUNT_MULTIPLIER=$(python3 -c 'import multiprocessing as mp; print(int(mp.cpu_count() * 1.5))')

make external -j $CPU_COUNT_MULTIPLIER && make main -j $CPU_COUNT_MULTIPLIER
