#!/bin/bash

package="libsdl2-dev"
if !(dpkg-query -W -f='${Status}' $package 2>/dev/null | grep -q "install ok installed"); then
    echo "$package is not installed. Installing..."
    sudo apt install -y $package
fi

./binary/linux/3DGameEngine
