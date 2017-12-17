#include "JumpableSpringPrefab.h"
#include "../Define.h"

USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(JumpableSpringPrefab, ala::PrefabV2)

void JumpableSpringPrefab::doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const {
  // components
  const auto spriteRenderer = new SpriteRenderer( object, "items.png" );

  const auto animator = new Animator( object, "spring_0", "items.anm" );

  const auto stateManager = new StateManager( object, "static" );

  const auto body = new Rigidbody( object, PhysicsMaterial(), ALA_BODY_TYPE_STATIC );

  const auto collider = new Collider( object, true, Vec2( 0, 0 ), Size( 30, 15 ), 1, 0 );
  collider->setTag( SPRING_TAG );
  collider->ignoreTag( SPRING_TAG );
  collider->ignoreTag( ENEMY_TAG );
  collider->ignoreTag( APPLE_TAG );
  collider->ignoreTag( SWORD_TAG );

  // helpers
  const auto transform = object->getTransform();

  // collider renderers
  new ColliderRenderer( collider );

  // configurations
  object->setTag( SPRING_TAG );
  object->setLayer( "Debug" );

  // states
  new State( stateManager, "static",
             [=] { animator->setAction( "spring_0" ); },
             NULL, NULL );

  new State( stateManager, "dynamic",
             [=] { animator->setAction( "spring" ); },
             NULL, NULL );

  new StateTransition( stateManager, "static", "dynamic", [=] {
    return !animator->isPlaying();
  } );
}
