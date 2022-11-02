#include "CreateShapeScript.h"
#include "Camera.h"
#include "RigidBody.h"
#include "CircleCollider.h"
#include <cmath>

CreateShapeScript::CreateShapeScript(GameObject* gameobject) : MonoBehaviour(gameobject)
{

}

void CreateShapeScript::OnColliderEnter(Collision* collision)
{
}

void CreateShapeScript::OnTriggerEnter(Collider* collider)
{
}

void CreateShapeScript::MonoStart()
{
}

void CreateShapeScript::MonoUpdate()
{
	//�}�E�X�������ꂽ��
	if (Input::GetMouseButtonDown(Input::MouseCode::Mouse_Left)) {
		//�}�E�X�̈ʒu���擾
		Vector3 mouseScreenPos = Camera::ScreenToWorldPoint(Input::GetMousePosition());

		for (int i = 0; i < 2; i++) {
			bool isCircle = !(bool)MyMath::RandomRange(0, 2);

			//�`�쐬
			GameObject* o = nullptr;
			if (isCircle) {
				o = SceneManager::GetNowScene()->CreateCircle();
			}
			else {
				o = SceneManager::GetNowScene()->CreateSquare();
			}
			//RigidBody�ǉ�
			RigidBody* rb = o->AddComponent<RigidBody>();
			//�d�͖���
			rb->gravityScale = 0;
			//�p�x����
			float angle = MyMath::RandomRange(0.0f, 360.0f);
			//�ʒu����
			o->transform->position = mouseScreenPos + Vector3(std::cosf(MyMath::EulerToRad(angle)), std::sinf(MyMath::EulerToRad(angle)), 0) * makeDistance;
			//o->transform->position = mouseScreenPos + (Vector3::Right() * makeDistance) * (i * 2.0f - 1);
			//���x����
			rb->velocity = -Vector3(std::cosf(MyMath::EulerToRad(angle)), std::sinf(MyMath::EulerToRad(angle)), 0) * ballSpeed;
			//rb->velocity = Vector3::Left() * ballSpeed * (i * 2.0f - 1);
			//�T�C�Y����
			float ballSize = 0;
			ballSize = isCircle? 0.3f : 1.0f;
			o->transform->scale = (Vector3::One() - Vector3::Forward()) * ballSize;
		}
	}
}

void CreateShapeScript::OnColliderStay(Collision* collision)
{
}

void CreateShapeScript::OnTriggerStay(Collider* collider)
{
}

void CreateShapeScript::OnColliderExit(Collision* collision)
{
}

void CreateShapeScript::OnTriggerExit(Collider* collider)
{
}
