#include "Ball.h"
void Ball::update(float delta, InputManager inpMan) {
	updateStart();
}

void Ball::startMovement(){
	if(sprCurrent != nullptr){
		sprCurrent->getPhysicsBody()->applyImpulse(force); 
	}
}

void Ball::stopMovement() {
	if (sprCurrent != nullptr) {
		sprCurrent->getPhysicsBody()->resetForces();
	}
}

void Ball::init(cocos2d::Sprite* spr, cocos2d::Vec2 pos) {
	spr->setPosition(pos);
	auto ballBody = cocos2d::PhysicsBody::createCircle(spr->getContentSize().width / 2.);
	ballBody->getShape(0)->setRestitution(1.0f);
	ballBody->getShape(0)->setFriction(0.0f);
	ballBody->getShape(0)->setDensity(1.0f);
	ballBody->setGravityEnable(false); 
	spr->setPhysicsBody(ballBody);
	ballBody->setContactTestBitmask(COLLISION_BITMASK_BALL); 
	spr->setTag(TAG_BALL);
	spr->setScale(SCALE_BALL);

	addSprite(spr);
	setCurrentSprite(sprList.getIndex(spr));
	hasPhysics = true;

}