#pragma once

#include "DxLib.h"
#include <unordered_map>
#include "KeyState.h"
#include "Vector3.h"
#include "Property.h"

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

		enum MouseCode {
			Mouse_Left = MOUSE_INPUT_LEFT,
			Mouse_Right = MOUSE_INPUT_RIGHT,
			Mouse_Wheel = MOUSE_INPUT_MIDDLE,
		};

		static std::unordered_map<int, KeyState*> keys;
		static std::unordered_map<int, KeyState*> mouses;

		Input();

		static void Update();	//入力の状態更新

		//キーボードの入力状態を取得
		static bool GetKey(KeyCode keyCode);	//押されているか
		static bool GetKeyDown(KeyCode keyCode);	//押した瞬間か
		static bool GetKeyUp(KeyCode keyCode);	//離した瞬間か

		//マウスの入力状態を取得
		static bool GetMouseButton(MouseCode mouseCode);
		static bool GetMouseButtonDown(MouseCode mouseCode);
		static bool GetMouseButtonUp(MouseCode mouseCode);

		//マウスのスクリーン座標を取得
		static Vector3 GetMousePosition();

};
