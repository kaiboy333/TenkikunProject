#include "VertexCollider.h"

VertexCollider::VertexCollider(GameObject* gameobject) : Collider(gameobject)
{
}

void VertexCollider::Draw()
{
    if (isHit) {
        downColor = GetColor(255, 0, 0);
    }
    else {
        downColor = GetColor(0, 255, 0);
    }

    auto vertexes = GetVertexes();
    GameWindow* gameWindow = WindowManager::gameWindow;

    for (int i = 0, length= (int)vertexes.size(); i < length; i++) {
        Vector3 drawPos1 = GetDrawPos(vertexes[i % length]);
        Vector3 drawPos2 = GetDrawPos(vertexes[(i + 1) % length]);

        //�ӂ�`��
        DrawLineAA(drawPos1.x, drawPos1.y, drawPos2.x, drawPos2.y, downColor);
    }

    //��_�̕`��
    Collider::Draw();
}

Rect VertexCollider::GetBoundingBox() const
{
    Vector3 minPos;
    Vector3 maxPos;

    auto vertexes = GetVertexes();
    for (int i = 0, len = (int)vertexes.size(); i < len; i++) {
        auto& vertex = vertexes[i];

        if (i == 0) {
            minPos = vertex;
            maxPos = vertex;
        }
        else {
            minPos.x = std::min<float>(vertex.x, minPos.x);
            minPos.y = std::min<float>(vertex.y, minPos.y);

            maxPos.x = std::max<float>(vertex.x, maxPos.x);
            maxPos.y = std::max<float>(vertex.y, maxPos.y);
        }
    }

    return Rect(minPos.x, minPos.y, maxPos.x - minPos.x, maxPos.y - minPos.y);
}

std::vector<Vector2> VertexCollider::GetVertexes(std::vector<Vector2> toVertexVecs) const
{
    std::vector<Vector2> vertexes;

    Vector3 position = GetPosition();

    for (Vector2 toVertexVec : toVertexVecs) {
        //���_���擾
        Vector2 vertex = position + toVertexVec;
        //z����]�̒l�����_����](�ړ�)
        vertex = Matrix::GetMRoteZ(position, gameobject->transform->rotation.r.z) * vertex;
        //�ϊ���̒��_�����X�g�ɒǉ�
        vertexes.push_back(vertex);
    }

    return vertexes;
}
