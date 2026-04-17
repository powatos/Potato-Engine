#include <iostream>

#include <ncurses.h>
#include "Utils/Debug.h"
#include "ScreenVirtualizer.h"
#include "IOController.h"

[[maybe_unused]] IOController* IOController::get() {
    // constructed on first call
    static IOController instance;
    
    return &instance;
}

IOController::IOController() {
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

void IOController::HandleInput() const {
    
    int ch = getch();
    
    if (InputDelegates.find(ch) != InputDelegates.end()) {
        // binding exists to pressed key
        
        for (const InputDelegate& delegate : InputDelegates.at(ch) ) {
            delegate();
        }
        
    }

}

void IOController::OutputDefault() const {
    
    // Pre-draw operations here

    ScreenVirtualizer::get()->Draw();
    
}

void IOController::Resolve() noexcept {

    LOG_DEFAULT(LogType::VITAL, "Resolve called to IOController");

    refresh();
    getch();

    curs_set(1);
    endwin();

}

IOController::~IOController() {
    
    Resolve();
}