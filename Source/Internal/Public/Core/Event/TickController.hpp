#pragma once

#include "EventController.hpp"

/**
 * @interface ITickController
 * @note This class is intended for internal use. @sa Tickable
 * @brief Interface to handle tick events
 */
class ITickController : public IEventController
{
public:
    virtual ~ITickController() = default;

    /**
     * @brief Registers a delegate to recieve tick updates
     * @note Must use method binded delegate in order to unregister
     * @param delegate Delegate
     */
    virtual void RegisterTick(EventDelegate<float> delegate) = 0;
    
    /**
     * @brief Unregisters an object from receiving tick events
     * @param object Object with the initial binding to unregister
     */
    virtual void UnregisterTick(void* object) = 0;

};