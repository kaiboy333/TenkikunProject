#pragma once

#include "DxLib.h"
#include <unordered_map>
#include "KeyState.h"

class KeyState;
class Input
{
	public:
		enum KeyCode {
			A = KEY_INPUT_A,
			B = KEY_INPUT_B,
			C = KEY_INPUT_C,
			D = KEY_INPUT_D,
			E = KEY_INPUT_E,
			F = KEY_INPUT_F,
			G = KEY_INPUT_G,
			H = KEY_INPUT_H,
			I = KEY_INPUT_I,
			J = KEY_INPUT_J,
			K = KEY_INPUT_K,
			L = KEY_INPUT_L,
			M = KEY_INPUT_M,
			N = KEY_INPUT_N,
			O = KEY_INPUT_O,
			P = KEY_INPUT_P,
			Q = KEY_INPUT_Q,
			R = KEY_INPUT_R,
			S = KEY_INPUT_S,
			T = KEY_INPUT_T,
			U = KEY_INPUT_U,
			V = KEY_INPUT_V,
			W = KEY_INPUT_W,
			X = KEY_INPUT_X,
			Y = KEY_INPUT_Y,
			Z = KEY_INPUT_Z,

			SPACE = KEY_INPUT_SPACE,

			LEFT_SHIFT = KEY_INPUT_LSHIFT,
			RIGHT_SHIFT = KEY_INPUT_RSHIFT,

			ENTER = KEY_INPUT_RETURN,

			LEFT = KEY_INPUT_LEFT,
			RIGHT = KEY_INPUT_RIGHT,
			UP = KEY_INPUT_UP,
			DOWN = KEY_INPUT_DOWN,

		};

		static std::unordered_map<int, KeyState*> keys;

		Input();

		static void Update();	//ì¸óÕÇÃèÛë‘çXêV

		static bool GetKey(KeyCode keyCode);	//âüÇ≥ÇÍÇƒÇ¢ÇÈÇ©
		static bool GetKeyDown(KeyCode keyCode);	//âüÇµÇΩèuä‘Ç©
		static bool GetKeyUp(KeyCode keyCode);	//ó£ÇµÇΩèuä‘Ç©
};
