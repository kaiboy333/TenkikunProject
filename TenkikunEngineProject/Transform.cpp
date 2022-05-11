#include "Transform.h"
#include "Scene.h"

Transform::Transform()
{
	this->canPutSameComponent = false;	//2つは入れられない
}

void Transform::Update()
{
	RivisionUpdate();

	RotateUpdate();
	ScaleUpdate();
	TransUpdate();

	//前回のローカルをいまのにする
	beforeLocalRotation = localRotation;
	beforeLocalScale = localScale;

	//前回のワールドをいまのにする
	beforePosition = position;
	beforeRotation = rotation;
	beforeScale = scale;

	////子の更新
	//for (Transform* child : children) {
	//	child->Update();
	//}
}

void Transform::RivisionUpdate()
{
	//位置の修正
	deltaPosition = localPosition - beforeLocalPosition + position - beforePosition;	//前回とのずれを計算する
	localPosition = beforeLocalPosition + deltaPosition;	//ローカルだけ修正

	//回転の修正
	deltaRotation = localRotation - beforeLocalRotation + rotation - beforeRotation;	//前回とのずれを計算する
	localRotation = beforeLocalRotation + deltaRotation;	//ローカルだけ修正

	//大きさの修正
	deltaScale = Vector3((localScale.x / beforeLocalScale.x) * (scale.x / beforeScale.x), (localScale.y / beforeLocalScale.y) * (scale.y / beforeScale.y), (localScale.z / beforeLocalScale.z) * (scale.z / beforeScale.z));	//前回とのずれを計算する
	localScale = Vector3(beforeLocalScale.x * deltaScale.x, beforeLocalScale.y * deltaScale.y, beforeLocalScale.z * deltaScale.z);	//ローカルだけ修正


	//for (Transform* child : children) {
	//	child->RivisionUpdate();
	//}
}

void Transform::SetParent(Transform* newParent)
{
	//新しい親が今の親と同じかまたは今の親が自身だったら
	if (newParent == parent || newParent == this)
		return;
	//親も新しい親もいるなら
	if (newParent != nullptr && parent != nullptr) {
		SetParent(nullptr);	//一旦親をなくす
	}
	//nullptrで親を消すなら
	if (newParent == nullptr) {
		//ローカルをワールドと同じにする
		parent->localPosition = parent->position;
		parent->localRotation = parent->rotation;
		parent->localScale = parent->scale;
	}
	//親にセット
	parent = newParent;
	if (newParent != nullptr) {
		//親に自身を追加
		newParent->children.push_back(this);
		////シーンのリストから外す
		//SceneManager::GetNowScene()->RemoveGameObject(gameobject);
		//親のワールドと自身のワールドからローカルを求める
		localPosition = position - parent->position;
		localRotation = rotation - parent->rotation;
		localScale = Vector3(scale.x / parent->scale.x, scale.y / parent->scale.y, scale.z / parent->scale.z);
	}
	else {
	}
}

void Transform::TransUpdate() {

	//移動による座標更新
	Vector3 parentPos = parent != nullptr ? parent->position : Vector3::Zero();

	position = Matrix::GetMTrans(localPosition) * parentPos;

	//回転による座標更新(子が回転するため)
	std::vector<Transform*> transforms = children;	//最初に自身の子たちを追加

	//すべての子が終わるまで繰り返す
	while (transforms.size() != 0) {
		std::vector<Transform*> tmp;	//仮のリスト

		for (Transform* transform : transforms) {
			transform->position = Matrix::GetMRote(position, deltaRotation) * transform->position;
			//transform->position = Matrix::GetMRote(position, deltaRotation) * Matrix::GetMScale(position, Vector3::One() + deltaScale) * transform->position;

			tmp.insert(tmp.end(), transform->children.begin(), transform->children.end());		//子を追加
		}

		transforms = tmp;	//中身を移動
	}

	////大きさによる座標更新(子が拡大するため)
	//std::vector<Transform*> transforms_t;
	//transforms_t.push_back(this);	//最初に自身を追加

	////すべての子が終わるまで繰り返す
	//while (transforms_t.size() != 0) {
	//	std::vector<Transform*> tmp;	//仮のリスト

	//	for (Transform* transform : transforms_t) {
	//		transform->position = Matrix::GetMScale(parentPos, Vector3::One() + deltaScale) * transform->position;	//座標更新
	//		tmp.insert(tmp.end(), transform->children.begin(), transform->children.end());		//子を追加
	//	}

	//	transforms_t = tmp;	//中身を移動
	//}

	//for (Transform* child : children) {
	//	child->TransUpdate();
	//}
}

void Transform::RotateUpdate() {
	Vector3 parentRote = parent != nullptr ? parent->rotation : Vector3::Zero();

	rotation = parentRote + localRotation;
}

void Transform::ScaleUpdate() {
	Vector3 parentScale = parent != nullptr ? parent->scale : Vector3::One();

	parentScale.x *= localScale.x;
	parentScale.y *= localScale.y;
	parentScale.z *= localScale.z;

	scale = parentScale;
}