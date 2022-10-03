#pragma once

#include "Vector2.h"
#include "Collider.h"
#include "VertexCollider.h"
#include "CircleCollider.h"
#include "Collision.h"

class GJK
{
	public:
		enum class CollisionResponseType {
			Penalty,
			Constraint,
		};

		static CollisionResponseType collisionResponseType;

		static bool IsHit(Collider* c1, Collider* c2);

	private:
		static Vector2 Support(Collider* c1, Collider* c2, Vector2 v);	//ミコンフスキー差のサポート写像を取得

		static Vector2 Support(Collider* c, Vector2 d);	//サポート写像を取得

		static Vector2 Support(VertexCollider* c, Vector2 d);	//内包する図形のサポート写像を取得
		static Vector2 Support(CircleCollider* c, Vector2 d);	//円のサポート写像を取得

		static bool IsPointInTriangle(Vector2 point, std::vector<Vector2> vertexes);	//三角形の中に点があるか

		static float GetShortestDistanceToShape(Vector2 targetPoint, std::vector<Vector2> vertexes, Vector2& crossPoint, int& minSideIndex);

		static Vector2 GetContactPoints(Collider* c1, Collider* c2);	//二つの図形の最短距離から衝突点を求め、Collisionに入れる
		static Vector2 GetContactPoints(VertexCollider* c1, VertexCollider* c2);
		static Vector2 GetContactPoints(CircleCollider* c1, VertexCollider* c2);
		static Vector2 GetContactPoints(CircleCollider* c1, CircleCollider* c2);

		//static void CollisionResponce(ContactPoint* contactPoint);
};

