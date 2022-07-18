#include "Rotate.h"
#include "GameObject.h"
#include "Input.h"

void Rotate::MonoStart()
{
}

void Rotate::MonoUpdate()
{
	gameobject->transform->rotation += Vector3::Forward() * rotateSpeed;
}
