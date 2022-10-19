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
		static SupportInfo* IsHit(Collider* c1, Collider* c2);

		static Vector2 Support(Collider* c1, Collider* c2, Vector2 v);	//ミコンフスキー差のサポート写像を取得

		static Vector2 Support(Collider* c, Vector2 d);	//サポート写像を取得
		static Vector2 Support(VertexCollider* c, Vector2 d);	//内包する図形のサポート写像を取得
		static Vector2 Support(CircleCollider* c, Vector2 d);	//円のサポート写像を取得

		static float GetShortestDistanceToShape(Vector2 targetPoint, std::vector<Vector2> vertexes, Vector2& crossPoint, int& minSideIndex);

	private:

		static bool IsPointInTriangle(Vector2 point, std::vector<Vector2> vertexes);	//三角形の中に点があるか

		//static void CollisionResponce(ContactPoint* contactPoint);
};

