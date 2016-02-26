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