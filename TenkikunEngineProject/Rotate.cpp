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
		//親がいるなら
		if (gameobject->transform->parent) {
			//外す
			gameobject->transform->SetParent(nullptr);
		}
		else {
			//セット
			gameobject->transform->SetParent(firstParent);
		}
	}
}
