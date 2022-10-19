#pragma once

#include "DrawComponent.h"
#include "Vector3.h"
#include "DxLib.h"
#include <vector>
#include "MyMath.h"
#include "Matrix.h"
#include "GameObject.h"

class Collider : public DrawComponent
{
	public:
		Vector3 offset;	//中心からどのくらいずれているか

		bool isTrigger = false;	//すり抜けるか

		bool isHit = false;

		unsigned int downColor = GetColor(0, 255, 0);

		std::vector<Vector3> crossPoints;

		Collider(GameObject* gameobject);

		virtual void Update() override;

		virtual void Draw() override;

		//コライダーの中心点を返す
		Vector3 GetPosition();

		virtual Rect GetBoundingBox() = 0;	//バウンディングボックスを返す

		void DrawBoundingBox();	//バウンディングボックスの描画

		virtual float GetI() = 0;	//慣性モーメントを取得
};
