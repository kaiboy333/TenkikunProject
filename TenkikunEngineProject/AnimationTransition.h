#pragma once

#include "AnimationState.h"
#include <iostream>
#include <vector>
#include "AnimatorController.h"
#include "AnimationCondition.h"

class AnimatorController;
class AnimationState;
class AnimationTransition : public SceneInfo
{
	public:
		AnimationTransition(AnimationState* fromState, AnimationState* toState, AnimatorController* ac);

		AnimatorController* ac = nullptr;
		AnimationState* fromState = nullptr;	//どこから
		AnimationState* toState = nullptr;	//どこへ移る

		//Conditionたち
		std::vector<AnimationCondition*> conditions;

		bool canTransition();	//条件を満たすとtrue

		//Conditionを作成
		void AddCondition(std::string name, float value, AnimationCondition::Mode mode);
};