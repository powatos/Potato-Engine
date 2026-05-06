#pragma once


class Widget;

class IHUDController
{
public:
    virtual ~IHUDController() = default;

    virtual void RemoveWidget(std::string UID) = 0;
    
    template<typename WidgetClass>
    WidgetClass* AddWidget(std::string UID);
    
protected:
    virtual void RegisterWidget(Widget* widget) = 0;
    

};

template <typename WidgetClass>
WidgetClass* IHUDController::AddWidget(std::string UID) {
    WidgetClass* widget = new WidgetClass(UID);
    RegisterWidget(widget);
    return widget;
}