#pragma once


class PEngine
{
    
public:
    [[maybe_unused]] static PEngine* get();
    
    void Resolve() noexcept;

    int main();                                     // main game loop


private:
    PEngine();                                      // private constructor
    ~PEngine();                                     // private destructor
    PEngine(const PEngine&) = delete;               // delete copy const
    PEngine& operator = (const PEngine&) = delete;  // delete assignment const
    PEngine(PEngine&&) = delete;                    // delete move const
    PEngine& operator = (PEngine&&) = delete;       // delete move op
    
    
    
    

    
};