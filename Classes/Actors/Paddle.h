#ifndef __KON_PADDLE_H__
#define __KON_PADDLE_H__
#include "Actor.h"
class Paddle : public Actor
{
public:
	float speed;

	void update(float delta, InputManager inpMan) override;
};

#endif