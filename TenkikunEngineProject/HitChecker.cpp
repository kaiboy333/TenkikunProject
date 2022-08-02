#include "HitChecker.h"

bool HitChecker::IsHit(Collider* c1, Collider* c2)
{
    auto& type1 = typeid(*c1);
    auto& type2 = typeid(*c2);

    auto& typeCC = typeid(CircleCollider);
    auto& typeBC = typeid(BoxCollider);

    //円と円の当たり判定
    if (type1 == typeCC && type2 == typeCC) {
        return IsHitCC(static_cast<CircleCollider*>(c1), static_cast<CircleCollider*>(c2));
    }
    //矩形と矩形の当たり判定
    else if (type1 == typeBC && type2 == typeBC) {
        return IsHitBB(static_cast<BoxCollider*>(c1), static_cast<BoxCollider*>(c2));
    }
    //円と矩形の当たり判定
    else if (type1 == typeCC && type2 == typeBC) {
        return IsHitCB(static_cast<CircleCollider*>(c1), static_cast<BoxCollider*>(c2));
    }
    else if (type1 == typeBC && type2 == typeCC) {
        return IsHitCB(static_cast<CircleCollider*>(c2), static_cast<BoxCollider*>(c1));
    }
    //どれにも当てはまらない場合
    else {
        //falseを返す
        return false;
    }
}

bool HitChecker::IsHitCC(CircleCollider* c1, CircleCollider* c2)
{
    float distance = Vector3::Distance(c1->GetPosition(), c2->GetPosition());

    return c1->radious + c2->radious >= distance;
}

bool HitChecker::IsHitBB(BoxCollider* c1, BoxCollider* c2)
{
    std::vector<Vector3> vertexes1 = c1->GetVertexes();
    std::vector<Vector3> vertexes2 = c2->GetVertexes();

    float roteZ1 = c1->gameobject->transform->rotation.r.z;
    for (Vector3& vertex1 : vertexes1) {
        //頂点を原点中心に-z度回転させる
        vertex1 = Matrix::GetMRoteZ(-roteZ1) * vertex1;
    }
    float roteZ2 = c2->gameobject->transform->rotation.r.z;
    for (Vector3& vertex2 : vertexes2) {
        //頂点を原点中心に-z度回転させる
        vertex2 = Matrix::GetMRoteZ(-roteZ2) * vertex2;
    }

    return vertexes1[0].x < vertexes2[2].x&& vertexes1[2].x > vertexes2[0].x && vertexes1[0].y < vertexes2[2].y&& vertexes1[2].y > vertexes2[0].y;
}

bool HitChecker::IsHitCB(CircleCollider* c1, BoxCollider* c2)
{
    //円の中心点を取得
    Vector3 circleCenter = c1->GetPosition();
    float roteZ1 = c1->gameobject->transform->rotation.r.z;
    //頂点を原点中心に-z度回転させる
    circleCenter = Matrix::GetMRoteZ(-roteZ1) * circleCenter;

    //矩形の頂点取得
    std::vector<Vector3> vertexes = c2->GetVertexes();
    float roteZ2 = c2->gameobject->transform->rotation.r.z;
    for (Vector3 vertex : vertexes) {
        //頂点を原点中心に-z度回転させる
        vertex = Matrix::GetMRoteZ(-roteZ2) * vertex;
    }

    //円の中心点から矩形への最短となる位置
    float px = MyMath::Clamp(circleCenter.x, vertexes[0].x, vertexes[2].x);
    float py = MyMath::Clamp(circleCenter.y, vertexes[0].y, vertexes[2].y);
    Vector3 nearPos = Vector3(px, py, 0);
    //教理をとる
    float distance = Vector3::Distance(circleCenter, nearPos);

    //距離が半径以下ならtrue
    return distance <= c1->radious;
}

