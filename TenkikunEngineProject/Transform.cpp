#include "Transform.h"
#include "Scene.h"
#include "Property.h"

Transform::Transform()
{
	this->canPutSameComponent = false;	//2つは入れられない
}

void Transform::Update()
{

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

	TreeList* treeList = SceneManager::GetNowScene()->treeList;

	//TreeListから自身の名前削除
	TreeNode* node = treeList->Delete(gameobject->GetName());

	//nullptrで親を消すなら
	if (newParent == nullptr) {
		//親に自身を削除
		parent->children.erase(std::remove(parent->children.begin(), parent->children.end(), this));
		//TreeListからルートを使って自身の名前追加
		treeList->Add(node, treeList->GetRoot());
	}
	else {
		//親に自身を追加
		newParent->children.push_back(this);
		//TreeListから新しい親を使って自身の名前追加
		treeList->Add(node, treeList->FindNode(newParent->gameobject->GetName()));
	}

	//親にセット
	parent = newParent;

	//親のワールドをセット
	Vector3 parentPos = parent != nullptr ? parent->position_t : Vector3::Zero();
	//ワールド位置と親のワールド位置の差がローカル位置になる
	localPosition_t = position_t - parentPos;

	//親のワールドをセット
	Vector3 parentRote = parent != nullptr ? parent->rotation_t : Vector3::Zero();
	//ワールド回転と親のワールド回転の差がローカル回転になる
	localRotation_t = rotation_t - parentRote;

	//親のワールドをセット
	Vector3 parentScal = parent != nullptr ? parent->scale_t : Vector3::One();
	//ワールド大きさから親のワールド大きさで割ったものがローカル大きさになる
	localScale_t.x = scale_t.x / parentScal.x;
	localScale_t.y = scale_t.y / parentScal.y;
	localScale_t.z = scale_t.z / parentScal.z;
}

void Transform::ChangedWorldPos(Vector3 pos)
{
	//最大値調整
	pos.x = MyMath::Clamp(pos.x, -maxValue, maxValue);
	pos.y = MyMath::Clamp(pos.y, -maxValue, maxValue);
	pos.z = MyMath::Clamp(pos.z, -maxValue, maxValue);

	//ワールド位置をセット
	position_t = pos;

	//親のワールドをセット
	Vector3 parentPos = parent != nullptr ? parent->position_t : Vector3::Zero();
	//ワールド位置と親のワールド位置の差がローカル位置になる
	localPosition_t = position_t - parentPos;

	std::vector<Transform*> transforms = children;	//最初に自身の子たちを追加

	//子のワールドもセット
	while (transforms.size() != 0) {
		std::vector<Transform*> tmp;	//仮のリスト

		for (Transform* transform : transforms) {
			//平行移動による座標更新
			transform->position_t = Matrix::GetMTrans(transform->localPosition_t) * transform->parent->position_t;

			tmp.insert(tmp.end(), transform->children.begin(), transform->children.end());		//子を追加
		}

		transforms = tmp;	//中身を移動
	}
}

void Transform::ChangedLocalPos(Vector3 localPos)
{
	//最大値調整
	localPos.x = MyMath::Clamp(localPos.x, -maxValue, maxValue);
	localPos.y = MyMath::Clamp(localPos.y, -maxValue, maxValue);
	localPos.z = MyMath::Clamp(localPos.z, -maxValue, maxValue);

	//ローカル位置をセット
	localPosition_t = localPos;

	//親のワールドをセット
	Vector3 parentPos = parent != nullptr ? parent->position_t : Vector3::Zero();
	//平行移動による座標更新
	position_t = Matrix::GetMTrans(localPosition_t) * parentPos;


	std::vector<Transform*> transforms = children;	//最初に自身の子たちを追加

	//子のワールドもセット
	while (transforms.size() != 0) {
		std::vector<Transform*> tmp;	//仮のリスト

		for (Transform* transform : transforms) {
			//平行移動による座標更新
			transform->position_t = Matrix::GetMTrans(transform->localPosition_t) * transform->parent->position_t;

			tmp.insert(tmp.end(), transform->children.begin(), transform->children.end());		//子を追加
		}

		transforms = tmp;	//中身を移動
	}
}

void Transform::ChangedWorldRote(Vector3 rote)
{
	//最大値調整
	rote.x = MyMath::Clamp(rote.x, -maxValue, maxValue);
	rote.y = MyMath::Clamp(rote.y, -maxValue, maxValue);
	rote.z = MyMath::Clamp(rote.z, -maxValue, maxValue);

	//親のワールドをセット
	Vector3 parentRote = parent != nullptr ? parent->rotation_t : Vector3::Zero();

	//変える前との差を求める
	Vector3 deltaRote = rote - (parentRote + localRotation_t);
	//ワールド回転をセット
	rotation_t = rote;

	//ワールド回転と親のワールド回転の差がローカル回転になる
	localRotation_t = rotation_t - parentRote;


	std::vector<Transform*> transforms = children;	//最初に自身の子たちを追加

	//子のワールドもセット
	while (transforms.size() != 0) {
		std::vector<Transform*> tmp;	//仮のリスト

		for (Transform* transform : transforms) {
			//子のワールド回転は親のローカルに今のローカルを足した値
			transform->rotation_t = transform->parent->rotation_t + transform->localRotation_t;

			//ワールド位置が動く
			transform->position_t = Matrix::GetMRote(position_t, deltaRote) * transform->position_t;
			//自身のローカルを動いた分修正
			transform->localPosition_t = transform->position_t - transform->parent->position_t;

			tmp.insert(tmp.end(), transform->children.begin(), transform->children.end());		//子を追加
		}

		transforms = tmp;	//中身を移動
	}
}

void Transform::ChangedLocalRote(Vector3 localRote)
{
	//最大値調整
	localRote.x = MyMath::Clamp(localRote.x, -maxValue, maxValue);
	localRote.y = MyMath::Clamp(localRote.y, -maxValue, maxValue);
	localRote.z = MyMath::Clamp(localRote.z, -maxValue, maxValue);

	//親のワールドをセット
	Vector3 parentRote = parent != nullptr ? parent->rotation_t : Vector3::Zero();

	//変える前との差を求める
	Vector3 deltaRote = localRote - (rotation_t - parentRote);
	//ローカル回転をセット
	localRotation_t = localRote;

	//ワールド回転は親のローカルに今のローカルを足した値
	rotation_t = parentRote + localRotation_t;


	std::vector<Transform*> transforms = children;	//最初に自身の子たちを追加

	//子のワールドもセット
	while (transforms.size() != 0) {
		std::vector<Transform*> tmp;	//仮のリスト

		for (Transform* transform : transforms) {
			//子のワールド回転は親のローカルに今のローカルを足した値
			transform->rotation_t = transform->parent->rotation_t + transform->localRotation_t;

			//ワールド位置が動く
			transform->position_t = Matrix::GetMRote(position_t, deltaRote) * transform->position_t;
			//自身のローカルを動いた分修正
			transform->localPosition_t = transform->position_t - transform->parent->position_t;

			tmp.insert(tmp.end(), transform->children.begin(), transform->children.end());		//子を追加
		}

		transforms = tmp;	//中身を移動
	}
}

void Transform::ChangedWorldScale(Vector3 scal)
{
	//最大値調整
	scal.x = MyMath::Clamp(scal.x, -maxValue, maxValue);
	scal.y = MyMath::Clamp(scal.y, -maxValue, maxValue);
	scal.z = MyMath::Clamp(scal.z, -maxValue, maxValue);

	//親のワールドをセット
	Vector3 parentScal = parent != nullptr ? parent->scale_t : Vector3::One();

	//変える前との差を求める
	Vector3 deltaScal;
	deltaScal.x = scal.x / (parentScal.x * localScale_t.x);
	deltaScal.y = scal.y / (parentScal.y * localScale_t.y);
	deltaScal.z = scal.z / (parentScal.z * localScale_t.z);
	//ワールド大きさをセット
	scale_t = scal;

	//ワールド大きさから親のワールド大きさで割ったものがローカル大きさになる
	localScale_t.x = scale_t.x / parentScal.x;
	localScale_t.y = scale_t.y / parentScal.y;
	localScale_t.z = scale_t.z / parentScal.z;

	std::vector<Transform*> transforms = children;	//最初に自身の子たちを追加

	//子のワールドもセット
	while (transforms.size() != 0) {
		std::vector<Transform*> tmp;	//仮のリスト

		for (Transform* transform : transforms) {
			//ワールド大きさに子のローカル大きさで掛けたものが子のワールド大きさになる
			transform->scale_t.x = transform->parent->scale_t.x * transform->localScale_t.x;
			transform->scale_t.y = transform->parent->scale_t.y * transform->localScale_t.y;
			transform->scale_t.z = transform->parent->scale_t.z * transform->localScale_t.z;

			//ワールド位置が動く
			transform->position_t = Matrix::GetMScale(position_t, deltaScal) * transform->position_t;
			//自身のローカルを動いた分修正
			transform->localPosition_t = transform->position_t - transform->parent->position_t;

			tmp.insert(tmp.end(), transform->children.begin(), transform->children.end());		//子を追加
		}

		transforms = tmp;	//中身を移動
	}
}

void Transform::ChangedLocalScale(Vector3 localScal)
{
	//最大値調整
	localScal.x = MyMath::Clamp(localScal.x, -maxValue, maxValue);
	localScal.y = MyMath::Clamp(localScal.y, -maxValue, maxValue);
	localScal.z = MyMath::Clamp(localScal.z, -maxValue, maxValue);

	//親のワールドをセット
	Vector3 parentScal = parent != nullptr ? parent->scale_t : Vector3::One();
	Vector3 deltaScal;
	deltaScal.x = localScal.x / (scale_t.x / parentScal.x);
	deltaScal.y = localScal.y / (scale_t.y / parentScal.y);
	deltaScal.z = localScal.z / (scale_t.z / parentScal.z);
	//ローカル大きさをセット
	localScale_t = localScal;

	//親のワールド大きさに自身のローカル大きさで掛けたものがワールド大きさになる
	scale_t.x = parentScal.x * localScale_t.x;
	scale_t.y = parentScal.y * localScale_t.y;
	scale_t.z = parentScal.z * localScale_t.z;

	std::vector<Transform*> transforms = children;	//最初に自身の子たちを追加

	//子のワールドもセット
	while (transforms.size() != 0) {
		std::vector<Transform*> tmp;	//仮のリスト

		for (Transform* transform : transforms) {
			//ワールド大きさに子のローカル大きさで掛けたものが子のワールド大きさになる
			transform->scale_t.x = transform->parent->scale_t.x * transform->localScale_t.x;
			transform->scale_t.y = transform->parent->scale_t.y * transform->localScale_t.y;
			transform->scale_t.z = transform->parent->scale_t.z * transform->localScale_t.z;

			//ワールド位置が動く
			transform->position_t = Matrix::GetMScale(position_t, deltaScal) * transform->position_t;
			//自身のローカルを動いた分修正
			transform->localPosition_t = transform->position_t - transform->parent->position_t;

			tmp.insert(tmp.end(), transform->children.begin(), transform->children.end());		//子を追加
		}

		transforms = tmp;	//中身を移動
	}
}

float Transform::maxValue = 1000000;	//最大の値は7桁くらい
