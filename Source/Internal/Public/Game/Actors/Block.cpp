/** @file Block.cpp */

#include "Block.hpp"

ARCHIVE_STATIC(Block)

Block::Block() {
    Texture = 'B';
    SetSize(Vector2(20, 5));
    SetMovability(ActorMovability::Static);
}