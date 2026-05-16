#pragma once

#include "Game/UI/UIElement.hpp"
#include "Core/Event/Tickable.hpp"

/**
 * @brief Wrapper for specialized sub-element that can be rendered by a Widget
 */
struct WidgetElement : public Tickable, public UIElement
{
    virtual const char* TYPE() const = 0; // TODO: find way to factorize (macros?) - refer to Archive constructors

    virtual ~WidgetElement() = default;

protected:
    // virtual void Tick(float dt) override;


};