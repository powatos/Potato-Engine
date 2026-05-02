#pragma once

#include <functional>

template<typename... CallbackArgs>
struct EventDelegate
{
private:
    std::function<void(CallbackArgs...)> callback;
    void* instance = nullptr;

public:

    EventDelegate() = default;
    ~EventDelegate() = default;

    template<typename BindingClass>
    EventDelegate(BindingClass* obj, void(BindingClass::*method)(CallbackArgs...)) {
        instance = obj;
        callback = [obj, method](CallbackArgs... args) { 
            (obj->*method)(std::forward<CallbackArgs>(args)...); // forward ensures value category preserved
        };
    }

    // @returns if sucessfully fired
    bool Fire(CallbackArgs... args) const {
        if (callback == nullptr) { return false; }
        callback( std::forward<CallbackArgs>(args)... );
        return true;
    }

    inline void* GetInstance() const { return instance; }

};
