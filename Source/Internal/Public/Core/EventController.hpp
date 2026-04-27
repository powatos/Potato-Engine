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

struct InputBinding
{
// optimized declaration order 
public:
    std::string name;

private:
    EventDelegate delegate;

public:
    char targetKey;
    bool isCaseSensitive;

    template<typename T>
    InputBinding(char targetKey, std::string name, T* obj, void(T::*callback)(), bool isCaseSensitive = false) : 
        name(name),
        delegate(obj, callback),
        targetKey(targetKey), 
        isCaseSensitive(isCaseSensitive)
    {}

    inline const EventDelegate& GetDelegate() const { return delegate; }

};

class IEventController
{
public:
    virtual ~IEventController() = default;

    virtual void RegisterInputBinding(InputBinding binding) = 0; 
    virtual void UnregisterInputBinding(std::string name) = 0;
    virtual void UnregisterAllInputBindings(void* object) = 0;

};