#pragma once

#include <unordered_map>
#include <vector>

using InputDelegate = void(*)();
using InputDelegateMap = std::unordered_map< int , std::vector<InputDelegate> >;

class IOController
{
public:
    [[maybe_unused]] static IOController* get();

    void Resolve() noexcept;

    void HandleInput() const;
    void OutputDefault() const;

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