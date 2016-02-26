#include "Brick.h"
#include "./Definitions.h"
void Brick::update(float delta, InputManager inpMan) {
	updateStart();
}

void Brick::init(cocos2d::Sprite* spr, cocos2d::Vec2 pos) {
	auto blockBody = cocos2d::PhysicsBody::createBox(spr->getContentSize(), cocos2d::PHYSICSBODY_MATERIAL_DEFAULT);
	blockBody->getShape(0)->setDensity(10.0f);
	blockBody->getShape(0)->setFriction(0.0f);
	blockBody->getShape(0)->setRestitution(1.f);
	blockBody->setDynamic(false);
	blockBody->setContactTestBitmask(COLLISION_BITMASK_BRICK);
	spr->setPhysicsBody(blockBody);
	spr->setTag(TAG_BRICK);
	spr->setScale(SCALE_BRICK);
	spr->setPosition(pos);
}