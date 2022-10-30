#include "EPA.h"
#include "RigidBody.h"
#include "BoxCollider.h"

HitInfo* EPA::GetHitInfo(std::vector<Collider*> colliders, SupportInfo* supportInfo)
{
    auto& vertexes = supportInfo->supports;
    auto c1 = colliders[supportInfo->colliderID1];
    auto c2 = colliders[supportInfo->colliderID2];

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

    for (int j = 0; j < 30; j++) {
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


    Contact contact;
    ContactPoint cp;
    cp.normal = crossPoint.GetNormalized();
    cp.distance = crossPoint.GetMagnitude();

    //�߂荞�ݐ[�x(����������L�΂�)
    auto moveVec = -crossPoint * 1.001f;

    //c1�𓮂���
    c1->gameobject->transform->position += moveVec;
    //c1�̏Փ˓_�����߂�
    cp.pointA = GetContactPoint(c1, c2);
    //c1��߂�
    c1->gameobject->transform->position -= moveVec;

    //c2�𓮂���
    c2->gameobject->transform->position += -moveVec;
    //c2�̏Փ˓_�����߂�
    cp.pointB = GetContactPoint(c1, c2);
    //c2��߂�
    c2->gameobject->transform->position -= -moveVec;

    contact.contactPoints.push_back(cp);
    contact.friction = std::sqrtf((rb1 ? rb1->friction : 0.5f) * (rb2 ? rb2->friction : 0.5f));
    HitInfo* hitInfo = new HitInfo(supportInfo->colliderID1, supportInfo->colliderID2, contact);
        
    return hitInfo;
}

Vector2 EPA::GetContactPoint(Collider* c1, Collider* c2)
{
    auto& type1 = typeid(*c1);
    auto& type2 = typeid(*c2);

    auto& typeCC = typeid(CircleCollider);
    auto& typeBC = typeid(BoxCollider);

    if (true) {
        //�~�Ɖ~�̏Փ˓_
        if (type1 == typeCC && type2 == typeCC) {
            return GetContactPoint(static_cast<CircleCollider*>(c1), static_cast<CircleCollider*>(c2));
        }
        //��`�Ƌ�`�̏Փ˓_
        if (type1 == typeBC && type2 == typeBC) {
            return GetContactPoint(static_cast<BoxCollider*>(c1), static_cast<BoxCollider*>(c2));
        }
        //�~�Ƌ�`�̏Փ˓_
        else if (type1 == typeCC && type2 == typeBC) {
            return GetContactPoint(static_cast<CircleCollider*>(c1), static_cast<BoxCollider*>(c2));
        }
        else if (type1 == typeBC && type2 == typeCC) {
            return GetContactPoint(static_cast<CircleCollider*>(c2), static_cast<BoxCollider*>(c1));
        }
    }

    return Vector2();
}

Vector2 EPA::GetContactPoint(VertexCollider* c1, VertexCollider* c2)
{
    float minDistance;
    Vector2 contactPoint;
    //c1�̓_��c2�̐}�`�̍ŒZ����
    for (int i = 0, len = (int)c1->GetVertexes().size(); i < len; i++) {
        int minSideIndex;
        Vector2 crossPoint;
        float distance = GJK::GetShortestDistanceToShape(c1->GetVertexes()[i], c2->GetVertexes(), crossPoint, minSideIndex);
        //�ŏ���
        if (i == 0) {
            minDistance = distance;
            contactPoint = c1->GetVertexes()[i];
        }
        //�ŒZ�Ȃ�
        else if (minDistance > distance) {
            minDistance = distance;
            contactPoint = c1->GetVertexes()[i];
        }
    }
    //c2�̓_��c1�̐}�`�̍ŒZ����
    for (int i = 0, len = (int)c1->GetVertexes().size(); i < len; i++) {
        int minSideIndex;
        Vector2 crossPoint;
        float distance = GJK::GetShortestDistanceToShape(c2->GetVertexes()[i], c1->GetVertexes(), crossPoint, minSideIndex);
        //�ŏ���
        if (i == 0) {
            minDistance = distance;
            contactPoint = c2->GetVertexes()[i];
        }
        //�ŒZ�Ȃ�
        else if (minDistance > distance) {
            minDistance = distance;
            contactPoint = c2->GetVertexes()[i];
        }
    }

    return contactPoint;
}

Vector2 EPA::GetContactPoint(CircleCollider* c1, VertexCollider* c2)
{
    //c1�̒��S�_��c2�̐}�`�̍ŒZ����
    int minSideIndex;
    Vector2 contactPoint;
    GJK::GetShortestDistanceToShape(c1->GetPosition(), c2->GetVertexes(), contactPoint, minSideIndex);
    //�ŒZ�̌�_���Փ˓_
    return contactPoint;
}

Vector2 EPA::GetContactPoint(CircleCollider* c1, CircleCollider* c2)
{
    //�~����~�̃x�N�g���̃T�|�[�g�ʑ����Փ˓_
    return GJK::Support(c1, c2->GetPosition() - c1->GetPosition());
}

