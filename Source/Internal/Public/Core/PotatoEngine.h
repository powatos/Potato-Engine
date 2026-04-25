// no pragma once; promote one time inclusion

#include <memory>

class IEventController;

// implementation in 'Internal/Private/PotatoEngine.cpp'
class PotatoEngine
{
public:
    PotatoEngine();
    ~PotatoEngine();

    void Initialize();
    void BeginPlay();

    IEventController* GetInputController() const;

protected:
    IEventController* InputController;

private:
    struct InitImpl;
    std::unique_ptr<InitImpl> Impl;
};