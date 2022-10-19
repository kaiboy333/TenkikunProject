#include "EPA.h"
#include "RigidBody.h"
#include "BoxCollider.h"

HitInfo* EPA::GetHitInfo(SupportInfo* supportInfo)
{
    auto& vertexes = supportInfo->supports;
    auto c1 = supportInfo->c1;
    auto c2 = supportInfo->c2;

    //反時計回り
    int dir = 1;
    //時計回りなら
    if (Vector2::Cross(vertexes[1] - vertexes[0], vertexes[2] - vertexes[0]) > 0) {
        //正負反転
        dir = -1;
    }

    //許せる誤差
    float okDistance = 0.1f;
    Vector2 beforeSupportVec = vertexes[2];
    Vector2 crossPoint;
    int minSideIndex;
    Vector2 v;

    for (int j = 0; j < 30; j++) {
        //原点から凸包への最短距離を求める
        GJK::GetShortestDistanceToShape(Vector2::Zero(), vertexes, crossPoint, minSideIndex);
        //最短距離となる辺に垂直なベクトルを取得(dirを掛けて図形の辺方向に向ける)
        v = Matrix::GetMRoteZ(Vector2::Zero(), 90) * (vertexes[(minSideIndex + 1) % (int)vertexes.size()] - vertexes[minSideIndex]) * (float)dir;
        //サポート写像を求める
        Vector2 supportVec = GJK::Support(c1, c2, v);
        //前回のサポート写像と今回のサポート写像の距離が一定以下なら
        if (Vector2::Distance(beforeSupportVec, supportVec) <= okDistance) {
            //終わり(それがめり込み深度)
            break;
        }
        //今回のを記憶
        beforeSupportVec = supportVec;
        //サポート写像を追加(最短距離となる辺の番号+1の頂点に)
        vertexes.insert(vertexes.begin() + ((minSideIndex + 1) % (int)vertexes.size()), supportVec);
    }

    //めり込み深度(少し長さを伸ばす)
    Vector2 sinkVec = crossPoint * 1.001f;

    RigidBody* rb1 = c1->gameobject->GetComponent<RigidBody>();
    RigidBody* rb2 = c2->gameobject->GetComponent<RigidBody>();

    //どちらかが剛体なら
    if (rb1 || rb2) {
        float mass1 = rb1 ? rb1->mass : 0;
        float mass2 = rb2 ? rb2->mass : 0;

        //お互いがぶつからないように移動させる
        Vector2 moveVec1 = Vector2(), moveVec2 = Vector2();
        if (rb1 && rb2) {
            moveVec1 = -sinkVec * (mass2 / (mass1 + mass2));
            moveVec2 = sinkVec * (mass1 / (mass1 + mass2));
        }
        else if (rb1) {
            moveVec1 = -sinkVec;
        }
        else if (rb2) {
            moveVec2 = sinkVec;
        }
        c1->gameobject->transform->position += moveVec1;
        c2->gameobject->transform->position += moveVec2;

        //位置を戻す
        c1->gameobject->transform->position -= moveVec1;
        c2->gameobject->transform->position -= moveVec2;

        return new HitInfo(c1, c2, crossPoint, GetContactPoint(c1, c2));
    }

    return nullptr;
}

Vector2 EPA::GetContactPoint(Collider* c1, Collider* c2)
{
    auto& type1 = typeid(*c1);
    auto& type2 = typeid(*c2);

    auto& typeCC = typeid(CircleCollider);
    auto& typeBC = typeid(BoxCollider);

    if (true) {
        //円と円の衝突点
        if (type1 == typeCC && type2 == typeCC) {
            return GetContactPoint(static_cast<CircleCollider*>(c1), static_cast<CircleCollider*>(c2));
        }
        //矩形と矩形の衝突点
        if (type1 == typeBC && type2 == typeBC) {
            return GetContactPoint(static_cast<BoxCollider*>(c1), static_cast<BoxCollider*>(c2));
        }
        //円と矩形の衝突点
        else if (type1 == typeCC && type2 == typeBC) {
            return GetContactPoint(static_cast<CircleCollider*>(c1), static_cast<BoxCollider*>(c2));
        }
        else if (type1 == typeBC && type2 == typeCC) {
            return GetContactPoint(static_cast<CircleCollider*>(c2), static_cast<BoxCollider*>(c1));
        }
    }

    return Vector2();
}

Vector2 EPA::GetContactPoint(VertexCollider* c1, VertexCollider* c2)
{
    float minDistance;
    Vector2 contactPoint;
    //c1の点とc2の図形の最短距離
    for (int i = 0, len = (int)c1->GetVertexes().size(); i < len; i++) {
        int minSideIndex;
        Vector2 crossPoint;
        float distance = GJK::GetShortestDistanceToShape(c1->GetVertexes()[i], c2->GetVertexes(), crossPoint, minSideIndex);
        //最初は
        if (i == 0) {
            minDistance = distance;
            contactPoint = c1->GetVertexes()[i];
        }
        //最短なら
        else if (minDistance > distance) {
            minDistance = distance;
            contactPoint = c1->GetVertexes()[i];
        }
    }
    //c2の点とc1の図形の最短距離
    for (int i = 0, len = (int)c1->GetVertexes().size(); i < len; i++) {
        int minSideIndex;
        Vector2 crossPoint;
        float distance = GJK::GetShortestDistanceToShape(c2->GetVertexes()[i], c1->GetVertexes(), crossPoint, minSideIndex);
        //最初は
        if (i == 0) {
            minDistance = distance;
            contactPoint = c2->GetVertexes()[i];
        }
        //最短なら
        else if (minDistance > distance) {
            minDistance = distance;
            contactPoint = c2->GetVertexes()[i];
        }
    }

    return contactPoint;
}

Vector2 EPA::GetContactPoint(CircleCollider* c1, VertexCollider* c2)
{
    //c1の中心点とc2の図形の最短距離
    int minSideIndex;
    Vector2 contactPoint;
    GJK::GetShortestDistanceToShape(c1->GetPosition(), c2->GetVertexes(), contactPoint, minSideIndex);
    //最短の交点が衝突点
    return contactPoint;
}

Vector2 EPA::GetContactPoint(CircleCollider* c1, CircleCollider* c2)
{
    //円から円のベクトルのサポート写像が衝突点
    return GJK::Support(c1, c2->GetPosition() - c1->GetPosition());
}

