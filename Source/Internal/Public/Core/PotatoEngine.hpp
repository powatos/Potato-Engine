/** @file PotatoEngine.hpp */

#include <memory>
#include <vector>

#include "EngineSubsystem.hpp"

class IInputController;
class EventController;
class IHUDController;

/**
 * @brief Global engine singleton class
 * @details This class manages the engine and engine subsystems. This class must be configured
 * before playing the game.
 */
class PotatoEngine // implementation in 'Internal/Private/PotatoEngine.cpp'
{
    PotatoEngine();
    ~PotatoEngine();
public:
    /**
     * @brief Global access to engine object
     * @note This class has an uppercased get method. Note that all other engine singletons have undercased get methods
     * @returns Engine reference
     */
    static PotatoEngine& Get();

    /**
     * @brief Loads all subobjects and calls corresponding initializing methods
     * @warning Must be called before BeginPlay()
     */
    void LoadSubobjects();

    /**
     * @brief Starts gameplay
     * @note Must be called to start gameplay
     */
    void BeginPlay();

    /**
     * @brief Resolve all subobjects and perform resolving engine functionality
     * @warning Must be called before exiting program
     */
    void Resolve() noexcept;

    /** @brief Gets @ref IInputController "input controller" @returns @ref IInputController "input controller" */
    IInputController* GetInputController() const;
    /** @brief Gets @ref ITickController "tick controller" @returns @ref ITickController "tick controller" */
    // ITickController* GetTickController() const;
    /** @brief Gets @ref IHUDController "HUD controller" @returns @ref IHUDController "HUD controller" */
    IHUDController* GetHUDController() const;
    /** @brief Gets @ref EventController "Native event controller" @returns @ref EventController "Native event controller" */
    EventController* GetNativeEventController() const;

protected:    
    std::vector<IEngineSubsystem*> SubsystemStack;

    IInputController* InputController;
    IHUDController* HUDController;
    EventController* NativeEventController;
};