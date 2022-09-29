#include "Collider.h"

Collider::Collider(GameObject* gameobject) : DrawComponent(gameobject)
{
}

void Collider::Update()
{
    //交点リセット
    crossPoints.clear();
    //当たり判定リセット
    isHit = false;
}

void Collider::Draw()
{
    for (Vector3 crossPoint : crossPoints) {
        //交点の描画
        Vector3 drawPos = DrawComponent::GetDrawPos(crossPoint);
        DrawCircleAA(drawPos.x, drawPos.y, 3, 30, GetColor(0, 255, 0), TRUE);
    }
}

Vector3 Collider::GetPosition()
{
    return gameobject->transform->position + offset;
}