#include "EPA.h"
#include "RigidBody.h"
#include "BoxCollider.h"
#include "Debug.h"
#include <set>
#include "Time.h"

HitInfo* EPA::GetHitInfo(const std::vector<Collider*>& colliders, SupportInfo* supportInfo)
{
    auto& vertexes = supportInfo->supports;
    auto* c1 = colliders[supportInfo->colliderID1];
    auto* c2 = colliders[supportInfo->colliderID2];

    RigidBody* rb1 = c1->gameobject->GetComponent<RigidBody>();
    RigidBody* rb2 = c2->gameobject->GetComponent<RigidBody>();

    //どちらも剛体でないなら
    if (!rb1 && !rb2)
        return nullptr;

    //反時計回り
    int dir = 1;
    //時計回りなら
    if (Vector2::Cross(vertexes[1] - vertexes[0], vertexes[2] - vertexes[0]) > 0) {
        //正負反転
        dir = -1;
    }

    //float time[9] = {};

    //time[0] = Time::GetTime();

    //許せる誤差
    float okDistance = 0.1f;
    Vector2 beforeSupportVec = vertexes[2];
    Vector2 crossPoint;
    int minSideIndex;
    Vector2 v;
    float minDistance = 0.001f;

    for (int j = 0; j < 100; j++) {
        //float time_t[6] = {};
        //time_t[0] = Time::GetTime();

        //原点から凸包への最短距離を求める
        auto gjk = GJK();
        gjk.GetShortestDistanceToShape(Vector2::Zero(), vertexes, crossPoint, minSideIndex);

        //time_t[1] = Time::GetTime();

        //最短距離となる辺に垂直なベクトルを取得(dirを掛けて図形の辺方向に向ける)
        auto& vertex1 = vertexes[(minSideIndex + 1) % (int)vertexes.size()];
        auto& vertex2 = vertexes[minSideIndex];
        v = (Matrix::GetMRoteZ(Vector2::Zero(), 90) * (vertex1 - vertex2) * (float)dir).GetNormalized();

        //time_t[2] = Time::GetTime();

        //サポート写像を求める
        Vector2 supportVec = gjk.Support(c1, c2, v);

        //time_t[3] = Time::GetTime();

        //前回のサポート写像と今回のサポート写像の距離が一定以下なら
        if (Vector2::Distance(beforeSupportVec, supportVec) <= okDistance) {
            //終わり(それがめり込み深度)
            break;
        }
        //今回のを記憶
        beforeSupportVec = supportVec;

        //time_t[4] = Time::GetTime();

        //サポート写像を追加(最短距離となる辺の番号+1の頂点に)
        vertexes.insert(vertexes.begin() + ((minSideIndex + 1) % (int)vertexes.size()), supportVec);

        //time_t[5] = Time::GetTime();
        //for (int i = 0; i < 5; i++) {
        //    Debug::Log("Shape" + std::to_string(i) + ":" + std::to_string(time_t[i + 1] - time_t[i]));
        //}
    }

    //time[1] = Time::GetTime();

    Contact* contact = new Contact();

    //めり込み深度(少し長さを伸ばす)
    auto moveVec = -crossPoint * 1.001f;

    //time[2] = Time::GetTime();

    //c1を動かす
    c1->gameobject->transform->position += moveVec;

    //time[3] = Time::GetTime();

    //c1の衝突点を求める
    auto pointsA = GetContactPoints(c1, c2);

    //time[4] = Time::GetTime();

    for (auto& pointA : pointsA) {
        //新しいContactPoint追加
        ContactPoint* cp = new ContactPoint();
        //法線ベクトル
        cp->normal = crossPoint.GetNormalized();
        //貫通深度
        cp->distance = crossPoint.GetMagnitude();
        //衝突点
        cp->pointA = pointA;
        //ContactPoint追加
        contact->contactPoints.push_back(cp);
    }

    //c1を戻す
    c1->gameobject->transform->position -= moveVec;

    //c2を動かす
    c2->gameobject->transform->position += -moveVec;

    //time[5] = Time::GetTime();

    //c2の衝突点を求める
    auto pointsB = GetContactPoints(c2, c1);

    //time[6] = Time::GetTime();

    //許せる距離の差
    okDistance = 0.1f;
    //pointsBをpointsAに対応した点にする
    if ((int)pointsA.size() == (int)pointsB.size()) {
        for (auto& pointA : pointsA) {
            for (int i = 0, len = (int)pointsB.size(); i < len; i++) {
                //pointAとの距離が貫通深度とほぼ同じならば正しい組み合わせ
                if (Vector2::Distance(pointA, pointsB[i]) - contact->contactPoints[i]->distance <= okDistance) {
                    //ContactPointを取得
                    ContactPoint* cp = contact->contactPoints[i];
                    //衝突点
                    cp->pointB = pointsB[i];
                }
            }
        }
    }
    else {
        //Debug::Log("pointsAとpointsBの数が合わないよ");
    }
    //c2を戻す
    c2->gameobject->transform->position -= -moveVec;

    //time[7] = Time::GetTime();

    //摩擦セット
    contact->friction = std::sqrtf((rb1 ? rb1->friction : 0.5f) * (rb2 ? rb2->friction : 0.5f));

    HitInfo* hitInfo = new HitInfo();
    hitInfo->colliderID1 = supportInfo->colliderID1;
    hitInfo->colliderID2 = supportInfo->colliderID2;
    hitInfo->contact = contact;

    //for (auto i = 0; i < 7; i++) {
    //    Debug::Log("EPA" + std::to_string(i) + ":" + std::to_string(time[i + 1] - time[i]));
    //}
        
    return hitInfo;
}

std::vector<Vector2> EPA::GetContactPoints(Collider* c1, Collider* c2)
{
    auto& type1 = typeid(*c1);
    auto& type2 = typeid(*c2);

    auto& typeCC = typeid(CircleCollider);
    auto& typeBC = typeid(BoxCollider);

    //円と円の衝突点
    if (type1 == typeCC && type2 == typeCC) {
        return GetContactPoints(static_cast<CircleCollider*>(c1), static_cast<CircleCollider*>(c2));
    }
    //矩形と矩形の衝突点
    else if (type1 == typeBC && type2 == typeBC) {
        return GetContactPoints(static_cast<BoxCollider*>(c1), static_cast<BoxCollider*>(c2));
    }
    //円と矩形の衝突点
    else if (type1 == typeCC && type2 == typeBC) {
        return GetContactPoints(static_cast<CircleCollider*>(c1), static_cast<BoxCollider*>(c2));
    }
    else if (type1 == typeBC && type2 == typeCC) {
        return GetContactPoints(static_cast<CircleCollider*>(c2), static_cast<BoxCollider*>(c1));
    }

    return std::vector<Vector2>();
}

std::vector<Vector2> EPA::GetContactPoints(VertexCollider* c1, VertexCollider* c2)
{
    std::vector<VertexCollider*> colliders = {c1, c2};
    const float okDistance = 0.1f;
    float minDistance = 0;
    //重複を許さない
    std::set<Vector2> contactPointsSet;
    //c1とc2の図形の最短距離
    for (int i = 0, len = (int)colliders.size(); i < len; i++) {
        VertexCollider* cA = colliders[i];
        VertexCollider* cB = colliders[std::abs(i - (len - 1))];

        //cAの頂点からcBへの最短距離を求める
        for (int j = 0, len2 = (int)cA->GetVertexes().size(); j < len2; j++) {
            int minSideIndex;
            Vector2 crossPoint;
            auto gjk = GJK();
            float distance = gjk.GetShortestDistanceToShape(cA->GetVertexes()[j], cB->GetVertexes(), crossPoint, minSideIndex);
            //最初は
            if (i == 0 && j == 0) {
                minDistance = distance;
                contactPointsSet.insert(crossPoint);
                contactPointsSet.insert(cA->GetVertexes()[j]);
            }
            //ほぼ同じなら
            else if (std::abs(minDistance - distance) <= okDistance) {
                //追加
                contactPointsSet.insert(crossPoint);
                contactPointsSet.insert(cA->GetVertexes()[j]);
            }
            //最短なら
            else if (minDistance > distance) {
                minDistance = distance;
                //古いのをすべて削除
                contactPointsSet.clear();
                //追加
                contactPointsSet.insert(crossPoint);
                contactPointsSet.insert(cA->GetVertexes()[j]);
            }
        }
    }

    std::vector<Vector2> contactPoints = std::vector<Vector2>(contactPointsSet.begin(), contactPointsSet.end());
    //4つあったら
    if ((int)contactPoints.size() == 4) {
        //2つの衝突点を取り出す(他のも似たような値のため)
        return { contactPoints[0], contactPoints[2] };
    }
    //2つなら
    else {
        //1つの衝突点を取り出す(他のも似たような値のため)
        return { contactPoints[0] };
    }
}

std::vector<Vector2> EPA::GetContactPoints(CircleCollider* c1, VertexCollider* c2)
{
    //c1の中心点とc2の図形の最短距離
    int minSideIndex;
    Vector2 contactPoint;
    auto gjk = GJK();
    gjk.GetShortestDistanceToShape(c1->GetPosition(), c2->GetVertexes(), contactPoint, minSideIndex);
    //最短の交点が衝突点
    return { contactPoint };
}

std::vector<Vector2> EPA::GetContactPoints(CircleCollider* c1, CircleCollider* c2)
{
    //円から円のベクトルのサポート写像が衝突点
    auto gjk = GJK();
    return { gjk.Support(c1, c2->GetPosition() - c1->GetPosition()) };
}

