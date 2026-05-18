/** @file GameInstance.hpp */
#pragma once

#include <functional>
#include <type_traits>

#include "PlayerController.hpp"
#include "Core/EngineSubsystem.hpp"

class Player;
class World;

/**
 * @def SET_DEFAULT_SUBCLASS(def, set)
 * @relates GameInstance
 * @brief Registers classes as the default subobject for its class
 * @details Default subobjects are managed by the engine, but custom overrides can be made
 * by inheriting from the base.
 * @remark Call this macro at the top of the source file to set as default
 * @warning Trying to set multiple classes as the default for a subclass is undefined behaviour,
 * as the macro utilizes static struct instantiation which is prone to the [static initialization
 * order fiasco](https://en.cppreference.com/cpp/language/siof)
 */
#define SET_DEFAULT_SUBCLASS(def, set) \
static struct __##set##_DEFAULT_SUBCLASS_REGISTER { \
    __##set##_DEFAULT_SUBCLASS_REGISTER() { \
        __DEFAULT_INSTANTIATORS::get_##def() = []() -> def* { return new set(); }; \
    } \
} __##set##_DEFAULT_SUBCLASS_REGISTER_i;

/**
 * @brief Singleton with various game properties and functions. This class also manages game subobjects
 * @details Set global constants and get objects using the @ref get() "instance". \n Subclasses must be registered 
 * using @ref SET_DEFAULT_SUBCLASS(def, set) "SET_DEFAULT_SUBCLASS".
 */
class GameInstance : public IEngineSubsystem
{
public:
    /**
     * @brief Gets singleton instance
     * @returns instance
     */
    static GameInstance* get();
    virtual void Resolve() noexcept override;

    void LoadSubobjects();

    /** @brief Gets @ref World "world" object @returns @ref World "World" object */
    World* GetWorld() const;
    /** @brief Gets @ref PlayerController "player controller" object @returns @ref PlayerController "player controller" object */
    PlayerController* GetPlayerController() const;

    // TODO: make requestshutdown function instead of property

    /**
     * @brief State of game loop
     * @details Set to false to queue engine shutdown immediately
     */
    bool isMainTickRunning;
    /**
     * @brief Global FPS constant for screen refresh
     * @note Reassignment after global @ref PotatoEngine::BeginPlay "BeginPlay" has no affect on refresh rate
     */
    float FRAMES_PER_SECOND;
    /**
     * @brief Threshold to wait for input completion in milliseconds
     * @details Terminal limitations make @ref InputType "input states" difficult to implement.
     * A delay is used to wait for marking an input as complete. Higher values will make
     * state based movement more smooth, but increase latency. Lower values will decrease smoothness
     * but maximize input delay. A value of `195` is recommended for the optimal smoothness-to-latency ratio
     * @warning A value of `0` will remove input state logic and minimize latency. However, 
     * inputs binded to states other than InputType::Triggered will never be fired
     * @note This setting also affects boolean input latency (single button press).
     */
    int MS_REPEAT_THRESHOLD;

private:
    GameInstance();
    ~GameInstance();
    GameInstance(const GameInstance&) = delete;
    GameInstance& operator = (const GameInstance&) = delete;
    GameInstance(GameInstance&&) = delete;
    GameInstance& operator = (GameInstance&&) = delete;

private:

    PlayerController* ActivePlayerController;
    World* world;

};

namespace __DEFAULT_INSTANTIATORS {
    inline std::function<Player*()>& get_Player() {
        static std::function<Player*()> f;
        return f;
    }
    inline std::function<PlayerController*()>& get_PlayerController() {
        static std::function<PlayerController*()> f;
        return f;
    }
}