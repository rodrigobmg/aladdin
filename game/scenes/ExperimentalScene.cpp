/*
 * Created by phuctm97 on Sep 30th 2017
 */

#include "ExperimentalScene.h"
#include "../scripts/CameraController.h"
#include "../scripts/NodeController.h"
#include "../Define.h"

USING_NAMESPACE_ALA;

ExperimentalScene::ExperimentalScene() : _logger( "ExperimentalScene" ) {}

void ExperimentalScene::onPreInitialize() {
  // constants
  const auto gameManager = GameManager::get();

  // configurations
  enablePhysics( Vec2( 0, -500.0f ) );
  new CameraController( getMainCamera() );

  // initial objects
  const auto background = new GameObject( this, "Background" );
  background->setTag( BACKGROUND_TAG );

  const auto backgroundSpriteRenderer = new SpriteRenderer( background, "background.png" );
  background->setLayer( "Background" );
  background->getTransform()->setPosition(
    Vec2( backgroundSpriteRenderer->getFrameSize().getWidth() / 2,
          backgroundSpriteRenderer->getFrameSize().getHeight() / 2 )
    - Vec2( gameManager->getVisibleWidth() / 2,
            gameManager->getVisibleHeight() / 2 ) );


  const auto foreground = new GameObject( this, "Foreground" );
  foreground->setTag( FOREGROUND_TAG );

  const auto foregroundSpriteRenderer = new SpriteRenderer( foreground, "foreground.png" );
  foreground->setLayer( "Foreground" );
  foreground->getTransform()->setPosition(
    Vec2( foregroundSpriteRenderer->getFrameSize().getWidth() / 2,
          foregroundSpriteRenderer->getFrameSize().getHeight() / 2 )
    - Vec2( gameManager->getVisibleWidth() / 2,
            gameManager->getVisibleHeight() / 2 ) );

  const auto ground = gameManager->getPrefab( "Ground" )->instantiate( "Ground" );
  ground->setTag( GROUND_TAG );

  const auto ropeOne = gameManager->getPrefab( "Rope" )->instantiate( "Rope 1" );
  ropeOne->setLayer( "Background" );
  ropeOne->getTransform()->setPosition( Vec2( 1931, 86 ) );
  ropeOne->getComponentT<Collider>()->setSize( Size( 5, 250 ) );

  const auto ropeTwo = gameManager->getPrefab( "Rope" )->instantiate( "Rope 2" );
  ropeTwo->setLayer( "Background" );
  ropeTwo->getTransform()->setPosition( Vec2( 1387, 298 ) );
  ropeTwo->getComponentT<Collider>()->setSize( Size( 5, 193 ) );

  const auto ropeThree = gameManager->getPrefab( "Rope" )->instantiate( "Rope 3" );
  ropeThree->setLayer( "Background" );
  ropeThree->getTransform()->setPosition( Vec2( 2539, 345 ) );
  ropeThree->getComponentT<Collider>()->setSize( Size( 5, 249 ) );

  const auto ropeFour = gameManager->getPrefab( "Rope" )->instantiate( "Rope 4" );
  ropeFour->setLayer( "Background" );
  ropeFour->getTransform()->setPosition( Vec2( 4555, 99 ) );
  ropeFour->getComponentT<Collider>()->setSize( Size( 5, 193 ) );

  const auto aladdin = gameManager->getPrefab( "Aladdin" )->instantiate( "Aladdin" );
  aladdin->setTag( ALADDIN_TAG );
  aladdin->setLayer( "Character" );
  aladdin->getTransform()->setPosition( Vec2( 900, -25 ) );

  /*const auto adorable_enemy = gameManager->getPrefab("Adorable Guard")->instantiate("Adorable Guard");
  adorable_enemy->setLayer("Enemy");
  adorable_enemy->getTransform()->setPosition(Vec2(500, -40));*/

  const auto nake_enemy = gameManager->getPrefab("Nake Guard")->instantiate("Nake Guard");
  nake_enemy->setLayer("Enemy");
  nake_enemy->getTransform()->setPosition(Vec2(500, -40));

  const auto hide_enemy = gameManager->getPrefab("Hide Guard")->instantiate("Hide Guard");
  hide_enemy->setLayer("Enemy");
  hide_enemy->getTransform()->setPosition(Vec2(200, -40));
}

void ExperimentalScene::onPreRelease() {}
