#pragma once

class PScreenVirtualizer
{
    
public:
    [[maybe_unused]] static PScreenVirtualizer* get();

    int Draw();


private:
    PScreenVirtualizer();                                            // private constructor
    ~PScreenVirtualizer();                                           // private destructor
    PScreenVirtualizer(const PScreenVirtualizer&) = delete;               // delete copy const
    PScreenVirtualizer& operator = (const PScreenVirtualizer&) = delete;  // delete assignment const
    PScreenVirtualizer(PScreenVirtualizer&&) = delete;                    // delete move const
    PScreenVirtualizer& operator = (PScreenVirtualizer&&) = delete;       // delete move op
    
    
    
    

    
};