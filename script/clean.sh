#!/bin/bash

FLAGS="-s -f make/main.mk DELETE_RESOURCE_FILES=0"

CLEAN="clean $FLAGS"
make $CLEAN
