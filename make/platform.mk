ifeq ($(OS), Windows_NT)
  UNAME := Windows
else
  UNAME := $(shell uname -s)
endif

ifeq ($(UNAME), Windows)
  SHELL := /Git/bin/sh.exe
else ifeq ($(UNAME), Linux)
  SHELL := /bin/sh
endif
