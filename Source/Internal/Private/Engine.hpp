/** @file Engine.hpp */
#pragma once

#include "Core/EngineSubsystem.hpp"
#include "Core/Event/TickController.hpp"

class Engine : public IEngineSubsystem, public ITickController
{
public:
    [[maybe_unused]] static Engine* get();
    virtual void Resolve() noexcept override;
    virtual void _BeginPlay() override;

    int main();

    virtual void RegisterTick(EventDelegate<float> delegate) override;
    virtual void UnregisterTick(void* object) override;

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