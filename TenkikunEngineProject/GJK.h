#pragma once

#include "Vector2.h"
#include "Collider.h"
#include "VertexCollider.h"
#include "CircleCollider.h"
#include "Collision.h"
#include "SupportInfo.h"

class GJK
{
	public:
		static SupportInfo* IsHit(std::vector<Collider*>& colliders, int colliderID1, int colliderID2);

		static Vector2 Support(Collider* c1, Collider* c2, const Vector2& v);	//ミコンフスキー差のサポート写像を取得

		static Vector2 Support(Collider* c, const Vector2& d);	//サポート写像を取得
		static Vector2 Support(const VertexCollider* c, const Vector2& d);	//内包する図形のサポート写像を取得
		static Vector2 Support(const CircleCollider* c, const Vector2& d);	//円のサポート写像を取得

		static float GetShortestDistanceToShape(const Vector2& targetPoint, const std::vector<Vector2>& vertexes, Vector2& crossPoint, int& minSideIndex);

	private:

		static bool IsPointInTriangle(const Vector2& point, const std::vector<Vector2>& vertexes);	//三角形の中に点があるか
};

