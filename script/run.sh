#!/bin/bash

if [ "$OS" = "Windows_NT" ]; then
  OUTPUT=$(find . -name "SimpleGameEngine.exe")
  $OUTPUT
elif [ "$(uname)" = "Linux" ]; then
  OUTPUT=$(find . -name "SimpleGameEngine")
  $OUTPUT
else
  echo "Unsupported OS"
fi
