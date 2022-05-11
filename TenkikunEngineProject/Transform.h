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

		std::vector<Transform*> children;	//子のTransformたち

	private:
		//前回のワールド
		Vector3 beforePosition;	//位置
		Vector3 beforeRotation;	//回転角度(オイラー角)
		Vector3 beforeScale = Vector3::One();	//大きさ

		//前回のローカル
		Vector3 beforeLocalPosition;
		Vector3 beforeLocalRotation;
		Vector3 beforeLocalScale = Vector3::One();

		//動いた分(ワールドとローカル合わせて)
		Vector3 deltaPosition;
		Vector3 deltaRotation;
		Vector3 deltaScale;

		void RivisionUpdate();	//ローカルとワールドでずれた分を修正する

		void TransUpdate();	//親のワールド座標と今のローカル座標で今のワールド座標を求める
		void RotateUpdate();	//親のワールド回転と今のローカル回転で今のワールド回転を求める
		void ScaleUpdate();	//親のワールド縮尺と今のローカル縮尺で今のワールド縮尺を求める
};
