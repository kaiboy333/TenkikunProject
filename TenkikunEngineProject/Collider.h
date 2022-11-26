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

		Collider(GameObject* gameobject);

		virtual void Update() override;

		virtual void Draw() override;

		//コライダーの中心点を返す
		Vector3 GetPosition() const;

		virtual Rect GetBoundingBox() const = 0;	//バウンディングボックスを返す

		void DrawBoundingBox() const;	//バウンディングボックスの描画

		virtual float GetI() const = 0;	//慣性モーメントを取得

		int GetNo() const;	//番号取得

		bool operator==(const Collider& other) const;
		bool operator!=(const Collider& other) const;
		bool operator<(const Collider& other) const;
		bool operator>(const Collider& other) const;

	private:
		int no = 0;
		static int newNo;
};
