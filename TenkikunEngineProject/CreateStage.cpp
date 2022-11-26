#include "CreateStage.h"
#include "RigidBody.h"

CreateStage::CreateStage(GameObject* gameobject) : MonoBehaviour(gameobject)
{
}

void CreateStage::OnColliderEnter(Collision* collision)
{
}

void CreateStage::OnTriggerEnter(Collider* collider)
{
}

void CreateStage::OnColliderStay(Collision* collision)
{
}

void CreateStage::OnTriggerStay(Collider* collider)
{
}

void CreateStage::OnColliderExit(Collision* collision)
{
}

void CreateStage::OnTriggerExit(Collider* collider)
{
}

void CreateStage::MonoStart()
{
	auto scene = SceneManager::GetNowScene();

	//右壁の作成
	auto rightWall = scene->CreateSquare();
	rightWall->transform->scale = Vector3(1, 10, 1);
	rightWall->transform->position = Vector3::Right() * 200;
	auto rb1 = rightWall->AddComponent<RigidBody>();
	//rb1->friction = 0;
	//rb1->restritution = 1;
	rb1->bodyType = RigidBody::BodyType::Static;

	//左壁の作成
	auto leftWall = scene->CreateSquare();
	leftWall->transform->scale = Vector3(1, 10, 1);
	leftWall->transform->position = Vector3::Left() * 200;
	auto rb2 = leftWall->AddComponent<RigidBody>();
	//rb2->friction = 0;
	//rb2->restritution = 1;
	rb2->bodyType = RigidBody::BodyType::Static;

	//上壁の作成
	auto upWall = scene->CreateSquare();
	upWall->transform->scale = Vector3(8, 1, 1);
	upWall->transform->position = Vector3::Up() * 200;
	auto rb3 = upWall->AddComponent<RigidBody>();
	//rb3->friction = 0;
	//rb3->restritution = 1;
	rb3->bodyType = RigidBody::BodyType::Static;

	//下壁の作成
	auto downWall = scene->CreateSquare();
	downWall->transform->scale = Vector3(20, 1, 1);
	downWall->transform->position = Vector3::Down() * 200;
	auto rb4 = downWall->AddComponent<RigidBody>();
	//rb4->friction = 0;
	//rb4->restritution = 1;
	rb4->bodyType = RigidBody::BodyType::Static;

	//球の作成
	for (int i = 0; i < 10; i++) {
		auto ball = scene->CreateCircle();
		ball->transform->scale = Vector3(0.1f, 0.1f, 1);
		auto rb5 = ball->AddComponent<RigidBody>();
		rb5->gravityScale = 10;
		//rb5->friction = 0;
		//rb5->restritution = 1;
		//rb5->AddForce((Vector3(1, 3, 0)).GetNormalized() * 500);
	}

	//プレイヤーの作成
	//player = scene->CreateSquare();
	//player->transform->scale = Vector3(2, 0.5f, 1);
	//player->transform->position = Vector3(0, -100, 0);
}

void CreateStage::MonoUpdate()
{
	//マウスが押されたら
	if (Input::GetMouseButtonDown(Input::MouseCode::Mouse_Left)) {
		//マウスの位置を取得
		Vector3 mouseScreenPos = Camera::ScreenToWorldPoint(Input::GetMousePosition());

		auto scene = SceneManager::GetNowScene();

		//球の作成
		for (int i = 0; i < 10; i++) {
			auto ball = scene->CreateCircle();
			ball->transform->position = mouseScreenPos;
			ball->transform->scale = Vector3(0.1f, 0.1f, 1);
			auto rb5 = ball->AddComponent<RigidBody>();
			rb5->gravityScale = 10;
		}
	}
}
