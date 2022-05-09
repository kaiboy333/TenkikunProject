#include "Input.h"

Input::Input()
{
	//�L�[��Ԃ̏�����
	for (int keyCode = KeyCode::A; keyCode <= KeyCode::DOWN; keyCode++) {
		keys.insert(std::make_pair(keyCode, new KeyState()));	//�L�[��Ԃ̍쐬
	}
}

void Input::Update()
{
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
