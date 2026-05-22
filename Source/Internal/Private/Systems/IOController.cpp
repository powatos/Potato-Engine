/** @file IOController.cpp */

#include <ncurses.h>
#include <signal.h>
#include <string>
#include <chrono>

#include "Debug/Debug.hpp"
#include "Util/Vector2.hpp"
#include "Game/World.hpp"
#include "Util/GameplayHelper.hpp"
#include "Game/Control/GameInstance.hpp"
#include "Game/Control/PlayerController.hpp"
#include "Game/Actors/Player.hpp"
#include "Game/Actors/Camera.hpp"
#include "Game/UI/Widgets/Widget.hpp"
#include "Game/UI/Widgets/TextElement.hpp"
#include "UIController.hpp"

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

IOController::IOController() : FRAMES_PER_SECOND(30.f) {
    LOG_DEFAULT(LogType::VITAL, "IOController constructed");

    ActiveKey = Keycode::UNKNOWN;
    
    setenv("ESCDELAY", "25", 1); // disables escape delay (shorten if arrow/f keys not working)

    initscr(); // init ncurses
    cbreak(); // disable line buffering
	noecho(); // disable input feedback

    DisplayWindow = newwin(24, 80, 1, 1);
    BoxWindow = newwin(24+2,80+2, 0, 0);

	keypad(DisplayWindow, TRUE); // enable keypad input
    nodelay(DisplayWindow, TRUE); // disable input delay
	curs_set(0); // disable cursor visibility
	wtimeout(DisplayWindow, 0); // Make getch() non-blocking

    // crash handlers
    signal(SIGINT, crashHandler);
    signal(SIGSEGV, crashHandler);
    
    LOG_DEFAULT(LogType::INFO, "ncurses window initialized");

}

void IOController::_BeginPlay() {
    
    box(BoxWindow, 0, 0);
    wrefresh(BoxWindow);

    GameInstance* instance = GameInstance::get();

    FRAMES_PER_SECOND = instance->FRAMES_PER_SECOND;
    MS_REPEAT_THRESHOLD = instance->MS_REPEAT_THRESHOLD;

}

void IOController::HandleInput() {
    static auto lastValidInput = std::chrono::steady_clock::now();

    // Flush input buffer to ignore old frame inputs
    int _ch;
    int _lch;
    while ((_ch = wgetch(DisplayWindow)) != ERR) {
        _lch = _ch;
    }

    const Keycode key = GetKeycode(_lch);

    // DEBUG
    if (key == Keycode::Escape) { LOG_DEFAULT(LogType::DEBUG, "esc"); GameInstance::get()->RequestShutdown(); }
    if (key == Keycode::T) { auto* _ = UIController::get()->GetWidget("W_DebugInfo"); _->SetVisibility(!_->isVisible()); }

    if (MS_REPEAT_THRESHOLD == 0) {

        ActiveKey = Keycode::UNKNOWN;
        FireBinding(InputBindingsTriggered, key);

    } else {

        const auto now = std::chrono::steady_clock::now();

        if (key != Keycode::UNKNOWN) {
            // key pressed

            if (ActiveKey != key) {

                if (ActiveKey != Keycode::UNKNOWN) {
                    FireBinding(InputBindingsCompleted, ActiveKey);
                }

                ActiveKey = key;
                FireBinding(InputBindingsTriggered, ActiveKey);
            }
            
            lastValidInput = now;

        } else {
            // maybe key released, maybe mid repeat
            const auto unkownInputElapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastValidInput);

            if (unkownInputElapsed > std::chrono::milliseconds(MS_REPEAT_THRESHOLD)) {
                // input completed

                const Keycode k = ActiveKey;
                ActiveKey = Keycode::UNKNOWN;

                if (k != Keycode::UNKNOWN) {
                    FireBinding(InputBindingsCompleted, k);
                }

            }
        }
    }

    // dynamic_cast<TextElement*>(UIController::get()->GetWidget("W_DebugInfo")->GetElement("KeyDisplay"))->field = std::to_string(static_cast<int>(ActiveKey));

}

void IOController::Draw() {

    DrawLevel();
    DrawHUD();

    doupdate();
}

void IOController::DrawLevel() {
    werase(DisplayWindow);
    
    const GameInstance* Instance = GameInstance::get();
    const ActorPool& renderActors = Instance->GetWorld()->GetAllActors();

    Camera* camera = Instance->GetPlayerController()->GetCamera();

    for ( Actor* actor : renderActors ) {
        if (actor == nullptr) {
            LOG_DEFAULT(LogType::WARNING, "nullptr actor found in actor pool while drawing - skipped actor");
            continue; 
        }

        if (!actor->isVisible()) { continue; }

        const Vector2 actorPos = actor->GetPosition();

        if (!GameplayHelper::IsPositionInCameraFrame(actorPos, camera)) { continue; }

        const Vector2 camOffsetActorPos = Vector2(actorPos.x - camera->GetPosition().x, actorPos.y);
        const Vector2 screenVector = GameplayHelper::VecToScreenVec(camOffsetActorPos);
        
        const Vector2 actorSize = actor->GetSize();


        for (int r = 0; r < actorSize.y; ++r) {
            std::string textureRowStr = "";
            textureRowStr.reserve(actorSize.x);

            for (int c = 0; c < actorSize.x; ++c) {
                textureRowStr += actor->Texture;
            }

            mvwaddstr(DisplayWindow, 
                static_cast<int>(screenVector.x + r), 
                static_cast<int>(screenVector.y), 
                textureRowStr.c_str()
            );
        }

        

    }

    touchwin(DisplayWindow);
    wnoutrefresh(DisplayWindow);
}

void IOController::DrawHUD() {
    using namespace std::string_literals;

    // iterate through each widget
    for (auto& [UID, map] : WidgetMaps) {
        werase(map->window);

        if (!map->widget->isVisible()) { continue; }
    
        box(map->window, 0, 0);
        
        // iterate through each ui element on the widget
        for (auto [name, elem] : map->widget->GetAllElements()) {
            if (!elem->isVisible()) { continue; }

            const char* t  = elem->TYPE();

            if (t == "TextElement"s) {
                const TextElement* e = dynamic_cast<const TextElement*>(elem);
                const Vector2 pos = e->GetScreenPosition() + Vector2(1.f,1.f);
                mvwprintw(map->window,
                    static_cast<int>(pos.y),
                    static_cast<int>(pos.x),
                    e->field.c_str()
                );
            }
            
        }
        touchwin(map->window);
        wnoutrefresh(map->window);
    }

}

void IOController::Tick(float dt) {
    Tickable::Tick(dt);

    FireBinding(InputBindingsOngoing, ActiveKey);    

}

void IOController::FireBinding(BindingMap& map, Keycode key) {
    const auto loc = map.find(key);
    if (loc == map.end()) { return; } // no binding yet

    for (const InputBinding& binding : loc->second ) {
        if (!binding.GetDelegate().Fire()) {
            LOG_DEFAULT(LogType::WARNING, fmt::format("Input event could not fire for binding: {}", binding.name));
        }
    }
}

void IOController::RegisterWidget(Widget* widget) {
    if (DisplayWindow == nullptr) { return; }

    const Vector2 widgetSize = widget->GetScreenSize();
    const Vector2 widgetPos = widget->GetScreenPosition();

    WINDOW* win = derwin(DisplayWindow, 
        static_cast<int>(widgetSize.y), 
        static_cast<int>(widgetSize.x), 
        static_cast<int>(widgetPos.y), 
        static_cast<int>(widgetPos.x)
    );
    
    WidgetMaps.emplace(widget->GetUID(), new WidgetMapper(widget, win));

}
void IOController::RemoveWidget(std::string UID) {

    for (auto it = WidgetMaps.begin(); it != WidgetMaps.end(); ) {
        if (it->second->window == nullptr) { continue; } // can happen if IOController resolve is called before UIController resolve
        if (it->second->widget->GetUID() == UID) {
            delwin(it->second->window);
            it->second->window = nullptr;

            delete it->second;
            WidgetMaps.erase(it);
            break;
        } else { it++; }
    }

}

void IOController::RegisterInputBinding(InputBinding binding) {

    switch (binding.type) {
        case InputType::Triggered:
            InputBindingsTriggered[binding.key].push_back( binding );
            break;
        case InputType::Completed:
            InputBindingsCompleted[binding.key].push_back( binding );
            break;
        case InputType::Ongoing:
            InputBindingsOngoing[binding.key].push_back( binding );
            break;
    }

}
void IOController::RegisterInputBinding(std::initializer_list<InputBinding> bindings) {
    for (InputBinding binding : bindings) { RegisterInputBinding(binding); }
}
void IOController::UnregisterBindingFrom(BindingMap& map, std::string deleteName) {
    for (auto& [keycode, vec] : map) {

        vec.erase(
            std::remove_if(vec.begin(), vec.end(), [deleteName](const InputBinding& binding) {
                return binding.name == deleteName;
            }),
            vec.end()
        );

    }
}
void IOController::UnregisterAllBindingsFrom(BindingMap& map, void* object) {
    for (auto& [keycode, vec] : map) {

        vec.erase(
            std::remove_if(vec.begin(), vec.end(), [object](const InputBinding& binding) {
                return binding.GetDelegate().GetInstance() == object;
            }),

            vec.end()
        );

    }
}
void IOController::UnregisterInputBinding(std::string deleteName) {

    UnregisterBindingFrom(InputBindingsTriggered, deleteName);
    UnregisterBindingFrom(InputBindingsCompleted, deleteName);
    UnregisterBindingFrom(InputBindingsOngoing, deleteName);

}
void IOController::UnregisterAllInputBindings(void* object) {

    UnregisterAllBindingsFrom(InputBindingsTriggered, object);
    UnregisterAllBindingsFrom(InputBindingsCompleted, object);
    UnregisterAllBindingsFrom(InputBindingsOngoing, object);

}

void IOController::Resolve() noexcept {
    LOG_DEFAULT(LogType::VITAL, "Resolving IOController");

    for (auto& [UID, map] : WidgetMaps) {
        delwin(map->window);
        map->window = nullptr;
        delete map;
    }

    delwin(BoxWindow);

    wrefresh(DisplayWindow);
    wgetch(DisplayWindow);
    delwin(DisplayWindow);
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