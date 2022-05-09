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
		AnimationState* fromState = nullptr;	//�ǂ�����
		AnimationState* toState = nullptr;	//�ǂ��ֈڂ�

		//Condition����
		std::vector<IntCondition*> intConditions;
		std::vector<FloatCondition*> floatConditions;
		std::vector<BoolCondition*> boolConditions;

		bool canTransition();	//�����𖞂�����true

		//Condition���쐬
		void AddIntCondition(std::string name);
		void AddFloatCondition(std::string name);
		void AddBoolCondition(std::string name);

		//Condition�̒l��ύX
		void ChangeIntCondition(std::string name, int value, int index);
		void ChangeFloatCondition(std::string name, float value, int index);
		void ChangeBoolCondition(std::string name, bool value, int index);

};