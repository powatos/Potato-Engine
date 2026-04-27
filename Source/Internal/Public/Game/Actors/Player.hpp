
#include "Game/Actors/Entity.hpp"

class Player : public Entity
{

public:
    Player();
    virtual ~Player();

protected:
    
    void MoveLeft();
    void MoveRight();
    void MoveUp();
    void MoveDown();

};
