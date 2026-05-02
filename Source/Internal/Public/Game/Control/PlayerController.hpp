#pragma once

class Player;
class Camera;

class PlayerController
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

private:
    void MoveLeft();
    void MoveRight();
    void MoveUp();
    void MoveDown();
};