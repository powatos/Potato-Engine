// no pragma once; promote one time inclusion

#include <memory>
#include <stack>

#include "EngineSubsystem.hpp"

class IEventController;

class PotatoEngine // implementation in 'Internal/Private/PotatoEngine.cpp'
{
public:
    PotatoEngine();
    ~PotatoEngine();

    static PotatoEngine& Get();
    void BeginPlay();
    void Resolve() noexcept;

    IEventController* GetInputController() const;

protected:    
    std::stack<IEngineSubsystem*> SubsystemStack;

    IEventController* InputController;

};