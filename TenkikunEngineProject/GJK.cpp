#include "GJK.h"
#include "BoxCollider.h"
#include "Debug.h"
#include "Collision.h"
#include "RigidBody.h"
#include "Time.h"

SupportInfo* GJK::IsHit(std::vector<Collider*>& colliders, int colliderID1, int colliderID2)
{
    auto c1 = colliders[colliderID1];
    auto c2 = colliders[colliderID2];

    Vector2 v = c1->GetPosition() - c2->GetPosition();
    if (v == Vector2::Zero()) {
        //return true;
        v = Vector2::One();
    }

    std::vector<Vector2> vertexes;
    vertexes.reserve(4);
    for (int i = 0; i < 30; i++) {

        //サポート写像を求める
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
                //vertexes[1] - vertexes[0]に垂直なベクトルを取得
                v = Matrix::GetMRoteZ(Vector2::Zero(), 90) * (vertexes[1] - vertexes[0]);
                //vertexes[0]との内積が負だったら方向を逆にする
                if (Vector2::Dot(v, vertexes[0]) < 0) {
                    v = -v;
                }
                break;
            case 3:
                //新しくできた頂点が他二点と被るなら(収束したなら)
                if (vertexes[2] == vertexes[0] || vertexes[2] == vertexes[1]) {
                    return nullptr;
                }
                //原点が3点で作った三角形に含まれているなら
                if (IsPointInTriangle(Vector2::Zero(), vertexes)) {
                    auto supportInfo = new SupportInfo();
                    supportInfo->supports = vertexes;
                    supportInfo->colliderID1 = colliderID1;
                    supportInfo->colliderID2 = colliderID2;
                    return supportInfo;
                }

                //原点から三角形への最短距離を求める
                GetShortestDistanceToShape(Vector2::Zero(), vertexes, crossPoint, minSideIndex);
                //原点から一番遠い点を削除(結果二点になる)
                vertexes.erase(vertexes.begin() + ((minSideIndex - 1 + (int)vertexes.size()) % (int)vertexes.size()));
                //次の方向を求める
                v = -crossPoint;
                break;
        }
    }

    return nullptr;
}

Vector2 GJK::Support(Collider* c1, Collider* c2, const Vector2& v)
{
    return Support(c1, v) - Support(c2, -v);
}

Vector2 GJK::Support(Collider* c, const Vector2& d)
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

Vector2 GJK::Support(const VertexCollider* c, const Vector2& d)
{
    //float times[2] = {};

    //times[0] = Time::GetTime();

    auto vertexes = c->GetVertexes();
    //最大内積
    float maxDot;
    //最大内積の時の頂点座標
    Vector2 supportVec;
    ////最大内積の時の長さ(距離)
    //float maxDistance;

    for (int i = 0, len = (int)vertexes.size(); i < len; i++) {
        Vector2& vertex = vertexes[i];
        float dot = Vector2::Dot(vertex, d);
        //float distance = vertex.GetMagnitude();
        if (i == 0) {
            maxDot = dot;
            supportVec = vertex;
            //maxDistance = distance;
        }
        //内積が今までで最大なら
        else if (dot > maxDot) {
            //更新
            maxDot = dot;
            //その時の頂点を記憶
            supportVec = vertex;
            ////長さを記憶
            //maxDistance = distance;
        }
        ////内積が同じ最大なら
        //else if (dot == maxDot) {
        //    //今回のほうが長いなら更新
        //    if (maxDistance < distance) {
        //        //その時の頂点を記憶
        //        supportVec = vertex;
        //        //長さを記憶
        //        maxDistance = distance;
        //    }
        //}
    }

    //times[1] = Time::GetTime();

    //Debug::Log("supportVert:" + std::to_string(times[1] - times[0]));

    return supportVec;
}

Vector2 GJK::Support(const CircleCollider* c, const Vector2& d)
{
    //float times[2] = {};

    //times[0] = Time::GetTime();

    //中心の座標を取得
    Vector2 centerPos = c->GetPosition();
    //中心からdの方向に伸ばした時の円との交点がサポート写像
    Vector2 supportVec = centerPos + d.GetNormalized() * c->GetActualRadious();

    //times[1] = Time::GetTime();

    //Debug::Log("supportCircle:" + std::to_string(times[1] - times[0]));

    return supportVec;
}

bool GJK::IsPointInTriangle(const Vector2& point, std::vector<Vector2>& vertexes)
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
        Vector2& vert1 = vertexes[i % len];
        Vector2& vert2 = vertexes[(i + 1) % len];

        //図形の一辺に対して点が外側にあるなら
        if (Vector2::Cross(vert2 - vert1, point - vert1) * dir > 0) {
            //中にない
            return false;
        }
    }

    //すべての辺の内側にあるならtrue
    return true;
}

float GJK::GetShortestDistanceToShape(const Vector2& targetPoint, const std::vector<Vector2>& vertexes, Vector2& crossPoint, int& minSideIndex)
{
    float minDistance = 0;

    for (int i = 0, len = (int)vertexes.size(); i < len; i++) {
        const Vector2& vert1 = vertexes[i % len];
        const Vector2& vert2 = vertexes[(i + 1) % len];

        Vector2 crossPoint2;
        float distance = Vector2::GetMinDistance(vert1, vert2, targetPoint, crossPoint2);
        //最初なら
        if (i == 0) {
            minDistance = distance;
            crossPoint = crossPoint2;
            minSideIndex = i;
        }
        //最短を見つけたら
        else if (minDistance > distance) {
            minDistance = distance;
            crossPoint = crossPoint2;
            minSideIndex = i;
        }
    }

    return minDistance;
}