/** @file Engine.hpp */
#pragma once

#include "Core/EngineSubsystem.hpp"
#include "Core/Event/EventDelegate.hpp"

class Engine : public IEngineSubsystem
{
public:
    [[maybe_unused]] static Engine* get();
    virtual void Resolve() noexcept override;
    virtual void _BeginPlay() override;

    int main();

private:
    Engine();
    ~Engine();
    Engine(const Engine&) = delete;
    Engine& operator = (const Engine&) = delete;
    Engine(Engine&&) = delete;
    Engine& operator = (Engine&&) = delete;
    

    void FireTick(const float dt) const;

protected:
    std::vector<EventDelegate<float>> TickDelegates;

};