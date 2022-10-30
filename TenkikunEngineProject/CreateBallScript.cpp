#include "CreateBallScript.h"
#include "Camera.h"
#include "RigidBody.h"
#include "CircleCollider.h"
#include <cmath>

CreateBallScript::CreateBallScript(GameObject* gameobject) : MonoBehaviour(gameobject)
{

}

void CreateBallScript::MonoStart()
{
}

void CreateBallScript::MonoUpdate()
{
	//�}�E�X�������ꂽ��
	if (Input::GetMouseButtonDown(Input::MouseCode::Mouse_Left)) {
		//�}�E�X�̈ʒu���擾
		Vector3 mouseScreenPos = Camera::ScreenToWorldPoint(Input::GetMousePosition());

		for (int i = 0; i < 2; i++) {
			//�{�[���쐬
			GameObject* ball = SceneManager::GetNowScene()->CreateSquare();
			//RigidBody�ǉ�
			RigidBody* rb = ball->AddComponent<RigidBody>();
			//�d�͖���
			rb->gravityScale = 0;
			//�p�x����
			float angle = MyMath::RandomRange(0.0f, 360.0f);
			//�ʒu����
			//ball->transform->position = mouseScreenPos + Vector3(std::cosf(MyMath::EulerToRad(angle)), std::sinf(MyMath::EulerToRad(angle)), 0) * makeDistance;
			ball->transform->position = mouseScreenPos + (Vector3::Right() * makeDistance) * (i * 2 - 1);
			//���x����
			//rb->velocity = -Vector3(std::cosf(MyMath::EulerToRad(angle)), std::sinf(MyMath::EulerToRad(angle)), 0) * ballSpeed;
			rb->velocity = Vector3::Left() * ballSpeed * (i * 2 - 1);
			//�T�C�Y����
			float ballSize = 1.0f;
			ball->transform->scale = (Vector3::One() - Vector3::Forward()) * ballSize;
		}
	}
}
