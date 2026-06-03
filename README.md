# Potato Engine

**Potato Engine is currently in development**

Potato Engine is a lightweight terminal based game engine designed for C++ development. This was inspired by Unreal Engine and initiated for the [2026 Horizons Hackathon](https://horizons.hackclub.com).

View insallation instructions [here](https://powatos.github.io/Potato-Engine/installation.html).

## Documentation
Potato Engine is fully documented (in development) using [Doxygen 1.17.0](https://www.doxygen.nl/). View the API Reference below.

[API Reference](https://powatos.github.io/Potato-Engine/)

## Horizons Information
Potato Engine is a game engine designed to be linked to external projects using CMake's `FetchContent` module. Installation instructions can be found in the project's [API Reference](https://powatos.github.io/Potato-Engine/installation.html). 

**Important: Developers link against each release *tag*** via CMake, not via traditional library includes.

The engine is still under development for Windows and MacOS. However, CI pipelines are executed for all three systems: [Github Actions workflow file](/.github/workflows/verify-compatibility.yml)    
*Workflow was produced with the help of generative AI*

## Declaration of AI Usage
Generative AI was used for the following purposes. All other code/logic authored by [@powatos](https://github.com/powatos).

* Repetitive code automation (ex. [input enum values](/Source/Internal/Public/Core/Input/Input.hpp))
* Code documentation with Doxygen
* CMake setup
* ~~vcpkg deployment~~
* CI + Project deployment (ex. Github Pages, Github Actions)
* Scripting for workflow/environment automation
* Timing game loop

## Third-Party Modules
The following modules are utilized by Potato Engine:
* [json](https://github.com/nlohmann/json) by nlohmann
* [{fmt}](https://github.com/fmtlib/fmt)

## Limitations
As a single-threaded terminal engine, there are a few limitations. Consider reviewing these before starting a project:

* Concurrency support is not built into the engine. Custom parallel operations could be made, but the engine is not fully thread-safe.
* Terminal input only handles the currently pressed key. This makes simultaneous input handling impossible to implement. Continuous key holds are also difficult to recognize (more info [here](ms_repeat_threshold)). TODO: fix link
* Terminal window settings aren't standardized and can vary based on OS and environment. Currently, the game is restricted to a 24 row x 80 col window
* Currently, only single-char actor textures are supported
