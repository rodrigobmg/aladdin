/*
 * Created by phuctm97 on Sep 30th 2017
 */

#include "MyResourceInitializer.h"
#include "../prefabs/NodePrefab.h"
#include "../prefabs/SpritePrefab.h"
#include "../prefabs/MenuSelectPrefab.h"
#include "../prefabs/BitmapTextPrefab.h"
#include "../prefabs/HubPrefab.h"
#include "../prefabs/PlayableAladdinPrefab.h"
#include "../prefabs/ThrowableApplePrefab.h"
#include "../prefabs/EatableApplePrefab.h"
#include "../prefabs/EnemyExplosionPrefab.h"
#include "../prefabs/FlamePrefab.h"
#include "../prefabs/CharcoalBurnerPrefab.h"
#include "../prefabs/GuardOnePrefab.h"
#include "../prefabs/GuardTwoPrefab.h"
#include "../prefabs/AgrabahMarketGroundPrefab.h"
#include "../prefabs/AgrabahMarketStairOnePrefab.h"

USING_NAMESPACE_ALA;

void MyResourceInitializer::doRun() {
  auto gameManager = GameManager::get();

  // Layers
  gameManager->addLayer( "Background" );
  gameManager->addLayer( "Sub Background" );
  gameManager->addLayer( "Character" );
  gameManager->addLayer( "Sub Character" );
  gameManager->addLayer( "Foreground" );
  gameManager->addLayer( "UI" );

  // Textures
  new Sprite( "background.png", "textures/backgrounds/scene_1_0.png" );
  new Sprite( "foreground.png", "textures/backgrounds/scene_1_1.png" );
  new Sprite( "aladdin.png", "textures/playable_characters/aladdin.png" );
  new Sprite( "enemy_explosions.png", "textures/miscellaneous/enemy_explosions.png" );
  new Sprite( "item_explosion.png", "textures/miscellaneous/item_explosion.png" );
  new Sprite( "items.png", "textures/miscellaneous/items.png" );
  new Sprite( "cutscenes.png", "textures/miscellaneous/cutscenes.png" );
  new Sprite( "title.png", "textures/miscellaneous/title.png" );
  new Sprite( "font_one.png", "textures/miscellaneous/font_one.png" );
  new Sprite( "font_two.png", "textures/miscellaneous/font_two.png" );
  new Sprite( "menu_select.png", "textures/miscellaneous/menu_select.png" );
  new Sprite( "guards.png", "textures/enemies/guards.png" );
  new Sprite( "civilian_enemies.png", "textures/enemies/civilian_enemies.png" );
  new Sprite( "jafar.png", "textures/bosses/jafar.png" );
  new Sprite( "camel.png", "textures/nonplayable_characters/camel.png" );
  new Sprite( "saliva.png", "textures/nonplayable_characters/saliva.png" );
  new Sprite( "spring.png", "textures/nonplayable_characters/spring.png" );
  new Sprite( "peddler.png", "textures/nonplayable_characters/peddler.png" );
  new Sprite( "abu.png", "textures/nonplayable_characters/abu.png" );

  // Fonts
  new Font( "aladdin.ttf", "aladdin.ttf", "fonts" );
  new Font( "arcade.ttf", "arcade.ttf", "fonts" );
  new BitmapFont( "one.fnt", "fonts/one.fnt" );
  new BitmapFont( "two.fnt", "fonts/two.fnt" );

  // Animations
  new Animation( "aladdin.anm", "animations/playable_characters/aladdin.anm" );
  new Animation( "enemy_explosions.anm", "animations/miscellaneous/enemy_explosions.anm" );
  new Animation( "item_explosion.anm", "animations/miscellaneous/item_explosion.anm" );
  new Animation( "apple.anm", "animations/miscellaneous/apple.anm" );
  new Animation( "items.anm", "animations/miscellaneous/items.anm" );
  new Animation( "cutscenes.anm", "animations/miscellaneous/cutscenes.anm" );
  new Animation( "guards.anm", "animations/enemies/guards.anm" );
  new Animation( "civilian_enemies.anm", "animations/enemies/civilian_enemies.anm" );
  new Animation( "jafar.anm", "animations/bosses/jafar.anm" );
  new Animation( "camel.anm", "animations/nonplayable_characters/camel.anm" );
  new Animation( "saliva.anm", "animations/nonplayable_characters/saliva.anm" );
  new Animation( "spring.anm", "animations/nonplayable_characters/spring.anm" );
  new Animation( "peddler.anm", "animations/nonplayable_characters/peddler.anm" );
  new Animation( "abu.anm", "animations/nonplayable_characters/abu.anm" );

  // Prefabs
  new SpritePrefab();
  new BitmapTextPrefab();

  new MenuSelectPrefab();

  new HubPrefab();
  new PlayableAladdinPrefab();
  new ThrowableApplePrefab();
  new EatableApplePrefab();
  new EnemyExplosionPrefab();
  new FlamePrefab();
  new CharcoalBurnerPrefab();
  new GuardOnePrefab();
  new GuardTwoPrefab();

  new AgrabahMarketGroundPrefab();
  new AgrabahMarketStairOnePrefab();

  // Dev tools
  new NodePrefab();
}
