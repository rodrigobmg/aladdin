/*
 * Created by phuctm97 on Sep 30th 2017
 */

#include "ExperimentalScene.h"
#include "../scripts/CameraController.h"
#include "../scripts/GuardController.h"
#include "../scripts/NodeController.h"
#include "../prefabs/PendalPrefab.h"
#include "../Define.h"

USING_NAMESPACE_ALA;

ExperimentalScene::ExperimentalScene() : _logger("ExperimentalScene") {}

void ExperimentalScene::onPreInitialize() {

  // constants
  const auto gameManager = GameManager::get();
  const auto halfVisibleWidth = gameManager->getVisibleWidth() / 2;
  const auto halfVisibleHeight = gameManager->getVisibleHeight() / 2;

  // configurations
  enablePhysics( Vec2( 0, -500.0f ) );

  //  enableQuadTree( -halfVisibleWidth, -halfVisibleHeight,
  //                  4771 - halfVisibleWidth, 688 - halfVisibleHeight, 3 );

  new CameraController( getMainCamera() );


	// initial objects
	const auto background = new GameObject(this, "Background");
	background->setTag(BACKGROUND_TAG);

	const auto backgroundSpriteRenderer = new SpriteRenderer(background, "background.png");
	background->setLayer("Background");
	background->getTransform()->setPosition(
		Vec2(backgroundSpriteRenderer->getFrameSize().getWidth() / 2,
			backgroundSpriteRenderer->getFrameSize().getHeight() / 2)
		- Vec2(gameManager->getVisibleWidth() / 2,
			gameManager->getVisibleHeight() / 2));

	const auto foreground = new GameObject(this, "Foreground");
	foreground->setTag(FOREGROUND_TAG);

	const auto foregroundSpriteRenderer = new SpriteRenderer(foreground, "foreground.png");
	foreground->setLayer("Foreground");
	foreground->getTransform()->setPosition(
		Vec2(foregroundSpriteRenderer->getFrameSize().getWidth() / 2,
			foregroundSpriteRenderer->getFrameSize().getHeight() / 2)
		- Vec2(gameManager->getVisibleWidth() / 2,
			gameManager->getVisibleHeight() / 2));

	const auto hub = gameManager->getPrefab("Hub")->instantiate("Hub");

	const auto ground = gameManager->getPrefab("Ground")->instantiate("Ground");

	const auto ropeOne = gameManager->getPrefab("Rope")->instantiate("Rope 1");
	ropeOne->getTransform()->setPosition(Vec2(1931, 86));
	ropeOne->getComponentT<Collider>()->setSize(Size(5, 250));

	/*const auto ropeTwo = gameManager->getPrefab("Rope")->instantiate("Rope 2");
	ropeTwo->getTransform()->setPosition(Vec2(1387, 298));
	ropeTwo->getComponentT<Collider>()->setSize(Size(5, 193));*/

	const auto ropeThree = gameManager->getPrefab("Rope")->instantiate("Rope 3");
	ropeThree->getTransform()->setPosition(Vec2(2539, 345));
	ropeThree->getComponentT<Collider>()->setSize(Size(5, 249));

	const auto ropeFour = gameManager->getPrefab("Rope")->instantiate("Rope 4");
	ropeFour->getTransform()->setPosition(Vec2(4555, 99));
	ropeFour->getComponentT<Collider>()->setSize(Size(5, 193));

	const auto charcoalBurnerOne = gameManager->getPrefab("Charcoal Burner")->instantiate("Charcoal Burner 1");
	charcoalBurnerOne->getTransform()->setPosition(Vec2(360.5f, -50));

	const auto charcoalBurnerTwo = gameManager->getPrefab("Charcoal Burner")->instantiate("Charcoal Burner 2");
	charcoalBurnerTwo->getTransform()->setPosition(Vec2(730.5f, -50));

	const auto charcoalBurnerThree = gameManager->getPrefab("Charcoal Burner")->instantiate("Charcoal Burner 3");
	charcoalBurnerThree->getTransform()->setPosition(Vec2(906.5f, -50));

	const auto guardOne = gameManager->getPrefab("Thin Guard")->instantiate("Guard 1");
	guardOne->getTransform()->setPositionY(-25);
	guardOne->getComponentT<GuardController>()->set( 550, 430, 670 );
	
	const auto guardTwo = gameManager->getPrefab( "Fat Guard" )->instantiate( "Guard 2" );
    guardTwo->getTransform()->setPositionY( -25 );
    guardTwo->getComponentT<GuardController>()->set( 818, 620, 992 );

	const auto aladdin = gameManager->getPrefab("Aladdin")->instantiate("Aladdin");
	aladdin->getTransform()->setPosition( Vec2( -80, -25 ) );
	//aladdin->getTransform()->setPosition(Vec2(4190.5f, 200));
	

#pragma region Stair

	//const auto stairGroupOne = gameManager->getPrefab("StairGroupOne")->instantiate();

	const auto stairGroupTwo = gameManager->getPrefab("StairGroupTwo")->instantiate("StairGroupTwo");

	const auto stairGroupThree = gameManager->getPrefab("StairGroupThree")->instantiate("StairGroupThree");

#pragma endregion

#pragma region MapBlocker
	const auto mapBlocker = gameManager->getPrefab("MapBlocker")->instantiate();
	mapBlocker->getTransform()->setPosition(Vec2(1300.5f, -51.5f));
	mapBlocker->getComponentT<Collider>()->setSize(Size(31, 101));

	//mapBlocker->setTag(ALADDIN_TAG);
	//new NodeController(mapBlocker);
#pragma endregion

#pragma region Apples
	/*float appleGroupOneX[] = { 325.5f, 355.0f, 388.0f, 691.5f, 723.0f, 755.5f, 869.5f, 901.5f, 932.0f,1363.0f, 1396.5f, 1409.0f, 1490.5f, 1526.0f, 1559.0f, 1589.0f, 1619.5f };
	float appleGroupOneY[] = { 27.5f, 43.0f, 27.5f, 25.5f, 44.5f, 25.5f, 27.0f, 45.0f, 27.0f, 90.5f, 75.0f, 41.0f, 14.5f, 29.5f, 14.5f, 29.5f, 14.5f };
	for (int index = 0; index < 17; index++)
	{
		const auto newApple = gameManager->getPrefab("Apple")->instantiate();
		newApple->getTransform()->setPosition(Vec2(appleGroupOneX[index], appleGroupOneY[index]));
	}*/

	/*const auto runningApple = gameManager->getPrefab("Apple")->instantiate();
	runningApple->getTransform()->setPosition(Vec2(0 ,0));

	runningApple->setTag(ALADDIN_TAG);
	new NodeController(runningApple);*/
#pragma endregion

#pragma region Horizontal bar

	const auto horizontalBar= gameManager->getPrefab("HorizontalBar")->instantiate();
	horizontalBar->getTransform()->setPosition(Vec2(4403.0f, 262.5f));
	horizontalBar->getComponentT<Collider>()->setSize(Size(380.0f, 8.0f));

	/*const auto runningBlock = gameManager->getPrefab("HorizontalBar")->instantiate();
	runningBlock->getTransform()->setPosition(Vec2(3000 ,0));

	runningBlock->setTag(ALADDIN_TAG);
	new NodeController(runningBlock);*/
#pragma endregion

#pragma region Platform

	/*const auto platform1 = gameManager->getPrefab("Platform")->instantiate();
	platform1->getTransform()->setPosition(Vec2(1735.0f, 128.0f));
	static_cast<Collider*>(platform1->getComponent("Upon"))->setSize(Size(295.0f, 4.5f));
	static_cast<Collider*>(platform1->getComponent("Below"))->setSize(Size(295.0f, 4.5f));
	static_cast<Collider*>(platform1->getComponent("Upon"))->setOffset(Vec2(0, 2.25f));
	static_cast<Collider*>(platform1->getComponent("Below"))->setOffset(Vec2(0, -3.f));

	const auto platform2 = gameManager->getPrefab("Platform")->instantiate(); 
	platform2->getTransform()->setPosition(Vec2(1367.5f, 127.0f));
	static_cast<Collider*>(platform2->getComponent("Upon"))->setSize(Size(105.0f, 4.5f));
	static_cast<Collider*>(platform2->getComponent("Below"))->setSize(Size(105.0f, 4.5f));
	static_cast<Collider*>(platform2->getComponent("Upon"))->setOffset(Vec2(0, 2.25f));
	static_cast<Collider*>(platform2->getComponent("Below"))->setOffset(Vec2(0, -3.0f));
	
	const auto platform3 = gameManager->getPrefab("Platform")->instantiate(); 
	platform3->getTransform()->setPosition(Vec2(1335.5f, 175.5f));
	static_cast<Collider*>(platform3->getComponent("Upon"))->setSize(Size(39.0f, 4.5f));
	static_cast<Collider*>(platform3->getComponent("Below"))->setSize(Size(39.0f, 4.5f));
	static_cast<Collider*>(platform3->getComponent("Upon"))->setOffset(Vec2(0, 2.25f));
	static_cast<Collider*>(platform3->getComponent("Below"))->setOffset(Vec2(0, -2.75f));

	const auto platform4 = gameManager->getPrefab("Platform")->instantiate();
	platform4->getTransform()->setPosition(Vec2(1768.50f, 289.00f));
	static_cast<Collider*>(platform4->getComponent("Upon"))->setSize(Size(682.00f, 5.50f));
	static_cast<Collider*>(platform4->getComponent("Below"))->setSize(Size(682.00f, 5.50f));
	static_cast<Collider*>(platform4->getComponent("Upon"))->setOffset(Vec2(0, 2.75f));
	static_cast<Collider*>(platform4->getComponent("Below"))->setOffset(Vec2(0, -3.50f));
	
	const auto platform5 = gameManager->getPrefab("Platform")->instantiate();
	platform5->getTransform()->setPosition(Vec2(2427.50f, 400.00f));
	static_cast<Collider*>(platform5->getComponent("Upon"))->setSize(Size(129.00f, 5.00f));
	static_cast<Collider*>(platform5->getComponent("Below"))->setSize(Size(129.00f, 5.00f));
	static_cast<Collider*>(platform5->getComponent("Upon"))->setOffset(Vec2(0, 2.50f));
	static_cast<Collider*>(platform5->getComponent("Below"))->setOffset(Vec2(0, -3.25f));

	const auto platform6 = gameManager->getPrefab("Platform")->instantiate();
	platform6->getTransform()->setPosition(Vec2(2786.00f, 141.50f));
	static_cast<Collider*>(platform6->getComponent("Upon"))->setSize(Size(275.00f, 5.00f));
	static_cast<Collider*>(platform6->getComponent("Below"))->setSize(Size(275.00f, 5.00f));
	static_cast<Collider*>(platform6->getComponent("Upon"))->setOffset(Vec2(0, 2.50f));
	static_cast<Collider*>(platform6->getComponent("Below"))->setOffset(Vec2(0, -3.25f));
	
	const auto platform7 = gameManager->getPrefab("Platform")->instantiate();
	platform7->getTransform()->setPosition(Vec2(3276.00f, 81.50f));
	static_cast<Collider*>(platform7->getComponent("Upon"))->setSize(Size(762.00f, 5.00f));
	static_cast<Collider*>(platform7->getComponent("Below"))->setSize(Size(762.00f, 5.00f));
	static_cast<Collider*>(platform7->getComponent("Upon"))->setOffset(Vec2(0, 2.50f));
	static_cast<Collider*>(platform7->getComponent("Below"))->setOffset(Vec2(0, -3.25f));

	const auto platform8 = gameManager->getPrefab("Platform")->instantiate();
	platform8->getTransform()->setPosition(Vec2(2631.00f, 0.50f));
	static_cast<Collider*>(platform8->getComponent("Upon"))->setSize(Size(106.00f, 5.50f));
	static_cast<Collider*>(platform8->getComponent("Below"))->setSize(Size(106.00f, 5.50f));
	static_cast<Collider*>(platform8->getComponent("Upon"))->setOffset(Vec2(0, 2.75f));
	static_cast<Collider*>(platform8->getComponent("Below"))->setOffset(Vec2(0, -3.50f));

	const auto platform9 = gameManager->getPrefab("Platform")->instantiate();
	platform9->getTransform()->setPosition(Vec2(2554.50f, 161.00f));
	static_cast<Collider*>(platform9->getComponent("Upon"))->setSize(Size(192.00f, 5.50f));
	static_cast<Collider*>(platform9->getComponent("Below"))->setSize(Size(192.00f, 5.50f));
	static_cast<Collider*>(platform9->getComponent("Upon"))->setOffset(Vec2(0, 2.75f));
	static_cast<Collider*>(platform9->getComponent("Below"))->setOffset(Vec2(0, -3.50f));

	const auto platform10 = gameManager->getPrefab("Platform")->instantiate();
	platform10->getTransform()->setPosition(Vec2(2837.00f, 272.50f));
	static_cast<Collider*>(platform10->getComponent("Upon"))->setSize(Size(409.00f, 5.50f));
	static_cast<Collider*>(platform10->getComponent("Below"))->setSize(Size(409.00f, 5.50f));
	static_cast<Collider*>(platform10->getComponent("Upon"))->setOffset(Vec2(0, 2.75f));
	static_cast<Collider*>(platform10->getComponent("Below"))->setOffset(Vec2(0, -3.50f));

	const auto platform11 = gameManager->getPrefab("Platform")->instantiate();
	platform11->getTransform()->setPosition(Vec2(2625.00f, 400.00f));
	static_cast<Collider*>(platform11->getComponent("Upon"))->setSize(Size(86.00f, 5.50f));
	static_cast<Collider*>(platform11->getComponent("Below"))->setSize(Size(86.00f, 5.50f));
	static_cast<Collider*>(platform11->getComponent("Upon"))->setOffset(Vec2(0, 2.75f));
	static_cast<Collider*>(platform11->getComponent("Below"))->setOffset(Vec2(0, -3.50f));

	const auto platform12 = gameManager->getPrefab("Platform")->instantiate();
	platform12->getTransform()->setPosition(Vec2(2906.50f, 399.50f));
	static_cast<Collider*>(platform12->getComponent("Upon"))->setSize(Size(193.00f, 6.50f));
	static_cast<Collider*>(platform12->getComponent("Below"))->setSize(Size(193.00f, 6.50f));
	static_cast<Collider*>(platform12->getComponent("Upon"))->setOffset(Vec2(0, 3.25f));
	static_cast<Collider*>(platform12->getComponent("Below"))->setOffset(Vec2(0, -4.00f));

	const auto platform13 = gameManager->getPrefab("Platform")->instantiate();
	platform13->getTransform()->setPosition(Vec2(4190.50f, 97.00f));
	static_cast<Collider*>(platform13->getComponent("Upon"))->setSize(Size(90.00f, 5.50f));
	static_cast<Collider*>(platform13->getComponent("Below"))->setSize(Size(90.00f, 5.50f));
	static_cast<Collider*>(platform13->getComponent("Upon"))->setOffset(Vec2(0, 2.75f));
	static_cast<Collider*>(platform13->getComponent("Below"))->setOffset(Vec2(0, -3.50f));*/
#pragma endregion

#pragma region Pendal
	const auto pendal1 = gameManager->getPrefab("Pendal")->instantiate();
	pendal1->getTransform()->setPosition(Vec2(1486.5f, 128.0f));

	const auto pendal2 = gameManager->getPrefab("Pendal")->instantiate();
	pendal2->getTransform()->setPosition(Vec2(4068.5f, 103.0f));

	const auto pendal3 = gameManager->getPrefab("Pendal")->instantiate();
	pendal3->getTransform()->setPosition(Vec2(3973.5f, 106.0f));
#pragma endregion


#pragma region Dev support
	/*const auto runningBlock = gameManager->getPrefab("HorizontalBar")->instantiate();
	runningBlock->getTransform()->setPosition(Vec2(2500 ,0));
	runningBlock->getComponentT<Collider>()->setSize(Size(5, 5));
	runningBlock->getComponentT<Collider>()->setTrigger(false);

	runningBlock->setTag(ALADDIN_TAG);
	new NodeController(runningBlock);*/
#pragma endregion



}

void ExperimentalScene::onPreRelease() {}

void ExperimentalScene::onPostInitialize()
{
	const auto stairGroupTwoCollider = GameManager::get()->getObjectByName("StairGroupTwo")->getAllComponents("Static");
	for (auto collider: stairGroupTwoCollider)
	{
		collider->setActive(false);
	}

	const auto stairGroupThreeCollider = GameManager::get()->getObjectByName("StairGroupThree")->getAllComponentTs<Collider>();
	for (auto collider: stairGroupThreeCollider)
	{
		collider->setActive(false);
	}
}
