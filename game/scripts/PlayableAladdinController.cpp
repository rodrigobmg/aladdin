#include "PlayableAladdinController.h"
#include "DirectionController.h"
#include "../Define.h"

USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(PlayableAladdinController, ala::GameObjectComponent)

PlayableAladdinController::
PlayableAladdinController( ala::GameObject* gameObject, const std::string& name )
  : GameObjectComponent( gameObject, name ), _health( 0 ), _lives( 0 ), _apples( 0 ), _recovering( false ),
    _hit( false ),
    _jumpOnCamel( false ),
    _pushingWall( false ),
    _reachedTopOfRope( false ),
    _holdingRope( NULL ),
    _selfTransform( NULL ),
    _selfActionManager( NULL ), _selfStateManager( NULL ), _selfAnimator( NULL ), _selfBodyCollider( NULL ),
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
    new CallFunc( [this] {
      _recovering = false;
      _hit = false;
    } )
  } ) );
}

void PlayableAladdinController::resetJumpOnCamel() {
  _jumpOnCamel = false;
}

bool PlayableAladdinController::isJumpOnCamel() const {
  return _jumpOnCamel;
}

void PlayableAladdinController::resetHit() {
  _hit = false;
}

bool PlayableAladdinController::isHit() const {
  return _hit;
}

bool PlayableAladdinController::isPushingWall() const {
  return _pushingWall;
}

void PlayableAladdinController::resetHoldingRope() {
  _holdingRope = NULL;
  _reachedTopOfRope = false;
}

bool PlayableAladdinController::isHoldingRope() const {
  return _holdingRope != NULL;
}

bool PlayableAladdinController::hasReachedTopOfRope() const {
  return _reachedTopOfRope;
}

ala::GameObject* PlayableAladdinController::getHodingRope() const {
  return _holdingRope;
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

void PlayableAladdinController::onCollisionEnter( const ala::CollisionInfo& collision ) {
  const auto otherCollider = collision.getColliderA()->getGameObject() == getGameObject()
                               ? collision.getColliderB()
                               : collision.getColliderA();
  const auto otherObject = otherCollider->getGameObject();

  if ( otherObject->getTag() == WALL_TAG && otherCollider->getTag() == WALL_TAG
    && collision.getNormal().getY() == 0 ) {
    _pushingWall = true;
  }
}

void PlayableAladdinController::onCollisionExit( const ala::CollisionInfo& collision ) {
  const auto otherCollider = collision.getColliderA()->getGameObject() == getGameObject()
                               ? collision.getColliderB()
                               : collision.getColliderA();
  const auto otherObject = otherCollider->getGameObject();

  if ( otherObject->getTag() == WALL_TAG && otherCollider->getTag() == WALL_TAG ) {
    _pushingWall = false;
  }
}

void PlayableAladdinController::onTriggerEnter( const ala::CollisionInfo& collision ) {
  const auto otherCollider = collision.getColliderA()->getGameObject() == getGameObject()
                               ? collision.getColliderB()
                               : collision.getColliderA();
  const auto otherObject = otherCollider->getGameObject();

  if ( otherObject->getTag() == ENEMY_TAG && otherCollider->getTag() == SWORD_TAG ) {
    onHit();
  }
  else if ( otherObject->getTag() == VASE_TAG ) {
    onHit();
  }
  else if ( otherObject->getTag() == CAMEL_TAG && otherCollider->getTag() == CAMEL_TAG ) {
    if ( collision.getNormal() == Vec2( 0, 1 ) ) {
      onJumpOnCamel();
    }
  }
  else if ( otherObject == _holdingRope && otherCollider->getName() == "T" ) {
    _reachedTopOfRope = true;
  }
}

void PlayableAladdinController::onTriggerStay( const ala::CollisionInfo& collision ) {
  const auto otherCollider = collision.getColliderA()->getGameObject() == getGameObject()
                               ? collision.getColliderB()
                               : collision.getColliderA();
  const auto otherObject = otherCollider->getGameObject();

  if ( otherObject->getTag() == CHARCOAL_BURNER_TAG ) {
    onHitCharcoalBurner();
  }
  else if ( otherObject->getTag() == ROPE_TAG ) {
    if ( !isHoldingRope() ) {
      if ( otherCollider->getName() == "M"
        && ABS(_selfTransform->getPositionX() - otherObject->getTransform()->getPositionX()) <= 5 ) {
        onCatchRope( otherObject );
      }
    }
    else if ( otherObject == _holdingRope && otherCollider->getName() == "T" ) {
      _reachedTopOfRope = true;
    }
  }
}

void PlayableAladdinController::onTriggerExit( const ala::CollisionInfo& collision ) {
  const auto otherCollider = collision.getColliderA()->getGameObject() == getGameObject()
                               ? collision.getColliderB()
                               : collision.getColliderA();
  const auto otherObject = otherCollider->getGameObject();

  if ( otherObject == _holdingRope ) {
    if ( otherCollider->getName() == "M" ) {
      resetHoldingRope();
    }
    else if ( otherCollider->getName() == "T" ) {
      _reachedTopOfRope = false;
    }
  }
}

void PlayableAladdinController::onInitialize() {
  _selfTransform = getGameObject()->getTransform();
  _selfActionManager = getGameObject()->getComponentT<ActionManager>();
  _selfStateManager = getGameObject()->getComponentT<StateManager>();
  _selfAnimator = getGameObject()->getComponentT<Animator>();
  _selfBodyCollider = static_cast<Collider*>(getGameObject()->getComponent( "Body" ));
  _throwableApplePrefab = GameManager::get()->getPrefabV2( "Throwable Apple" );
}

void PlayableAladdinController::onHitCharcoalBurner() {
  if ( _selfStateManager->getCurrentStateName() == "idle" ) {
    onHit();
  }
}

void PlayableAladdinController::onHit( const int damage ) {
  if ( _recovering ) return;

  _health -= damage;
  _hit = true;

  setRecovering();
}

void PlayableAladdinController::onJumpOnCamel() {
  _jumpOnCamel = true;

  // TODO: refactor to state transition
  _selfStateManager->changeState( "jump" );
}

void PlayableAladdinController::onCatchRope( ala::GameObject* rope ) {
  if ( isHoldingRope() ||
    _selfStateManager->getCurrentStateName() == "climb" ||
    _selfAnimator->getActionName() == "climb_to_jump" )
    return;

  _holdingRope = rope;

  // TODO: refactor to state transition
  _selfStateManager->changeState( "climb" );
}
