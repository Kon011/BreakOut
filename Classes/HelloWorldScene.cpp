#include "HelloWorldScene.h"
#include "Definitions.h"
USING_NS_CC;

// git add -u .

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    //auto scene = Scene::create();
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	Vect gravity(0.0f, 0.0f);
	scene->getPhysicsWorld()->setGravity(gravity);
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();
	layer->setPhyWorld(scene->getPhysicsWorld());

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;

	


}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	// Start Custom
	// Define Edge
	Sprite* pEdge = Sprite::create();
	edge.init(pEdge, visibleSize);
	this->addChild(pEdge); // Add into Layer


	// Create Paddle
	Sprite* pPaddle = Sprite::create(SPRITE_PATH_PADDLE);
	paddle.init(pPaddle, Vec2(visibleSize.width / 2, 50));
	this->addChild(pPaddle);

	// Create Ball
	Sprite* pBall = Sprite::create(SPRITE_PATH_BALL, Rect(0, 0, 52, 52));
	ball.init(pBall, Vec2(pPaddle->getPositionX(), pPaddle->getPositionY() + 100));
	this->addChild(pBall);

	// Create Bricks

	for (int i = 0; i < (int)visibleSize.width / TILE_WIDTH; i++)
		for (int j = 0; j < (int)visibleSize.height / TILE_HEIGHT; j++) {
			if (true) {
				auto block = Sprite::create(SPRITE_PATH_BRICK);
				auto blockBody = PhysicsBody::createBox(block->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
				blockBody->getShape(0)->setDensity(10.0f);
				blockBody->getShape(0)->setFriction(0.0f);
				blockBody->getShape(0)->setRestitution(1.f);
				blockBody->setDynamic(false);
				blockBody->setContactTestBitmask(COLLISION_BITMASK_BRICK);
				block->setPhysicsBody(blockBody);
				block->setTag(TAG_BRICK);
				block->setScale(SCALE_BRICK);

				// Set position of bricks

				block->setPosition(Point((i * TILE_WIDTH) + block->getContentSize().width / 2,
					(j * TILE_HEIGHT) + block->getContentSize().height / 2));

				this->addChild(block);
			}
		}

	// Contact Listener

	auto dispatcher = Director::getInstance()->getEventDispatcher();
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(HelloWorld::onContactBegin, this);
	dispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

	// Input

	auto keyListener = EventListenerKeyboard::create();


	keyListener->onKeyPressed = CC_CALLBACK_2(HelloWorld::onKeyPressed, this);
	keyListener->onKeyReleased = CC_CALLBACK_2(HelloWorld::onKeyReleased, this);

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyListener, this);
	this->scheduleUpdate();
	// End Custom

	return true;
}

bool HelloWorld::onContactBegin(PhysicsContact& contact)
{
	// Get two collided object
	auto spriteA = (Sprite*)contact.getShapeA()->getBody()->getNode();
	auto spriteB = (Sprite*)contact.getShapeB()->getBody()->getNode();

	// Check kinds of objects
	int tagA = spriteA->getTag();
	int tagB = spriteB->getTag();

	if (tagA == TAG_BRICK) // is brick
	{

		this->removeChild(spriteA, true); // delete brick

										  //spriteA->removeFromParentAndCleanup(true);
	}

	if (tagB == TAG_BRICK)  // is brick
	{
		this->removeChild(spriteB, true); // delete brick

										  //spriteB->removeFromParentAndCleanup(true);
	}

	// If the ball collides with the floor and the coordinate Y of the ball is smaller than the paddle, Game Over happens
	if ((tagA == 0 || tagB == 0)& (ball.getCurrentSprite()->getPositionY() <= paddle.getCurrentSprite()->getPositionY()))
	{
		/*
		auto gameOverScene = GameOverScene::create();
		gameOverScene->getLayer()->getLabel()->setString("You Lose!");
		Director::getInstance()->replaceScene(gameOverScene);
		*/
	}

	return true;
}



void HelloWorld::update(float delta) {

	ball.update(delta, inputManager);
	paddle.update(delta, inputManager);
	
}


void HelloWorld::onKeyEvent(EventKeyboard::KeyCode keyCode, bool isPressed) {
	switch (keyCode) {
	case EventKeyboard::KeyCode::KEY_SPACE:
	case EventKeyboard::KeyCode::KEY_ENTER:
		inputManager.getKeyboard().setKey(Keyboard::KeyCode::KEY_ENTER, isPressed);
		if (!gameStarted) {
			gameStarted = true;
			ball.startMovement();
		}
		break;
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
	case EventKeyboard::KeyCode::KEY_A:
		inputManager.getKeyboard().setKey(Keyboard::KeyCode::KEY_LEFT_ARROW, isPressed);
		//pPaddle->setPositionX(pPaddle->getPositionX() + 1.0f);
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
	case EventKeyboard::KeyCode::KEY_D:
		inputManager.getKeyboard().setKey(Keyboard::KeyCode::KEY_RIGHT_ARROW, isPressed);
		//pPaddle->setPositionX(pPaddle->getPositionX() - 1.0f);
		break;
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
	case EventKeyboard::KeyCode::KEY_W:
		//
		break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
	case EventKeyboard::KeyCode::KEY_S:
		//
		break;
	}
}

void HelloWorld::onKeyPressed(EventKeyboard::KeyCode keyCode, Event *event) {
	onKeyEvent(keyCode, true);
}

void HelloWorld::onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event) {
	onKeyEvent(keyCode, false);
}
