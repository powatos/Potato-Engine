
#include "EventController.hpp"

EventController* EventController::get() {
    static EventController instance;
    
    return &instance;
}

EventController::EventController() {
    LOG_DEFAULT(LogType::VITAL, "EventController constructed");

}

void EventController::Resolve() noexcept {
    LOG_DEFAULT(LogType::VITAL, "Resolving EventController");

}