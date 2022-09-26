#include "GJK.h"

bool GJK::IsHit(Collider* c1, Collider* c2)
{
    //c1の中心とc2の中心の差を任意のベクトルとする(ミコンフスキー差でできた図形の中心)
    Vector2 p0 = c1->GetPosition() - c2->GetPosition();
    //それが原点だったら
    if (p0 == Vector2::Zero()) {
        //衝突している
        return true;
    }
    //中心から原点に向かうベクトルをd1とする
    Vector2 d1 = -p0;
    //d1方向でのサポート写像を求める(p1)
    Vector3 p1 = Support(c1, c2, d1);
    //d1とp1の内積が負なら
    if (Vector2::Inner(d1, p1) < 0) {
        //衝突していない
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
    //最大内積
    float maxDot = 0.0f;
    //最大内積の時の頂点座標
    Vector2 supportVec;
    for (Vector2 vertex : c->GetVertexes()) {
        float dot = Vector2::Inner(vertex, d);
        //内積が今までで最大なら
        if (dot > maxDot) {
            //更新
            maxDot = dot;
            //その時の頂点を記憶
            supportVec = vertex;
        }
    }

    return supportVec;
}

Vector2 GJK::Support(CircleCollider* c, Vector2 d)
{
    //中心の座標を取得
    Vector2 centerPos = c->GetPosition();
    //中心からdの方向に伸ばした時の円との交点がサポート写像
    Vector2 supportVec = centerPos + d.GetNormalized() * c->GetActualRadious();

    return supportVec;
}

bool GJK::IsPointInTriangle(Vector2 point, std::vector<Vector2> vertexes)
{
    //頂点が3つではないなら終わり
    if (vertexes.size() != 3) {
        return false;
    }

    //反時計回り
    int dir = 1;
    //時計回りなら
    if (Vector2::Cross(vertexes[1] - vertexes[0], vertexes[2] - vertexes[0]) > 0) {
        //正負反転
        dir = -1;
    }

    for (int i = 0, len = vertexes.size(); i < len; i++) {
        Vector2 vert1 = vertexes[i % len];
        Vector2 vert2 = vertexes[(i + 1) % len];

        //図形の一辺に対して点が外側にあるなら
        if (Vector2::Cross(point - vert1, vert2 - vert1) * dir > 0) {
            //中にない
            return false;
        }
    }

    //すべての辺の内側にあるならtrue
    return true;
}
