/** @file Block.cpp */

#include "Block.hpp"

ARCHIVE_STATIC(Block)

Block::Block() {
    SetSize(Vector2(20, 5));
    SetMovability(ActorMovability::Static);

    SetUsingCTex(true);
    ctex = 'B';
}