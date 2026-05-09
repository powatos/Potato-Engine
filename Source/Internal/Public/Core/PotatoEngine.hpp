// no pragma once; promote one time inclusion

#include <memory>
#include <vector>

#include "EngineSubsystem.hpp"

class IInputController;
class ITickController;
class IHUDController;

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
    IHUDController* GetHUDController() const;

protected:    
    std::vector<IEngineSubsystem*> SubsystemStack;

    IInputController* InputController;
    ITickController* TickController;
    IHUDController* HUDController;

};