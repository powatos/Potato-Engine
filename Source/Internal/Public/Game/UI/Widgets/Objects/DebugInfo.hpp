#pragma once

#include "Game/UI/Widgets/Widget.hpp"

struct Vector2;

class DebugInfo : public Widget
{
public:
    DebugInfo(std::string UID);
    ~DebugInfo();

protected:
    virtual void Tick(float dt) override;

};