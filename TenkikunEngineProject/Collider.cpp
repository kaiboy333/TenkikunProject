#include "Collider.h"

Collider::Collider(GameObject* gameobject) : DrawComponent(gameobject)
{
}

void Collider::Update()
{
    //��_���Z�b�g
    crossPoints.clear();
}

void Collider::Draw()
{
    for (Vector3 crossPoint : crossPoints) {
        //��_�̕`��
        Vector3 drawPos = DrawComponent::GetDrawPos(crossPoint);
        DrawCircleAA(drawPos.x, drawPos.y, 3, 30, GetColor(0, 0, 255), TRUE);
    }
}

Vector3 Collider::GetPosition()
{
    return gameobject->transform->position + offset;
}