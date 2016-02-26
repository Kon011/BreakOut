#ifndef __KON_KEYBOARD_H__
#define __KON_KEYBOARD_H__

class Keyboard
{
public:

	enum KeyCode {
		KEY_0, KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7, KEY_8, KEY_9,
		KEY_A, KEY_B, KEY_C, KEY_D, KEY_E, KEY_F, KEY_G, KEY_H, KEY_I,
		KEY_J, KEY_K, KEY_L, KEY_M, KEY_N, KEY_O, KEY_P, KEY_Q, KEY_R,
		KEY_S, KEY_T, KEY_U, KEY_V, KEY_W, KEY_X, KEY_Y, KEY_Z,
		KEY_UP_ARROW, KEY_DOWN_ARROW, KEY_LEFT_ARROW, KEY_RIGHT_ARROW, 
		KEY_SPACE, KEY_ENTER, KEY_ESCAPE,
		// Always ensure KEY_LAST is last key to be enumerated
		KEY_LAST
	};

	bool& getKey(KeyCode key) { return keyMap[key]; }
	void setKey(KeyCode key, bool value) { 
		if(keyMap[key] != value)
			keyMap[key] = value;
	}
	void toggleKey(KeyCode key) { keyMap[key] = !keyMap[key]; }
private:
	bool keyMap[KeyCode::KEY_LAST + 1] = { false };
};

#endif