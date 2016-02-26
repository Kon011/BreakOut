#ifndef __KON_INPUT_MANAGER_H__
#define __KON_INPUT_MANAGER_H__

#include "Keyboard.h"

class InputManager
{
public:
	Keyboard& getKeyboard();
private:	
	Keyboard inpKeyboard;
};

#endif