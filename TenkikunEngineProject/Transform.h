#pragma once

#include <vector>
#include "Vector3.h"
#include "Component.h"
#include "Matrix.h"
#include "Property.h"

class Transform : public Component
{
	public:
		//ワールド情報
		//位置
		Property<Vector3> position{
			position_t
				, [this](Vector3 v) {
					ChangedWorldPos(v);
				}
				, nullptr
		};
		//回転
		Property<Vector3> rotation{
			rotation_t
				, [this](Vector3 v) {
					ChangedWorldRote(v);
				}
				, nullptr
		};
		//大きさ
		Property<Vector3> scale{
			scale_t
				, [this](Vector3 v) {
					ChangedWorldScale(v);
				}
				, nullptr
		};


		//ローカル情報
		//位置
		Property<Vector3> localPosition{
			localPosition_t
				, [this](Vector3 v) {
					ChangedLocalPos(v);
				}
				, nullptr
		};
		//回転
		Property<Vector3> localRotation{
			localRotation_t
				, [this](Vector3 v) {
					ChangedLocalRote(v);
				}
				, nullptr
		};
		//大きさ
		Property<Vector3> localScale{
			localScale_t
				, [this](Vector3 v) {
					ChangedLocalScale(v);
				}
				, nullptr
		};

		Transform* parent = nullptr;	//親のTransform

		Transform();

		void Update() override;	//親の相対によって変える

		void SetParent(Transform* newParent);	//親オブジェクトをセットする

		std::vector<Transform*> children;	//子のTransformたち

	private:
		Vector3 position_t;
		Vector3 rotation_t;
		Vector3 scale_t = Vector3::One();

		Vector3 localPosition_t;
		Vector3 localRotation_t;
		Vector3 localScale_t = Vector3::One();

		//void RivisionUpdate();	//ローカルとワールドでずれた分を修正する

		//void TransUpdate();	//親のワールド座標と今のローカル座標で今のワールド座標を求める
		//void RotateUpdate();	//親のワールド回転と今のローカル回転で今のワールド回転を求める
		//void ScaleUpdate();	//親のワールド縮尺と今のローカル縮尺で今のワールド縮尺を求める

		void ChangedWorldPos(Vector3 pos);	//ワールド位置が変更されたら呼び出す
		void ChangedLocalPos(Vector3 localPos);	//ローカル位置が変更されたら呼び出す

		void ChangedWorldRote(Vector3 rote);	//回転が変更されたら呼び出す
		void ChangedLocalRote(Vector3 localRote);	//回転が変更されたら呼び出す

		void ChangedWorldScale(Vector3 scale);	//大きさが変更されたら呼び出す
		void ChangedLocalScale(Vector3 localScale);	//大きさが変更されたら呼び出す

};
