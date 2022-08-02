#include "HitChecker.h"

bool HitChecker::IsHit(Collider* c1, Collider* c2)
{
    auto& type1 = typeid(*c1);
    auto& type2 = typeid(*c2);

    auto& typeCC = typeid(CircleCollider);
    auto& typeBC = typeid(BoxCollider);

    //�~�Ɖ~�̓����蔻��
    if (type1 == typeCC && type2 == typeCC) {
        return IsHitCC(static_cast<CircleCollider*>(c1), static_cast<CircleCollider*>(c2));
    }
    //��`�Ƌ�`�̓����蔻��
    else if (type1 == typeBC && type2 == typeBC) {
        return IsHitBB(static_cast<BoxCollider*>(c1), static_cast<BoxCollider*>(c2));
    }
    //�~�Ƌ�`�̓����蔻��
    else if (type1 == typeCC && type2 == typeBC) {
        return IsHitCB(static_cast<CircleCollider*>(c1), static_cast<BoxCollider*>(c2));
    }
    else if (type1 == typeBC && type2 == typeCC) {
        return IsHitCB(static_cast<CircleCollider*>(c2), static_cast<BoxCollider*>(c1));
    }
    //�ǂ�ɂ����Ă͂܂�Ȃ��ꍇ
    else {
        //false��Ԃ�
        return false;
    }
}

bool HitChecker::IsHitCC(CircleCollider* c1, CircleCollider* c2)
{
    float distance = Vector3::Distance(c1->GetPosition(), c2->GetPosition());

    return c1->radious + c2->radious >= distance;
}

bool HitChecker::IsHitBB(BoxCollider* c1, BoxCollider* c2)
{
    std::vector<Vector3> vertexes1 = c1->GetVertexes();
    std::vector<Vector3> vertexes2 = c2->GetVertexes();

    float roteZ1 = c1->gameobject->transform->rotation.r.z;
    for (Vector3& vertex1 : vertexes1) {
        //���_�����_���S��-z�x��]������
        vertex1 = Matrix::GetMRoteZ(-roteZ1) * vertex1;
    }
    float roteZ2 = c2->gameobject->transform->rotation.r.z;
    for (Vector3& vertex2 : vertexes2) {
        //���_�����_���S��-z�x��]������
        vertex2 = Matrix::GetMRoteZ(-roteZ2) * vertex2;
    }

    return vertexes1[0].x < vertexes2[2].x&& vertexes1[2].x > vertexes2[0].x && vertexes1[0].y < vertexes2[2].y&& vertexes1[2].y > vertexes2[0].y;
}

bool HitChecker::IsHitCB(CircleCollider* c1, BoxCollider* c2)
{
    //�~�̒��S�_���擾
    Vector3 circleCenter = c1->GetPosition();
    float roteZ1 = c1->gameobject->transform->rotation.r.z;
    //���_�����_���S��-z�x��]������
    circleCenter = Matrix::GetMRoteZ(-roteZ1) * circleCenter;

    //��`�̒��_�擾
    std::vector<Vector3> vertexes = c2->GetVertexes();
    float roteZ2 = c2->gameobject->transform->rotation.r.z;
    for (Vector3 vertex : vertexes) {
        //���_�����_���S��-z�x��]������
        vertex = Matrix::GetMRoteZ(-roteZ2) * vertex;
    }

    //�~�̒��S�_�����`�ւ̍ŒZ�ƂȂ�ʒu
    float px = MyMath::Clamp(circleCenter.x, vertexes[0].x, vertexes[2].x);
    float py = MyMath::Clamp(circleCenter.y, vertexes[0].y, vertexes[2].y);
    Vector3 nearPos = Vector3(px, py, 0);
    //�������Ƃ�
    float distance = Vector3::Distance(circleCenter, nearPos);

    //���������a�ȉ��Ȃ�true
    return distance <= c1->radious;
}

