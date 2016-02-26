#include "Paddle.h"

void Paddle::update(float delta, InputManager inpMan) {
	updateStart();

	if (inpMan.getKeyboard().getKey(Keyboard::KeyCode::KEY_LEFT_ARROW))
		sprCurrent->setPositionX(sprCurrent->getPositionX() - speed);
	if (inpMan.getKeyboard().getKey(Keyboard::KeyCode::KEY_RIGHT_ARROW))
		sprCurrent->setPositionX(sprCurrent->getPositionX() + speed);

}