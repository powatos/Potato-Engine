#pragma once

class ScreenVirtualizer
{
    
public:
    [[maybe_unused]] static ScreenVirtualizer* get();

    int Draw();


private:
    ScreenVirtualizer();                                            // private constructor
    ~ScreenVirtualizer();                                           // private destructor
    ScreenVirtualizer(const ScreenVirtualizer&) = delete;               // delete copy const
    ScreenVirtualizer& operator = (const ScreenVirtualizer&) = delete;  // delete assignment const
    ScreenVirtualizer(ScreenVirtualizer&&) = delete;                    // delete move const
    ScreenVirtualizer& operator = (ScreenVirtualizer&&) = delete;       // delete move op
    
    
    
    

    
};