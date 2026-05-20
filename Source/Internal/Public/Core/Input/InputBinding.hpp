/** @file InputBinding.hpp */
#pragma once

#include "Core/Event/EventController.hpp"
#include "Input.hpp"

/**
 * @brief Wrapper for input bindings
 */
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

    /**
     * @brief Constructs binding with method callback
     * * @tparam T Class of binding object
     * @param key Keycode to bind to
     * @param type InputType to bind to
     * @param name Identifier for binding
     * @param obj Object to bind to
     * @param callback Function to notify
     */
    template<typename T>
    InputBinding(Keycode key, InputType type, std::string name, T* obj, void(T::*callback)()) : 
        name(name),
        delegate(obj, callback),
        key(key),
        type(type)
    {}

    /**
     * @brief Constructs binding with standalone callback
     * @param key Keycode to bind to
     * @param type InputType to bind to
     * @param name Identifier for binding
     * @param callback Function to notify
     */
    InputBinding(Keycode key, InputType type, std::string name, void(*callback)()) : 
        name(name),
        delegate(callback),
        key(key),
        type(type)
    {}

    /** @brief Gets EventDelegate reference @returns Delegate */
    inline const EventDelegate<>& GetDelegate() const { return delegate; }

};