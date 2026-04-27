#pragma once

#include "Core/EngineSubsystem.hpp"

class World;

struct GameState
{
    GameState();

    bool isMainTickRunning;
};

class GameInstance : public IEngineSubsystem
{
public:
    [[maybe_unused]] static GameInstance* get();
    virtual void Resolve() noexcept override;

    inline GameState& GetState() { return state; }
    inline World* GetWorld() { return world; }

private:
    GameInstance();
    ~GameInstance();
    GameInstance(const GameInstance&) = delete;
    GameInstance& operator = (const GameInstance&) = delete;
    GameInstance(GameInstance&&) = delete;
    GameInstance& operator = (GameInstance&&) = delete;

    
protected:
    GameState state;
    World* world;

};

