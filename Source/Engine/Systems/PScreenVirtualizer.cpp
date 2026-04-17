#include "PScreenVirtualizer.h"

#include "PIOController.h"

[[maybe_unused]] PScreenVirtualizer* PScreenVirtualizer::get() {
    // constructs on first call
    static PScreenVirtualizer instance;
    
    return &instance;
}

PScreenVirtualizer::PScreenVirtualizer() {
    
}

PScreenVirtualizer::~PScreenVirtualizer() {
    
}

int PScreenVirtualizer::Draw() { 
    
        
    return 0;
}
    