#include "HitChecker.h"
#include "DrawComponent.h"
#include "Rect.h"
#include <set>

bool HitChecker::IsHit(Collider* c1, Collider* c2, std::vector<Vector3>& crossPoints)
{
    //初期化
    crossPoints.clear();

    auto& type1 = typeid(*c1);
    auto& type2 = typeid(*c2);

    auto& typeCC = typeid(CircleCollider);
    auto& typeBC = typeid(BoxCollider);

    //バウンディングサークルからおおよそ当たるか確認
    //バウンディングサークルで当たったら
    if(true) {
        //円と円の当たり判定
        if (type1 == typeCC && type2 == typeCC) {
            return IsHitCC(static_cast<CircleCollider*>(c1), static_cast<CircleCollider*>(c2), crossPoints);
        }
        //矩形と矩形の当たり判定
        if (type1 == typeBC && type2 == typeBC) {
            return IsHitBB(static_cast<BoxCollider*>(c1), static_cast<BoxCollider*>(c2), crossPoints);
        }
        //円と矩形の当たり判定
        else if (type1 == typeCC && type2 == typeBC) {
            return IsHitCB(static_cast<CircleCollider*>(c1), static_cast<BoxCollider*>(c2), crossPoints);
        }
        else if (type1 == typeBC && type2 == typeCC) {
            return IsHitCB(static_cast<CircleCollider*>(c2), static_cast<BoxCollider*>(c1), crossPoints);
        }
        //どれにも当てはまらない場合
        else {
            //falseを返す
            return false;
        }
    }
}

bool HitChecker::IsHitCC(CircleCollider* c1, CircleCollider* c2)
{
    float distance = Vector3::Distance(c1->GetPosition(), c2->GetPosition());

    Vector3 scale1 = c1->gameobject->transform->scale;
    Vector3 scale2 = c2->gameobject->transform->scale;
    float r1 = c1->radious * std::max<float>(scale1.x, scale1.y);
    float r2 = c2->radious * std::max<float>(scale2.x, scale2.y);

    return r1 + r2 >= distance;
}

bool HitChecker::IsHitCC(CircleCollider* c1, CircleCollider* c2, std::vector<Vector3>& crossPoints)
{
    float distance = Vector3::Distance(c1->GetPosition(), c2->GetPosition());

    Vector3 centerPos1 = c1->GetPosition();
    Vector3 centerPos2 = c2->GetPosition();
    Vector3 scale1 = c1->gameobject->transform->scale;
    Vector3 scale2 = c2->gameobject->transform->scale;
    float r1 = c1->radious * std::max<float>(scale1.x, scale1.y);
    float r2 = c2->radious * std::max<float>(scale2.x, scale2.y);

    //円が二点で交わっているなら
    if (std::abs(r1 - r2) < Vector3::Distance(centerPos1, centerPos2) && Vector3::Distance(centerPos1, centerPos2) < r1 + r2) {
        float a = 2 * (centerPos2.x - centerPos1.x);
        float b = 2 * (centerPos2.y - centerPos1.y);
        float c = (centerPos1.x + centerPos2.x) * (centerPos1.x - centerPos2.x) + (centerPos1.y + centerPos2.y) * (centerPos1.y - centerPos2.y) + (r2 + r1) * (r2 - r1);

        float d1 = -(a * centerPos1.x + b * centerPos1.y + c);

        float tmp0 = std::powf(a, 2) + std::powf(b, 2);

        float tmp1 = std::sqrtf((tmp0 * std::powf(r1, 2) - std::powf(d1, 2)));

        Vector3 crossPoint1 = Vector3((a * d1 - b * tmp1) / tmp0 + centerPos1.x, (b * d1 + a * tmp1) / tmp0 + centerPos1.y, 0);
        Vector3 crossPoint2 = Vector3((a * d1 + b * tmp1) / tmp0 + centerPos1.x, (b * d1 - a * tmp1) / tmp0 + centerPos1.y, 0);

        //交点をリストに追加
        if (std::find(crossPoints.begin(), crossPoints.end(), crossPoint1) == crossPoints.end()) {
            crossPoints.push_back(crossPoint1);
        }
        if (std::find(crossPoints.begin(), crossPoints.end(), crossPoint2) == crossPoints.end()) {
            crossPoints.push_back(crossPoint2);
        }
    }

    return IsHitCC(c1, c2);
}

bool HitChecker::IsHitBB(BoxCollider* c1, BoxCollider* c2, std::vector<Vector3>& crossPoints)
{
    std::vector<Vector3> vertexes1 = c1->GetVertexes();
    std::vector<Vector3> vertexes2 = c2->GetVertexes();

    for (int i = 0, length1 = (int)vertexes1.size(); i < length1; i++) {
        for (int j = 0, length2 = (int)vertexes2.size(); j < length2; j++) {
            Vector3 p1 = vertexes1[i % length1];
            Vector3 p2 = vertexes1[(i + 1) % length1];
            Vector3 p3 = vertexes2[j % length2];
            Vector3 p4 = vertexes2[(j + 1) % length2];

            Vector3 crossPoint;

            //交点があるなら
            if (Vector3::IsCross(p1, p2, p3, p4, crossPoint)) {
                //リストに追加
                if (std::find(crossPoints.begin(), crossPoints.end(), crossPoint) == crossPoints.end()) {
                    crossPoints.push_back(crossPoint);
                }
            }
        }
    }

    return (int)crossPoints.size() != 0;
}

bool HitChecker::IsHitCB(CircleCollider* c1, BoxCollider* c2, std::vector<Vector3>& crossPoints)
{
    //円の中心点を取得
    Vector3 centerPos = c1->GetPosition();
    Vector3 scale = c1->gameobject->transform->scale;
    float r = c1->radious * std::max<float>(scale.x, scale.y);
    //矩形の頂点を取得
    std::vector<Vector3> vertexes = c2->GetVertexes();

    for (int i = 0, length = (int)vertexes.size(); i < length; i++) {
        Vector3 p1 = vertexes[i % length];
        Vector3 p2 = vertexes[(i + 1) % length];

        float a = p1.y - p2.y;
        float b = p2.x - p1.x;
        float c = Vector3::Cross(p1, p2);

        //円の中心から直線までの最短距離を求める
        float minDistance = std::abs(a * centerPos.x + b * centerPos.y + c) / std::sqrtf(std::powf(a, 2) + std::powf(b, 2));

        //直線が交わるなら
        if (minDistance <= r) {
            float d = -(a * centerPos.x + b * centerPos.y + c);

            float tmp0 = std::powf(a, 2) + std::powf(b, 2);

            float tmp1 = std::sqrtf((tmp0 * std::powf(r, 2) - std::powf(d, 2)));

            Vector3 crossPoint1 = Vector3((a * d - b * tmp1) / tmp0 + centerPos.x, (b * d + a * tmp1) / tmp0 + centerPos.y, 0);
            Vector3 crossPoint2 = Vector3((a * d + b * tmp1) / tmp0 + centerPos.x, (b * d - a * tmp1) / tmp0 + centerPos.y, 0);

            float s = (crossPoint1 - p1).GetMagnitude() / (p2 - p1).GetMagnitude();
            //交点が線分の範囲内にあるなら(ベクトルが同じ方向かつ長さの比が0から1)
            if (s >= 0 && s <= 1 && Vector3::Inner(crossPoint1 - p1, p2 - p1) >= 0.99f) {
                if (std::find(crossPoints.begin(), crossPoints.end(), crossPoint1) == crossPoints.end()) {
                    crossPoints.push_back(crossPoint1);
                }
            }
            float t = (crossPoint2 - p1).GetMagnitude() / (p2 - p1).GetMagnitude();
            //交点が線分の範囲内にあるなら(ベクトルが同じ方向かつ長さの比が0から1)
            if (t >= 0 && t <= 1 && Vector3::Inner(crossPoint2 - p1, p2 - p1) >= 0.99f) {
                if (std::find(crossPoints.begin(), crossPoints.end(), crossPoint2) == crossPoints.end()) {
                    crossPoints.push_back(crossPoint2);
                }
            }
        }
    }

    return (int)crossPoints.size() != 0;
}

