#pragma once

#include "WidgetElement.hpp"

// TODO: implement color text (ideally using Enum -> could make public for other stuff like debug streamlining)
/**
 * @brief Element that displays text on a widget
 */
struct TextElement : public WidgetElement
{
    virtual const char* TYPE() const override { return "TextElement"; }

    TextElement() = default;

    /**
     * @brief Text to display
     */
    std::string field;

};