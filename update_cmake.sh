#!/bin/bash
set -e

sudo apt remove cmake -y
sudo apt update

# install kitware
sudo apt install -y software-properties-common wget gpg
wget -O - https://apt.kitware.com/keys/kitware-archive-latest.asc 2>/dev/null | gpg --dearmor - | sudo tee /usr/share/keyrings/kitware-archive-keyring.gpg > /dev/null

# add to sources file
echo "deb [signed-by=/usr/share/keyrings/kitware-archive-keyring.gpg] https://apt.kitware.com/ubuntu/ $(lsb_release -cs) main" | sudo tee /etc/apt/sources.list.d/kitware.list > /dev/null

# install cmake
sudo apt update
sudo apt install -y cmake

cmake --version