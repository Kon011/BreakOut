#include "MainMenuScene.h"
#include "GameScene.h"
#include "Definitions.h"

USING_NS_CC;

Scene* MainMenuScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = MainMenuScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool MainMenuScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto backgroundSprite = Sprite::create("Background.png");
	backgroundSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	this->addChild(backgroundSprite);

	/*
	auto titleSprite = Sprite::create("Title.png");
	titleSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height - titleSprite->getContentSize().height));

	this->addChild(titleSprite);
	*/
	// visibleSize.height - titleLabel->getContentSize().height //to set at top
	auto titleLabel = Label::createWithTTF(WINDOW_TITLE, "fonts/mecha_cf/Mecha_Bold.ttf", FONT_SIZE_4);
	titleLabel->setPosition(Point(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height / 2 + 100)));
	titleLabel->setColor(Color3B::BLACK);
	this->addChild(titleLabel);
	//


	auto playLabel = Label::createWithTTF("Play!", "fonts/mecha_cf/Mecha_Bold.ttf", FONT_SIZE_3);
	playLabel->setColor(Color3B::BLACK);
	auto BtnPlay = MenuItemLabel::create(playLabel, CC_CALLBACK_1(MainMenuScene::GoToGameScene, this));
	BtnPlay->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 80));
	auto menu = Menu::create(BtnPlay, NULL);

	menu->setPosition(Point::ZERO);

	this->addChild(menu);

	//

	return true;
}

void MainMenuScene::GoToGameScene(cocos2d::Ref *sender)
{
	auto scene = GameScene::createScene();

	Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}