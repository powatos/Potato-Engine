
#include <ncurses.h>

#include "Debug/Debug.h"
#include "Util/Vector2.h"
#include "Game/World.h"
#include "Game/GameInstance.h"

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

void IOController::RegisterInputBinding(char targetKey, Delegate EventCallback) {

    InputDelegates[static_cast<int>(targetKey)].push_back(std::move(EventCallback));

}

void IOController::HandleInput() const {
    
    int ch = getch();
    
    if (InputDelegates.find(ch) != InputDelegates.end()) {
        // binding exists to pressed key
        
        for (const Delegate& delegate : InputDelegates.at(ch) ) {
            delegate();
        }
        
    }

    // DEBUG
    if (ch == 't') { GameInstance::get()->GetState().isMainTickRunning = false; }

}

void IOController::Draw() const {
    
    const World* world = GameInstance::get()->GetWorld();

    for ( Actor* actor : world->GetAllActors() ) {
        if (actor == nullptr) { continue; }

        Vector2 pos = actor->GetPosition();
        
        mvaddch(static_cast<int>(pos.y), static_cast<int>(pos.x), '@');

    }




}

IOController::~IOController() {
    LOG_DEFAULT(LogType::VITAL, "IOController destroying");

    refresh();
    getch();

    curs_set(1);
    endwin();

}