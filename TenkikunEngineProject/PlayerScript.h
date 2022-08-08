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

	protected:
		void MonoStart() override;

		void MonoUpdate() override;

	private:
		float speed = 3.0f;

		RigidBody* rb = nullptr;
};
