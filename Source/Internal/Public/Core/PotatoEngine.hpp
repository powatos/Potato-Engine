// no pragma once; promote one time inclusion

#include <memory>
#include <stack>

#include "EngineSubsystem.hpp"

class IEventController;
class IInputController;

class PotatoEngine // implementation in 'Internal/Private/PotatoEngine.cpp'
{
public:
    PotatoEngine();
    ~PotatoEngine();

    static PotatoEngine& Get();
    void LoadSubobjects();
    void BeginPlay();
    void Resolve() noexcept;

    IEventController* GetEventController() const;
    IInputController* GetInputController() const;

protected:    
    std::stack<IEngineSubsystem*> SubsystemStack;

    IEventController* EventController;
    IInputController* InputController;

};