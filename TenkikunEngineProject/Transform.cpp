#include "Transform.h"
#include "Scene.h"
#include "Property.h"

Transform::Transform()
{
	this->canPutSameComponent = false;	//2�͓�����Ȃ�
}

void Transform::Update()
{

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

	TreeList* treeList = SceneManager::GetNowScene()->treeList;

	//TreeList���玩�g�̖��O�폜
	TreeNode* node = treeList->Delete(gameobject->GetName());

	//nullptr�Őe�������Ȃ�
	if (newParent == nullptr) {
		//�e�Ɏ��g���폜
		parent->children.erase(std::remove(parent->children.begin(), parent->children.end(), this));
		//TreeList���烋�[�g���g���Ď��g�̖��O�ǉ�
		treeList->Add(node, treeList->GetRoot());
	}
	else {
		//�e�Ɏ��g��ǉ�
		newParent->children.push_back(this);
		//TreeList����V�����e���g���Ď��g�̖��O�ǉ�
		treeList->Add(node, treeList->FindNode(newParent->gameobject->GetName()));
	}

	//�e�ɃZ�b�g
	parent = newParent;

	//�e�̃��[���h���Z�b�g
	Vector3 parentPos = parent != nullptr ? parent->position_t : Vector3::Zero();
	//���[���h�ʒu�Ɛe�̃��[���h�ʒu�̍������[�J���ʒu�ɂȂ�
	localPosition_t = position_t - parentPos;

	//�e�̃��[���h���Z�b�g
	Vector3 parentRote = parent != nullptr ? parent->rotation_t : Vector3::Zero();
	//���[���h��]�Ɛe�̃��[���h��]�̍������[�J����]�ɂȂ�
	localRotation_t = rotation_t - parentRote;

	//�e�̃��[���h���Z�b�g
	Vector3 parentScal = parent != nullptr ? parent->scale_t : Vector3::One();
	//���[���h�傫������e�̃��[���h�傫���Ŋ��������̂����[�J���傫���ɂȂ�
	localScale_t.x = scale_t.x / parentScal.x;
	localScale_t.y = scale_t.y / parentScal.y;
	localScale_t.z = scale_t.z / parentScal.z;
}

void Transform::ChangedWorldPos(Vector3 pos)
{
	//�ő�l����
	pos.x = MyMath::Clamp(pos.x, -maxValue, maxValue);
	pos.y = MyMath::Clamp(pos.y, -maxValue, maxValue);
	pos.z = MyMath::Clamp(pos.z, -maxValue, maxValue);

	//���[���h�ʒu���Z�b�g
	position_t = pos;

	//�e�̃��[���h���Z�b�g
	Vector3 parentPos = parent != nullptr ? parent->position_t : Vector3::Zero();
	//���[���h�ʒu�Ɛe�̃��[���h�ʒu�̍������[�J���ʒu�ɂȂ�
	localPosition_t = position_t - parentPos;

	std::vector<Transform*> transforms = children;	//�ŏ��Ɏ��g�̎q������ǉ�

	//�q�̃��[���h���Z�b�g
	while (transforms.size() != 0) {
		std::vector<Transform*> tmp;	//���̃��X�g

		for (Transform* transform : transforms) {
			//���s�ړ��ɂ����W�X�V
			transform->position_t = Matrix::GetMTrans(transform->localPosition_t) * transform->parent->position_t;

			tmp.insert(tmp.end(), transform->children.begin(), transform->children.end());		//�q��ǉ�
		}

		transforms = tmp;	//���g���ړ�
	}
}

void Transform::ChangedLocalPos(Vector3 localPos)
{
	//�ő�l����
	localPos.x = MyMath::Clamp(localPos.x, -maxValue, maxValue);
	localPos.y = MyMath::Clamp(localPos.y, -maxValue, maxValue);
	localPos.z = MyMath::Clamp(localPos.z, -maxValue, maxValue);

	//���[�J���ʒu���Z�b�g
	localPosition_t = localPos;

	//�e�̃��[���h���Z�b�g
	Vector3 parentPos = parent != nullptr ? parent->position_t : Vector3::Zero();
	//���s�ړ��ɂ����W�X�V
	position_t = Matrix::GetMTrans(localPosition_t) * parentPos;


	std::vector<Transform*> transforms = children;	//�ŏ��Ɏ��g�̎q������ǉ�

	//�q�̃��[���h���Z�b�g
	while (transforms.size() != 0) {
		std::vector<Transform*> tmp;	//���̃��X�g

		for (Transform* transform : transforms) {
			//���s�ړ��ɂ����W�X�V
			transform->position_t = Matrix::GetMTrans(transform->localPosition_t) * transform->parent->position_t;

			tmp.insert(tmp.end(), transform->children.begin(), transform->children.end());		//�q��ǉ�
		}

		transforms = tmp;	//���g���ړ�
	}
}

void Transform::ChangedWorldRote(Vector3 rote)
{
	//�ő�l����
	rote.x = MyMath::Clamp(rote.x, -maxValue, maxValue);
	rote.y = MyMath::Clamp(rote.y, -maxValue, maxValue);
	rote.z = MyMath::Clamp(rote.z, -maxValue, maxValue);

	//�e�̃��[���h���Z�b�g
	Vector3 parentRote = parent != nullptr ? parent->rotation_t : Vector3::Zero();

	//�ς���O�Ƃ̍������߂�
	Vector3 deltaRote = rote - (parentRote + localRotation_t);
	//���[���h��]���Z�b�g
	rotation_t = rote;

	//���[���h��]�Ɛe�̃��[���h��]�̍������[�J����]�ɂȂ�
	localRotation_t = rotation_t - parentRote;


	std::vector<Transform*> transforms = children;	//�ŏ��Ɏ��g�̎q������ǉ�

	//�q�̃��[���h���Z�b�g
	while (transforms.size() != 0) {
		std::vector<Transform*> tmp;	//���̃��X�g

		for (Transform* transform : transforms) {
			//�q�̃��[���h��]�͐e�̃��[�J���ɍ��̃��[�J���𑫂����l
			transform->rotation_t = transform->parent->rotation_t + transform->localRotation_t;

			//���[���h�ʒu������
			transform->position_t = Matrix::GetMRote(position_t, deltaRote) * transform->position_t;
			//���g�̃��[�J���𓮂������C��
			transform->localPosition_t = transform->position_t - transform->parent->position_t;

			tmp.insert(tmp.end(), transform->children.begin(), transform->children.end());		//�q��ǉ�
		}

		transforms = tmp;	//���g���ړ�
	}
}

void Transform::ChangedLocalRote(Vector3 localRote)
{
	//�ő�l����
	localRote.x = MyMath::Clamp(localRote.x, -maxValue, maxValue);
	localRote.y = MyMath::Clamp(localRote.y, -maxValue, maxValue);
	localRote.z = MyMath::Clamp(localRote.z, -maxValue, maxValue);

	//�e�̃��[���h���Z�b�g
	Vector3 parentRote = parent != nullptr ? parent->rotation_t : Vector3::Zero();

	//�ς���O�Ƃ̍������߂�
	Vector3 deltaRote = localRote - (rotation_t - parentRote);
	//���[�J����]���Z�b�g
	localRotation_t = localRote;

	//���[���h��]�͐e�̃��[�J���ɍ��̃��[�J���𑫂����l
	rotation_t = parentRote + localRotation_t;


	std::vector<Transform*> transforms = children;	//�ŏ��Ɏ��g�̎q������ǉ�

	//�q�̃��[���h���Z�b�g
	while (transforms.size() != 0) {
		std::vector<Transform*> tmp;	//���̃��X�g

		for (Transform* transform : transforms) {
			//�q�̃��[���h��]�͐e�̃��[�J���ɍ��̃��[�J���𑫂����l
			transform->rotation_t = transform->parent->rotation_t + transform->localRotation_t;

			//���[���h�ʒu������
			transform->position_t = Matrix::GetMRote(position_t, deltaRote) * transform->position_t;
			//���g�̃��[�J���𓮂������C��
			transform->localPosition_t = transform->position_t - transform->parent->position_t;

			tmp.insert(tmp.end(), transform->children.begin(), transform->children.end());		//�q��ǉ�
		}

		transforms = tmp;	//���g���ړ�
	}
}

void Transform::ChangedWorldScale(Vector3 scal)
{
	//�ő�l����
	scal.x = MyMath::Clamp(scal.x, -maxValue, maxValue);
	scal.y = MyMath::Clamp(scal.y, -maxValue, maxValue);
	scal.z = MyMath::Clamp(scal.z, -maxValue, maxValue);

	//�e�̃��[���h���Z�b�g
	Vector3 parentScal = parent != nullptr ? parent->scale_t : Vector3::One();

	//�ς���O�Ƃ̍������߂�
	Vector3 deltaScal;
	deltaScal.x = scal.x / (parentScal.x * localScale_t.x);
	deltaScal.y = scal.y / (parentScal.y * localScale_t.y);
	deltaScal.z = scal.z / (parentScal.z * localScale_t.z);
	//���[���h�傫�����Z�b�g
	scale_t = scal;

	//���[���h�傫������e�̃��[���h�傫���Ŋ��������̂����[�J���傫���ɂȂ�
	localScale_t.x = scale_t.x / parentScal.x;
	localScale_t.y = scale_t.y / parentScal.y;
	localScale_t.z = scale_t.z / parentScal.z;

	std::vector<Transform*> transforms = children;	//�ŏ��Ɏ��g�̎q������ǉ�

	//�q�̃��[���h���Z�b�g
	while (transforms.size() != 0) {
		std::vector<Transform*> tmp;	//���̃��X�g

		for (Transform* transform : transforms) {
			//���[���h�傫���Ɏq�̃��[�J���傫���Ŋ|�������̂��q�̃��[���h�傫���ɂȂ�
			transform->scale_t.x = transform->parent->scale_t.x * transform->localScale_t.x;
			transform->scale_t.y = transform->parent->scale_t.y * transform->localScale_t.y;
			transform->scale_t.z = transform->parent->scale_t.z * transform->localScale_t.z;

			//���[���h�ʒu������
			transform->position_t = Matrix::GetMScale(position_t, deltaScal) * transform->position_t;
			//���g�̃��[�J���𓮂������C��
			transform->localPosition_t = transform->position_t - transform->parent->position_t;

			tmp.insert(tmp.end(), transform->children.begin(), transform->children.end());		//�q��ǉ�
		}

		transforms = tmp;	//���g���ړ�
	}
}

void Transform::ChangedLocalScale(Vector3 localScal)
{
	//�ő�l����
	localScal.x = MyMath::Clamp(localScal.x, -maxValue, maxValue);
	localScal.y = MyMath::Clamp(localScal.y, -maxValue, maxValue);
	localScal.z = MyMath::Clamp(localScal.z, -maxValue, maxValue);

	//�e�̃��[���h���Z�b�g
	Vector3 parentScal = parent != nullptr ? parent->scale_t : Vector3::One();
	Vector3 deltaScal;
	deltaScal.x = localScal.x / (scale_t.x / parentScal.x);
	deltaScal.y = localScal.y / (scale_t.y / parentScal.y);
	deltaScal.z = localScal.z / (scale_t.z / parentScal.z);
	//���[�J���傫�����Z�b�g
	localScale_t = localScal;

	//�e�̃��[���h�傫���Ɏ��g�̃��[�J���傫���Ŋ|�������̂����[���h�傫���ɂȂ�
	scale_t.x = parentScal.x * localScale_t.x;
	scale_t.y = parentScal.y * localScale_t.y;
	scale_t.z = parentScal.z * localScale_t.z;

	std::vector<Transform*> transforms = children;	//�ŏ��Ɏ��g�̎q������ǉ�

	//�q�̃��[���h���Z�b�g
	while (transforms.size() != 0) {
		std::vector<Transform*> tmp;	//���̃��X�g

		for (Transform* transform : transforms) {
			//���[���h�傫���Ɏq�̃��[�J���傫���Ŋ|�������̂��q�̃��[���h�傫���ɂȂ�
			transform->scale_t.x = transform->parent->scale_t.x * transform->localScale_t.x;
			transform->scale_t.y = transform->parent->scale_t.y * transform->localScale_t.y;
			transform->scale_t.z = transform->parent->scale_t.z * transform->localScale_t.z;

			//���[���h�ʒu������
			transform->position_t = Matrix::GetMScale(position_t, deltaScal) * transform->position_t;
			//���g�̃��[�J���𓮂������C��
			transform->localPosition_t = transform->position_t - transform->parent->position_t;

			tmp.insert(tmp.end(), transform->children.begin(), transform->children.end());		//�q��ǉ�
		}

		transforms = tmp;	//���g���ړ�
	}
}

float Transform::maxValue = 1000000;	//�ő�̒l��7�����炢
