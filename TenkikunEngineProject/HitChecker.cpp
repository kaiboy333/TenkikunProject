#include "HitChecker.h"
#include "DrawComponent.h"
#include "Rect.h"
#include <set>
#include "RigidBody.h"
#include "Physics.h"

bool HitChecker::IsHit(Collider* c1, Collider* c2, std::vector<Vector2>& crossPoints)
{
    //������
    crossPoints.clear();

    auto& type1 = typeid(*c1);
    auto& type2 = typeid(*c2);

    auto& typeCC = typeid(CircleCollider);
    auto& typeBC = typeid(BoxCollider);

    if(true) {
        //�~�Ɖ~�̓����蔻��
        if (type1 == typeCC && type2 == typeCC) {
            return IsHitCC(static_cast<CircleCollider*>(c1), static_cast<CircleCollider*>(c2), crossPoints);
        }
        //��`�Ƌ�`�̓����蔻��
        if (type1 == typeBC && type2 == typeBC) {
            return IsHitBB(static_cast<BoxCollider*>(c1), static_cast<BoxCollider*>(c2), crossPoints);
        }
        //�~�Ƌ�`�̓����蔻��
        else if (type1 == typeCC && type2 == typeBC) {
            return IsHitCB(static_cast<CircleCollider*>(c1), static_cast<BoxCollider*>(c2), crossPoints);
        }
        else if (type1 == typeBC && type2 == typeCC) {
            return IsHitCB(static_cast<CircleCollider*>(c2), static_cast<BoxCollider*>(c1), crossPoints);
        }
        //�ǂ�ɂ����Ă͂܂�Ȃ��ꍇ
        else {
            //false��Ԃ�
            return false;
        }
    }
}

bool HitChecker::IsHitCC(CircleCollider* c1, CircleCollider* c2)
{
    float d = Vector2::Distance(c1->GetPosition(), c2->GetPosition());

    float r1 = c1->GetActualRadious();
    float r2 = c2->GetActualRadious();

    bool isHit = r1 + r2 >= d;

    RigidBody* rb1 = c1->gameobject->GetComponent<RigidBody>();
    RigidBody* rb2 = c2->gameobject->GetComponent<RigidBody>();

    //���̂ł��蔲���Ȃ��A�����I�u�W�F�N�g�ɂ��Ă��Ȃ����
    if (rb1 && rb2 && !c1->isTrigger && !c2->isTrigger && isHit
        && c1->gameobject != c2->gameobject) {
        Vector2 p12 = c2->GetPosition() - c1->GetPosition();
        Vector2 n = p12 / p12.GetMagnitude();
        Vector2 v12 = rb2->velocity - rb1->velocity;
        Vector2 vn1 = n * Vector2::Inner(rb1->velocity, n);
        Vector2 vt1 = rb1->velocity - vn1;
        Vector2 t = vt1 / vt1.GetMagnitude();
        float j = (1 + Physics::e) * (rb1->mass * rb2->mass / (rb1->mass + rb2->mass)) * Vector2::Inner(v12, n);
        Vector2 J = n * j;

        //�͂��u�ԓI�ɉ�����
        rb1->AddForce(J, RigidBody::ForceMode::Impulse);
        rb2->AddForce(-J, RigidBody::ForceMode::Impulse);

        //float k = 3.0f;
        //float e = 1.0f;
        //Vector3 p12 = c2->GetPosition() - c1->GetPosition();
        //Vector3 n = p12 / p12.GetMagnitude();
        //Vector3 v12 = rb2->velocity - rb1->velocity;
        //Vector3 vn1 = n * Vector3::Inner(rb1->velocity, n);
        //Vector3 vt1 = rb1->velocity - vn1;
        //Vector3 t = vt1 / vt1.GetMagnitude();
        //float spring = -k * (r1 + r2 - d);
        //float j = (1 + Physics::e) * (rb1->mass * rb2->mass / (rb1->mass + rb2->mass)) * Vector3::Inner(v12, n);
        //Vector3 impulse = n * (j + spring);
        //rb1->AddForce(impulse, RigidBody::ForceMode::Impulse);
        //rb2->AddForce(-impulse, RigidBody::ForceMode::Impulse);
    }

    return isHit;
}

bool HitChecker::IsHitCC(CircleCollider* c1, CircleCollider* c2, std::vector<Vector2>& crossPoints)
{
    float distance = Vector2::Distance(c1->GetPosition(), c2->GetPosition());

    Vector2 centerPos1 = c1->GetPosition();
    Vector2 centerPos2 = c2->GetPosition();
    float r1 = c1->GetActualRadious();
    float r2 = c2->GetActualRadious();

    //�~����_�Ō�����Ă���Ȃ�
    if (std::abs(r1 - r2) < Vector2::Distance(centerPos1, centerPos2) && Vector2::Distance(centerPos1, centerPos2) < r1 + r2) {
        float a = 2 * (centerPos2.x - centerPos1.x);
        float b = 2 * (centerPos2.y - centerPos1.y);
        float c = (centerPos1.x + centerPos2.x) * (centerPos1.x - centerPos2.x) + (centerPos1.y + centerPos2.y) * (centerPos1.y - centerPos2.y) + (r2 + r1) * (r2 - r1);

        float d1 = -(a * centerPos1.x + b * centerPos1.y + c);

        float tmp0 = std::powf(a, 2) + std::powf(b, 2);

        float tmp1 = std::sqrtf((tmp0 * std::powf(r1, 2) - std::powf(d1, 2)));

        Vector2 crossPoint1 = Vector2((a * d1 - b * tmp1) / tmp0 + centerPos1.x, (b * d1 + a * tmp1) / tmp0 + centerPos1.y);
        Vector2 crossPoint2 = Vector2((a * d1 + b * tmp1) / tmp0 + centerPos1.x, (b * d1 - a * tmp1) / tmp0 + centerPos1.y);

        //��_�����X�g�ɒǉ�
        if (std::find(crossPoints.begin(), crossPoints.end(), crossPoint1) == crossPoints.end()) {
            crossPoints.push_back(crossPoint1);
        }
        if (std::find(crossPoints.begin(), crossPoints.end(), crossPoint2) == crossPoints.end()) {
            crossPoints.push_back(crossPoint2);
        }
    }

    return IsHitCC(c1, c2);
}

bool HitChecker::IsHitBB(BoxCollider* c1, BoxCollider* c2, std::vector<Vector2>& crossPoints)
{
    std::vector<Vector2> vertexes1 = c1->GetVertexes();
    std::vector<Vector2> vertexes2 = c2->GetVertexes();

    for (int i = 0, length1 = (int)vertexes1.size(); i < length1; i++) {
        for (int j = 0, length2 = (int)vertexes2.size(); j < length2; j++) {
            Vector2 p1 = vertexes1[i % length1];
            Vector2 p2 = vertexes1[(i + 1) % length1];
            Vector2 p3 = vertexes2[j % length2];
            Vector2 p4 = vertexes2[(j + 1) % length2];

            Vector2 crossPoint;

            //��_������Ȃ�
            if (Vector2::IsCross(p1, p2, p3, p4, crossPoint)) {
                //���X�g�ɒǉ�
                if (std::find(crossPoints.begin(), crossPoints.end(), crossPoint) == crossPoints.end()) {
                    crossPoints.push_back(crossPoint);
                }
            }
        }
    }

    return (int)crossPoints.size() != 0;
}

bool HitChecker::IsHitCB(CircleCollider* c1, BoxCollider* c2, std::vector<Vector2>& crossPoints)
{
    //�~�̒��S�_���擾
    Vector2 centerPos = c1->GetPosition();
    Vector3 scale = c1->gameobject->transform->scale;
    float r = c1->GetActualRadious();
    //��`�̒��_���擾
    std::vector<Vector2> vertexes = c2->GetVertexes();

    for (int i = 0, length = (int)vertexes.size(); i < length; i++) {
        Vector2 p1 = vertexes[i % length];
        Vector2 p2 = vertexes[(i + 1) % length];

        float a = p1.y - p2.y;
        float b = p2.x - p1.x;
        float c = Vector2::Cross(p1, p2);

        //�~�̒��S���璼���܂ł̍ŒZ���������߂�
        float minDistance = std::abs(a * centerPos.x + b * centerPos.y + c) / std::sqrtf(std::powf(a, 2) + std::powf(b, 2));

        //�����������Ȃ�
        if (minDistance <= r) {
            float d = -(a * centerPos.x + b * centerPos.y + c);

            float tmp0 = std::powf(a, 2) + std::powf(b, 2);

            float tmp1 = std::sqrtf((tmp0 * std::powf(r, 2) - std::powf(d, 2)));

            Vector2 crossPoint1 = Vector3((a * d - b * tmp1) / tmp0 + centerPos.x, (b * d + a * tmp1) / tmp0 + centerPos.y, 0);
            Vector2 crossPoint2 = Vector3((a * d + b * tmp1) / tmp0 + centerPos.x, (b * d - a * tmp1) / tmp0 + centerPos.y, 0);

            float s = (crossPoint1 - p1).GetMagnitude() / (p2 - p1).GetMagnitude();
            //��_�������͈͓̔��ɂ���Ȃ�(�x�N�g�������������������̔䂪0����1)
            if (s >= 0 && s <= 1 && Vector2::Inner(crossPoint1 - p1, p2 - p1) >= 0.99f) {
                if (std::find(crossPoints.begin(), crossPoints.end(), crossPoint1) == crossPoints.end()) {
                    crossPoints.push_back(crossPoint1);
                }
            }
            float t = (crossPoint2 - p1).GetMagnitude() / (p2 - p1).GetMagnitude();
            //��_�������͈͓̔��ɂ���Ȃ�(�x�N�g�������������������̔䂪0����1)
            if (t >= 0 && t <= 1 && Vector2::Inner(crossPoint2 - p1, p2 - p1) >= 0.99f) {
                if (std::find(crossPoints.begin(), crossPoints.end(), crossPoint2) == crossPoints.end()) {
                    crossPoints.push_back(crossPoint2);
                }
            }
        }
    }

    return (int)crossPoints.size() != 0;
}

