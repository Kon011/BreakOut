#ifndef __KON_PADDLE_H__
#define __KON_PADDLE_H__
#include "Actor.h"
class Paddle : public Actor
{
public:
	float speed;

	void init(cocos2d::Sprite* spr, cocos2d::Vec2 pos);
	void update(float delta, InputManager inpMan) override;
};

#endif