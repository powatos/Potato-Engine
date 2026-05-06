#pragma once

#include "WidgetElement.hpp"

// TODO: implement color text (ideally using Enum -> could make public for other stuff like debug streamlining)
struct TextElement : public WidgetElement
{
    virtual const char* TYPE() const override { return "TextElement"; }

    TextElement() = default;

    std::string field;

};