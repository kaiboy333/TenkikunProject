#include "Input.h"

Input::Input()
{
	//キー状態の初期化
	for (int keyCode = KeyCode::A; keyCode <= KeyCode::DOWN; keyCode++) {
		keys.insert(std::make_pair(keyCode, new KeyState()));	//キー状態の作成
	}
}

void Input::Update()
{
	char buf[256];
	GetHitKeyStateAll(buf);	//すべてのキーの入力状態を取得
	for (auto iter = keys.begin(); iter != keys.end(); iter++) {
		KeyState* keyState = iter->second;
		//指定のキーが押されていたら
		if (buf[iter->first]) {
			keyState->Push();
		}
		//押されていなかったら
		else {
			keyState->Release();
		}
	}
}

bool Input::GetKey(KeyCode keyCode)
{
	KeyState* keyState = keys[keyCode];
	return keyState->GetIsPush();
}

bool Input::GetKeyDown(KeyCode keyCode)
{
	KeyState* keyState = keys[keyCode];
	return keyState->GetIsPush() && keyState->GetIsFirst();
}

bool Input::GetKeyUp(KeyCode keyCode)
{
	KeyState* keyState = keys[keyCode];
	return !keyState->GetIsPush() && keyState->GetIsFirst();
}

std::unordered_map<int, KeyState*> Input::keys;
