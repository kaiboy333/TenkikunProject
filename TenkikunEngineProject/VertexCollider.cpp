#include "VertexCollider.h"

VertexCollider::VertexCollider(GameObject* gameobject) : Collider(gameobject)
{
}

void VertexCollider::Draw()
{
    auto vertexes = GetVertexes();
    GameWindow* gameWindow = WindowManager::gameWindow;

    for (int i = 0, length= vertexes.size(); i < length; i++) {
        Vector3 drawPos1 = GetDrawPos(vertexes[i % length]);
        Vector3 drawPos2 = GetDrawPos(vertexes[(i + 1) % length]);

        //辺を描画
        DrawLineAA(drawPos1.x, drawPos1.y, drawPos2.x, drawPos2.y, color);
    }
}

std::vector<Vector3> VertexCollider::GetVertexes(std::vector<Vector3> toVertexVecs)
{
    std::vector<Vector3> vertexes;

    Vector3 position = GetPosition();

    for (Vector3 toVertexVec : toVertexVecs) {
        //頂点を取得
        Vector3 vertex = position + toVertexVec;
        //z軸回転の値分頂点を回転(移動)
        vertex = Matrix::GetMRoteZ(position, gameobject->transform->rotation.r.z) * vertex;
        //変換後の頂点をリストに追加
        vertexes.push_back(vertex);
    }

    return vertexes;
}
