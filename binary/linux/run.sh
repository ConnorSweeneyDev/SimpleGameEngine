#!/bin/bash

is_installed() {
    type "$1" > /dev/null 2>&1 && $1 -q $2 >/dev/null 2>&1
}
install_package() {
    echo "Installing $1"
    sudo $1 install -y $1
}

if type apt > /dev/null 2>&1; then
    PACKAGE_MANAGER="apt"
elif type yum > /dev/null 2>&1 || type dnf > /dev/null 2>&1; then
    PACKAGE_MANAGER="yum"
elif type zypper > /dev/null 2>&1; then
    PACKAGE_MANAGER="zypper"
else
    echo "Unsupported distribution"
    exit 1
fi

PACKAGE_NAME="libsdl2-dev"
if is_installed $PACKAGE_MANAGER $PACKAGE_NAME; then
    echo "$PACKAGE_NAME is already installed."
else
    if [ "$PACKAGE_MANAGER" == "apt" ]; then
        install_package apt-get
    elif [ "$PACKAGE_MANAGER" == "yum" ] || [ "$PACKAGE_MANAGER" == "dnf" ]; then
        install_package yum
    else
        echo "Unsupported distribution"
        exit 1
    fi
fi
