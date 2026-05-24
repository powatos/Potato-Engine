/** @file DebugInfo.hpp */
#pragma once

#include "Game/UI/Widgets/Widget.hpp"

struct Vector2;

/**
 * @internal
 * @brief Displays debug information on screen updating in real time
 */
class DebugInfo : public Widget
{
public:
    DebugInfo(std::string UID);
    ~DebugInfo();

protected:
    virtual void Tick([[maybe_unused]] float dt) override;

};