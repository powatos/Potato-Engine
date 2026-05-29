/** @file DebugInfo.cpp */

#include "Core/Control/GameInstance.hpp"
#include "UI/Widgets/TextElement.hpp"

#include "DebugInfo.hpp"

DebugInfo::DebugInfo(std::string UID) : Widget(std::move(UID)) {
    
    TextElement* playerPosElem = AddElement<TextElement>("PlayerPosText");
    TextElement* playerVelElem = AddElement<TextElement>("PlayerVelText");

    playerPosElem->SetScreenPosition(Vector2(0.0,0.0));
    playerVelElem->SetScreenPosition(Vector2(0.0,1.0));

    playerPosElem->SetVisibility(true);
    playerVelElem->SetVisibility(true);

    SetScreenSize(Vector2(40.0, 5.0));
    SetScreenPosition(Vector2(0.0, 0.0));

    SetTicking(true);
    SetVisibility(true);
}

void DebugInfo::Tick([[maybe_unused]] float dt) {
    Widget::Tick(dt);

    PlayerController* plrCtrl = GameInstance::Get()->GetPlayerController();
    Vector2 playerPos = plrCtrl->GetPlayer()->GetPosition();
    Vector2 playerVel = plrCtrl->GetPlayer()->GetVelocity();
    
    dynamic_cast<TextElement*>(GetElement("PlayerPosText"))->field = "Player position: " + playerPos.ToString();
    dynamic_cast<TextElement*>(GetElement("PlayerVelText"))->field = "Player velocity: " + playerVel.ToStringF();

}

DebugInfo::~DebugInfo() {

} 