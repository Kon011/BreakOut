#include "Edge.h"
#include "./Definitions.h"

void Edge::init(cocos2d::Sprite* spr, cocos2d::Size visibleSize) {

	auto boundBody = cocos2d::PhysicsBody::createEdgeBox(visibleSize, cocos2d::PHYSICSBODY_MATERIAL_DEFAULT, 3);
	boundBody->getShape(0)->setRestitution(1.0f);
	boundBody->getShape(0)->setFriction(0.0f);
	boundBody->getShape(0)->setDensity(1.0f);
	spr->setPosition(cocos2d::Point(visibleSize.width / 2, visibleSize.height / 2)); 
	spr->setPhysicsBody(boundBody);
	boundBody->setContactTestBitmask(COLLISION_BITMASK_EDGE);
	spr->setTag(TAG_EDGE);
}