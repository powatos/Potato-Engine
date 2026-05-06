
#include "Debug/Debug.hpp"
#include "Game/UI/Widgets/Widget.hpp"
#include "IOController.hpp"

#include "UIController.hpp"


[[maybe_unused]] UIController* UIController::get() {
    // constructed on first call
    static UIController instance;
    
    return &instance;
}

UIController::UIController() {
    LOG_DEFAULT(LogType::VITAL, "UIController constructed");

}

void UIController::RegisterWidget(Widget* widget) {

    IOController::get()->RegisterWidget(widget);
    ActiveWidgets.push_back(widget);

}

void UIController::RemoveWidget(std::string UID) {
    IOController::get()->RemoveWidget(UID);
}

const std::vector<Widget*>& UIController::GetActiveWidgets() {
    return ActiveWidgets;
}

void UIController::Resolve() noexcept {
    LOG_DEFAULT(LogType::VITAL, "Resolving UIController");

    IOController* controller = IOController::get();

    for (Widget* widget : ActiveWidgets) {
        controller->RemoveWidget(widget->GetUID()); // cleans up ncurses window
        delete widget;
    }

}

UIController::~UIController() {
    LOG_DEFAULT(LogType::VITAL, "UIController destroying");
}

