#pragma once

#include "AnimationState.h"
#include <iostream>
#include <vector>
#include "AnimatorController.h"
#include "AnimationCondition.h"
#include "Animator.h"

class AnimatorController;
class AnimationState;
class Animator;
class AnimationTransition : public SceneInfo
{
	public:
		//AnimationTransition();
		//AnimationTransition(const AnimationTransition& transition);	//コピーコンストラクタ

		AnimationState* fromState = nullptr;	//どこから
		AnimationState* toState = nullptr;	//どこへ移る

		//Conditionたち
		std::vector<AnimationCondition*> conditions;

		bool canTransition(Animator* animator);	//条件を満たすとtrue

		//Conditionを作成
		void AddCondition(std::string name, float value, AnimationCondition::Mode mode);
};