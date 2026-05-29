/** @file WidgetElement.hpp */
#pragma once

#include "Core/Event/Tickable.hpp"
#include "UI/UIElement.hpp"

/**
 * @brief Wrapper for specialized sub-element that can be rendered by a Widget
 */
struct WidgetElement : public Tickable, public UIElement
{
    virtual const char* TYPE() const = 0; // TODO: find way to factorize (macros?) - refer to Archive constructors

    virtual ~WidgetElement() = default;

protected:
    // virtual void Tick([[maybe_unused]] float dt) override;


};