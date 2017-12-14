#include "PlayableAladdinController.h"
#include "DirectionController.h"
#include "../Define.h"

USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(PlayableAladdinController, ala::GameObjectComponent)

PlayableAladdinController::
PlayableAladdinController( ala::GameObject* gameObject, const std::string& name )
  : GameObjectComponent( gameObject, name ), _health( 0 ), _lives( 0 ), _apples( 0 ), _recovering( false ),
    _selfTransform( NULL ),
    _selfActionManager( NULL ), _selfStateManager( NULL ), _selfBodyCollider( NULL ),
    _throwableApplePrefab( NULL ) {}

void PlayableAladdinController::setLives( const int lives ) {
  _lives = lives;
}

int PlayableAladdinController::getLives() const {
  return _lives;
}

void PlayableAladdinController::setApples( const int apples ) {
  _apples = apples;
}

int PlayableAladdinController::getApples() const {
  return _apples;
}

void PlayableAladdinController::setHealth( const int health ) {
  _health = health;
}

int PlayableAladdinController::getHealth() const {
  return _health;
}

bool PlayableAladdinController::isRecovering() const {
  return _recovering;
}

void PlayableAladdinController::setRecovering() {
  if ( _recovering ) return;

  _recovering = true;

  _selfActionManager->play( new Sequence( {
    new Blink( 0.05f, 10 ),
    new CallFunc( [this] { this->_recovering = false; } )
  } ) );
}

void PlayableAladdinController::throwApple( const char direction,
                                            const float offsetX, const float offsetY,
                                            const float impulseX, const float impulseY ) {
  if ( _apples <= 0 ) return;
  _apples -= 1;

  std::stringstream argsStream;
  argsStream << direction << ' ' << impulseX << ' ' << impulseY;

  _throwableApplePrefab->instantiateWithArgs( argsStream.str() )
                       ->getTransform()
                       ->setPosition( _selfTransform->getPosition() +
                         Vec2( _selfBodyCollider->getSize().getWidth() / 2 + offsetX,
                               _selfBodyCollider->getSize().getHeight() / 2 + offsetY ) );
}

void PlayableAladdinController::onCollisionEnter( const ala::CollisionInfo& collision ) {}

void PlayableAladdinController::onTriggerEnter( const ala::CollisionInfo& collision ) {
  const auto otherCollider = collision.getColliderA()->getGameObject() == getGameObject()
                               ? collision.getColliderB()
                               : collision.getColliderA();
  const auto otherObject = otherCollider->getGameObject();

  if ( otherObject->getTag() == ENEMY_TAG && otherCollider->getTag() == SWORD_TAG ) {
    onHit();
  }
}

void PlayableAladdinController::onTriggerStay( const ala::CollisionInfo& collision ) {
  const auto otherCollider = collision.getColliderA()->getGameObject() == getGameObject()
                               ? collision.getColliderB()
                               : collision.getColliderA();
  const auto otherObject = otherCollider->getGameObject();

  if ( otherObject->getTag() == CHARCOAL_BURNER_TAG ) {
    onHit();
  }
}

void PlayableAladdinController::onTriggerExit( const ala::CollisionInfo& collision ) {}

void PlayableAladdinController::onInitialize() {
  _selfTransform = getGameObject()->getTransform();
  _selfActionManager = getGameObject()->getComponentT<ActionManager>();
  _selfStateManager = getGameObject()->getComponentT<StateManager>();
  _selfBodyCollider = static_cast<Collider*>(getGameObject()->getComponent( "Body" ));
  _throwableApplePrefab = GameManager::get()->getPrefabV2( "Throwable Apple" );
}

void PlayableAladdinController::onHit() {
  if ( _recovering ) return;

  if ( _selfStateManager->getCurrentStateName() == "idle" ) {
    setRecovering();
    _selfStateManager->changeState( "hit" );
  }
}
