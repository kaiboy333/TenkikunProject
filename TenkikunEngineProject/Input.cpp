#include "Input.h"
#include "WindowManager.h"

Input::Input()
{
	//キー状態の初期化
	for (int keyCode = 0; keyCode < 256; keyCode++) {
		keys.insert(std::make_pair(keyCode, new KeyState()));	//キー状態の作成
	}

	//マウス状態の初期化
	for (int mouseCode = 0; mouseCode <= 4; mouseCode++) {
		mouses.insert(std::make_pair(mouseCode, new KeyState));	//マウス状態の作成
	}
}

void Input::Update()
{
	//キーボードの入力状態更新
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

	//マウスの入力状態取得
	int mouseState = GetMouseInput();	//すべてのマウスの入力状態を取得
	for (auto iter = mouses.begin(); iter != mouses.end(); iter++) {
		KeyState* keyState = iter->second;
		//指定のキーが押されていたら
		if (mouseState & iter->first) {
			keyState->Push();
		}
		//押されていなかったら
		else {
			keyState->Release();
		}
	}

	//マウスホイール回転値更新
	mouseWheelRoteValue = GetMouseWheelRotVolF();
}

bool Input::GetKey(KeyCode keyCode, bool canUseGameWnd)
{
	KeyState* keyState = keys[keyCode];
	return keyState->GetIsPush() && !(canUseGameWnd ^ WindowManager::canUseGameWnd);
}

bool Input::GetKeyDown(KeyCode keyCode, bool canUseGameWnd)
{
	KeyState* keyState = keys[keyCode];
	return keyState->GetIsPush() && keyState->GetIsFirst() && !(canUseGameWnd ^ WindowManager::canUseGameWnd);
}

bool Input::GetKeyUp(KeyCode keyCode, bool canUseGameWnd)
{
	KeyState* keyState = keys[keyCode];
	return !keyState->GetIsPush() && keyState->GetIsFirst() && !(canUseGameWnd ^ WindowManager::canUseGameWnd);
}

bool Input::GetMouseButton(MouseCode mouseCode, bool canUseGameWnd)
{
	KeyState* keyState = mouses[mouseCode];
	return keyState->GetIsPush() && !(canUseGameWnd ^ WindowManager::canUseGameWnd);
}

bool Input::GetMouseButtonDown(MouseCode mouseCode, bool canUseGameWnd)
{
	KeyState* keyState = mouses[mouseCode];
	return keyState->GetIsPush() && keyState->GetIsFirst() && !(canUseGameWnd ^ WindowManager::canUseGameWnd);
}

bool Input::GetMouseButtonUp(MouseCode mouseCode, bool canUseGameWnd)
{
	KeyState* keyState = mouses[mouseCode];
	return !keyState->GetIsPush() && keyState->GetIsFirst() && !(canUseGameWnd ^ WindowManager::canUseGameWnd);
}

Vector3 Input::GetMousePosition()
{
	int x, y;
	GetMousePoint(&x, &y);
	return Vector3((float)x, (float)y, 0.0f);
}

float Input::GetMouseWheelRoteValue()
{
	return mouseWheelRoteValue;
}

std::unordered_map<int, KeyState*> Input::keys;
std::unordered_map<int, KeyState*> Input::mouses;

float Input::mouseWheelRoteValue = 0;