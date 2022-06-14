#include "Rotate.h"
#include "GameObject.h"
#include "Input.h"

void Rotate::ScriptStart()
{
}

void Rotate::ScriptUpdate()
{
	gameobject->transform->rotation += Vector3::Forward() * rotateSpeed;
}
