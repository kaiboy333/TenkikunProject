#include "Rotate.h"
#include "GameObject.h"
#include "Input.h"

void Rotate::ScriptStart()
{
	firstParent = gameobject->transform->parent;
}

void Rotate::ScriptUpdate()
{
	gameobject->transform->rotation += Vector3::Forward() * rotateSpeed;

	if (Input::GetKeyDown(Input::KeyCode::P)) {
		//�e������Ȃ�
		if (gameobject->transform->parent) {
			//�O��
			gameobject->transform->SetParent(nullptr);
		}
		else {
			//�Z�b�g
			gameobject->transform->SetParent(firstParent);
		}
	}
}
