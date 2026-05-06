#pragma once

#include "Util/Vector2.hpp"
#include "Core/Event/Tickable.hpp"

struct WidgetElement : public Tickable
{
    virtual const char* TYPE() const = 0; // TODO: find way to factorize (macros?) - refer to Archive constructors

    virtual ~WidgetElement() = default;

    Vector2 GetPosition() const;
    void SetPosition(const Vector2& position);

    void AddOffset(const Vector2& offset);
    
    bool isVisible() const;
    void SetVisibility(bool visibility);


protected:
    // virtual void Tick(float dt) override;

    Vector2 Position;
    bool Visible;

};