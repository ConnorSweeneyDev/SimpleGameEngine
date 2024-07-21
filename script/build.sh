#!/bin/bash

make external -j $(python3 -c 'import multiprocessing as mp; print(int(mp.cpu_count() * 1.5))') && make main -j $(python3 -c 'import multiprocessing as mp; print(int(mp.cpu_count() * 1.5))')
