#include "GJK.h"
#include "BoxCollider.h"
#include "Debug.h"

bool GJK::IsHit(Collider* c1, Collider* c2)
{
    Vector2 v = c1->GetPosition() - c2->GetPosition();
    if (v == Vector2::Zero()) {
        return true;
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
                    return false;
                }
                //vertexes[1] - vertexes[0]�ɐ����ȃx�N�g�����擾
                v = Matrix::GetMRoteZ(Vector2::Zero(), 90) * (vertexes[1] - vertexes[0]);
                //vertexes[0]�Ƃ̓��ς�����������������t�ɂ���
                if (Vector2::Inner(v, vertexes[0]) < 0) {
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
                    return false;
                }
                //���_��3�_�ō�����O�p�`�Ɋ܂܂�Ă���Ȃ�
                if (IsPointInTriangle(Vector2::Zero(), vertexes)) {
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
                    for (int j = 0; j < 30; j++) {
                        //���_����ʕ�ւ̍ŒZ���������߂�
                        GetShortestDistanceToShape(Vector2::Zero(), vertexes, crossPoint, minSideIndex);
                        //�ŒZ�����ƂȂ�ӂɐ����ȃx�N�g�����擾(dir���|���Đ}�`�̕ӕ����Ɍ�����)
                        v = Matrix::GetMRoteZ(Vector2::Zero(), 90) * (vertexes[(minSideIndex + 1) % (int)vertexes.size()] - vertexes[minSideIndex]) * (float)dir;
                        //�T�|�[�g�ʑ������߂�
                        Vector2 supportVec = Support(c1, c2, v);
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

                    //�߂荞�ݐ[�x��
                    Vector2 sinkVec = crossPoint;
                    return true;
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

    for (int i = 0, len = (int)vertexes.size(); i < len; i++) {
        Vector2 vertex = vertexes[i];
        float dot = Vector2::Inner(vertex, d);
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

float GJK::GetShortestDistanceToShape(Vector2 targetPoint, std::vector<Vector2> &vertexes, Vector2& crossPoint, int& minSideIndex)
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

//Vector2 GJK::GetFirstP(Collider* c)
//{
//    auto& type = typeid(*c);
//
//    auto& typeBC = typeid(BoxCollider);
//    auto& typeCC = typeid(CircleCollider);
//
//    if (type == typeBC) {
//        return GetFirstP(static_cast<VertexCollider*>(c));
//    }
//    else if (type == typeCC) {
//        return GetFirstP(static_cast<CircleCollider*>(c));
//    }
//
//    return Vector2();
//}

//Vector2 GJK::GetFirstP(VertexCollider* c)
//{
//    //�ŏ��̒��_��Ԃ�
//    return c->GetVertexes()[0];
//}
//
//Vector2 GJK::GetFirstP(CircleCollider* c)
//{
//    return c->GetPosition() + Vector2::Up() * c->GetActualRadious();
//}
