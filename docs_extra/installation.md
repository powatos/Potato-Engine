@page installation Installation

# Installing Potato Engine

This page convers installation of the Potato Engine

@remark Potato Engine is currently under development and this page is subject to change

## CMake Setup

Ensure CMake is installed and updated to the latest version
```bash
cmake --version
```
<em>
if command not found or version is less than 3.24, continue with the next steps
</em>

<br>

* [Linux](#linux)
* [Windows](#windows)
* [MacOS](#macos)

### Linux
```bash
sudo apt update
sudo apt install -y cmake
cmake --version
```
<em>
if version is less than 3.24, continue with the next steps
</em>

<br>

```bash
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
```
<em>
if cmake is still not updated to a version after 3.24, get help at <a href="https://cmake.org">cmake.org</a>
</em>

### Windows
```powershell
# install cmake
winget install kitware.cmake
cmake --version
```
<em>
if cmake is still not updated to a version after 3.24, get help at <a href="https://cmake.org">cmake.org</a>
</em>

### MacOS
```bash
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

# if this command outputs any version, cmake is installed
cmake --version 

# if cmake is already installed:
brew upgrade cmake

# if cmake is not installed:
brew install cmake
```

## Project Setup
Once CMake is installed, setup the project by creating a `CMakeLists.txt` file in the root directory. Ensure the case matches exactly.

Add configurations
```CMake
project(myGame CXX)

# This can be any version above the engine version (3.24)
cmake_minimum_required(VERSION 3.24)

# This can be any version above the engine version (C++17)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# include the engine module
include(FetchContent)
FetchContent_Declare(
    PotatoEngine
    GIT_REPOSITORY https://github.com/powatos/Potato-Engine.git
    GIT_TAG v1.0-alpha # change to your version preference
)
FetchContent_MakeAvailable(PotatoEngine)

# Ensure all game code is captured under SOURCES (assumes root/src/...)
file(GLOB_RECURSE SOURCES 
    "src/*.h"
    "src/*.hpp"
    "src/*.cpp"
)

# Ensure the executable name matches the other references
add_executable(myGameExec ${SOURCES})

# Include the source directory for header files (assumes root/src/...)
target_include_directories(myGameExec PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)


# Link libraries to the game
target_link_libraries(myGameExec PRIVATE PotatoEngine::PotatoEngine)
```

## Engine externals
After configuring CMake, setup the external directories.
@remark This section is under development

#### Log folder
Create a directory in the project root: `logs/`  
Create the default log file: `logs/debug.log`

#### Data folder
Create a directory in the project root: `Data/`  
Create the textures folder: `Data/Textures/` (texture files can be placed here)


## Build configuration
After setting up your project, build the setup files.

Configure the build files every time a change is made to the CMakeLists.txt file or the project directory structure is changed (file additions, removals, moves)
```bash
cmake -B build -S .
```
Build the game files every time a change is made to your code
```bash
cmake --build build
```

## Engine coupling
Include game files
```cpp
#include <Core/PotatoEngine.hpp>
#include <Debug/Debug.hpp>

int main()
{
    PotatoEngine& engine = PotatoEngine::Get();
    LOG_DEFAULT(LogType::INFO, "Engine object has been constructed");
    // ...

    return 0;
}
```

For more detailed information, continue to the next section: [Setting Up Your Game](setup.html)

## Extra

Build scripts are reccommended to enhance development:
```bash
#!/bin/bash

GAME_TARGET=myGame # replace with your target executable 

OBJDIR=build/
LOGFILE=logs/debug.log

SCRIPT=$(basename "$0")
CBTYPE=${2:-Debug}

case "$1" in
    "conf") # ./game.sh conf Debug|Release, generate build files
        cmake -B $OBJDIR -DCMAKE_BUILD_TYPE=$CBTYPE
        echo "Rebuild complete"
        ;;
    "build"|"b") # ./game.sh build|b, build project
        cmake --build $OBJDIR
        echo "Build complete"
        ;;
    "run"|"r") # ./game.sh run|r, run game
        if  [[ -f $OBJDIR/$GAME_TARGET ]]; then
            ./$OBJDIR/$GAME_TARGET
        else
            echo "Invalid game target"
            exit 1
        fi
        ;;
    "clean"|"-c") # ./game.sh clean|-c, reset build
        rm -rf $OBJDIR
        echo "Cleaned up binaries"
        ;;
    "flush"|"-f") # ./game.sh flush|-f, flush log file
        > $LOGFILE
	    echo "Flushed $LOGFILE"
        ;;
    *)
        echo "Invalid argument"
        exit 1
        ;;

esac
```
<em>
Build script in <code>./game.sh</code> used for automating building procedures.  
Ensure the script is runnable before using: <code>chmod +x game.sh</code> (may have to git bash on windows)
</em>