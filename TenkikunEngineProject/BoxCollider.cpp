#include "BoxCollider.h"
#include "ImageRenderer.h"
#include "RigidBody.h"

BoxCollider::BoxCollider(GameObject* gameobject) : VertexCollider(gameobject)
{
	//ImageRenderer�擾
	ImageRenderer* ir = this->gameobject->GetComponent<ImageRenderer>();

	if (ir) {
		//Image������Ȃ�
		if (ir->image) {
			//���A������size�ɃZ�b�g
			size.x = ir->image->GetWidth();
			size.y = ir->image->GetHeight();
		}
	}
}

std::vector<Vector2> BoxCollider::GetVertexes()
{
	//���S�ʒu����e���_�܂ł̃x�N�g�������
	std::vector<Vector2> toVertexVecs;

	//����̒��_�ւ̃x�N�g��
	toVertexVecs.push_back(Vector2(-GetActualWidth() / 2, GetActualHeight() / 2));
	//�E��̒��_�ւ̃x�N�g��
	toVertexVecs.push_back(Vector2(GetActualWidth() / 2, GetActualHeight() / 2));
	//�E���̒��_�ւ̃x�N�g��
	toVertexVecs.push_back(Vector2(GetActualWidth() / 2, -GetActualHeight() / 2));
	//�����̒��_�ւ̃x�N�g��
	toVertexVecs.push_back(Vector2(-GetActualWidth() / 2, -GetActualHeight() / 2));

	//���_���擾�A�����Ԃ�
	return VertexCollider::GetVertexes(toVertexVecs);
}

float BoxCollider::GetActualWidth()
{
	//�X�P�[���擾
	Vector3 scale = gameobject->transform->scale;

	return size.x * scale.x;
}

float BoxCollider::GetActualHeight()
{
	//�X�P�[���擾
	Vector3 scale = gameobject->transform->scale;

	return size.y * scale.y;
}

float BoxCollider::GetI()
{
	auto rb = gameobject->GetComponent<RigidBody>();

	return rb ? 1.0f / 3 * rb->mass * (std::powf(GetActualWidth() / 2, 2) + std::powf(GetActualHeight() / 2, 2)) : FLT_MAX;
}
