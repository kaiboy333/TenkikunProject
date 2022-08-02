#include "Collider.h"

Collider::Collider(GameObject* gameobject) : DrawComponent(gameobject)
{
}

void Collider::Update()
{

}

Vector3 Collider::GetPosition()
{
    return gameobject->transform->position + offset;
}