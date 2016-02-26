#include "Paddle.h"
#include "./Definitions.h"
void Paddle::update(float delta, InputManager inpMan) {
	updateStart();

	if (inpMan.getKeyboard().getKey(Keyboard::KeyCode::KEY_LEFT_ARROW))
		sprCurrent->setPositionX(sprCurrent->getPositionX() - speed);
	if (inpMan.getKeyboard().getKey(Keyboard::KeyCode::KEY_RIGHT_ARROW))
		sprCurrent->setPositionX(sprCurrent->getPositionX() + speed);

	if(sprCurrent->getPositionX() - sprCurrent->getContentSize().width * SCALE_PADDLE / 2 < 0)
		sprCurrent->setPositionX(sprCurrent->getContentSize().width * SCALE_PADDLE / 2);
	if(sprCurrent->getPositionX() + sprCurrent->getContentSize().width * SCALE_PADDLE / 2 > windowWidth)
		sprCurrent->setPositionX(windowWidth - sprCurrent->getContentSize().width * SCALE_PADDLE / 2);

}

void Paddle::init(cocos2d::Sprite* spr, cocos2d::Vec2 pos, int width) {
	defaultPosition = pos;
	windowWidth = width;
	spr->setPosition(pos);
	auto paddleBody = cocos2d::PhysicsBody::createBox(spr->getContentSize(), cocos2d::PHYSICSBODY_MATERIAL_DEFAULT);
	paddleBody->getShape(0)->setRestitution(1.0f);
	paddleBody->getShape(0)->setFriction(0.0f);
	paddleBody->getShape(0)->setDensity(10.0f);
	paddleBody->setGravityEnable(false);
	paddleBody->setDynamic(false);
	spr->setPhysicsBody(paddleBody);
	paddleBody->setContactTestBitmask(COLLISION_BITMASK_PADDLE); 
	spr->setTag(TAG_PADDLE);
	spr->setScale(SCALE_PADDLE);

	addSprite(spr);
	setCurrentSprite(sprList.getIndex(spr));
	hasPhysics = true;
	speed = SPEED_PADDLE * SPEED_PADDLE_MULTIPLIER;
}