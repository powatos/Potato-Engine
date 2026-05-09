#pragma once

#include "Game/Actors/Player.hpp"
#include "Game/Actors/Camera.hpp"
#include "Core/Event/Tickable.hpp"

class PlayerController : public Tickable
{
public:
    PlayerController();
    virtual ~PlayerController();

    void Initialize();

    void AssignPlayer(Player* player);

    Player* GetPlayer() const;
    Camera* GetCamera() const;

    virtual void SetupInputBindings();

protected:
    Player* ActivePlayer;
    Camera* ActiveCamera;

    virtual void Tick(float dt) override;

private:
    Vector2 playerMoveVec;

    void sMvL(); void eMvL();
    void sMvR(); void eMvR();
    void sMvU(); void eMvU();
    void sMvD(); void eMvD();
};