#include "ScreenVirtualizer.h"

#include "IOController.h"

[[maybe_unused]] ScreenVirtualizer* ScreenVirtualizer::get() {
    // constructs on first call
    static ScreenVirtualizer instance;
    
    return &instance;
}

ScreenVirtualizer::ScreenVirtualizer() {
    
}

ScreenVirtualizer::~ScreenVirtualizer() {
    
}

int ScreenVirtualizer::Draw() { 
    
        
    return 0;
}
    