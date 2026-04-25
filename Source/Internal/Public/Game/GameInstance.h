#pragma once

class World;

struct GameState
{
    GameState();

    bool isMainTickRunning;
};

class GameInstance
{

public:
    [[maybe_unused]] static GameInstance* get();

    inline GameState& GetState() { return state; }
    inline World* GetWorld() { return world; }

private:
    GameInstance();                                            // private constructor
    ~GameInstance();                                           // private destructor
    GameInstance(const GameInstance&) = delete;               // delete copy const
    GameInstance& operator = (const GameInstance&) = delete;  // delete assignment const
    GameInstance(GameInstance&&) = delete;                    // delete move const
    GameInstance& operator = (GameInstance&&) = delete;       // delete move op

    
protected:
    GameState state;
    World* world;

};

