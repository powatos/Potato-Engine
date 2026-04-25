#pragma once

class Engine
{
    
public:
    [[maybe_unused]] static Engine* get();
    
    int main();                                     // main game loop



private:
    Engine();                                      // private constructor
    ~Engine();                                     // private destructor
    Engine(const Engine&) = delete;               // delete copy const
    Engine& operator = (const Engine&) = delete;  // delete assignment const
    Engine(Engine&&) = delete;                    // delete move const
    Engine& operator = (Engine&&) = delete;       // delete move op
    
    void Resolve() noexcept;


    bool isLooping;

protected:
    
};