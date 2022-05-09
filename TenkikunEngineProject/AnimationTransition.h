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
		AnimationState* fromState = nullptr;	//‚Ç‚±‚©‚ç
		AnimationState* toState = nullptr;	//‚Ç‚±‚ÖˆÚ‚é

		//Condition‚½‚¿
		std::vector<IntCondition*> intConditions;
		std::vector<FloatCondition*> floatConditions;
		std::vector<BoolCondition*> boolConditions;

		bool canTransition();	//ğŒ‚ğ–‚½‚·‚Ætrue

		//Condition‚ğì¬
		void AddIntCondition(std::string name);
		void AddFloatCondition(std::string name);
		void AddBoolCondition(std::string name);

		//Condition‚Ì’l‚ğ•ÏX
		void ChangeIntCondition(std::string name, int value, int index);
		void ChangeFloatCondition(std::string name, float value, int index);
		void ChangeBoolCondition(std::string name, bool value, int index);

};