#pragma once

#include <vector>

#include "Game/UI/HUDController.hpp"
#include "Core/EngineSubsystem.hpp"

class Widget;

class UIController : public IEngineSubsystem, public IHUDController
{
public:
    [[maybe_unused]] static UIController* get();
    virtual void Resolve() noexcept override;

    std::vector<Widget*> GetActiveHUDs();

private:
    UIController();
    ~UIController();
    UIController(const UIController&) = delete;
    UIController& operator = (const UIController&) = delete;
    UIController(UIController&&) = delete;
    UIController& operator = (UIController&&) = delete;

protected:

    std::vector<Widget*> ActiveWidgets;

};
