#include "AgrabahMarketScene.h"
#include "../Define.h"
#include "../scripts/CameraController.h"
#include "../scripts/DebugCameraController.h"
#include "../scripts/NodeController.h"

USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(AgrabahMarketScene, ala::Scene)

void AgrabahMarketScene::onPreInitialize() {
  // constants
  const auto gameManager = GameManager::get();

  // configurations
  enablePhysics( Vec2( 0, -500.0f ) );

  new CameraController( getMainCamera() );

  // initial objects
  gameManager->getPrefabV2( "Sprite" )->instantiateWithArgs( "background.png 0", "Background" )
             ->setTag( BACKGROUND_TAG )
             ->setLayer( "Background" )
             ->getTransform()
             ->setPosition( Vec2( 2385.5f, 344 ) - Vec2( gameManager->getVisibleWidth() / 2,
                                                         gameManager->getVisibleHeight() / 2 ) );

  gameManager->getPrefabV2( "Sprite" )->instantiateWithArgs( "foreground.png 0", "Foreground" )
             ->setTag( FOREGROUND_TAG )
             ->setLayer( "Foreground" )
             ->getTransform()
             ->setPosition( Vec2( 2385.5f, 344 ) - Vec2( gameManager->getVisibleWidth() / 2,
                                                         gameManager->getVisibleHeight() / 2 ) );

  gameManager->getPrefabV2( "Hub" )->instantiateWithArgs( "", "Hub" );

  gameManager->getPrefabV2( "Agrabah Market Ground" )->instantiateWithArgs( "", "Ground" );

  gameManager->getPrefabV2( "Charcoal Burner" )->instantiateWithArgs( "90", "Charcoal Burner 1" )
             ->getTransform()
             ->setPosition( Vec2( 360.5f, -50 ) );

  gameManager->getPrefabV2( "Charcoal Burner" )->instantiateWithArgs( "90", "Charcoal Burner 2" )
             ->getTransform()
             ->setPosition( Vec2( 730.5f, -50 ) );

  gameManager->getPrefabV2( "Charcoal Burner" )->instantiateWithArgs( "90", "Charcoal Burner 3" )
             ->getTransform()
             ->setPosition( Vec2( 906.5f, -50 ) );

  gameManager->getPrefabV2( "Charcoal Burner" )->instantiateWithArgs( "90", "Charcoal Burner 4" )
             ->getTransform()
             ->setPosition( Vec2( 1915.5f, -79 ) );

  gameManager->getPrefabV2( "Charcoal Burner" )->instantiateWithArgs( "110", "Charcoal Burner 4" )
             ->getTransform()
             ->setPosition( Vec2( 2987, -82 ) );

  gameManager->getPrefabV2( "Stair 1" )->instantiateWithArgs( "", "Start 1" );

  gameManager->getPrefabV2( "Guard 1" )->instantiateWithArgs( "550 430 670", "Guard 1" )
             ->getTransform()->setPositionY( -25 );

//  gameManager->getPrefabV2( "Guard 2" )->instantiateWithArgs( "550 200 670", "Guard 2" )
//             ->getTransform()->setPositionY( -25 );

  const auto aladdin = gameManager->getPrefab( "Playable Aladdin" )->instantiate( "Aladdin" );
  aladdin->getTransform()->setPosition( Vec2( -80, -25 ) );
}
