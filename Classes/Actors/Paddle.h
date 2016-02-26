#ifndef __KON_PADDLE_H__
#define __KON_PADDLE_H__
#include "Actor.h"
class Paddle : public Actor
{
public:
	cocos2d::Vec2 defaultPosition;
	float speed;
	int windowWidth;
	void init(cocos2d::Sprite* spr, cocos2d::Vec2 pos, int width);
	void update(float delta, InputManager inpMan) override;
};

#endif