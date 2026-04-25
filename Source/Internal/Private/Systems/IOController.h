#pragma once

#include <unordered_map>
#include <functional>
#include <vector>

#include "Core/EventController.h"

using InputDelegateMap = std::unordered_map< int , std::vector<Delegate> >;

class IOController : public IEventController
{

public:
    [[maybe_unused]] static IOController* get();

    void HandleInput() const;
    void Draw() const;

    virtual void RegisterInputBinding(char targetKey, Delegate EventCallback) override;

    const int FRAMES_PER_SECOND = 24;


private:
    IOController();                                            // private constructor
    ~IOController();                                           // private destructor
    IOController(const IOController&) = delete;               // delete copy const
    IOController& operator = (const IOController&) = delete;  // delete assignment const
    IOController(IOController&&) = delete;                    // delete move const
    IOController& operator = (IOController&&) = delete;       // delete move op

    
protected:
    
    InputDelegateMap InputDelegates;
    
    
};