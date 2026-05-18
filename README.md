# Potato-Engine

**Potato Engine is currently in development**

Potato Engine is a lightweight terminal based game engine designed for C++ development. Inspired by Unreal Engine, this SDK is easy to get started with and highly customizable.

## Limitations
As a single-threaded terminal engine, there are a few limitations. Consider reviewing these before starting a project:

* Concurrency support is not built into the engine. Custom parallel operations could be made, but the engine is not fully thread-safe.
* Terminal input only handles the currently pressed key. This makes simultaneous input handling impossible to implement. Continuous key holds are also difficult to recognize (more info [here](ms_repeat_threshold)). TODO: fix link
* Terminal window settings aren't standardized and can vary based on OS and environment. Currently, the game is restricted to a 24 row x 80 col window

## Documentation
Potato Engine is fully documented (in development) using [Doxygen 1.17.0](https://www.doxygen.nl/). View the API Reference below.

[API Reference](https://powatos.github.io/Potato-Engine/)

## Declaration of AI Usage
Generative AI was used for the following purposes. All other code/logic authored by [@powatos](https://github.com/powatos).

* Code automation (ex. [input enum values](Input_8hpp_source.html)) TODO: fix link
* Documentation *setup* (doxygen)
* Project deployment (ex. Github Pages, Github Actions)
* Scripting for workflow/environment automation
* Timing game loop
