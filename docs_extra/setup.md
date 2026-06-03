@page setup Setup

# Engine Setup

This page covers setup of the engine prior to making the game.

**Note: code examples omit header includes for visibility. See @ref header-includes "Header Includes" for more information**

@remark The engine is still under development and this page is subject to change.

TODO: includes

## Game Setup
Prior to initializing the engine, game functionality may be defined. This includes game variables, constants, functions, or class instantiations.

Only game functionality that is **independant** of engine functionality may be performed here.

```cpp

void Welcome() {
    std::cout << "Welcome to the game!" << '\n';
    std::cout << "This game is a fighting game..." << '\n';
    // ...
}

int main() {

    const std::string GAME_NAME = "Enemy fighter";
    const int GAME_VERSION = 4;

    const int NUM_ENEMIES = 3;
    
    Welcome();


    // Initialize engine
    // ...

    return 0;
}
```
<em> 
A welcome message function, as well as game constants are defined prior to initializing the engine
</em>

@anchor header-includes
## Header Includes
Potato Engine uses modular class linking. All engine classes must be included to the active code file:
```cpp
#include <Core/PotatoEngine>
#include <Game/World.hpp>
#include <Debug/Debug.hpp>
// ...
```
For all engine classes, the exact header path can be found at the top of the class page.


## Initializing the engine
The global engine object must be initialized using @ref PotatoEngine::Get "Get()", prior to any engine operations. Engine subobjects must also be loaded using @ref PotatoEngine::LoadSubobjects "LoadSubobjects()".

```cpp
PotatoEngine& engine = PotatoEngine::Get()
engine.LoadSubobjects();
```
<em>
Initializes the engine object and returns a PotatoEngine&. It is stored in the <code>engine</code> object. <code>LoadSubobjects()</code> is called.
</em>
<br>

> Ensure `PotatoEngine::Get()` is called before anything else (see [Game Setup](#game-setup) for more info)

## Instance Settings
Setup engine constants and settings using `GameInstance`.

```cpp
GameInstance* instance = GameInstance::get();

instance->FRAMES_PER_SECOND = 24.f;
instance->MS_REPEAT_THRESHOLD = 195;
```
<em>
Gets the game instance and sets the FPS and repeat threshold values
</em>

## Level Setup
@remark This is currently under developoment. It is not required to start gameplay 
Load the persistent level. Fetch dynamic actors (TODO) and load static actors into world using @ref PersistentLevel::LoadStaticActors "LoadStaticActors()".  
The save file passed in must be reoccuring (eg. `save1.json` and `save2.json` may be used interchangably for unique save states)

```cpp
PersistentLevel level("mySave.json");

level.LoadStaticActors();
```
<em>
Creates a level object associated with "mySave.json" and loads static actors.
</em>

## UI Setup
Add widgets and other UI elements using the HUDController.

```cpp
// engine declared

IHUDController* HUDController = engine.GetHUDController();

HealthBarWidget* healthBar = HUDController->AddWidget<HealthBarWidget>("healthbar");
MapWidget* minimap = HUDController->AddWidget<MapWidget>("minimap");
InventoryWidget* inventoryDisplay = HUDController->AddWidget<InventoryWidget>("inventory");
```
<em>
Adds health bar, minimap, and inventory widgets to the HUD. Note that these are placeholder classes not implemented by the engine.
</em>

## Other Game Setup
Other game settings that involve engine functionality may be performed here. This includes player setup or player controller settings.

```cpp
// instance declared

PlayerController* playerController = instance->GetPlayerController();
Player* player = playerController->GetPlayer();

player->Texture = 'P';
player->SetVisibility(false);
```
<em>
Sets the player texture to 'P' and hides the actor (prior to game start).
</em>

## Game Loop
Start the main game loop using @ref PotatoEngine::BeginPlay "BeginPlay()" and handle loop exit using @ref PotatoEngine::Resolve "Resolve()".

After starting the game loop, `Resolve()` will only be called after the loop has completed and the engine is shutting down.

```cpp
// engine declared

engine.BeginPlay();

engine.Resolve();
```
<em>
Calls <code>BeginPlay()</code> and <code>Resolve()</code> sequentially
<br>

</em>

> Ensure `Resolve()` is called prior to post-game functionality. This is vital to ensure proper memory cleanup for engine internals.

## Exit
Complete post-game operations and exit program.

Only game functionality that is **independant** of engine functionality may be performed here.

```cpp
// engine declared

void Goodbye() {
    std::cout << "Thanks for playing!";
}

int main() {
    
    // ...
    engine.Resolve()

    Goodbye();

    return 0;
}
```
<em>
After resolving engine, a goodbye message is displayed and the program returns
</em>

<br>

# Example
This is a full example of a prototype game main function
```cpp
void Welcome() {
    std::cout << "Welcome to Enemy fighter!" << '\n';
    std::cout << "This game was developed by bob." << '\n';
    std::cout << "Press enter to start...";
    std::cin.get();
}
void Goodbye() {
    std::cout << "Thanks for playing Enemy Fighter!";
    std::cout << "Support me at bob.com!";
}

int main() {

    const std::string GAME_NAME = "Enemy fighter";
    const int GAME_VERSION = 4;

    const int NUM_ENEMIES = 3;
    
    Welcome();

    PotatoEngine& engine = PotatoEngine::Get()
    engine.LoadSubobjects();

    GameInstance* instance = GameInstance::get();

    instance->FRAMES_PER_SECOND = 24.f;
    instance->MS_REPEAT_THRESHOLD = 195;

    PersistentLevel level("mySave.json"); 
    level.LoadStaticActors();

    IHUDController* HUDController = engine.GetHUDController();

    HealthBarWidget* healthBar = HUDController->AddWidget<HealthBarWidget>("healthbar");
    MapWidget* minimap = HUDController->AddWidget<MapWidget>("minimap");
    InventoryWidget* inventoryDisplay = HUDController->AddWidget<InventoryWidget>("inventory");

    PlayerController* playerController = instance->GetPlayerController();
    Player* player = playerController->GetPlayer();

    player->Texture = 'P';

    // GAME START
    engine.BeginPlay();

    engine.Resolve();
    // GAME END

    Goodbye();

    return 0;
}

```