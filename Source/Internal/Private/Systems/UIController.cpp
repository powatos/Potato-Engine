
#include "Debug/Debug.hpp"
#include "Game/UI/Widgets/Widget.hpp"

#include "UIController.hpp"


[[maybe_unused]] UIController* UIController::get() {
    // constructed on first call
    static UIController instance;
    
    return &instance;
}

UIController::UIController() {
    LOG_DEFAULT(LogType::VITAL, "UIController constructed");


}

std::vector<Widget*> UIController::GetActiveWidgets() {
    return ActiveWidgets;
}

void UIController::Resolve() noexcept {
    LOG_DEFAULT(LogType::VITAL, "Resolving UIController");

}

UIController::~UIController() {
    LOG_DEFAULT(LogType::VITAL, "UIController destroying");
}

