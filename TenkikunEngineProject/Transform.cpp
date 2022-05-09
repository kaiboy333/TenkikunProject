#include "Transform.h"

Transform::Transform()
{
	this->canPutSameComponent = false;	//2�͓�����Ȃ�
}

void Transform::Update()
{
	//���[�J���������ƂɃ��[���h�����X�V����
	position = GetLocalToWorldPos();	//���W
	rotation = GetLocalToWorldRote();	//��]
	scale = GetLocalToWorldScale();	//�傫��

	//�q�̍X�V
	for (Transform* child : children) {
		child->Update();
	}
}

void Transform::SetParent(Transform* newParent)
{
	//���ɐe������Ȃ�
	if (parent != nullptr) {
		//���[�J�������[���h�Ɠ����ɂ���
		parent->localPosition = parent->position;
		parent->localRotation = parent->rotation;
		parent->localScale = parent->scale;
	}
	//�e�ɃZ�b�g
	parent = newParent;
	if (newParent != nullptr) {
		//�e�Ɏ��g��ǉ�
		newParent->children.push_back(this);
	}
}

Vector3 Transform::GetLocalToWorldPos()
{
	Vector3 worldPos = parent != nullptr ? parent->position : Vector3::Zero();
	Vector3 worldRote = parent != nullptr ? parent->rotation : Vector3::Zero();
	Vector3 worldScale = parent != nullptr ? parent->scale : Vector3::One();

	Matrix mat = Matrix::GetMRote(localRotation);
	Vector4 vec4_t = mat * Vector4(worldPos.x, worldPos.y, worldPos.z, 1.0f);	//���W��ϊ�

	Matrix mMatrix = Matrix::GetMMatrix(localPosition, localRotation, localScale);
	Vector4 vec4 = mMatrix * Vector4(worldPos.x, worldPos.y, worldPos.z, 1.0f);	//���W��ϊ�

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
