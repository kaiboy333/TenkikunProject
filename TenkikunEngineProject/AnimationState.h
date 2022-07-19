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
		AnimationState(AnimatorController* ac);

		AnimatorController* ac = nullptr;
		Animation* animation = nullptr;

		std::string name = "New Animation";

		float speed = 1.0f;
		float count = 0;

		std::vector<AnimationTransition*> transitions;

		void Update();

		AnimationTransition* AddTransition(AnimationState* toState);	//êVÇµÇ¢Transitioní«â¡
};

