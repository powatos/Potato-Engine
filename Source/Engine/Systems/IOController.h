#pragma once

#include <unordered_map>
#include <functional>
#include <vector>

using InputDelegate = std::function<void()>;
using InputDelegateMap = std::unordered_map< int , std::vector<InputDelegate> >;

class IOController
{

public:
    [[maybe_unused]] static IOController* get();

    void HandleInput() const;
    void Draw() const;

    void BindInput(char targetKey, InputDelegate EventCallback);

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