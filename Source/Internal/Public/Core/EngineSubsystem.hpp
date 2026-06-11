/** @file EngineSubsystem.hpp */
#pragma once

#include "PotatoEngine.hpp"
#include "Singleton.hpp"

/**
 * @brief Interface for internal engine classes
 * @note This class is intended for internal use
 */
class IEngineSubsystem
{
public:
    virtual ~IEngineSubsystem() = default;
    virtual void Resolve() noexcept {};
    virtual void BeginPlay() {};
};

/**
 * @brief Inheriting class for internal engine classes
 * @note This class is intended for internal use
 */
template<typename T>
class EngineSubsystem : public IEngineSubsystem, public Singleton<T> 
{};

#define ENGINE_SUBSYSTEM(type) \
friend class Singleton<type>; \
inline static struct __##type##_RegisterSubsystem { \
    __##type##_RegisterSubsystem() { \
        __SubsystemRegistry::_GetList().push_back( reinterpret_cast< IEngineSubsystem*(*)() >(&type::Get) ); \
    } \
} __##type##_registerSubsystem;
