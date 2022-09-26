#include "GJK.h"

bool GJK::IsHit(Collider* c1, Collider* c2)
{
    //c1�̒��S��c2�̒��S�̍���C�ӂ̃x�N�g���Ƃ���(�~�R���t�X�L�[���łł����}�`�̒��S)
    Vector2 p0 = c1->GetPosition() - c2->GetPosition();
    //���ꂪ���_��������
    if (p0 == Vector2::Zero()) {
        //�Փ˂��Ă���
        return true;
    }
    //���S���猴�_�Ɍ������x�N�g����d1�Ƃ���
    Vector2 d1 = -p0;
    //d1�����ł̃T�|�[�g�ʑ������߂�(p1)
    Vector3 p1 = Support(c1, c2, d1);
    //d1��p1�̓��ς����Ȃ�
    if (Vector2::Inner(d1, p1) < 0) {
        //�Փ˂��Ă��Ȃ�
        return false;
    }

    Vector2 d2 = -p1;
    Vector2 p2 = Support(c1, c2, d2);

    Vector2 crossPoint;
    Vector2::GetShortestDistance(p1, p2, Vector2::Zero(), crossPoint);
    Vector2 d3 = -crossPoint;
    Vector2 p3 = Support(c1, c2, d3);
}

Vector2 GJK::Support(Collider* c1, Collider* c2, Vector2 d)
{
    return Support(c1, d) - Support(c2, d);
}

Vector2 GJK::Support(Collider* c, Vector2 d)
{
    auto& type = typeid(*c);

    auto& typeVC = typeid(VertexCollider);
    auto& typeCC = typeid(CircleCollider);

    if (type == typeVC) {
        return Support(static_cast<VertexCollider*>(c), d);
    }
    else if (type == typeCC) {
        return Support(static_cast<CircleCollider*>(c), d);
    }

    return Vector2();
}

Vector2 GJK::Support(VertexCollider* c, Vector2 d)
{
    //�ő����
    float maxDot = 0.0f;
    //�ő���ς̎��̒��_���W
    Vector2 supportVec;
    for (Vector2 vertex : c->GetVertexes()) {
        float dot = Vector2::Inner(vertex, d);
        //���ς����܂łōő�Ȃ�
        if (dot > maxDot) {
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

    for (int i = 0, len = vertexes.size(); i < len; i++) {
        Vector2 vert1 = vertexes[i % len];
        Vector2 vert2 = vertexes[(i + 1) % len];

        //�}�`�̈�ӂɑ΂��ē_���O���ɂ���Ȃ�
        if (Vector2::Cross(point - vert1, vert2 - vert1) * dir > 0) {
            //���ɂȂ�
            return false;
        }
    }

    //���ׂĂ̕ӂ̓����ɂ���Ȃ�true
    return true;
}
