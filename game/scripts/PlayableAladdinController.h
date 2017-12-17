#ifndef __PLAYABLE_ALADDIN_CONTROLLER_H__
#define __PLAYABLE_ALADDIN_CONTROLLER_H__

#include <aladdin.h>
#include "../app/MyAppData.h"

ALA_CLASS_HEADER_1( PlayableAladdinController, ala::GameObjectComponent)
private:
  int _maxHealth;
  int _maxLives;
  int _maxApples;

  int _health;
  int _lives;
  int _apples;
  bool _recovering;
  bool _hit;
  bool _jumpOnCamel;
  bool _jumpOnSpring;
  bool _pushingWall;
  bool _reachedTopOfRope;
  ala::GameObject* _holdingRope;
  ala::GameObject* _holdingBar;

  ala::Transform* _selfTransform;
  ala::ActionManager* _selfActionManager;
  ala::StateManager* _selfStateManager;
  ala::Animator* _selfAnimator;
  ala::Collider* _selfBodyCollider;
  ala::PrefabV2* _throwableApplePrefab;

  MyAppData* _myAppData;

public:
  PlayableAladdinController( ala::GameObject* gameObject, const std::string& name = "" );

  void setLives( const int lives );

  int getLives() const;

  void setApples( const int apples );

  int getApples() const;

  void setHealth( const int health );

  int getHealth() const;

  bool isRecovering() const;

  void setRecovering();

  void resetJumpOnCamel();

  bool isJumpOnCamel() const;

  void resetJumpOnSpring();

  bool isJumpOnSpring() const;

  void resetHit();

  bool isHit() const;

  bool isPushingWall() const;

  void resetHoldingRope();

  bool isHoldingRope() const;

  ala::GameObject* getHodingRope() const;

  bool hasReachedTopOfRope() const;

  void resetHoldingBar();

  bool isHoldingBar() const;

  ala::GameObject* getHoldingBar() const;

  void throwApple( const char direction,
                   const float offsetX, const float offsetY,
                   const float impulseX, const float impulseY );

  void onCollisionEnter( const ala::CollisionInfo& collision ) override;

  void onCollisionExit( const ala::CollisionInfo& collision ) override;

  void onTriggerEnter( const ala::CollisionInfo& collision ) override;

  void onTriggerStay( const ala::CollisionInfo& collision ) override;

  void onTriggerExit( const ala::CollisionInfo& collision ) override;

protected:
  void onInitialize() override;

private:
  void onHitCharcoalBurner();

  void onHit( const int damage = 1 );

  void onJumpOnCamel();

  void onJumpOnSpring( ala::GameObject* spring );

  void onCatchRope( ala::GameObject* rope );

  void onCatchBar( ala::GameObject* bar );
};

#endif //!__PLAYABLE_ALADDIN_CONTROLLER_H__
