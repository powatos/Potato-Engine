@page tutorial Tutorial

# Tutorial: Lazer Assault
This page showcases the engine with a tutorial for a simple lazer obstacle game.

The tutorial project was developed on Windows using MSVC. The full project repo can be found at [LazerAssaultv2](https://github.com/powatos/LazerAssaultv2)

## Game Overview

* %Player can move around in a terminal sized world
* Vertical and horizontal lazers appear, damaging the player
* Lazers flicker 3 times before firing to allow player time to dodge
* Game is over when player health reaches 0
* Score is tracked by waves completed
* Score is displayed on screen
* Health is displayed on screen

## Project setup
To get started, create a folder for the game. This example uses `Documents/LazerAssault`. Open the folder in a code editor and initialize the project:

`src/main.cpp` (empty entrypoint for now)  
`CMakeLists.txt` (following the **template**)  
`game.bat` (downloaded from the release page)  

## Game setup
Initialize the engine with desired settings:
```cpp
#include <Core/PotatoEngine.hpp>
#include <Core/Control/GameInstance.hpp>
#include <Core/Data/PersistentLevel.hpp>

// incl

int main()
{
    auto& engine = PotatoEngine::Get();
    engine.LoadSubclasses();

    auto* gameInstance = GameInstance::Get();

    gameInstance->FRAMES_PER_SECOND = 24.f;
    gameInstance->MS_REPEAT_THRESHOLD = 195;

    PersistentLevel level("save.json");
    level.LoadStaticActors();

    // Custom world settings
    auto* world = gameInstance->GetWorld();
    world->Settings.doGravity = false;
    world->Settings.clipAllowed = 0.f;
    world->Settings.Size = Vector2(80,24); // terminal window size

    auto* HUDController = engine.GetHUDController();
    // add widget later

    auto* PC = gameInstance->GetPlayerController();
    auto* player = PC->GetPlayer();

    // Custom player settings
    player->ctex = 'X';
    player->SetUsingCTex(true);
    player->SetSize(Vector2(1,1));

    engine.BeginPlay();
    engine.Resolve();

    return 0;
}
```

## Character Controller

Playing the game (via `game.bat conf` `game.bat b` `game.bat r`) will result in irregular player movement. Gravity is disabled, but the default player controller uses acceleration driven movement. We will implement our own player controller to override this.

Create a custom player controller class: `src/CharacterController.hpp`, `src/CharacterController.hpp`  
```h
// CharacterController.hpp
#pragma once

#include <Game/Control/PlayerController.hpp>

class CharacterController : public PlayerController // inherit from the default player controller
{
public:
    CharacterController();
    
    void SetupInputBindings() override; // override to change default movement binds

private:
    float moveSpeed;

    // implement custom movement logic
    void moveup();
    void movedown();
    void moveright();
    void moveleft();
};
```
```cpp
// CharacterController.cpp

#include <Core/PotatoEngine.hpp>
#include <Core/Control/GameInstance.hpp>
#include <Core/Input/InputController.hpp>

#include "CharacterController.hpp"

// Override the PlayerController subclass with our own custom class
SET_DEFAULT_SUBCLASS(PlayerController, CharacterController)

CharacterController::CharacterController() {
    moveSpeed = 1.f;
}

void CharacterController::SetupInputBindings() {

    auto InputController = PotatoEngine::Get().GetInputController();

    // Register the bindings for each key
    InputController->RegisterInputBinding({
        InputBinding(Keycode::W, InputType::Impulse, "moveup", this, &CharacterController::moveup),
        InputBinding(Keycode::A, InputType::Impulse, "moveleft", this, &CharacterController::moveleft),
        InputBinding(Keycode::S, InputType::Impulse, "movedown", this, &CharacterController::movedown),
        InputBinding(Keycode::D, InputType::Impulse, "moveright", this, &CharacterController::moveright)
    });

}

// Custom movement logic; adds to position vector based on input
void CharacterController::moveup() {
    GetPlayer()->AddLocalOffset(Vector2::Up() * moveSpeed);
}
void CharacterController::moveleft() {
    GetPlayer()->AddLocalOffset(-Vector2::Right() * moveSpeed);
}
void CharacterController::movedown() {
    GetPlayer()->AddLocalOffset(-Vector2::Up() * moveSpeed);
}
void CharacterController::moveright() {
    GetPlayer()->AddLocalOffset(Vector2::Right() * moveSpeed);
}
```
Upon building and running the program, the player will be able to move across the screen using WASD. However, moving halfway across the screen will cause the camera to follow the player. To prevent this, update the controller constructor:
```cpp
CharacterController::CharacterController() {
    moveSpeed = 1.f;
    CameraFollowsPlayer = false; // disable camera follow
}
```
## Gamemode
Handling the lazers requires a custom gamemode override. Create the custom class: `src/LazerAssaultGM.hpp`, `src/LazerAssaultGM.cpp`

```h
#pragma once

#include <Core/Control/Gamemode.hpp>

class LazerAssaultGM : public Gamemode
{
public:
    void BeginPlay() override;
    
private:
    void StartWave();
    // functions made later declared here
};
```
When the game begins, a 3 second delay will be enforced to wait for the player to get comfortable with the movement.
```cpp
// LazerAssaultGM.cpp

#include <Util/TimerManager.hpp>
#include <Core/Control/GameInstance.hpp>

#include "LazerAssaultGM.hpp"

// Override the default gamemode with the custom class
SET_DEFAULT_SUBCLASS(Gamemode, LazerAssaultGM)

void LazerAssaultGM::BeginPlay() {
    auto timerManager = TimerManager::Get();

    timerManager->AddTimer(
        "gameStartDelay",
        3.0,
        this,
        &LazerAssaultGM::StartWave
    );

}
```
A vector will be used to keep track of the lazers being used. Every wave, another lazer will be added to the list to increase difficulty. For the purposes of this game, a lazer will simply be a `Block` with a width of 1.
```h
// LazerAssaultGM.hpp

class Block;

// ...

private:
    std::vector<Block*> lazerList;

    void SpawnLazer();

// ...
```
```cpp
// LazerAssaultGM.cpp

#include <Game/Actors/Block.hpp>

// ...

void LazerAssaultGM::SpawnLazer() {
    auto world = GameInstance::Get()->GetWorld();

    auto lazer = world->SpawnActor<Block>();
    lazer->SetMovability(ActorMovability::Static);
    lazer->SetSimulatingPhysics(false);
    lazer->SetSize( Vector2(100, 1) );
    lazer->SetVisibility(false);
    lazer->SetCollisionType(CollisionType::None);
    
    lazerList.push_back(lazer);

}
```
When the wave starts, all lazers are randomly assigned horizontal/vertical and a position to flash.
```cpp
// LazerAssaultGM.cpp

void LazerAssaultGM::StartWave() {
    SpawnLazer();

    for (auto lazer : lazerList) {
        bool b = GameplayHelper::RandomBool(); // horizontal or vertical
        if (b) {
            // horizontal

            lazer->ctex = '-'; // set texture to repeat horizontally
            lazer->SetSize( Vector2(100,1) );
            lazer->SetPosition(Vector2(0, GameplayHelper::RandomInt(0,23)));
        } else {
            // vertical

            lazer->ctex = '|'; // set texture to repeat vertically
            lazer->SetSize( Vector2(1,100) );
            lazer->SetPosition(Vector2(GameplayHelper::RandomInt(0,80), 23));
        }
    }

}
```
Lazers are randomly positioned somwhere on the left-most column (if horizontal) or the top-most row (if vertical). All lazers extend 100 units right (if horizontal) or down (if vertical).

Next, the lazers flash 3 times on/off before activation to warn the player of their positions. There must be a visible delay before each flash, so a timer will be used again. Since the timer doesn't halt execution, but calls a function when complete, The flash must be recursive in nature.
```h
// LazerAssaultGM.hpp

// ...

private:
    float flashDelay; // add a variable to change the delay between flashes

    void FlashLazers(int currentIteration, const int totalIterations, bool bOn);

// ...
```
```cpp
// LazerAssaultGM.cpp

void LazerAssaultGM::FlashLazers(int currentIteration, const int totalIterations, bool bOn) {

    if (currentIteration >= totalIterations) {
        // flashes complete
        // TODO: Activate lazers
    }

    for (auto lazer : lazerList) {
        lazer->SetVisibility(bOn);
    }

    bOn = !bOn;
    currentIteration++;
    
    auto timerManager = TimerManager::Get();
    timerManager->AddTimer("flash",
        flashDelay,
        this,
        &LazerAssaultGM::FlashLazers,
        currentIteration, totalIterations, bOn
    );

}
```
Call the flash function initially in `StartWave()`
```cpp
// LazerAssaultGM.cpp

// ...

// at the end of StartWave(): 
auto timerManager = TimerManager::Get();
timerManager->AddTimer(
    "initFlash",
    flashDelay,
    this,
    &LazerAssaultGM::FlashLazers,
    0, 7, true
);
```
Lastly, initialize `flashDelay` in a constructor:
```cpp
// LazerAssaultGM.cpp

LazerAssaultGM::LazerAssaultGM() {
    flashDelay = 0.1f;
}
```
Upon running the game, the lazer starts flashing indefinitely. To fix this, the activation logic must be implemented and exit the recursive flash.
```h
// LazerAssaultGM.hpp

// ...

private:
    void ActivateLazers();

// ...
```
Upon activation, each lazer should check for a collision with the player, damaging them if so
```cpp
// LazerAssaultGM.cpp

void LazerAssaultGM::ActivateLazers() {
    auto player = GameInstance::Get()->GetPlayerController()->GetPlayer();

    for (auto lazer : lazerList) {
        if (GameplayHelper::IsActorOverlapping(player, lazer)) {
            player->TakeDamage(10);
        }
    }
    
}
```
Then, make the lazers activate when the flash is complete:
```cpp
// LazerAssaultGM.cpp

// At the top of FlashLazers():
if (currentIteration >= totalIterations) {
    ActivateLazers();
    return;
}

// ...
```
Lastly, the lazers have to increment, reset, and have a delay before starting the next wave.
```h
// LazerAssaultGM.hpp

// ...

private:
    void EndWave();

// ...
```
```cpp
// LazerAssaultGM.cpp

void LazerAssaultGM::EndWave() {

    for (auto lazer : lazerList) {
        lazer->SetVisibility(false);
    }

    // Increment happens on wave start

    auto timerManager = TimerManager::Get();
    timerManager->AddTimer(
        "waveDelay",
        2.0,
        this,
        &LazerAssaultGM::StartWave
    );

}
```
Call `EndWave()` after checking for collisions with a short delay
```cpp
// LazerAssaultGM.cpp

// ...

// At the end of ActivateLazers():
auto timerManager = TimerManager::Get();
timerManager->AddTimer(
    "waveEndDelay",
    1.0,
    this,
    &LazerAssaultGM::EndWave
);
```
## Score Display
Now that the player can be damaged, the user should know their current health and their score. A custom UI can be made to do that.

Create a custom UI object `src/InfoDisplay.hpp`, `src/InfoDisplay.cpp`
```h
// InfoDisplay.hpp

#pragma once

#include <UI/Widgets/Widget.hpp>

class InfoDisplay : public Widget
{
    // All widgets must use this constructor overload
    InfoDisplay(std::string UID);

public:
    void TickPostUpdate(float dt) override;
    
};
```
`TickPostUpdate()` occurs each tick after the main update loop is complete, including the collision check between the lazer and player. Updating the UI in this tick ensures that it displays the most current information (information that happened on the same tick)

Start by initializing the text fields for the score and health
```cpp
// InfoDisplay.cpp

#include "InfoDisplay.hpp"

InfoDisplay::InfoDisplay(std::string UID) : Widget(UID) {

    auto healthDisplay = AddElement<TextElement>("healthDisplay");
    auto scoreDisplay = AddElement<TextElement>("scoreDisplay");

    // Screen positions originate from the top-left of the widget
    healthDisplay->SetScreenPosition(Vector2(0,0));
    scoreDisplay->SetScreenPosition(Vector2(0,1));

    healthDisplay->SetVisibility(true);
    scoreDisplay->SetVisibility(true);

    // add 2 to the Y-size for border padding
    SetScreenSize(Vector2(20,4));
    SetScreenPosition(Vector2());

    SetVisibility(true);
}

void InfoDisplay::TickPostUpdate(float dt) {
    // TODO
}
```
Now, the elements can be updated every tick
```cpp
// InfoDisplay.cpp

void InfoDisplay::TickPostUpdate(float dt) {
    auto gameInstance = GameInstance::Get();
    auto player = gameInstance->GetPlayerController()->GetPlayer();

    auto gm = dynamic_cast<LazerAssaultGM*>(gameInstance->GetGamemode());

    auto healthDisplay = dynamic_cast<TextElement*>(GetElement("healthDisplay"));
    auto scoreDisplay = dynamic_cast<TextElement*>(GetElement("scoreDisplay"));

    // nullptr check
    if (!(healthDisplay && scoreDisplay && gm)) { return; }

    float health = player->GetHealth();
    int score = 0; // TODO

    healthDisplay->field = "Health: " + std::to_string(health);
    scoreDisplay->field = "Score: " + std::to_string(score);
}

```
Lastly, create the widget:
```cpp
// main.cpp

#include <UI/HUDController.hpp>
#include "InfoDisplay.hpp"

// ...

IHUDController* HUDController = engine.GetHUDController();
HUDController->AddWidget<InfoDisplay>("main info display");

// ...

```

## Score
The score updates every time a wave is complete. Add the variable and expose it so the UI can read it in `LazerAssaultGM`:
```h
// LazerAssaultGM.hpp

// ...
public:
    int GetScore() const;

private:
    int score;

// ...
```
```cpp
// LazerAssaultGM.cpp

LazerAssaultGM::LazerAssaultGM() {
    flashDelay = 0.2f;
    score = 0;
}

int LazerAssaultGM::GetScore() const {
    return score;
}

// In EndWave():
score++;

// ...
```
```cpp
// InfoDisplay.cpp

void InfoDisplay::TickPostUpdate(float dt) {
    auto gameInstance = GameInstance::Get();
    auto player = gameInstance->GetPlayerController()->GetPlayer();

    auto gm = dynamic_cast<LazerAssaultGM*>(gameInstance->GetGamemode());

    auto healthDisplay = dynamic_cast<TextElement*>(GetElement("healthDisplay"));
    auto scoreDisplay = dynamic_cast<TextElement*>(GetElement("scoreDisplay"));

    // nullptr check
    if (!(healthDisplay && scoreDisplay && gm)) { return; }

    float health = player->GetHealth();
    int score = gm->GetScore();

    healthDisplay->field = "Health: " + std::to_string(health);
    scoreDisplay->field = "Score: " + std::to_string(score);
}
```
## End game
When the player health reaches 0, the game should end.
```h
// LazerAssaultGM.hpp

// ...

private:
    void damagePlayer();

// ...
```
```cpp
// LazerAssaultGM.cpp

// ...

void LazerAssaultGM::damagePlayer() {
    auto gameInstance = GameInstance::Get();
    auto player = gameInstance->GetPlayerController()->GetPlayer();

    player->TakeDamage(10);
    if (player->GetHealth() <= 0.f) {
        gameInstance->RequestShutdown();
    }
}

// In ActivateLazers():
for (auto lazer : lazerList) {
    if (GameplayHelper::IsActorOverlapping(player, lazer)) {
        damagePlayer();
    }
}

// ...
```