#include "PlayerScript.h"
#include "AnimationState.h"
#include "Input.h"
#include <cmath>
#include "Physics.h"

PlayerScript::PlayerScript(GameObject* gameobject) : MonoBehaviour(gameobject)
{

}

void PlayerScript::MonoStart()
{
	rb = gameobject->GetComponent<RigidBody>();
	rb->gravityScale = 0;
	rb->velocity = Vector3::Down() * 50;
}

void PlayerScript::MonoUpdate()
{
	ImageRenderer* imageRenderer = gameobject->GetComponent<ImageRenderer>();

	Animator* animator = gameobject->GetComponent<Animator>();
	AnimatorController* ac = animator->ac;

	//if (Input::GetKey(Input::KeyCode::D)) {
	//	rb->AddForce(Vector3::Right() * speed);
	//	ac->AddFloatParamater("isSpeed", std::abs(rb->velocity.x));
	//	imageRenderer->isFlipX = false;
	//}
	//else if (Input::GetKey(Input::KeyCode::A)) {
	//	rb->AddForce(Vector3::Left() * speed);
	//	ac->AddFloatParamater("isSpeed", std::abs(rb->velocity.x));
	//	imageRenderer->isFlipX = true;
	//}
	//else {
	//	ac->AddFloatParamater("isSpeed", 0.0f);
	//}

	//if (Input::GetKey(Input::R) && Input::GetKey(Input::LEFT_SHIFT)) {
	//	gameobject->transform->rotation += Vector3::Back() * 1.0f;
	//}
	//else if (Input::GetKey(Input::R) && !Input::GetKey(Input::LEFT_SHIFT)) {
	//	gameobject->transform->rotation += Vector3::Forward() * 1.0f;
	//}

	if (Input::GetKey(Input::KeyCode::RIGHT)) {
		gameobject->transform->scale += Vector3::Right() * 0.01f;
	}
	else if (Input::GetKey(Input::KeyCode::LEFT)) {
		gameobject->transform->scale += Vector3::Left() * 0.01f;
	}
	else if (Input::GetKey(Input::KeyCode::UP)) {
		gameobject->transform->scale += Vector3::Up() * 0.01f;
	}
	else if (Input::GetKey(Input::KeyCode::DOWN)) {
		gameobject->transform->scale += Vector3::Down() * 0.01f;
	}

	//if (Input::GetKey(Input::Q) && !Input::GetKey(Input::LEFT_SHIFT)) {
	//	SceneManager::GetNowScene()->Destroy(gameobject);
	//}
	//else if (Input::GetKey(Input::Q) && Input::GetKey(Input::LEFT_SHIFT)) {
	//	SceneManager::GetNowScene()->Destroy(gameobject->transform->children[0]->gameobject);
	//}

	if (Input::GetMouseButton(Input::Mouse_Left)) {
		Vector3 mousePos = Input::GetMousePosition();
		gameobject->transform->position = Camera::ScreenToWorldPoint(mousePos);
	}

	//if (Input::GetKeyDown(Input::KeyCode::P)) {
	//	//子がいるなら
	//	if (gameobject->transform->children.size() != 0) {
	//		//外す
	//		firstChild->SetParent(nullptr);
	//	}
	//	else {
	//		//セット
	//		firstChild->SetParent(gameobject->transform);
	//	}
	//}

	if (Input::GetKeyDown(Input::SPACE)) {

	}
}
