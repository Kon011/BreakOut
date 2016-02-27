#include "GameScene.h"
#include "MainMenuScene.h"
#include "Definitions.h"
#include <SimpleAudioEngine.h>
#include "Definitions.h"
USING_NS_CC;

// git add -u .

Scene* GameScene::createScene()
{
	// 'scene' is an autorelease object
	//auto scene = Scene::create();
	auto scene = Scene::createWithPhysics();
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	Vect gravity(0.0f, 0.0f);
	scene->getPhysicsWorld()->setGravity(gravity);

	// 'layer' is an autorelease object
	auto layer = GameScene::create();
	layer->setPhyWorld(scene->getPhysicsWorld());

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	// Background

	auto backgroundSprite = Sprite::create("Background.png");
	backgroundSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	this->addChild(backgroundSprite);

	// Create Game Edge
	Sprite* pEdge = Sprite::create();
	edge.init(pEdge, visibleSize);
	this->addChild(pEdge); // Add into Layer


	// Create Paddle
	Sprite* pPaddle = Sprite::create(SPRITE_PATH_PADDLE);
	paddle.init(pPaddle, Vec2(visibleSize.width / 2, 50), visibleSize.width);
	this->addChild(pPaddle);

	// Create Ball
	Sprite* pBall = Sprite::create(SPRITE_PATH_BALL, Rect(0, 0, 24, 24));
	ball.init(pBall, Vec2(pPaddle->getPositionX(),
		pPaddle->getPositionY() + pBall->getContentSize().height + 10));
	this->addChild(pBall);

	// Set up game
	for (int i = 0; i < (int)visibleSize.width / TILE_WIDTH; i++)
		for (int j = 0; j < (int)visibleSize.height / TILE_HEIGHT; j++) {
			// level set
			if (genLevel(j, i)) {
				Sprite* pBlock;
				if (j % 16 >= 0 && j % 16 <= 3)
					pBlock = Sprite::create(SPRITE_PATH_BRICK_1);
				else if (j % 16 >= 4 && j % 16 <= 7)
					pBlock = Sprite::create(SPRITE_PATH_BRICK_2);
				else if (j % 16 >= 8 && j % 16 <= 11)
					pBlock = Sprite::create(SPRITE_PATH_BRICK_3);
				else if (j % 16 >= 12 && j % 16 <= 15)
					pBlock = Sprite::create(SPRITE_PATH_BRICK_4);
				else pBlock = Sprite::create(SPRITE_PATH_BRICK_1);
				Brick brick;
				brick.init(pBlock, Vec2((i * TILE_WIDTH) + TILE_WIDTH / 2,
					(j * TILE_HEIGHT) + TILE_HEIGHT / 2));
				brickList.push_back(brick);
				this->addChild(pBlock);
			}
		}

	// Score

	score = 0;

	__String *tempScore = __String::createWithFormat("%i", score);

	scoreLabel = Label::createWithTTF(tempScore->getCString(), "fonts/mecha_cf/Mecha_Condensed.ttf", FONT_SIZE_3);
	scoreLabel->setColor(Color3B::BLACK);
	scoreLabel->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height * 0.75 + origin.y));

	this->addChild(scoreLabel, 10000);
	// Contact Listener

	auto dispatcher = Director::getInstance()->getEventDispatcher();
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
	dispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

	// Input

	auto keyListener = EventListenerKeyboard::create();


	keyListener->onKeyPressed = CC_CALLBACK_2(GameScene::onKeyPressed, this);
	keyListener->onKeyReleased = CC_CALLBACK_2(GameScene::onKeyReleased, this);

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyListener, this);
	this->scheduleUpdate();

	return true;
}

bool GameScene::onContactBegin(PhysicsContact& contact)
{

	auto spriteA = (Sprite*)contact.getShapeA()->getBody()->getNode();
	auto spriteB = (Sprite*)contact.getShapeB()->getBody()->getNode();

	int tagA = spriteA->getTag();
	int tagB = spriteB->getTag();

	if (tagA == TAG_BRICK)
	{
		this->removeChild(spriteA, true);

		score++;
		brickCount--;
		if (gameStart && !gameEnded) {
			__String *tempScore = __String::createWithFormat("%i", score);
			scoreLabel->setString(tempScore->getCString());
		}
	}

	if (tagB == TAG_BRICK)
	{
		this->removeChild(spriteB, true);

		score++;
		brickCount--;
		if (gameStart && !gameEnded) {
			__String *tempScore = __String::createWithFormat("%i", score);
			scoreLabel->setString(tempScore->getCString());
		}
	}
	if (brickCount == 0 && gameStart) {
	
		auto endText = Label::createWithTTF("You Win!", "fonts/mecha_cf/Mecha_Bold.ttf", FONT_SIZE_2);
		endText->setColor(Color3B::BLACK);
		endText->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height * 0.50 + origin.y));
		this->addChild(endText, 10001);

		auto scene = MainMenuScene::createScene();
		Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME_WIN, scene));

	}


	if ((tagA == 0 || tagB == 0)& (ball.getCurrentSprite()->getPositionY() <= paddle.getCurrentSprite()->getPositionY()))
	{
		gameEnded = true;
		//auto scene = GameScene::createScene();
		//Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
		
		auto endText = Label::createWithTTF("You Lose!", "fonts/mecha_cf/Mecha_Bold.ttf", FONT_SIZE_2);
		endText->setColor(Color3B::BLACK);
		endText->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height * 0.50 + origin.y));
		this->addChild(endText, 10001);

		auto scene = MainMenuScene::createScene();
		Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME_LOSE, scene));
		/*
		auto gameOverScene = GameOverScene::create();
		gameOverScene->getLayer()->getLabel()->setString("You Lose!");
		Director::getInstance()->replaceScene(gameOverScene);
		*/
	}

	return true;
}



void GameScene::update(float delta) {

	ball.update(delta, inputManager);
	paddle.update(delta, inputManager);

	// Before game start

	if (!gameStart) {
		ball.getCurrentSprite()->setPositionX(paddle.getCurrentSprite()->getPositionX());
	}
}


void GameScene::onKeyEvent(EventKeyboard::KeyCode keyCode, bool isPressed) {
	switch (keyCode) {
	case EventKeyboard::KeyCode::KEY_SPACE:
	case EventKeyboard::KeyCode::KEY_ENTER:
		inputManager.getKeyboard().setKey(Keyboard::KeyCode::KEY_ENTER, isPressed);
		if (!gameStart) {
			gameStart = true;
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

void GameScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event *event) {
	onKeyEvent(keyCode, true);
}

void GameScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event) {
	onKeyEvent(keyCode, false);
}

bool GameScene::genLevel(int row, int col) {
	bool result = true;

	// Set no spawn height
	if (!(row * TILE_HEIGHT + TILE_HEIGHT / 2 > ZONE_NOSPAWN_HEIGHT))
		result &= false;
	if (!(col == 15 || col == 0 && row > 20 || (row == 21 || row == 22) && col != 14
		|| (row == 43 || row == 42 || (row == 27 || row == 28) && col != 12) && col != 14 && col != 1
		|| row > 20 && col == 13 && row < 44 || row > 26 && col == 2 && row < 44 || (row == 43 || row == 42) && col < 14 && col > 1
		|| (col == 6 || col == 5 || col == 10 || col == 9) && (row == 16 || row == 17 || row == 34 || row == 35)
		))
		result &= false;
	if (result)
		brickCount++;
	return result;
}
