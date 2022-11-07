#include "Collider.h"

Collider::Collider(GameObject* gameobject) : DrawComponent(gameobject)
{
    //番号をつける
    no = Collider::newNo++;
}

void Collider::Update()
{
    ////交点リセット
    //crossPoints.clear();
    //当たり判定リセット
    isHit = false;
}

void Collider::Draw()
{
    //バウンディングボックスの描画
    //DrawBoundingBox();
}

Vector3 Collider::GetPosition()
{
    return gameobject->transform->position + offset;
}

void Collider::DrawBoundingBox()
{
    Rect bb = GetBoundingBox();

    Vector3 leftDownDrawPos = GetDrawPos(Vector3(bb.startX, bb.startY, 0));
    Vector3 rightUpDrawPos = GetDrawPos(Vector3(bb.startX + bb.width, bb.startY + bb.height, 0));

    //青で描画
    DrawBoxAA(leftDownDrawPos.x, leftDownDrawPos.y, rightUpDrawPos.x, rightUpDrawPos.y, GetColor(0, 0, 255), FALSE);
}

int Collider::GetNo() const
{
    return no;
}

bool Collider::operator==(const Collider& other) const
{
    return this->GetNo() == other.GetNo();
}

bool Collider::operator!=(const Collider& other) const
{
    return !(*this == other);
}

bool Collider::operator<(const Collider& other) const
{
    return this->GetNo() < other.GetNo();
}

bool Collider::operator>(const Collider& other) const
{
    return !(*this < other);
}

int Collider::newNo = 0;
