// no pragma once; promote one time inclusion

#include <memory>
#include <stack>

#include "EngineSubsystem.hpp"

class IInputController;
class ITickController;

class PotatoEngine // implementation in 'Internal/Private/PotatoEngine.cpp'
{
public:
    PotatoEngine();
    ~PotatoEngine();

    static PotatoEngine& Get();
    void LoadSubobjects();
    void BeginPlay();
    void Resolve() noexcept;

    IInputController* GetInputController() const;
    ITickController* GetTickController() const;

protected:    
    std::stack<IEngineSubsystem*> SubsystemStack;

    IInputController* InputController;
    ITickController* TickController;

};