#pragma once

#include "Vector2.h"
#include "Collider.h"
#include "VertexCollider.h"
#include "CircleCollider.h"

class GJK
{
	public:
		static bool IsHit(Collider* c1, Collider* c2);
		//static bool IsHit2(Collider* c1);

		static Vector2 Support(Collider* c1, Collider* c2, Vector2 d);	//ミコンフスキー差のサポート写像を取得

	private:
		static Vector2 Support(Collider* c, Vector2 d);	//サポート写像を取得

		static Vector2 Support(VertexCollider* c, Vector2 d);	//内包する図形のサポート写像を取得
		static Vector2 Support(CircleCollider* c, Vector2 d);	//円のサポート写像を取得

		static bool IsPointInTriangle(Vector2 point, std::vector<Vector2> vertexes);	//三角形の中に点があるか

		static Vector2 GetShortestDistanceVecToTriangle(Vector2 targetPoint, std::vector<Vector2> &vertexes);

		static Vector2 GetFirstP(Collider* c);
		static Vector2 GetFirstP(VertexCollider* c);
		static Vector2 GetFirstP(CircleCollider* c);
};

