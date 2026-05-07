
#include "Game/Control/GameInstance.hpp"
#include "Game/UI/Widgets/TextElement.hpp"

#include "DebugInfo.hpp"

DebugInfo::DebugInfo(std::string UID) : Widget(std::move(UID)) {
    
    TextElement* playerPosElem = AddElement<TextElement>("PlayerPosText");
    TextElement* cameraPosElem = AddElement<TextElement>("CameraPosText");

    playerPosElem->SetScreenPosition(Vector2(0,0));
    cameraPosElem->SetScreenPosition(Vector2(0,1));

    playerPosElem->SetVisibility(true);
    cameraPosElem->SetVisibility(true);

    SetScreenSize(Vector2(30, 4));
    SetScreenPosition(Vector2(0,0));

    SetTicking(true);
    SetVisibility(false);
}

void DebugInfo::Tick(float dt) {
    PlayerController* plrCtrl = GameInstance::get()->GetPlayerController();
    Vector2 playerPos = plrCtrl->GetPlayer()->GetPosition();
    Vector2 cameraPos = plrCtrl->GetCamera()->GetPosition();
    
    dynamic_cast<TextElement*>(GetElement("PlayerPosText"))->field = "Player position: " + playerPos.ToString();
    dynamic_cast<TextElement*>(GetElement("CameraPosText"))->field = "Camera position: " + cameraPos.ToString();

}

DebugInfo::~DebugInfo() {

} 