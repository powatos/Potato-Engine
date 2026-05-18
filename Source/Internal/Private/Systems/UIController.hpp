/** @file UIController.hpp */
#pragma once

#include <vector>

#include "Game/UI/HUDController.hpp"
#include "Core/EngineSubsystem.hpp"

/**
 * UI construction chain
 * --> IHUDController pointer accessed (actually UIController in memory)
 * --> AddWidget called with desired class and ID
 * --> Widget pointer created, passed into RegisterWidget
 * --> RegisterWidget operates on overrided function (in UIController)
 * --> Widget added to ActiveWidgets
 * --> IOController::RegisterWidget called with widget
 * --> IOController creates private window and manages it
 * 
 * Resolving
 * --> Resolve calls to UIController
 * --> Resolve DOES NOT call IOController remove on all widgets because 
 *     IOController resolve (called after UIController resolve) does that already
 * --> Frees widget pointers
 * --> returns resolve
 */

class Widget;

class UIController : public IEngineSubsystem, public IHUDController
{
public:
    [[maybe_unused]] static UIController* get();
    virtual void Resolve() noexcept override;

    const std::vector<Widget*>& GetActiveWidgets();

    // add widget happens in HUDController -> calls register
    virtual void RemoveWidget(std::string UID) override;
    virtual void RegisterWidget(Widget* widget) override;
    virtual Widget* GetWidget(std::string UID) const override;

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
