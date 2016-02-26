#ifndef __KON_BRICK_H__
#define __KON_BRICK_H__
#include "Actor.h"
class Brick : public Actor
{
public:
	int health;
	void update(float delta, InputManager inpMan) override;
	void init(cocos2d::Sprite* spr, cocos2d::Vec2 pos);
};

#endif