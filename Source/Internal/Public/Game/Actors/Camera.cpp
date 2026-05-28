/** @file Camera.cpp */

#include "Camera.hpp"

Camera::Camera() {
    SetVisibility(false);

    SetSimulatingPhysics(false);
    SetSize(Vector2(80.f, 24.f));

    Texture = 'C';
}

Camera::~Camera() {
    
}
