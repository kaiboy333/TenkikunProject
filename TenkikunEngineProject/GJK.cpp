#include "GJK.h"
#include "BoxCollider.h"
#include "Debug.h"
#include "Collision.h"
#include "RigidBody.h"
#include "HitChecker.h"
#include "ContactPoint.h"

bool GJK::IsHit(Collider* c1, Collider* c2)
{
    Vector2 v = c1->GetPosition() - c2->GetPosition();
    if (v == Vector2::Zero()) {
        return true;
    }

    std::vector<Vector2> vertexes;
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
                    return false;
                }
                //vertexes[1] - vertexes[0]に垂直なベクトルを取得
                v = Matrix::GetMRoteZ(Vector2::Zero(), 90) * (vertexes[1] - vertexes[0]);
                //vertexes[0]との内積が負だったら方向を逆にする
                if (Vector2::Dot(v, vertexes[0]) < 0) {
                    v = -v;
                }
                //Vector2::GetMinDistance(vertexes[0], vertexes[1], originPos, crossPoint);
                ////垂線ではないのなら
                //if (crossPoint == vertexes[0] || crossPoint == vertexes[1]) {
                //    return false;
                //}
                //v = -crossPoint;
                break;
            case 3:
                //新しくできた頂点が他二点と被るなら(収束したなら)
                if (vertexes[2] == vertexes[0] || vertexes[2] == vertexes[1]) {
                    return false;
                }
                //原点が3点で作った三角形に含まれているなら
                if (IsPointInTriangle(Vector2::Zero(), vertexes)) {
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
                    for (int j = 0; j < 30; j++) {
                        //原点から凸包への最短距離を求める
                        GetShortestDistanceToShape(Vector2::Zero(), vertexes, crossPoint, minSideIndex);
                        //最短距離となる辺に垂直なベクトルを取得(dirを掛けて図形の辺方向に向ける)
                        v = Matrix::GetMRoteZ(Vector2::Zero(), 90) * (vertexes[(minSideIndex + 1) % (int)vertexes.size()] - vertexes[minSideIndex]) * (float)dir;
                        //サポート写像を求める
                        Vector2 supportVec = Support(c1, c2, v);
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


                    Collision* collision1 = new Collision(c1);
                    Collision* collision2 = new Collision(c2);

                    //めり込み深度(少し長さを伸ばす)
                    Vector2 sinkVec = crossPoint * 1.001f;

                    RigidBody* rb1 = c1->gameobject->GetComponent<RigidBody>();
                    RigidBody* rb2 = c2->gameobject->GetComponent<RigidBody>();

                    //どちらかが剛体なら
                    if (rb1 || rb2) {
                        if (collisionResponseType == CollisionResponseType::Constraint) {
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

                                //衝突点を求める
                                collision1->contactPoint = GetContactPoints(c1, c2);
                                collision2->contactPoint = GetContactPoints(c1, c2);

                                ////位置を戻す
                                //c1->gameobject->transform->position -= moveVec1;
                                //c2->gameobject->transform->position -= moveVec2;
                        }
                        else if (collisionResponseType == CollisionResponseType::Penalty) {

                        }
                        ////これから衝突応答をする
                        //ContactPoint* contactPoint = new ContactPoint(c1, c2, collision1->contactPoint, crossPoint);
                        //CollisionResponce(contactPoint);
                    }
                    else {
                        //衝突点を求める
                    }

                    return true;
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

    return false;
}

Vector2 GJK::Support(Collider* c1, Collider* c2, Vector2 v)
{
    return Support(c1, v) - Support(c2, -v);
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
    //最大内積の時の長さ(距離)
    float maxDistance = 0;

    for (int i = 0, len = (int)vertexes.size(); i < len; i++) {
        Vector2 vertex = vertexes[i];
        float dot = Vector2::Dot(vertex, d);
        float distance = vertex.GetMagnitude();
        if (i == 0) {
            maxDot = dot;
            supportVec = vertex;
            maxDistance = distance;
        }
        //内積が今までで最大なら
        else if (dot > maxDot) {
            //更新
            maxDot = dot;
            //その時の頂点を記憶
            supportVec = vertex;
            //長さを記憶
            maxDistance = distance;
        }
        //内積が同じ最大なら
        else if (dot == maxDot) {
            //今回のほうが長いなら更新
            if (maxDistance < distance) {
                //その時の頂点を記憶
                supportVec = vertex;
                //長さを記憶
                maxDistance = distance;
            }
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

float GJK::GetShortestDistanceToShape(Vector2 targetPoint, std::vector<Vector2> vertexes, Vector2& crossPoint, int& minSideIndex)
{
    float minDistance = 0;
    for (int i = 0, len = (int)vertexes.size(); i < len; i++) {
        Vector2 vert1 = vertexes[i % len];
        Vector2 vert2 = vertexes[(i + 1) % len];

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

Vector2 GJK::GetContactPoints(Collider* c1, Collider* c2)
{
    auto& type1 = typeid(*c1);
    auto& type2 = typeid(*c2);

    auto& typeCC = typeid(CircleCollider);
    auto& typeBC = typeid(BoxCollider);

    if (true) {
        //円と円の衝突点
        if (type1 == typeCC && type2 == typeCC) {
            return GetContactPoints(static_cast<CircleCollider*>(c1), static_cast<CircleCollider*>(c2));
        }
        //矩形と矩形の衝突点
        if (type1 == typeBC && type2 == typeBC) {
            return GetContactPoints(static_cast<BoxCollider*>(c1), static_cast<BoxCollider*>(c2));
        }
        //円と矩形の衝突点
        else if (type1 == typeCC && type2 == typeBC) {
            return GetContactPoints(static_cast<CircleCollider*>(c1), static_cast<BoxCollider*>(c2));
        }
        else if (type1 == typeBC && type2 == typeCC) {
            return GetContactPoints(static_cast<CircleCollider*>(c2), static_cast<BoxCollider*>(c1));
        }
    }

    return Vector2();
}

Vector2 GJK::GetContactPoints(VertexCollider* c1, VertexCollider* c2)
{
    float minDistance;
    Vector2 contactPoint;
    //c1の点とc2の図形の最短距離
    for (int i = 0, len = (int)c1->GetVertexes().size(); i < len; i++) {
        int minSideIndex;
        Vector2 crossPoint;
        float distance = GetShortestDistanceToShape(c1->GetVertexes()[i], c2->GetVertexes(), crossPoint, minSideIndex);
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
        float distance = GetShortestDistanceToShape(c2->GetVertexes()[i], c1->GetVertexes(), crossPoint, minSideIndex);
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

Vector2 GJK::GetContactPoints(CircleCollider* c1, VertexCollider* c2)
{
    //c1の中心点とc2の図形の最短距離
    int minSideIndex;
    Vector2 contactPoint;
    GetShortestDistanceToShape(c1->GetPosition(), c2->GetVertexes(), contactPoint, minSideIndex);
    //最短の交点が衝突点
    return contactPoint;
}

Vector2 GJK::GetContactPoints(CircleCollider* c1, CircleCollider* c2)
{
    //円から円のベクトルのサポート写像が衝突点
    return Support(c1, c2->GetPosition() - c1->GetPosition());
}

//void GJK::CollisionResponce(ContactPoint* contactPoint)
//{
//    Collider* c1 = contactPoint->thisCollider;
//    Collider* c2 = contactPoint->otherCollider;
//    RigidBody* rb1 = c1->gameobject->GetComponent<RigidBody>();
//    RigidBody* rb2 = c2->gameobject->GetComponent<RigidBody>();
//
//    Vector3 cp = contactPoint->point;
//    Vector3 dp = contactPoint->depthPoint;
//
//    Vector3 r1 = cp - c1->GetPosition();
//    Vector3 r2 = cp - c2->GetPosition();
//
//    //いったん衝突法線を3次元ベクトルにする
//    Vector3 normal = dp.GetNormalized();
//
//    Vector3 velocityA = rb1 ? rb1->velocity : Vector3::Zero() + Vector3::Cross((rb1 ? rb1->angularVelocity : Vector3::Zero()) * MyMath::DEG_TO_RAD, r1);
//    Vector3 velocityB = rb2 ? rb2->velocity : Vector3::Zero() + Vector3::Cross((rb2 ? rb2->angularVelocity : Vector3::Zero()) * MyMath::DEG_TO_RAD, r2);
//
//    //2つの物体の相対速度を求める（V1 - V2）
//    Vector3 relativeVelocity = velocityA - velocityB;
//
//    //接線ベクトルを求める
//    Vector3 tangent1 = Matrix::GetMRoteZ(90) * normal;
//
//    //反発係数
//    float restitution = 1.0;
//
//    // 衝突法線方向の計算
//    {
//        Vector3 axis = normal;
//
//        //rhs = Right Hand Side = 右辺
//        float jacDiagInv = 1.0 / (
//            ((rb1 ? 1.0 / rb1->mass : 0) + (rb1 ? 1.0 / rb2->mass : 0))
//            + Vector3::Dot(axis, Vector3::Cross(Vector3::Cross(r1, axis) * solverBodyA.inertiaInv, r1)
//            + Vector3::Dot(axis, Vector3::Cross(Vector3::Cross(r2, axis) * solverBodyB.inertiaInv, r2)
//            );
//        float rhs = -((1 + restitution) * Vector3::Dot(relativeVelocity, axis));
//        rhs -= (bias * std::max<float>(0.0f, contact.distance + slop)) / timeStep; // position error
//        rhs *= jacDiagInv;
//        Constraint constraint1 = Constraint(jacDiagInv, rhs, -FLT_MAX, 0.0f, axis);
//        contactPoint->constraints.push_back(constraint1);
//    }
//
//    //Tangent1
//    {
//        var axis = tangent1;
//        contact.constraints[1].jacDiagInv = 1.0 / (
//            (solverBodyA.massInv + solverBodyB.massInv)
//            + vec3.dot(axis, vec3.cross(vec3.multiplyScalar(vec3.cross(r1, axis), solverBodyA.inertiaInv), r1))
//            + vec3.dot(axis, vec3.cross(vec3.multiplyScalar(vec3.cross(r2, axis), solverBodyB.inertiaInv), r2))
//            );
//        contact.constraints[1].rhs = -vec3.dot(relativeVelocity, axis);
//        contact.constraints[1].rhs *= contact.constraints[1].jacDiagInv;
//        contact.constraints[1].lowerLimit = 0.0;
//        contact.constraints[1].upperLimit = 0.0;
//        contact.constraints[1].axis = axis;
//    }
//
//    //Warm starting
//    {
//        //あとで
//    }
//}

GJK::CollisionResponseType GJK::collisionResponseType = GJK::CollisionResponseType::Constraint;
