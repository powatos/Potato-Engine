#pragma once

#include "Core/EngineSubsystem.hpp"

class Engine : public IEngineSubsystem
{
    ~Engine();

public:
    [[maybe_unused]] static Engine* get();
    
    int main();

private:
    Engine();
    Engine(const Engine&) = delete;
    Engine& operator = (const Engine&) = delete;
    Engine(Engine&&) = delete;
    Engine& operator = (Engine&&) = delete;
    
    void Resolve() noexcept;

protected:


};