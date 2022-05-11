#include "Transform.h"
#include "Scene.h"

Transform::Transform()
{
	this->canPutSameComponent = false;	//2�͓�����Ȃ�
}

void Transform::Update()
{
	RivisionUpdate();

	RotateUpdate();
	ScaleUpdate();
	TransUpdate();

	//�O��̃��[�J�������܂̂ɂ���
	beforeLocalRotation = localRotation;
	beforeLocalScale = localScale;

	//�O��̃��[���h�����܂̂ɂ���
	beforePosition = position;
	beforeRotation = rotation;
	beforeScale = scale;

	////�q�̍X�V
	//for (Transform* child : children) {
	//	child->Update();
	//}
}

void Transform::RivisionUpdate()
{
	//�ʒu�̏C��
	deltaPosition = localPosition - beforeLocalPosition + position - beforePosition;	//�O��Ƃ̂�����v�Z����
	localPosition = beforeLocalPosition + deltaPosition;	//���[�J�������C��

	//��]�̏C��
	deltaRotation = localRotation - beforeLocalRotation + rotation - beforeRotation;	//�O��Ƃ̂�����v�Z����
	localRotation = beforeLocalRotation + deltaRotation;	//���[�J�������C��

	//�傫���̏C��
	deltaScale = Vector3((localScale.x / beforeLocalScale.x) * (scale.x / beforeScale.x), (localScale.y / beforeLocalScale.y) * (scale.y / beforeScale.y), (localScale.z / beforeLocalScale.z) * (scale.z / beforeScale.z));	//�O��Ƃ̂�����v�Z����
	localScale = Vector3(beforeLocalScale.x * deltaScale.x, beforeLocalScale.y * deltaScale.y, beforeLocalScale.z * deltaScale.z);	//���[�J�������C��


	//for (Transform* child : children) {
	//	child->RivisionUpdate();
	//}
}

void Transform::SetParent(Transform* newParent)
{
	//�V�����e�����̐e�Ɠ������܂��͍��̐e�����g��������
	if (newParent == parent || newParent == this)
		return;
	//�e���V�����e������Ȃ�
	if (newParent != nullptr && parent != nullptr) {
		SetParent(nullptr);	//��U�e���Ȃ���
	}
	//nullptr�Őe�������Ȃ�
	if (newParent == nullptr) {
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
		////�V�[���̃��X�g����O��
		//SceneManager::GetNowScene()->RemoveGameObject(gameobject);
		//�e�̃��[���h�Ǝ��g�̃��[���h���烍�[�J�������߂�
		localPosition = position - parent->position;
		localRotation = rotation - parent->rotation;
		localScale = Vector3(scale.x / parent->scale.x, scale.y / parent->scale.y, scale.z / parent->scale.z);
	}
	else {
	}
}

void Transform::TransUpdate() {

	//�ړ��ɂ����W�X�V
	Vector3 parentPos = parent != nullptr ? parent->position : Vector3::Zero();

	position = Matrix::GetMTrans(localPosition) * parentPos;

	//��]�ɂ����W�X�V(�q����]���邽��)
	std::vector<Transform*> transforms = children;	//�ŏ��Ɏ��g�̎q������ǉ�

	//���ׂĂ̎q���I���܂ŌJ��Ԃ�
	while (transforms.size() != 0) {
		std::vector<Transform*> tmp;	//���̃��X�g

		for (Transform* transform : transforms) {
			transform->position = Matrix::GetMRote(position, deltaRotation) * transform->position;
			//transform->position = Matrix::GetMRote(position, deltaRotation) * Matrix::GetMScale(position, Vector3::One() + deltaScale) * transform->position;

			tmp.insert(tmp.end(), transform->children.begin(), transform->children.end());		//�q��ǉ�
		}

		transforms = tmp;	//���g���ړ�
	}

	////�傫���ɂ����W�X�V(�q���g�傷�邽��)
	//std::vector<Transform*> transforms_t;
	//transforms_t.push_back(this);	//�ŏ��Ɏ��g��ǉ�

	////���ׂĂ̎q���I���܂ŌJ��Ԃ�
	//while (transforms_t.size() != 0) {
	//	std::vector<Transform*> tmp;	//���̃��X�g

	//	for (Transform* transform : transforms_t) {
	//		transform->position = Matrix::GetMScale(parentPos, Vector3::One() + deltaScale) * transform->position;	//���W�X�V
	//		tmp.insert(tmp.end(), transform->children.begin(), transform->children.end());		//�q��ǉ�
	//	}

	//	transforms_t = tmp;	//���g���ړ�
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