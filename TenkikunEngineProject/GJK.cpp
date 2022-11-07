#include "GJK.h"
#include "BoxCollider.h"
#include "Debug.h"
#include "Collision.h"
#include "RigidBody.h"

SupportInfo* GJK::IsHit(std::vector<Collider*> colliders, int colliderID1, int colliderID2)
{
    auto c1 = colliders[colliderID1];
    auto c2 = colliders[colliderID2];

    Vector2 v = c1->GetPosition() - c2->GetPosition();
    if (v == Vector2::Zero()) {
        //return true;
        v = Vector2::One();
    }

    std::vector<Vector2> vertexes;
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
                //Vector2::GetMinDistance(vertexes[0], vertexes[1], originPos, crossPoint);
                ////�����ł͂Ȃ��̂Ȃ�
                //if (crossPoint == vertexes[0] || crossPoint == vertexes[1]) {
                //    return false;
                //}
                //v = -crossPoint;
                break;
            case 3:
                //�V�����ł������_������_�Ɣ��Ȃ�(���������Ȃ�)
                if (vertexes[2] == vertexes[0] || vertexes[2] == vertexes[1]) {
                    return nullptr;
                }
                //���_��3�_�ō�����O�p�`�Ɋ܂܂�Ă���Ȃ�
                if (IsPointInTriangle(Vector2::Zero(), vertexes)) {
                    return new SupportInfo(vertexes, colliderID1, colliderID2);
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

Vector2 GJK::Support(Collider* c1, Collider* c2, Vector2 v)
{
    return Support(c1, v) - Support(c2, -v);
}

Vector2 GJK::Support(Collider* c, Vector2 d)
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

Vector2 GJK::Support(VertexCollider* c, Vector2 d)
{
    std::vector<Vector2> vertexes = c->GetVertexes();
    //�ő����
    float maxDot = 0;
    //�ő���ς̎��̒��_���W
    Vector2 supportVec;
    //�ő���ς̎��̒���(����)
    float maxDistance = 0;
    ////�T�|�[�g�x�N�g�����X�g
    //std::vector<Vector2> supportVecs;

    for (int i = 0, len = (int)vertexes.size(); i < len; i++) {
        Vector2 vertex = vertexes[i];
        float dot = Vector2::Dot(vertex, d);
        float distance = vertex.GetMagnitude();
        if (i == 0) {
            maxDot = dot;
            supportVec = vertex;
            maxDistance = distance;
        }
        //���ς����܂łōő�Ȃ�
        else if (dot > maxDot) {
            //�X�V
            maxDot = dot;
            //���̎��̒��_���L��
            supportVec = vertex;
            //supportVecs.push_back(vertex);
            //�������L��
            maxDistance = distance;
        }
        //���ς������ő�Ȃ�
        else if (dot == maxDot) {
            //����̂ق��������Ȃ�X�V
            if (maxDistance < distance) {
                //���̎��̒��_���L��
                supportVec = vertex;
                //�������L��
                maxDistance = distance;
            }
            //supportVecs.push_back(vertex);
        }
    }

    ////����鎞��
    //if (supportVecs.size() == 2) {
    //    //�^�񒆂��Ƃ�
    //    return supportVecs[0] + ((supportVecs[1] - supportVecs[0]) / 2);
    //}
    //else {
    //    return supportVecs[0];
    //}

    return supportVec;
}

Vector2 GJK::Support(CircleCollider* c, Vector2 d)
{
    //���S�̍��W���擾
    Vector2 centerPos = c->GetPosition();
    //���S����d�̕����ɐL�΂������̉~�Ƃ̌�_���T�|�[�g�ʑ�
    Vector2 supportVec = centerPos + d.GetNormalized() * c->GetActualRadious();

    return supportVec;
}

bool GJK::IsPointInTriangle(Vector2 point, std::vector<Vector2> vertexes)
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
        Vector2 vert1 = vertexes[i % len];
        Vector2 vert2 = vertexes[(i + 1) % len];

        //�}�`�̈�ӂɑ΂��ē_���O���ɂ���Ȃ�
        if (Vector2::Cross(vert2 - vert1, point - vert1) * dir > 0) {
            //���ɂȂ�
            return false;
        }
    }

    //���ׂĂ̕ӂ̓����ɂ���Ȃ�true
    return true;
}

float GJK::GetShortestDistanceToShape(Vector2 targetPoint, std::vector<Vector2> vertexes, Vector2& crossPoint, int& minSideIndex)
{
    float minDistance = 0;
    for (int i = 0, len = (int)vertexes.size(); i < len; i++) {
        Vector2 vert1 = vertexes[i % len];
        Vector2 vert2 = vertexes[(i + 1) % len];

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

//void GJK::CollisionResponce(ContactPoint* contactPoint)
//{
//    Collider* c1 = contactPoint->thisCollider;
//    Collider* c2 = contactPoint->otherCollider;
//    RigidBody* rb1 = c1->gameobject->GetComponent<RigidBody>();
//    RigidBody* rb2 = c2->gameobject->GetComponent<RigidBody>();
//
//    Vector3 cp = contactPoint->point;
//    Vector3 dp = contactPoint->depthPoint;
//
//    Vector3 r1 = cp - c1->GetPosition();
//    Vector3 r2 = cp - c2->GetPosition();
//
//    //��������Փ˖@����3�����x�N�g���ɂ���
//    Vector3 normal = dp.GetNormalized();
//
//    Vector3 velocityA = rb1 ? rb1->velocity : Vector3::Zero() + Vector3::Cross((rb1 ? rb1->angularVelocity : Vector3::Zero()) * MyMath::DEG_TO_RAD, r1);
//    Vector3 velocityB = rb2 ? rb2->velocity : Vector3::Zero() + Vector3::Cross((rb2 ? rb2->angularVelocity : Vector3::Zero()) * MyMath::DEG_TO_RAD, r2);
//
//    //2�̕��̂̑��Α��x�����߂�iV1 - V2�j
//    Vector3 relativeVelocity = velocityA - velocityB;
//
//    //�ڐ��x�N�g�������߂�
//    Vector3 tangent1 = Matrix::GetMRoteZ(90) * normal;
//
//    //�����W��
//    float restitution = 1.0;
//
//    // �Փ˖@�������̌v�Z
//    {
//        Vector3 axis = normal;
//
//        //rhs = Right Hand Side = �E��
//        float jacDiagInv = 1.0 / (
//            ((rb1 ? 1.0 / rb1->mass : 0) + (rb1 ? 1.0 / rb2->mass : 0))
//            + Vector3::Dot(axis, Vector3::Cross(Vector3::Cross(r1, axis) * solverBodyA.inertiaInv, r1)
//            + Vector3::Dot(axis, Vector3::Cross(Vector3::Cross(r2, axis) * solverBodyB.inertiaInv, r2)
//            );
//        float rhs = -((1 + restitution) * Vector3::Dot(relativeVelocity, axis));
//        rhs -= (bias * std::max<float>(0.0f, contact.distance + slop)) / timeStep; // position error
//        rhs *= jacDiagInv;
//        Constraint constraint1 = Constraint(jacDiagInv, rhs, -FLT_MAX, 0.0f, axis);
//        contactPoint->constraints.push_back(constraint1);
//    }
//
//    //Tangent1
//    {
//        var axis = tangent1;
//        contact.constraints[1].jacDiagInv = 1.0 / (
//            (solverBodyA.massInv + solverBodyB.massInv)
//            + vec3.dot(axis, vec3.cross(vec3.multiplyScalar(vec3.cross(r1, axis), solverBodyA.inertiaInv), r1))
//            + vec3.dot(axis, vec3.cross(vec3.multiplyScalar(vec3.cross(r2, axis), solverBodyB.inertiaInv), r2))
//            );
//        contact.constraints[1].rhs = -vec3.dot(relativeVelocity, axis);
//        contact.constraints[1].rhs *= contact.constraints[1].jacDiagInv;
//        contact.constraints[1].lowerLimit = 0.0;
//        contact.constraints[1].upperLimit = 0.0;
//        contact.constraints[1].axis = axis;
//    }
//
//    //Warm starting
//    {
//        //���Ƃ�
//    }
//}