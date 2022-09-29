#include "VertexCollider.h"

VertexCollider::VertexCollider(GameObject* gameobject) : Collider(gameobject)
{
}

void VertexCollider::Draw()
{
    if (isHit) {
        color = GetColor(255, 0, 0);
    }
    else {
        color = GetColor(0, 255, 0);
    }

    auto vertexes = GetVertexes();
    GameWindow* gameWindow = WindowManager::gameWindow;

    for (int i = 0, length= (int)vertexes.size(); i < length; i++) {
        Vector3 drawPos1 = GetDrawPos(vertexes[i % length]);
        Vector3 drawPos2 = GetDrawPos(vertexes[(i + 1) % length]);

        //�ӂ�`��
        DrawLineAA(drawPos1.x, drawPos1.y, drawPos2.x, drawPos2.y, color);
    }

    //��_�̕`��
    Collider::Draw();
}

std::vector<Vector2> VertexCollider::GetVertexes(std::vector<Vector2> toVertexVecs)
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
