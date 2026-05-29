/** @file Engine.hpp */
#pragma once

#include "Core/Singleton.hpp"
#include "Core/EngineSubsystem.hpp"
#include "Core/Event/EventDelegate.hpp"

class Engine : public Singleton<Engine>, public IEngineSubsystem
{
    friend class Singleton<Engine>;
public:
    virtual void Resolve() noexcept override;
    virtual void _BeginPlay() override;

    int main();

private:
    Engine();
    ~Engine();
    

    void FireTick(const float dt) const;
    void FireTickPostPhysics(const float dt) const;

protected:
    std::vector<EventDelegate<float>> TickDelegates;

};