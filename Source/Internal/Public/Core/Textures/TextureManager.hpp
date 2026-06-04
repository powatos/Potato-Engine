/** @file TextureManager.hpp */
#pragma once

#include "Core/Singleton.hpp"
#include "Core/EngineSubsystem.hpp"

class TextureManager : public Singleton<TextureManager>, public IEngineSubsystem
{
    friend class Singleton<TextureManager>;

public:
    virtual void Resolve() noexcept override;
    virtual void BeginPlay() override;

    TextureManager();

};