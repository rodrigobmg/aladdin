#include "StaticPlatformPrefab.h"
#include "../Define.h"

USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(StaticPlatformPrefab, ala::PrefabV2)

void StaticPlatformPrefab::doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const {
  // args
  const auto width = nextFloat( argsStream );
  const auto height = nextFloat( argsStream );

  // components
  const auto body = new Rigidbody( object, PhysicsMaterial(), ALA_BODY_TYPE_STATIC );

  const auto collider = new Collider( object, false, Vec2(), Size( width, height ), 1, 0 );

  // collider renderer
  //  new ColliderRenderer( collider );

  // flags
  collider->setFlags( COLLIDE_ENEMY_FLAG | STATIC_FLAG | COLLIDE_FREE_OBJECT_FLAG );
  collider->ignoreIfHasAnyFlags( STATIC_FLAG );

  // configurations
  object->setTag( GROUND_TAG );
  object->setLayer( "Debug" );
}
