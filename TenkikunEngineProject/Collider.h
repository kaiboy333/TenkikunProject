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
		Vector3 offset;

		unsigned int color = GetColor(0, 255, 0);

		Collider(GameObject* gameobject);

		virtual void Update() override;

		//コライダーの中心点を返す
		Vector3 GetPosition();
};
