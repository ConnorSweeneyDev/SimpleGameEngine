ifeq ($(OS), Windows_NT)
  UNAME := Windows
  SHELL := /Git/bin/sh.exe
else
  UNAME := $(shell uname -s)
  SHELL := /bin/sh
endif
