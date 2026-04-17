#include <iostream>

#include <ncurses.h>
#include "Utils/Debug.h"
#include "PScreenVirtualizer.h"
#include "PIOController.h"

[[maybe_unused]] PIOController* PIOController::get() {
    // constructed on first call
    static PIOController instance;
    
    return &instance;
}

PIOController::PIOController() {
    LOG_DEFAULT(LogType::VITAL, "IOController instantiated");
    
    // initialize ncurses
    initscr(); // init ncurses
	cbreak(); // disables line buffering
	noecho(); // disables input feedback
// 	keypad(stdscr, TRUE); // enables keypad input
	curs_set(0); // disables cursor visibility
	timeout(0); // Make getch() non-blocking IMMEDIATELY
    
    LOG_DEFAULT(LogType::VITAL, "ncurses window initialized");

}

void PIOController::HandleInput() const {
    
    int ch = getch();
    
    if (InputDelegates.find(ch) != InputDelegates.end()) {
        // binding exists to pressed key
        
        for (const InputDelegate& delegate : InputDelegates.at(ch) ) {
            delegate();
        }
        
    }

}

void PIOController::OutputDefault() const {
    
    // Pre-draw operations here

    PScreenVirtualizer::get()->Draw();
    
}

void PIOController::Resolve() noexcept {

    LOG_DEFAULT(LogType::VITAL, "Resolve called to IOController");

    refresh();
    getch();

    curs_set(1);
    endwin();

}

PIOController::~PIOController() {
    
    Resolve();
}