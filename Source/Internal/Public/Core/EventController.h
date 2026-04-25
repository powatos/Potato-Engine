#pragma once

#include <functional>

using Delegate = std::function<void()>;


class IEventController
{
public:
    virtual ~IEventController() = default;

    virtual void RegisterInputBinding(char targetKey, Delegate EventCallback) = 0; 

};