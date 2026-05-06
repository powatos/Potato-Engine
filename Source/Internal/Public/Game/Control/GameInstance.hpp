#pragma once

#include <functional>
#include <type_traits>

// #include "Game/Actors/Player.hpp"
#include "PlayerController.hpp"
#include "Core/EngineSubsystem.hpp"

class Player;
class World;

#define SET_DEFAULT_SUBCLASS(def, set) \
static struct __##set##_DEFAULT_SUBCLASS_REGISTER { \
    __##set##_DEFAULT_SUBCLASS_REGISTER() { \
        DEFAULT_INSTANTIATORS::get_##def() = []() -> def* { return new set(); }; \
    } \
} __##set##_DEFAULT_SUBCLASS_REGISTER_i;


class GameInstance : public IEngineSubsystem
{
public:
    [[maybe_unused]] static GameInstance* get();
    virtual void Resolve() noexcept override;

    void LoadSubobjects();

    World* GetWorld() const;

    PlayerController* GetPlayerController() const;

    bool isMainTickRunning;


private:
    GameInstance();
    ~GameInstance();
    GameInstance(const GameInstance&) = delete;
    GameInstance& operator = (const GameInstance&) = delete;
    GameInstance(GameInstance&&) = delete;
    GameInstance& operator = (GameInstance&&) = delete;

protected:

    PlayerController* ActivePlayerController;

    World* world;

};

namespace DEFAULT_INSTANTIATORS {
    inline std::function<Player*()>& get_Player() {
        static std::function<Player*()> f;
        return f;
    }
    inline std::function<PlayerController*()>& get_PlayerController() {
        static std::function<PlayerController*()> f;
        return f;
    }
}