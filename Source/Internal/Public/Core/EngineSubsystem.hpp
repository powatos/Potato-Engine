#pragma once

#include <stack>

class IEngineSubsystem
{
public:
    virtual ~IEngineSubsystem() = default;
    virtual void Resolve() noexcept = 0;
};