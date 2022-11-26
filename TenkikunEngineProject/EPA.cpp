#include "EPA.h"
#include "RigidBody.h"
#include "BoxCollider.h"
#include "Debug.h"
#include <set>

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

    //������덷
    float okDistance = 0.1f;
    Vector2 beforeSupportVec = vertexes[2];
    Vector2 crossPoint;
    int minSideIndex;
    Vector2 v;

    for (int j = 0; j < 100; j++) {
        //���_����ʕ�ւ̍ŒZ���������߂�
        GJK::GetShortestDistanceToShape(Vector2::Zero(), vertexes, crossPoint, minSideIndex);
        //�ŒZ�����ƂȂ�ӂɐ����ȃx�N�g�����擾(dir���|���Đ}�`�̕ӕ����Ɍ�����)
        v = Matrix::GetMRoteZ(Vector2::Zero(), 90) * (vertexes[(minSideIndex + 1) % (int)vertexes.size()] - vertexes[minSideIndex]) * (float)dir;
        //�T�|�[�g�ʑ������߂�
        Vector2 supportVec = GJK::Support(c1, c2, v);
        //�O��̃T�|�[�g�ʑ��ƍ���̃T�|�[�g�ʑ��̋��������ȉ��Ȃ�
        if (Vector2::Distance(beforeSupportVec, supportVec) <= okDistance) {
            //�I���(���ꂪ�߂荞�ݐ[�x)
            break;
        }
        //����̂��L��
        beforeSupportVec = supportVec;
        //�T�|�[�g�ʑ���ǉ�(�ŒZ�����ƂȂ�ӂ̔ԍ�+1�̒��_��)
        vertexes.insert(vertexes.begin() + ((minSideIndex + 1) % (int)vertexes.size()), supportVec);
    }


    Contact* contact = new Contact();

    //�߂荞�ݐ[�x(����������L�΂�)
    auto moveVec = -crossPoint * 1.001f;

    //c1�𓮂���
    c1->gameobject->transform->position += moveVec;
    //c1�̏Փ˓_�����߂�
    auto pointsA = GetContactPoints(c1, c2);
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
    //c2�̏Փ˓_�����߂�
    auto pointsB = GetContactPoints(c2, c1);
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
        Debug::Log("pointsA��pointsB�̐�������Ȃ���");
    }
    //c2��߂�
    c2->gameobject->transform->position -= -moveVec;

    //���C�Z�b�g
    contact->friction = std::sqrtf((rb1 ? rb1->friction : 0.5f) * (rb2 ? rb2->friction : 0.5f));
    HitInfo* hitInfo = new HitInfo(supportInfo->colliderID1, supportInfo->colliderID2, contact);
        
    return hitInfo;
}

std::vector<Vector2> EPA::GetContactPoints(Collider* c1, Collider* c2)
{
    auto& type1 = typeid(*c1);
    auto& type2 = typeid(*c2);

    auto& typeCC = typeid(CircleCollider);
    auto& typeBC = typeid(BoxCollider);

    if (true) {
        //�~�Ɖ~�̏Փ˓_
        if (type1 == typeCC && type2 == typeCC) {
            return GetContactPoints(static_cast<CircleCollider*>(c1), static_cast<CircleCollider*>(c2));
        }
        //��`�Ƌ�`�̏Փ˓_
        if (type1 == typeBC && type2 == typeBC) {
            return GetContactPoints(static_cast<BoxCollider*>(c1), static_cast<BoxCollider*>(c2));
        }
        //�~�Ƌ�`�̏Փ˓_
        else if (type1 == typeCC && type2 == typeBC) {
            return GetContactPoints(static_cast<CircleCollider*>(c1), static_cast<BoxCollider*>(c2));
        }
        else if (type1 == typeBC && type2 == typeCC) {
            return GetContactPoints(static_cast<CircleCollider*>(c2), static_cast<BoxCollider*>(c1));
        }
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
            float distance = GJK::GetShortestDistanceToShape(cA->GetVertexes()[j], cB->GetVertexes(), crossPoint, minSideIndex);
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
    GJK::GetShortestDistanceToShape(c1->GetPosition(), c2->GetVertexes(), contactPoint, minSideIndex);
    //�ŒZ�̌�_���Փ˓_
    return { contactPoint };
}

std::vector<Vector2> EPA::GetContactPoints(CircleCollider* c1, CircleCollider* c2)
{
    //�~����~�̃x�N�g���̃T�|�[�g�ʑ����Փ˓_
    return { GJK::Support(c1, c2->GetPosition() - c1->GetPosition()) };
}

