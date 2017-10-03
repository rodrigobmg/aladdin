#include "CameraPrefab.h"

void CameraPrefab::doInstantiate( ala::GameObject* object ) {
  new ala::Camera( object, "Camera 2d",
                   ala::GameManager::get()->getScreenWidth(),
                   ala::GameManager::get()->getScreenHeight(),
                   0,
                   ala::Vec2( 1.0f, 1.0f ) );
}
