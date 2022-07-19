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
		AnimationState* fromState = nullptr;	//‚Ç‚±‚©‚ç
		AnimationState* toState = nullptr;	//‚Ç‚±‚ÖˆÚ‚é

		//Condition‚½‚¿
		std::vector<AnimationCondition*> conditions;

		bool canTransition();	//ğŒ‚ğ–‚½‚·‚Ætrue

		//Condition‚ğì¬
		void AddCondition(std::string name, float value, AnimationCondition::Mode mode);
};