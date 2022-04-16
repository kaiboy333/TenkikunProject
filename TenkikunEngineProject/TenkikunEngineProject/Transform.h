#pragma once

#include "Component.h"
#include "Vector3.h"
#include <vector>

class Transform : public Component
{
	public:
		Vector3 position;	//位置
		Vector3 rotation;	//回転角度(オイラー角)
		Vector3 scale = Vector3(1, 1, 1);		//大きさ

		Vector3 localPosition;
		Vector3 localRotation;
		Vector3 localScale = Vector3(1, 1, 1);

		Transform* parent;	//親のTransform

		void Update();	//親の相対によって変える

	private:
		std::vector<Transform*> childrens;	//子のTransformたち
};

