/** @file EngineSubsystem.hpp */
#pragma once

/**
 * @brief Interface for internal engine classes
 * @note This class is intended for internal use
 */
class IEngineSubsystem
{
public:
    virtual ~IEngineSubsystem() = default;
    virtual void Resolve() noexcept = 0;
    virtual void _BeginPlay() {};
};