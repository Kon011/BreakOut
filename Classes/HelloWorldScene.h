#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include <vector>
#include "cocos2d.h"
#include "KonFu\Input\InputManager.h"
#include "Actors\Ball.h"
#include "Actors\Paddle.h"
#include "Actors\Edge.h"
#include "Actors\Brick.h"
USING_NS_CC;

class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

	void update(float) override;

	// CUSTOM
	bool gameStarted = false;
	bool gameEnded = false;

	InputManager inputManager;

	Ball ball;
	Paddle paddle;
	Edge edge;
	std::vector<Brick> brickList;

	PhysicsWorld* pWorld;
	bool onContactBegin(PhysicsContact& contact);
	void setPhyWorld(PhysicsWorld* world) { world = pWorld; };
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event *event);
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event);
	void onKeyEvent(EventKeyboard::KeyCode keyCode, bool isPressed);
private:


};

#endif // __HELLOWORLD_SCENE_H__
