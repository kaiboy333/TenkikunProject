#include "GJK.h"
#include "BoxCollider.h"
#include "Debug.h"

bool GJK::IsHit(Collider* c1, Collider* c2)
{
    const Vector2 originPos = Vector2::Zero();
    Vector2 v = c1->GetPosition() - c2->GetPosition();
    //図形の中心が原点だったら
    if (v == originPos) {
        return true;
    }

    std::vector<Vector2> vertexes;
    for (int i = 0; i < 10; i++) {
        //サポート写像を求める
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
                //垂線ではないのなら
                if (crossPoint == vertexes[0] || crossPoint == vertexes[1]) {
                    return false;
                }
                v = -crossPoint;
                break;
            case 3:
                if (vertexes[2] == vertexes[0] || vertexes[2] == vertexes[1]) {
                    return false;
                }
                //原点が3点で作った三角形に含まれているなら
                if (IsPointInTriangle(originPos, vertexes)) {
                    return true;
                }
                //原点から三角形への最短距離を求め、遠い点を削除する(結果二点になる)
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
//        //サポート写像を求める
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
//            //原点が3点で作った三角形に含まれているなら
//            if (IsPointInTriangle(originPos, vertexes)) {
//                Debug::Log("Hit");
//                return true;
//            }
//            //原点から三角形への最短距離を求め、遠い点を削除する(結果二点になる)
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
    //最大内積
    float maxDot = 0;
    //最大内積の時の頂点座標
    Vector2 supportVec;

    for (int i = 0, len = (int)vertexes.size(); i < len; i++) {
        Vector2 vertex = vertexes[i];
        float dot = Vector2::Inner(vertex, d);
        if (i == 0) {
            maxDot = dot;
            supportVec = vertex;
        }
        //内積が今までで最大なら
        else if (dot > maxDot) {
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

    for (int i = 0, len = (int)vertexes.size(); i < len; i++) {
        Vector2 vert1 = vertexes[i % len];
        Vector2 vert2 = vertexes[(i + 1) % len];

        //図形の一辺に対して点が外側にあるなら
        if (Vector2::Cross(vert2 - vert1, point - vert1) * dir > 0) {
            //中にない
            return false;
        }
    }

    //すべての辺の内側にあるならtrue
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
        //最初なら
        if (i == 0) {
            minDistance = distance;
            crossPoint = crossPoint2;
        }
        //最短を見つけたら
        else if (minDistance > distance) {
            minDistance = distance;
            crossPoint = crossPoint2;
            removeIndex = (i + 2) % len;
        }
    }

    //原点から一番遠い点を削除
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
    //最初の頂点を返す
    return c->GetVertexes()[0];
}

Vector2 GJK::GetFirstP(CircleCollider* c)
{
    return c->GetPosition() + Vector2::Up() * c->GetActualRadious();
}
