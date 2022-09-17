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
			GameObject* ball = SceneManager::GetNowScene()->CreateCircle();
			//RigidBody�ǉ�
			RigidBody* rb = ball->AddComponent<RigidBody>();
			//�d�͖���
			rb->gravityScale = 0;
			//�p�x����
			float angle = MyMath::RandomRange(0.0f, 360.0f);
			CircleCollider* collider = ball->GetComponent<CircleCollider>();
			//�ʒu����
			ball->transform->position = mouseScreenPos + Vector3(std::cosf(MyMath::EulerToRad(angle)), std::sinf(MyMath::EulerToRad(angle)), 0) * makeDistance;
			//���x����
			rb->velocity = -Vector3(std::cosf(MyMath::EulerToRad(angle)), std::sinf(MyMath::EulerToRad(angle)), 0) * ballSpeed;
			//�T�C�Y����
			float ballSize = MyMath::RandomRange(0.05f, ballSizeMax);
			ball->transform->scale = (Vector3::One() - Vector3::Forward()) * ballSize;
			//�d������
			rb->mass = ballSize * ballWeight;
		}
	}
}
