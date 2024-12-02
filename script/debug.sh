#!/bin/bash

if [ "$OS" == "Windows_NT" ]; then
  gdb -tui ./binary/windows/SimpleGameEngine.exe
elif [ "$(uname)" == "Linux" ]; then
  gdb -tui ./binary/linux/SimpleGameEngine.out
else
  echo "Unsupported OS"
fi
