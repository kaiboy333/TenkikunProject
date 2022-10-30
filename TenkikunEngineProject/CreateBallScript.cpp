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
	//マウスが押されたら
	if (Input::GetMouseButtonDown(Input::MouseCode::Mouse_Left)) {
		//マウスの位置を取得
		Vector3 mouseScreenPos = Camera::ScreenToWorldPoint(Input::GetMousePosition());

		for (int i = 0; i < 2; i++) {
			//ボール作成
			GameObject* ball = SceneManager::GetNowScene()->CreateSquare();
			//RigidBody追加
			RigidBody* rb = ball->AddComponent<RigidBody>();
			//重力無視
			rb->gravityScale = 0;
			//角度生成
			float angle = MyMath::RandomRange(0.0f, 360.0f);
			//位置調整
			//ball->transform->position = mouseScreenPos + Vector3(std::cosf(MyMath::EulerToRad(angle)), std::sinf(MyMath::EulerToRad(angle)), 0) * makeDistance;
			ball->transform->position = mouseScreenPos + (Vector3::Right() * makeDistance) * (i * 2 - 1);
			//速度調整
			//rb->velocity = -Vector3(std::cosf(MyMath::EulerToRad(angle)), std::sinf(MyMath::EulerToRad(angle)), 0) * ballSpeed;
			rb->velocity = Vector3::Left() * ballSpeed * (i * 2 - 1);
			//サイズ調整
			float ballSize = 1.0f;
			ball->transform->scale = (Vector3::One() - Vector3::Forward()) * ballSize;
		}
	}
}
