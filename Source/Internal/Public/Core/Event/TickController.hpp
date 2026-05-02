#pragma once

#include "EventController.hpp"

class ITickController : public IEventController
{
public:
    virtual ~ITickController() = default;

    virtual void RegisterTick(EventDelegate<float> delegate) = 0;
    virtual void UnregisterTick(void* object) = 0;

};