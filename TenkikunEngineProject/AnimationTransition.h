#pragma once

#include "AnimationState.h"
#include <iostream>
#include "IntCondition.h"
#include "FloatCondition.h"
#include "BoolCondition.h"
#include "Condition.h"
#include <vector>
#include "AnimatorController.h"

class AnimatorController;
class AnimationState;
class AnimationTransition
{
	public:
		AnimationTransition(AnimationState* fromState, AnimationState* toState, AnimatorController* ac);

		AnimatorController* ac = nullptr;
		AnimationState* fromState = nullptr;	//どこから
		AnimationState* toState = nullptr;	//どこへ移る

		//Conditionたち
		std::vector<IntCondition*> intConditions;
		std::vector<FloatCondition*> floatConditions;
		std::vector<BoolCondition*> boolConditions;

		bool canTransition();	//条件を満たすとtrue

		//Conditionを作成
		void AddIntCondition(std::string name);
		void AddFloatCondition(std::string name);
		void AddBoolCondition(std::string name);

		//Conditionの値を変更
		void ChangeIntCondition(std::string name, int value, int index);
		void ChangeFloatCondition(std::string name, float value, int index);
		void ChangeBoolCondition(std::string name, bool value, int index);

};