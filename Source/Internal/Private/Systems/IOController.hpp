/** @file IOController.hpp */
#pragma once

#include <unordered_map>
#include <functional>
#include <vector>

#include "Core/EngineSubsystem.hpp"
#include "Core/Input/InputController.hpp"
#include "Core/Event/Tickable.hpp"

using BindingMap = std::unordered_map<Keycode, std::vector<InputBinding>, __KeycodeHash>;

struct _win_st;
typedef struct _win_st WINDOW;
struct WidgetMapper;
class Widget;

class IOController : public IEngineSubsystem, public IInputController, public Tickable
{
public:
    [[maybe_unused]] static IOController* get();
    virtual void Resolve() noexcept override;
    virtual void _BeginPlay() override;

    void HandleInput();
    void Draw();

    void RegisterWidget(Widget* widget);
    void RemoveWidget(std::string UID);

    virtual void RegisterInputBinding(InputBinding binding) override;
    virtual void RegisterInputBinding(std::initializer_list<InputBinding> bindings) override;
    virtual void UnregisterInputBinding(std::string deleteName) override;
    virtual void UnregisterAllInputBindings(void* object) override;

    float FRAMES_PER_SECOND;
    int MS_REPEAT_THRESHOLD;

private:
    IOController();
    ~IOController();
    IOController(const IOController&) = delete;
    IOController& operator = (const IOController&) = delete;
    IOController(IOController&&) = delete;
    IOController& operator = (IOController&&) = delete;

    void UnregisterBindingFrom(BindingMap&, std::string deleteName);
    void UnregisterAllBindingsFrom(BindingMap&, void* object);
    void FireBinding(BindingMap&, Keycode key);

    void DrawLevel();
    void DrawHUD();
    
protected:
    virtual void Tick(float dt) override;

    WINDOW* BoxWindow;
    WINDOW* DisplayWindow;

    std::unordered_map<std::string, WidgetMapper*> WidgetMaps;

    BindingMap InputBindingsTriggered;
    BindingMap InputBindingsOngoing;
    BindingMap InputBindingsCompleted;
    BindingMap InputBindingsImpulse;

    Keycode ActiveKey;
    Keycode ImpulseKey;
    
};

struct WidgetMapper {
    Widget* widget;
    WINDOW* window;

    WidgetMapper(Widget* widget, WINDOW* window) : widget(widget), window(window) {}
};