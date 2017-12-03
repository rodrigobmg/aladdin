#include "ThinGuardPrefab.h"
#include "../scripts/ThinGuardController.h"
#include "../Define.h"

USING_NAMESPACE_ALA;

void ThinGuardPrefab::doInstantiate(ala::GameObject* object) const
{
	// constants
	const auto gameManager = GameManager::get();
	const auto input = Input::get();

	const auto density = 5.0f;
	const auto runVelocity = 100.0f;

	// components
	const auto spriteRenderer = new SpriteRenderer(object, "guards.png");
	const auto animator = new Animator(object, "enemy_guard_run", "guards.anm");

	// For animationEditor
	/*const auto animationEditor = new AnimationEditor( object, "fat_guard_run" );
	object->getTransform()->setPosition( 80, -40 );
	return;*/
	// For animationEditor

	const auto body = new Rigidbody(object, PhysicsMaterial(density), ALA_BODY_TYPE_DYNAMIC, 1.0f);
	const auto collider = new Collider(object, false, Vec2(0, 0), Size(40, 50));
	collider->setTag(ENEMY_TAG);

	const auto colliderRenderer = new ColliderRenderer(collider);
	const auto timer1 = new Timer(object);
	const auto stateManager = new StateManager(object, "enemy_guard_run_left");
	const auto controller = new ThinGuardController(object);
	const auto transform = object->getTransform();
	// states

	new State(stateManager, "enemy_guard_run_left",
		[=]{
		animator->setAction("enemy_guard_run");
		transform->setScaleX(ABS(transform->getScale().getX()));
		timer1->start(2);
		body->setVelocity(Vec2(-runVelocity, body->getVelocity().getY()));
	}, [=](float dt) {

	}, NULL);

	new State(stateManager, "enemy_guard_run_left_to_Aladdin",
		[=] {
		animator->setAction("enemy_guard_run");
		transform->setScaleX(ABS(transform->getScale().getX()));
		body->setVelocity(Vec2(-runVelocity, body->getVelocity().getY()));
	}, [=](float dt) {

	}, NULL);

	new State(stateManager, "enemy_guard_run_right",
		[=] {
		animator->setAction("enemy_guard_run");
		transform->setScaleX(-ABS(transform->getScale().getX()));
		timer1->start(2);
		body->setVelocity(Vec2(runVelocity, body->getVelocity().getY()));
		
	}, [=](float dt) {}, NULL);
	new State(stateManager, "enemy_guard_run_right_to_Aladdin",
		[=] {
		animator->setAction("enemy_guard_run");
		transform->setScaleX(-ABS(transform->getScale().getX()));
		timer1->start(2);
		body->setVelocity(Vec2(runVelocity, body->getVelocity().getY()));

	}, [=](float dt) {}, NULL);

	new State(stateManager, "enemy_guard_attack_left", 
		[=]{
		animator->setAction("enemy_guard_attack");
		transform->setScaleX(ABS(transform->getScale().getX()));
		body->setVelocity(Vec2(0,0));
	}, NULL, NULL);

	new State(stateManager, "enemy_guard_attack_right",
		[=] {
		animator->setAction("enemy_guard_attack");
		transform->setScaleX(-ABS(transform->getScale().getX()));
		body->setVelocity(Vec2(0, 0));
	}, NULL, NULL);

	new StateTransition(stateManager, "enemy_guard_run_left", "enemy_guard_run_right", [=]{
		return timer1->isDone();
	});
	new StateTransition(stateManager, "enemy_guard_run_right", "enemy_guard_run_left", [=] {
		return timer1->isDone();
	});

	new StateTransition(stateManager, "enemy_guard_run_left", "enemy_guard_run_left_to_Aladdin", [=] {
		return controller->isSeeingWithAladdin();
	});
	new StateTransition(stateManager, "enemy_guard_run_left_to_Aladdin", "enemy_guard_attack_left", [=] {
		return controller->isCollidedWithAladdin();
	});
	new StateTransition(stateManager, "enemy_guard_attack_left", "enemy_guard_run_left_to_Aladdin", [=] {
		if(controller->isCollidedWithAladdin() == false && controller->isInTheLeftAladdin() == true)
		{
			return true;
		}
		else return false;
	});
	new StateTransition(stateManager, "enemy_guard_run_right", "enemy_guard_run_right_to_Aladdin", [=] {
		return controller->isSeeingWithAladdin();
	});
	new StateTransition(stateManager, "enemy_guard_run_right", "enemy_guard_attack_right", [=] {
		return controller->isCollidedWithAladdin();
	});
	new StateTransition(stateManager, "enemy_guard_attack_right", "enemy_guard_run_right_to_Aladdin", [=] {
		if (controller->isCollidedWithAladdin() == false && controller->isInTheLeftAladdin() == false)
		{
			return true;
		}
		else return false;
	});
	new StateTransition(stateManager, "enemy_guard_run_right", "enemy_guard_run_right_to_Aladdin", [=] {
		return controller->isSeeingWithAladdin();
	});
	new StateTransition(stateManager, "enemy_guard_attack_left", "enemy_guard_run_right_to_Aladdin", [=] {
		if (controller->isCollidedWithAladdin() == false && controller->isInTheLeftAladdin() == false )
		{
			return true;
		}
		else return false;
	});
	new StateTransition(stateManager, "enemy_guard_run_right_to_Aladdin", "enemy_guard_attack_right", [=] {
		return controller->isCollidedWithAladdin();
	});
	new StateTransition(stateManager, "enemy_guard_attack_right", "enemy_guard_run_left_to_Aladdin", [=] {
		if (controller->isCollidedWithAladdin() == false && controller->isInTheLeftAladdin() == true)
		{
			return true;
		}
		else return false;
	});
}
