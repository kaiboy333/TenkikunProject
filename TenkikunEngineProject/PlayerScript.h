#pragma once

#include "MonoBehaviour.h"
#include "Image.h"
#include "ImageRenderer.h"
#include "GameObject.h"
#include "Transform.h"
#include "Animation.h"
#include "Animator.h"
#include "AnimatorController.h"
#include <vector>
#include <iostream>
#include <sstream>
#include "RigidBody.h"

class PlayerScript : public MonoBehaviour {
	public:
		PlayerScript(GameObject* gameobject);

		virtual void OnColliderEnter(Collision* collision) override;
		virtual void OnTriggerEnter(Collider* collider) override;

		virtual void OnColliderStay(Collision* collision) override;
		virtual void OnTriggerStay(Collider* collider) override;

		virtual void OnColliderExit(Collision* collision) override;
		virtual void OnTriggerExit(Collider* collider) override;

	protected:
		void MonoStart() override;

		void MonoUpdate() override;

	private:
		float speed = 30.0f;

		RigidBody* rb = nullptr;
};
