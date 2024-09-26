@ECHO OFF

set FLAGS=-s -f "make/main.mk" DELETE_RESOURCE_SOURCE_FILES=0

set CLEAN=clean %FLAGS%
make %CLEAN%
