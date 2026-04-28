#pragma once

#include <functional>

struct EventDelegate
{
private:
    std::function<void()> callback;
    void* instance = nullptr;

public:

    EventDelegate() = default;
    ~EventDelegate() = default;

    template<typename BindingClass>
    EventDelegate(BindingClass* obj, void(BindingClass::*method)()) {
        instance = obj;
        callback = [obj, method]() { (obj->*method)(); };
    }

    // @returns if sucessfully fired
    bool Fire() const {
        if (callback == nullptr) { return false; }
        callback();
        return true;
    }

    inline void* GetInstance() const { return instance; }

};
