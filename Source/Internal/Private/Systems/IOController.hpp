#pragma once

#include <unordered_map>
#include <functional>
#include <vector>

#include "Core/EngineSubsystem.hpp"
#include "Core/Input/InputController.hpp"

struct _win_st;
typedef struct _win_st WINDOW;

class IOController : public IEngineSubsystem, public IInputController
{
public:
    [[maybe_unused]] static IOController* get();
    virtual void Resolve() noexcept override;

    void HandleInput() const;
    void Draw() const;

    virtual void RegisterInputBinding(InputBinding binding) override;
    virtual void UnregisterInputBinding(std::string deleteName) override;
    virtual void UnregisterAllInputBindings(void* object) override;

    const float FRAMES_PER_SECOND;

private:
    IOController();
    ~IOController();
    IOController(const IOController&) = delete;
    IOController& operator = (const IOController&) = delete;
    IOController(IOController&&) = delete;
    IOController& operator = (IOController&&) = delete;

    
protected:
    WINDOW* window;

    std::unordered_map<Keycode , std::vector<InputBinding>, KeycodeHash> InputBindings;
    

};