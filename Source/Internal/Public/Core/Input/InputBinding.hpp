#pragma once

#include "Core/Event/EventController.hpp"
#include "Input.hpp"

struct InputBinding
{
// optimized declaration order 
public:
    std::string name;

private:
    EventDelegate<> delegate;

public:
    Keycode key;
    InputType type;

    template<typename T>
    InputBinding(Keycode key, InputType type, std::string name, T* obj, void(T::*callback)()) : 
        name(name),
        delegate(obj, callback),
        key(key),
        type(type)
    {}

    InputBinding(Keycode key, InputType type, std::string name, void(*callback)()) : 
        name(name),
        delegate(callback),
        key(key),
        type(type)
    {}

    inline const EventDelegate<>& GetDelegate() const { return delegate; }

};