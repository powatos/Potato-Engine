
#include <ncurses.h>
#include <signal.h>

#include "Debug/Debug.hpp"
#include "Util/Vector2.hpp"
#include "Game/World.hpp"
#include "Util/GameplayHelper.hpp"
#include "Game/Control/GameInstance.hpp"

#include "fmt/core.h"
#include "IOController.hpp"

static constexpr char toggleCase(char c);
void crashHandler(int);
static constexpr Keycode GetKeycode(int ch);

[[maybe_unused]] IOController* IOController::get() {
    // constructed on first call
    static IOController instance;
    
    return &instance;
}

IOController::IOController() {
    LOG_DEFAULT(LogType::VITAL, "IOController constructed");
    
    setenv("ESCDELAY", "25", 1); // disables escape delay (shorten if arrow/f keys not working)

    // initialize ncurses
    initscr(); // init ncurses
	cbreak(); // disables line buffering
	noecho(); // disables input feedback
	keypad(stdscr, TRUE); // enables keypad input
    nodelay(stdscr, TRUE); // disables input delay
	curs_set(0); // disables cursor visibility
	timeout(0); // Make getch() non-blocking IMMEDIATELY

    // crash handlers
    signal(SIGINT, crashHandler);
    signal(SIGSEGV, crashHandler);
    
    LOG_DEFAULT(LogType::VITAL, "ncurses window initialized");

}

void IOController::RegisterInputBinding(InputBinding binding) {

    InputBindings[binding.key].push_back( binding );

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
    int _ch = getch();
    Keycode key = GetKeycode(_ch);

    // DEBUG
    if (key == Keycode::Escape) { LOG_DEFAULT(LogType::DEBUG, "esc"); GameInstance::get()->isMainTickRunning = false; }

    auto loc = InputBindings.find(key);
    if (loc == InputBindings.end()) { return; } // no binding exists

    for (const InputBinding& binding : loc->second ) {
        if (!binding.GetDelegate().Fire()) {
            LOG_DEFAULT(LogType::WARNING, fmt::format("Input event could not fire for binding: {}", binding.name));
        }
    }
        
}

void IOController::Draw() const {
    erase();
    
    const World* world = GameInstance::get()->GetWorld();

    for ( Actor* actor : world->GetAllActors() ) {
        if (actor == nullptr) {
            LOG_DEFAULT(LogType::WARNING, "nullptr actor found in actor pool while drawing - skipped actor");
            continue; 
        }
        Vector2 screenVector = GameplayHelper::WorldToScreenPos(actor->GetPosition());
        
        mvaddch(static_cast<int>(screenVector.x), static_cast<int>(screenVector.y), actor->Texture);

    }

    refresh();
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


static constexpr char toggleCase(char c) {
    if (c >= 'a' && c <= 'z') { return c - 32; }
    if (c >= 'A' && c <= 'Z') { return c + 32; }
    return c;
}

void crashHandler(int) {
    endwin();
    exit(1);
}

/// @returns Keycode from passed ASCII input
static constexpr Keycode GetKeycode(int ch)
{
    // ASCII
    if (ch >= 'a' && ch <= 'z') {
        return static_cast<Keycode>(static_cast<int>(Keycode::A) + (ch - 'a'));
    }
    if (ch >= 'A' && ch <= 'Z') {
        return static_cast<Keycode>(static_cast<int>(Keycode::A) + (ch - 'A'));
    }
    if (ch >= '0' && ch <= '9') {
        return static_cast<Keycode>(static_cast<int>(Keycode::Num0) + (ch - '0'));
    }

    switch (ch)
    {

        case ' ': return Keycode::Space;
        case '\n': return Keycode::Enter;
        case 27: return Keycode::Escape;
        case '\t': return Keycode::Tab;

        case KEY_UP:    return Keycode::ArrowUp;
        case KEY_DOWN:  return Keycode::ArrowDown;
        case KEY_LEFT:  return Keycode::ArrowLeft;
        case KEY_RIGHT: return Keycode::ArrowRight;

        case KEY_F(1):  return Keycode::F1;
        case KEY_F(2):  return Keycode::F2;
        case KEY_F(3):  return Keycode::F3;
        case KEY_F(4):  return Keycode::F4;
        case KEY_F(5):  return Keycode::F5;
        case KEY_F(6):  return Keycode::F6;
        case KEY_F(7):  return Keycode::F7;
        case KEY_F(8):  return Keycode::F8;
        case KEY_F(9):  return Keycode::F9;
        case KEY_F(10): return Keycode::F10;
        case KEY_F(11): return Keycode::F11;
        case KEY_F(12): return Keycode::F12;

        default: return Keycode::UNKNOWN;

    }

}