#pragma once

#include <vector>
#include "Vector3.h"
#include "Component.h"
#include "Matrix.h"

class Transform : public Component
{
	public:
		Vector3 position;	//位置
		Vector3 rotation;	//回転角度(オイラー角)
		Vector3 scale = Vector3::One();		//大きさ

		Vector3 localPosition;
		Vector3 localRotation;
		Vector3 localScale = Vector3::One();

		Transform* parent = nullptr;	//親のTransform

		Transform();

		void Update() override;	//親の相対によって変える

		void SetParent(Transform* newParent);	//親オブジェクトをセットする

	private:
		std::vector<Transform*> children;	//子のTransformたち

		Vector3 GetLocalToWorldPos();	//親のワールド座標と今のローカル座標で今のワールド座標を求める
		Vector3 GetLocalToWorldRote();	//親のワールド回転と今のローカル回転で今のワールド回転を求める
		Vector3 GetLocalToWorldScale();	//親のワールド縮尺と今のローカル縮尺で今のワールド縮尺を求める
};
