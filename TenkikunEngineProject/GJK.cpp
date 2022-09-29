#include "GJK.h"
#include "BoxCollider.h"
#include "Debug.h"

bool GJK::IsHit(Collider* c1, Collider* c2)
{
    const Vector2 originPos = Vector2::Zero();
    Vector2 v = c1->GetPosition() - c2->GetPosition();
    //�}�`�̒��S�����_��������
    if (v == originPos) {
        return true;
    }

    std::vector<Vector2> vertexes;
    for (int i = 0; i < 10; i++) {
        //�T�|�[�g�ʑ������߂�
        vertexes.push_back(Support(c1, c2, v));

        Vector2 crossPoint;
        switch ((int)vertexes.size()) {
            case 1:
                v = originPos - vertexes[0];
                break;
            case 2:
                if (vertexes[0] == vertexes[1]) {
                    return false;
                }
                Vector2::GetMinDistance(vertexes[0], vertexes[1], originPos, crossPoint);
                //�����ł͂Ȃ��̂Ȃ�
                if (crossPoint == vertexes[0] || crossPoint == vertexes[1]) {
                    return false;
                }
                v = -crossPoint;
                break;
            case 3:
                if (vertexes[2] == vertexes[0] || vertexes[2] == vertexes[1]) {
                    return false;
                }
                //���_��3�_�ō�����O�p�`�Ɋ܂܂�Ă���Ȃ�
                if (IsPointInTriangle(originPos, vertexes)) {
                    return true;
                }
                //���_����O�p�`�ւ̍ŒZ���������߁A�����_���폜����(���ʓ�_�ɂȂ�)
                v = -GetShortestDistanceVecToTriangle(originPos, vertexes);
                break;
        }
    }

    return false;
}

//bool GJK::IsHit2(Collider* c1)
//{
//    const Vector2 originPos = Vector2::Zero();
//    Vector2 v = Vector2::Right();
//    if (v == originPos) {
//        return true;
//    }
//
//    std::vector<Vector2> vertexes;
//    for (int i = 0; i < 10; i++) {
//        //c1->Draw();
//        Debug::DrawLine(Vector2::Zero(), v, GetColor(100, 0, 0));
//        //�T�|�[�g�ʑ������߂�
//        vertexes.push_back(Support(c1, v));
//        for (Vector2 vertex : vertexes) {
//            Debug::DrawPoint(vertex, GetColor(0, 0, 255));
//        }
//
//        Vector2 crossPoint;
//        switch ((int)vertexes.size()) {
//        case 1:
//            v = originPos - vertexes[0];
//            break;
//        case 2:
//            if (vertexes[0] == vertexes[1]) {
//                return false;
//            }
//            Vector2::GetMinDistance(vertexes[0], vertexes[1], originPos, crossPoint);
//            v = -crossPoint;
//            break;
//        case 3:
//            for (int i = 0, len = (int)vertexes.size(); i < len; i++) {
//                Vector2 vertex1 = vertexes[i];
//                Vector2 vertex2 = vertexes[(i + 1) % len];
//                Debug::DrawLine(vertex1, vertex2, GetColor(0, 255, 0));
//            }
//            if (vertexes[2] == vertexes[0] || vertexes[2] == vertexes[1]) {
//                return false;
//            }
//            //���_��3�_�ō�����O�p�`�Ɋ܂܂�Ă���Ȃ�
//            if (IsPointInTriangle(originPos, vertexes)) {
//                Debug::Log("Hit");
//                return true;
//            }
//            //���_����O�p�`�ւ̍ŒZ���������߁A�����_���폜����(���ʓ�_�ɂȂ�)
//            v = -GetShortestDistanceVecToTriangle(originPos, vertexes);
//            break;
//        }
//
//        Debug::DrawPoint(Vector2::Zero(), GetColor(255, 0, 0));
//        ScreenFlip();
//    }
//
//    return false;
//}

Vector2 GJK::Support(Collider* c1, Collider* c2, Vector2 d)
{
    return Support(c1, d) - Support(c2, -d);
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

    for (int i = 0, len = (int)vertexes.size(); i < len; i++) {
        Vector2 vertex = vertexes[i];
        float dot = Vector2::Inner(vertex, d);
        if (i == 0) {
            maxDot = dot;
            supportVec = vertex;
        }
        //���ς����܂łōő�Ȃ�
        else if (dot > maxDot) {
            //�X�V
            maxDot = dot;
            //���̎��̒��_���L��
            supportVec = vertex;
        }
    }

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

Vector2 GJK::GetShortestDistanceVecToTriangle(Vector2 targetPoint, std::vector<Vector2> &vertexes)
{
    float minDistance = 0;
    int removeIndex = 0;
    Vector2 crossPoint;
    for (int i = 0, len = (int)vertexes.size(); i < len; i++) {
        Vector2 vert1 = vertexes[i % len];
        Vector2 vert2 = vertexes[(i + 1) % len];

        Vector2 crossPoint2;
        float distance = Vector2::GetMinDistance(vert1, vert2, targetPoint, crossPoint2);
        //�ŏ��Ȃ�
        if (i == 0) {
            minDistance = distance;
            crossPoint = crossPoint2;
        }
        //�ŒZ����������
        else if (minDistance > distance) {
            minDistance = distance;
            crossPoint = crossPoint2;
            removeIndex = (i + 2) % len;
        }
    }

    //���_�����ԉ����_���폜
    vertexes.erase(vertexes.begin() + removeIndex);
    return crossPoint;
}

Vector2 GJK::GetFirstP(Collider* c)
{
    auto& type = typeid(*c);

    auto& typeBC = typeid(BoxCollider);
    auto& typeCC = typeid(CircleCollider);

    if (type == typeBC) {
        return GetFirstP(static_cast<VertexCollider*>(c));
    }
    else if (type == typeCC) {
        return GetFirstP(static_cast<CircleCollider*>(c));
    }

    return Vector2();
}

Vector2 GJK::GetFirstP(VertexCollider* c)
{
    //�ŏ��̒��_��Ԃ�
    return c->GetVertexes()[0];
}

Vector2 GJK::GetFirstP(CircleCollider* c)
{
    return c->GetPosition() + Vector2::Up() * c->GetActualRadious();
}
