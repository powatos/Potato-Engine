/** @file PlayerController.hpp */
#pragma once

#include "Game/Actors/Player.hpp"
#include "Game/Actors/Camera.hpp"
#include "Core/Event/Tickable.hpp"

/**
 * @brief Main managing class for the player, controlling interactions and non-local behavior
 * @details 
 */
class PlayerController : public Tickable
{
public:
    /**
     * @internal
     * @brief Constructs player controller
     */
    PlayerController();
    virtual ~PlayerController();

    char temp;

    void Initialize();
    void AssignPlayer(Player* player);

    /** @brief Gets assigned Player @returns Player */
    Player* GetPlayer() const;
    /** @brief Gets assigned Camera @returns Camera */
    Camera* GetCamera() const;

    /**
     * @brief Called automatically to bind player inputs to InputController
     * @details Override to setup bindings:
     * @code
     * IInputController* controller = PotatoEngine::Get().GetInputController();
     * controller->RegisterInputBinding(
     *     InputBinding(
     *         Keycode::Space, 
     *         InputType::Triggered, 
     *         "JumpAction", 
     *         this, 
     *         &PlayerController::DoJump)
     * );
     * @endcode
     * @note Always call base method when overriding:
     * @code
     * void PlayerControllerClass::SetupInputBindings() {
     *     BasePlayerController::SetupInputBindings();
     *     // ...
     * }
     * @endcode
     */
    virtual void SetupInputBindings();


protected:
    virtual void Tick([[maybe_unused]] float dt) override;

    float TargetMovementVelocity;
    float JumpForce;

private:
    Player* ActivePlayer;
    Camera* ActiveCamera;
    Vector2 playerMoveVec;

    void sMvL(); void eMvL();
    void sMvR(); void eMvR();
    void jump();

};