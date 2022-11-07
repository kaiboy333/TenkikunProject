#include "Collider.h"

Collider::Collider(GameObject* gameobject) : DrawComponent(gameobject)
{
    //�ԍ�������
    no = Collider::newNo++;
}

void Collider::Update()
{
    ////��_���Z�b�g
    //crossPoints.clear();
    //�����蔻�胊�Z�b�g
    isHit = false;
}

void Collider::Draw()
{
    //�o�E���f�B���O�{�b�N�X�̕`��
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

    //�ŕ`��
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
