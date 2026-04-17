#pragma once

#include <unordered_map>
#include <vector>

using InputDelegate = void(*)();
using InputDelegateMap = std::unordered_map< int , std::vector<InputDelegate> >;

class PIOController
{
public:
    [[maybe_unused]] static PIOController* get();

    void Resolve() noexcept;

    void HandleInput() const;
    void OutputDefault() const;

private:
    PIOController();                                            // private constructor
    ~PIOController();                                           // private destructor
    PIOController(const PIOController&) = delete;               // delete copy const
    PIOController& operator = (const PIOController&) = delete;  // delete assignment const
    PIOController(PIOController&&) = delete;                    // delete move const
    PIOController& operator = (PIOController&&) = delete;       // delete move op

    
protected:
    
    InputDelegateMap InputDelegates;
    
};