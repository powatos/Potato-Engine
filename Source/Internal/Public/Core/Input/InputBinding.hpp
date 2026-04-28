#pragma once

#include "Core/Event/EventController.hpp"
#include "Input.hpp"

struct InputBinding
{
// optimized declaration order 
public:
    std::string name;

private:
    EventDelegate delegate;

public:
    Keycode key;

    template<typename T>
    InputBinding(Keycode key, std::string name, T* obj, void(T::*callback)()) : 
        name(name),
        delegate(obj, callback),
        key(key)
    {}

    inline const EventDelegate& GetDelegate() const { return delegate; }

};