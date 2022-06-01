#include "Input.h"

Input::Input()
{
	//�L�[��Ԃ̏�����
	for (int keyCode = 0; keyCode < 256; keyCode++) {
		keys.insert(std::make_pair(keyCode, new KeyState()));	//�L�[��Ԃ̍쐬
	}

	//�}�E�X��Ԃ̏�����
	for (int mouseCode = 0; mouseCode <= 4; mouseCode++) {
		mouses.insert(std::make_pair(mouseCode, new KeyState));	//�}�E�X��Ԃ̍쐬
	}
}

void Input::Update()
{
	//�L�[�{�[�h�̓��͏�ԍX�V
	char buf[256];
	GetHitKeyStateAll(buf);	//���ׂẴL�[�̓��͏�Ԃ��擾
	for (auto iter = keys.begin(); iter != keys.end(); iter++) {
		KeyState* keyState = iter->second;
		//�w��̃L�[��������Ă�����
		if (buf[iter->first]) {
			keyState->Push();
		}
		//������Ă��Ȃ�������
		else {
			keyState->Release();
		}
	}

	//�}�E�X�̓��͏�Ԏ擾
	int mouseState = GetMouseInput();	//���ׂẴ}�E�X�̓��͏�Ԃ��擾
	for (auto iter = mouses.begin(); iter != mouses.end(); iter++) {
		KeyState* keyState = iter->second;
		//�w��̃L�[��������Ă�����
		if (mouseState & iter->first) {
			keyState->Push();
		}
		//������Ă��Ȃ�������
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

bool Input::GetMouseButton(MouseCode mouseCode)
{
	KeyState* keyState = mouses[mouseCode];
	return keyState->GetIsPush();
}

bool Input::GetMouseButtonDown(MouseCode mouseCode)
{
	KeyState* keyState = mouses[mouseCode];
	return keyState->GetIsPush() && keyState->GetIsFirst();
}

bool Input::GetMouseButtonUp(MouseCode mouseCode)
{
	KeyState* keyState = mouses[mouseCode];
	return !keyState->GetIsPush() && keyState->GetIsFirst();
}

Vector3 Input::GetMousePosition()
{
	int x, y;
	GetMousePoint(&x, &y);
	return Vector3((float)x, (float)y, 0.0f);
}

std::unordered_map<int, KeyState*> Input::keys;
std::unordered_map<int, KeyState*> Input::mouses;