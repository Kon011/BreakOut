#ifndef __KON_BRICK_H__
#define __KON_BRICK_H__
#include "Actor.h"
class Brick : public Actor
{
public:

	void update(float delta, InputManager inpMan) override;
};

#endif