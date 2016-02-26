#ifndef __KON_ACTOR_H__
#define __KON_ACTOR_H__

#include "cocos2d.h"
#include "./KonFu/Input/InputManager.h"
class Actor
{
public:
	cocos2d::Vector<cocos2d::Sprite *> sprList;
	cocos2d::Sprite* sprCurrent = nullptr;
	cocos2d::Vec2 posVector;
	bool hasPhysics;
	// Update Function

	void virtual update(float delta, InputManager inpMan) {}

	// Sprite Functions

	void setCurrentSprite(int index) { if (index < sprList.capacity()) sprCurrent = sprList.at(index); }
	cocos2d::Sprite* getCurrentSprite() { return sprCurrent; }

	void addSprite(cocos2d::Sprite* sprite) { sprList.pushBack(sprite); }
	cocos2d::Sprite* getSprite(int index) {  if (index < sprList.capacity())return sprList.at(index); return nullptr; }
	int  getSpriteListSize() { sprList.capacity(); }
	void clearSpriteList() { sprList.clear(); }
	void removeSprite(int index) { if(index < sprList.capacity()) sprList.erase(index); }
	void removeSprite(cocos2d::Sprite* sprite) { sprList.eraseObject(sprite); }

protected:
	void updateStart() {
		if (sprCurrent != nullptr) {
			if (hasPhysics)
				posVector = sprCurrent->getPosition();
			else
				sprCurrent->setPosition(posVector);
		}
	}
};
#endif