#ifndef __KON_BALL_H__
#define __KON_BALL_H__
#include "Actor.h"
#include "./Definitions.h"
class Ball : public Actor
{
public:

	cocos2d::Vect force = cocos2d::Vect(SPEED_BALL_X, SPEED_BALL_Y);
	void init(cocos2d::Sprite* spr, cocos2d::Vec2 pos);
	void startMovement();
	void stopMovement();
	void update(float delta, InputManager inpMan) override;
};

#endif