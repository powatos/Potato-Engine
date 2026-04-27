
#include <ncurses.h>
#include <signal.h>

#include "Debug/Debug.hpp"
#include "Util/Vector2.hpp"
#include "Game/World.hpp"
#include "Game/GameInstance.hpp"

#include "fmt/core.h"
#include "IOController.hpp"

static constexpr char toggleCase(char c) {
    if (c >= 'a' && c <= 'z') { return c - 32; }
    if (c >= 'A' && c <= 'Z') { return c + 32; }
    return c;
}

void crashHandler(int) {
    endwin();
    exit(1);
}

[[maybe_unused]] IOController* IOController::get() {
    // constructed on first call
    static IOController instance;
    
    return &instance;
}

IOController::IOController() {
    LOG_DEFAULT(LogType::VITAL, "IOController constructed");
    
    // initialize ncurses
    initscr(); // init ncurses
	cbreak(); // disables line buffering
	noecho(); // disables input feedback
// 	keypad(stdscr, TRUE); // enables keypad input
	curs_set(0); // disables cursor visibility
	timeout(0); // Make getch() non-blocking IMMEDIATELY

    // crash handlers
    signal(SIGINT, crashHandler);
    signal(SIGSEGV, crashHandler);
    
    LOG_DEFAULT(LogType::VITAL, "ncurses window initialized");

}

void IOController::RegisterInputBinding(InputBinding binding) {

    InputBindings[static_cast<int>(binding.targetKey)].push_back( binding );

    if (!binding.isCaseSensitive) {
        InputBindings[static_cast<int>(toggleCase(binding.targetKey))].push_back( binding );
    }

}

void IOController::UnregisterInputBinding(std::string deleteName) {

    for (auto& pair : InputBindings) {
        auto& vec = pair.second;

        vec.erase(
            std::remove_if(vec.begin(), vec.end(), [deleteName](const InputBinding& binding) {
                return binding.name == deleteName;
            }),
            vec.end()
        );

    }

}

void IOController::UnregisterAllInputBindings(void* object) {

    for (auto& pair : InputBindings) {
        auto& vec = pair.second;

        vec.erase(
            std::remove_if(vec.begin(), vec.end(), [object](const InputBinding& binding) {
                return binding.GetDelegate().GetInstance() == object;
            }),
            vec.end()
        );

    }

}

void IOController::HandleInput() const {
    
    int ch = getch();
    
    if (InputBindings.find(ch) != InputBindings.end()) {
        // binding exists to pressed key
        
        for (const InputBinding& binding : InputBindings.at(ch) ) {
            if (!binding.GetDelegate().Fire()) {
                LOG_DEFAULT(LogType::WARNING, fmt::format("Input event could not fire for binding: {}", binding.name));
            }
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

void IOController::Resolve() noexcept {
    LOG_DEFAULT(LogType::VITAL, "Resolving IOController");

    refresh();
    getch();

    curs_set(1);
    endwin();
}

IOController::~IOController() {
    LOG_DEFAULT(LogType::VITAL, "IOController destroying");
}