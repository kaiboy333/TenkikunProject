#include "BoxCollider.h"
#include "ImageRenderer.h"

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
	//�X�P�[���擾
	Vector3 scale = gameobject->transform->scale;

	//����̒��_�ւ̃x�N�g��
	toVertexVecs.push_back(Vector2(-size.x / 2 * scale.x, size.y / 2 * scale.y));
	//�E��̒��_�ւ̃x�N�g��
	toVertexVecs.push_back(Vector2(size.x / 2 * scale.x, size.y / 2 * scale.y));
	//�E���̒��_�ւ̃x�N�g��
	toVertexVecs.push_back(Vector2(size.x / 2 * scale.x, -size.y / 2 * scale.y));
	//�����̒��_�ւ̃x�N�g��
	toVertexVecs.push_back(Vector2(-size.x / 2 * scale.x, -size.y / 2 * scale.y));

	//���_���擾�A�����Ԃ�
	return VertexCollider::GetVertexes(toVertexVecs);
}