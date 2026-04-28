#pragma once

#include <unordered_map>
#include <functional>
#include <vector>

#include "Core/EngineSubsystem.hpp"
#include "Core/Input/InputController.hpp"


class IOController : public IInputController, public IEngineSubsystem
{
public:
    [[maybe_unused]] static IOController* get();
    virtual void Resolve() noexcept override;

    void HandleInput() const;
    void Draw() const;

    virtual void RegisterInputBinding(InputBinding binding) override;
    virtual void UnregisterInputBinding(std::string deleteName) override;
    virtual void UnregisterAllInputBindings(void* object) override;

    const int FRAMES_PER_SECOND = 24;


private:
    IOController();
    ~IOController();
    IOController(const IOController&) = delete;
    IOController& operator = (const IOController&) = delete;
    IOController(IOController&&) = delete;
    IOController& operator = (IOController&&) = delete;

    
protected:
    
    std::unordered_map<Keycode , std::vector<InputBinding>, KeycodeHash> InputBindings;
    
};