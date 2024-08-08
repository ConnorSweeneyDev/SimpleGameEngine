ifeq ($(OS), Windows_NT)
  UNAME := Windows
else
  UNAME := $(shell uname -s)
endif
