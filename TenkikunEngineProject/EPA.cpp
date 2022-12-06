#include "EPA.h"
#include "RigidBody.h"
#include "BoxCollider.h"
#include "Debug.h"
#include <set>
#include "Time.h"

HitInfo* EPA::GetHitInfo(const std::vector<Collider*>& colliders, SupportInfo* supportInfo)
{
    auto& vertexes = supportInfo->supports;
    auto* c1 = colliders[supportInfo->colliderID1];
    auto* c2 = colliders[supportInfo->colliderID2];

    RigidBody* rb1 = c1->gameobject->GetComponent<RigidBody>();
    RigidBody* rb2 = c2->gameobject->GetComponent<RigidBody>();

    //�ǂ�������̂łȂ��Ȃ�
    if (!rb1 && !rb2)
        return nullptr;

    //�����v���
    int dir = 1;
    //���v���Ȃ�
    if (Vector2::Cross(vertexes[1] - vertexes[0], vertexes[2] - vertexes[0]) > 0) {
        //�������]
        dir = -1;
    }

    //float time[9] = {};

    //time[0] = Time::GetTime();

    //������덷
    float okDistance = 0.1f;
    Vector2 beforeSupportVec = vertexes[2];
    Vector2 crossPoint;
    int minSideIndex;
    Vector2 v;
    float minDistance = 0.001f;

    for (int j = 0; j < 100; j++) {
        //float time_t[6] = {};
        //time_t[0] = Time::GetTime();

        //���_����ʕ�ւ̍ŒZ���������߂�
        auto gjk = GJK();
        gjk.GetShortestDistanceToShape(Vector2::Zero(), vertexes, crossPoint, minSideIndex);

        //time_t[1] = Time::GetTime();

        //�ŒZ�����ƂȂ�ӂɐ����ȃx�N�g�����擾(dir���|���Đ}�`�̕ӕ����Ɍ�����)
        auto& vertex1 = vertexes[(minSideIndex + 1) % (int)vertexes.size()];
        auto& vertex2 = vertexes[minSideIndex];
        v = (Matrix::GetMRoteZ(Vector2::Zero(), 90) * (vertex1 - vertex2) * (float)dir).GetNormalized();

        //time_t[2] = Time::GetTime();

        //�T�|�[�g�ʑ������߂�
        Vector2 supportVec = gjk.Support(c1, c2, v);

        //time_t[3] = Time::GetTime();

        //�O��̃T�|�[�g�ʑ��ƍ���̃T�|�[�g�ʑ��̋��������ȉ��Ȃ�
        if (Vector2::Distance(beforeSupportVec, supportVec) <= okDistance) {
            //�I���(���ꂪ�߂荞�ݐ[�x)
            break;
        }
        //����̂��L��
        beforeSupportVec = supportVec;

        //time_t[4] = Time::GetTime();

        //�T�|�[�g�ʑ���ǉ�(�ŒZ�����ƂȂ�ӂ̔ԍ�+1�̒��_��)
        vertexes.insert(vertexes.begin() + ((minSideIndex + 1) % (int)vertexes.size()), supportVec);

        //time_t[5] = Time::GetTime();
        //for (int i = 0; i < 5; i++) {
        //    Debug::Log("Shape" + std::to_string(i) + ":" + std::to_string(time_t[i + 1] - time_t[i]));
        //}
    }

    //time[1] = Time::GetTime();

    Contact* contact = new Contact();

    //�߂荞�ݐ[�x(����������L�΂�)
    auto moveVec = -crossPoint * 1.001f;

    //time[2] = Time::GetTime();

    //c1�𓮂���
    c1->gameobject->transform->position += moveVec;

    //time[3] = Time::GetTime();

    //c1�̏Փ˓_�����߂�
    auto pointsA = GetContactPoints(c1, c2);

    //time[4] = Time::GetTime();

    for (auto& pointA : pointsA) {
        //�V����ContactPoint�ǉ�
        ContactPoint* cp = new ContactPoint();
        //�@���x�N�g��
        cp->normal = crossPoint.GetNormalized();
        //�ђʐ[�x
        cp->distance = crossPoint.GetMagnitude();
        //�Փ˓_
        cp->pointA = pointA;
        //ContactPoint�ǉ�
        contact->contactPoints.push_back(cp);
    }

    //c1��߂�
    c1->gameobject->transform->position -= moveVec;

    //c2�𓮂���
    c2->gameobject->transform->position += -moveVec;

    //time[5] = Time::GetTime();

    //c2�̏Փ˓_�����߂�
    auto pointsB = GetContactPoints(c2, c1);

    //time[6] = Time::GetTime();

    //�����鋗���̍�
    okDistance = 0.1f;
    //pointsB��pointsA�ɑΉ������_�ɂ���
    if ((int)pointsA.size() == (int)pointsB.size()) {
        for (auto& pointA : pointsA) {
            for (int i = 0, len = (int)pointsB.size(); i < len; i++) {
                //pointA�Ƃ̋������ђʐ[�x�Ƃقړ����Ȃ�ΐ������g�ݍ��킹
                if (Vector2::Distance(pointA, pointsB[i]) - contact->contactPoints[i]->distance <= okDistance) {
                    //ContactPoint���擾
                    ContactPoint* cp = contact->contactPoints[i];
                    //�Փ˓_
                    cp->pointB = pointsB[i];
                }
            }
        }
    }
    else {
        //Debug::Log("pointsA��pointsB�̐�������Ȃ���");
    }
    //c2��߂�
    c2->gameobject->transform->position -= -moveVec;

    //time[7] = Time::GetTime();

    //���C�Z�b�g
    contact->friction = std::sqrtf((rb1 ? rb1->friction : 0.5f) * (rb2 ? rb2->friction : 0.5f));

    HitInfo* hitInfo = new HitInfo();
    hitInfo->colliderID1 = supportInfo->colliderID1;
    hitInfo->colliderID2 = supportInfo->colliderID2;
    hitInfo->contact = contact;

    //for (auto i = 0; i < 7; i++) {
    //    Debug::Log("EPA" + std::to_string(i) + ":" + std::to_string(time[i + 1] - time[i]));
    //}
        
    return hitInfo;
}

std::vector<Vector2> EPA::GetContactPoints(Collider* c1, Collider* c2)
{
    auto& type1 = typeid(*c1);
    auto& type2 = typeid(*c2);

    auto& typeCC = typeid(CircleCollider);
    auto& typeBC = typeid(BoxCollider);

    //�~�Ɖ~�̏Փ˓_
    if (type1 == typeCC && type2 == typeCC) {
        return GetContactPoints(static_cast<CircleCollider*>(c1), static_cast<CircleCollider*>(c2));
    }
    //��`�Ƌ�`�̏Փ˓_
    else if (type1 == typeBC && type2 == typeBC) {
        return GetContactPoints(static_cast<BoxCollider*>(c1), static_cast<BoxCollider*>(c2));
    }
    //�~�Ƌ�`�̏Փ˓_
    else if (type1 == typeCC && type2 == typeBC) {
        return GetContactPoints(static_cast<CircleCollider*>(c1), static_cast<BoxCollider*>(c2));
    }
    else if (type1 == typeBC && type2 == typeCC) {
        return GetContactPoints(static_cast<CircleCollider*>(c2), static_cast<BoxCollider*>(c1));
    }

    return std::vector<Vector2>();
}

std::vector<Vector2> EPA::GetContactPoints(VertexCollider* c1, VertexCollider* c2)
{
    std::vector<VertexCollider*> colliders = {c1, c2};
    const float okDistance = 0.1f;
    float minDistance = 0;
    //�d���������Ȃ�
    std::set<Vector2> contactPointsSet;
    //c1��c2�̐}�`�̍ŒZ����
    for (int i = 0, len = (int)colliders.size(); i < len; i++) {
        VertexCollider* cA = colliders[i];
        VertexCollider* cB = colliders[std::abs(i - (len - 1))];

        //cA�̒��_����cB�ւ̍ŒZ���������߂�
        for (int j = 0, len2 = (int)cA->GetVertexes().size(); j < len2; j++) {
            int minSideIndex;
            Vector2 crossPoint;
            auto gjk = GJK();
            float distance = gjk.GetShortestDistanceToShape(cA->GetVertexes()[j], cB->GetVertexes(), crossPoint, minSideIndex);
            //�ŏ���
            if (i == 0 && j == 0) {
                minDistance = distance;
                contactPointsSet.insert(crossPoint);
                contactPointsSet.insert(cA->GetVertexes()[j]);
            }
            //�قړ����Ȃ�
            else if (std::abs(minDistance - distance) <= okDistance) {
                //�ǉ�
                contactPointsSet.insert(crossPoint);
                contactPointsSet.insert(cA->GetVertexes()[j]);
            }
            //�ŒZ�Ȃ�
            else if (minDistance > distance) {
                minDistance = distance;
                //�Â��̂����ׂč폜
                contactPointsSet.clear();
                //�ǉ�
                contactPointsSet.insert(crossPoint);
                contactPointsSet.insert(cA->GetVertexes()[j]);
            }
        }
    }

    std::vector<Vector2> contactPoints = std::vector<Vector2>(contactPointsSet.begin(), contactPointsSet.end());
    //4��������
    if ((int)contactPoints.size() == 4) {
        //2�̏Փ˓_�����o��(���̂������悤�Ȓl�̂���)
        return { contactPoints[0], contactPoints[2] };
    }
    //2�Ȃ�
    else {
        //1�̏Փ˓_�����o��(���̂������悤�Ȓl�̂���)
        return { contactPoints[0] };
    }
}

std::vector<Vector2> EPA::GetContactPoints(CircleCollider* c1, VertexCollider* c2)
{
    //c1�̒��S�_��c2�̐}�`�̍ŒZ����
    int minSideIndex;
    Vector2 contactPoint;
    auto gjk = GJK();
    gjk.GetShortestDistanceToShape(c1->GetPosition(), c2->GetVertexes(), contactPoint, minSideIndex);
    //�ŒZ�̌�_���Փ˓_
    return { contactPoint };
}

std::vector<Vector2> EPA::GetContactPoints(CircleCollider* c1, CircleCollider* c2)
{
    //�~����~�̃x�N�g���̃T�|�[�g�ʑ����Փ˓_
    auto gjk = GJK();
    return { gjk.Support(c1, c2->GetPosition() - c1->GetPosition()) };
}

