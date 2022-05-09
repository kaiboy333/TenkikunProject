#include "Transform.h"

Transform::Transform()
{
	this->canPutSameComponent = false;	//2つは入れられない
}

void Transform::Update()
{
	//ローカル情報をもとにワールド情報を更新する
	position = GetLocalToWorldPos();	//座標
	rotation = GetLocalToWorldRote();	//回転
	scale = GetLocalToWorldScale();	//大きさ

	//子の更新
	for (Transform* child : children) {
		child->Update();
	}
}

void Transform::SetParent(Transform* newParent)
{
	//既に親がいるなら
	if (parent != nullptr) {
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
	}
}

Vector3 Transform::GetLocalToWorldPos()
{
	Vector3 worldPos = parent != nullptr ? parent->position : Vector3::Zero();
	Vector3 worldRote = parent != nullptr ? parent->rotation : Vector3::Zero();
	Vector3 worldScale = parent != nullptr ? parent->scale : Vector3::One();

	Matrix mat = Matrix::GetMRote(localRotation);
	Vector4 vec4_t = mat * Vector4(worldPos.x, worldPos.y, worldPos.z, 1.0f);	//座標を変換

	Matrix mMatrix = Matrix::GetMMatrix(localPosition, localRotation, localScale);
	Vector4 vec4 = mMatrix * Vector4(worldPos.x, worldPos.y, worldPos.z, 1.0f);	//座標を変換

	return Vector3(vec4.x, vec4.y, vec4.z);
}

Vector3 Transform::GetLocalToWorldRote()
{
	Vector3 worldRote = parent != nullptr ? parent->rotation : Vector3::Zero();

	return worldRote + localRotation;
}

Vector3 Transform::GetLocalToWorldScale()
{
	Vector3 worldScale = parent != nullptr ? parent->scale : Vector3::One();

	worldScale.x *= localScale.x;
	worldScale.y *= localScale.y;
	worldScale.z *= localScale.z;

	return worldScale;
}
