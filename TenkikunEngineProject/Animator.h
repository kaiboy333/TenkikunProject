#pragma once

#include "AnimatorController.h"
#include <iostream>
#include <unordered_map>
#include "AnimationState.h"

class AnimationState;
class AnimatorController;
class Animator : public Component
{
	public:
		Animator(GameObject* gameobject);

		void Update() override;

		AnimatorController* ac = nullptr;

		AnimationState* nowState = nullptr;

		float count = 0;
		int index = 0;

		AnimationState* AddState(Animation* animation, std::string stateName);

		virtual void PreparationLibrate() override;
};

