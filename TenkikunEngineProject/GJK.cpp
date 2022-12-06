#include "GJK.h"
#include "BoxCollider.h"
#include "Debug.h"
#include "Collision.h"
#include "RigidBody.h"
#include "Time.h"

SupportInfo* GJK::IsHit(std::vector<Collider*>& colliders, int colliderID1, int colliderID2)
{
    auto c1 = colliders[colliderID1];
    auto c2 = colliders[colliderID2];

    Vector2 v = c1->GetPosition() - c2->GetPosition();
    if (v == Vector2::Zero()) {
        //return true;
        v = Vector2::One();
    }

    std::vector<Vector2> vertexes;
    vertexes.reserve(4);
    for (int i = 0; i < 30; i++) {

        //�T�|�[�g�ʑ������߂�
        vertexes.push_back(Support(c1, c2, v));

        Vector2 crossPoint;
        int minSideIndex;

        switch ((int)vertexes.size()) {
            case 1:
                v = -vertexes[0];
                break;
            case 2:
                if (vertexes[0] == vertexes[1]) {
                    return nullptr;
                }
                //vertexes[1] - vertexes[0]�ɐ����ȃx�N�g�����擾
                v = Matrix::GetMRoteZ(Vector2::Zero(), 90) * (vertexes[1] - vertexes[0]);
                //vertexes[0]�Ƃ̓��ς�����������������t�ɂ���
                if (Vector2::Dot(v, vertexes[0]) < 0) {
                    v = -v;
                }
                break;
            case 3:
                //�V�����ł������_������_�Ɣ��Ȃ�(���������Ȃ�)
                if (vertexes[2] == vertexes[0] || vertexes[2] == vertexes[1]) {
                    return nullptr;
                }
                //���_��3�_�ō�����O�p�`�Ɋ܂܂�Ă���Ȃ�
                if (IsPointInTriangle(Vector2::Zero(), vertexes)) {
                    auto supportInfo = new SupportInfo();
                    supportInfo->supports = vertexes;
                    supportInfo->colliderID1 = colliderID1;
                    supportInfo->colliderID2 = colliderID2;
                    return supportInfo;
                }

                //���_����O�p�`�ւ̍ŒZ���������߂�
                GetShortestDistanceToShape(Vector2::Zero(), vertexes, crossPoint, minSideIndex);
                //���_�����ԉ����_���폜(���ʓ�_�ɂȂ�)
                vertexes.erase(vertexes.begin() + ((minSideIndex - 1 + (int)vertexes.size()) % (int)vertexes.size()));
                //���̕��������߂�
                v = -crossPoint;
                break;
        }
    }

    return nullptr;
}

Vector2 GJK::Support(Collider* c1, Collider* c2, const Vector2& v)
{
    return Support(c1, v) - Support(c2, -v);
}

Vector2 GJK::Support(Collider* c, const Vector2& d)
{
    auto& type = typeid(*c);

    auto& typeBC = typeid(BoxCollider);
    auto& typeCC = typeid(CircleCollider);

    if (type == typeBC) {
        return Support(static_cast<VertexCollider*>(c), d);
    }
    else if (type == typeCC) {
        return Support(static_cast<CircleCollider*>(c), d);
    }

    return Vector2();
}

Vector2 GJK::Support(const VertexCollider* c, const Vector2& d)
{
    //float times[2] = {};

    //times[0] = Time::GetTime();

    auto vertexes = c->GetVertexes();
    //�ő����
    float maxDot;
    //�ő���ς̎��̒��_���W
    Vector2 supportVec;
    ////�ő���ς̎��̒���(����)
    //float maxDistance;

    for (int i = 0, len = (int)vertexes.size(); i < len; i++) {
        Vector2& vertex = vertexes[i];
        float dot = Vector2::Dot(vertex, d);
        //float distance = vertex.GetMagnitude();
        if (i == 0) {
            maxDot = dot;
            supportVec = vertex;
            //maxDistance = distance;
        }
        //���ς����܂łōő�Ȃ�
        else if (dot > maxDot) {
            //�X�V
            maxDot = dot;
            //���̎��̒��_���L��
            supportVec = vertex;
            ////�������L��
            //maxDistance = distance;
        }
        ////���ς������ő�Ȃ�
        //else if (dot == maxDot) {
        //    //����̂ق��������Ȃ�X�V
        //    if (maxDistance < distance) {
        //        //���̎��̒��_���L��
        //        supportVec = vertex;
        //        //�������L��
        //        maxDistance = distance;
        //    }
        //}
    }

    //times[1] = Time::GetTime();

    //Debug::Log("supportVert:" + std::to_string(times[1] - times[0]));

    return supportVec;
}

Vector2 GJK::Support(const CircleCollider* c, const Vector2& d)
{
    //float times[2] = {};

    //times[0] = Time::GetTime();

    //���S�̍��W���擾
    Vector2 centerPos = c->GetPosition();
    //���S����d�̕����ɐL�΂������̉~�Ƃ̌�_���T�|�[�g�ʑ�
    Vector2 supportVec = centerPos + d.GetNormalized() * c->GetActualRadious();

    //times[1] = Time::GetTime();

    //Debug::Log("supportCircle:" + std::to_string(times[1] - times[0]));

    return supportVec;
}

bool GJK::IsPointInTriangle(const Vector2& point, std::vector<Vector2>& vertexes)
{
    //���_��3�ł͂Ȃ��Ȃ�I���
    if (vertexes.size() != 3) {
        return false;
    }

    //�����v���
    int dir = 1;
    //���v���Ȃ�
    if (Vector2::Cross(vertexes[1] - vertexes[0], vertexes[2] - vertexes[0]) > 0) {
        //�������]
        dir = -1;
    }

    for (int i = 0, len = (int)vertexes.size(); i < len; i++) {
        Vector2& vert1 = vertexes[i % len];
        Vector2& vert2 = vertexes[(i + 1) % len];

        //�}�`�̈�ӂɑ΂��ē_���O���ɂ���Ȃ�
        if (Vector2::Cross(vert2 - vert1, point - vert1) * dir > 0) {
            //���ɂȂ�
            return false;
        }
    }

    //���ׂĂ̕ӂ̓����ɂ���Ȃ�true
    return true;
}

float GJK::GetShortestDistanceToShape(const Vector2& targetPoint, const std::vector<Vector2>& vertexes, Vector2& crossPoint, int& minSideIndex)
{
    float minDistance = 0;

    for (int i = 0, len = (int)vertexes.size(); i < len; i++) {
        const Vector2& vert1 = vertexes[i % len];
        const Vector2& vert2 = vertexes[(i + 1) % len];

        Vector2 crossPoint2;
        float distance = Vector2::GetMinDistance(vert1, vert2, targetPoint, crossPoint2);
        //�ŏ��Ȃ�
        if (i == 0) {
            minDistance = distance;
            crossPoint = crossPoint2;
            minSideIndex = i;
        }
        //�ŒZ����������
        else if (minDistance > distance) {
            minDistance = distance;
            crossPoint = crossPoint2;
            minSideIndex = i;
        }
    }

    return minDistance;
}