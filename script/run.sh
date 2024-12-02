#!/bin/bash

if [ "$OS" == "Windows_NT" ]; then
  ./binary/windows/SimpleGameEngine.exe
elif [ "$(uname)" == "Linux" ]; then
  ./binary/linux/SimpleGameEngine.out
else
  echo "Unsupported OS"
fi
