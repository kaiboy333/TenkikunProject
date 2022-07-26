#pragma once

#include "Animation.h"
#include <vector>
#include <iostream>
#include "AnimationTransition.h"
#include "Animator.h"
#include "AnimatorController.h"

class Transition;
class Animator;
class AnimatorController;
class AnimationTransition;
class AnimationState : public SceneInfo
{
	public:
		//AnimatorController* ac = nullptr;
		//GameObject* gameobject = nullptr;
		Animation* animation = nullptr;

		std::string name = "New Animation";

		float speed = 1.0f;

		std::vector<AnimationTransition*> transitions;

		//AnimationState();
		//AnimationState(const AnimationState& state);

		void Update(Animator* animator);

		AnimationTransition* AddTransition(AnimationState* toState);	//êVÇµÇ¢Transitioní«â¡
};

