#pragma once

#include "InputBinding.hpp"
#include "Core/Event/EventController.hpp"

class IInputController : public IEventController
{
public:
    virtual ~IInputController() = default;

    virtual void RegisterInputBinding(InputBinding binding) = 0; 
    virtual void UnregisterInputBinding(std::string name) = 0;
    virtual void UnregisterAllInputBindings(void* object) = 0;
};