@page installation Installation

# Installing Potato Engine

This page convers installation of the Potato Engine.

Start by navigating to the project [releases page](https://github.com/powatos/Potato-Engine/releases) to find the latest (or preferred) release

@remark Potato Engine is currently under development and this page is subject to change

# Windows

This section covers installation on Windows operating systems.

All commands are run in a Powershell CLI, but equivalent commands can be run from cmd.

## CMake Setup
Ensure CMake is installed and updated to the latest version
```pwsh
cmake --version
```
<em>
if command not found or version is less than 3.24, continue with the next steps
</em>

</br>

```pwsh
# install cmake
winget install kitware.cmake
cmake --version
```
<em>
if cmake is still not updated to a version after 3.24, get help at <a href="https://cmake.org">cmake.org</a>
</em>

## Windows Project Setup
Follow instructions under the @ref project-setup "Project Setup section"

## Build configuration
After setting up your project, build the setup files. Scripts can be accessed via the release page.

Configure the build files every time a change is made to the CMakeLists.txt file or the project directory structure is changed (file additions, removals, moves)

```pwsh
.\game.bat conf
```

Build the game files every time a change is made to your code
```pwsh
.\game.bat build
```

*Hint: Add the script as an alias using `function game { .\game.bat $args }` to run the script easier: `game conf`, `game build`*


# Linux

This section covers installation on Linux operating systems.

All commands are in run in a bash CLI.

## CMake Setup
Ensure CMake is installed and updated to the latest version

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

## Linux Project Setup
Follow instructions under the @ref project-setup "Project Setup section"

## Build configuration
After setting up your project, build the setup files. Scripts can be accessed via the release page.

Configure the build files every time a change is made to the CMakeLists.txt file or the project directory structure is changed (file additions, removals, moves)

```bash
./game.sh conf
```

Build the game files every time a change is made to your code
```bash
./game.sh build
```

*Hint: Add the script as an alias using `alias game='./game.sh'` to run the script easier: `game conf`, `game build`*

@anchor project-setup
# Project Setup
After installing CMake, set up the project by creating a `CMakeLists.txt` file in the root directory. Ensure the case matches exactly.

Add configurations
```CMake
project(myGame CXX) # Replace with the name of your game

cmake_minimum_required(VERSION 3.24)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Specify the engine version (via github tag)
set(POTATO_ENGINE_VERSION "v2.0.0-beta") 

# include the engine module
include(FetchContent)
FetchContent_Declare(
    PotatoEngine
    URL "https://github.com/powatos/Potato-Engine/releases/tag/${POTATO_ENGINE_VERSION}/download/PotatoEngine.zip"
)
FetchContent_MakeAvailable(PotatoEngine)

# Ensure all source code is captured under SOURCES
file(GLOB_RECURSE SOURCES 
    "src/*.h"
    "src/*.hpp"
    "src/*.cpp"
)

# Ensure the executable name is consistent
add_executable(myGameExec ${SOURCES})

# Include the source directory for header files
target_include_directories(myGameExec PRIVATE src/)


# Link engine libraries to the game
target_link_libraries(myGameExec PRIVATE PotatoEngine::PotatoEngine)

# Copy default engine folders to the root (optional but reccomended)
PotatoEngineDefaults(myGameExec)
```

# Engine coupling
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

