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
		AnimationState* fromState = nullptr;	//�ǂ�����
		AnimationState* toState = nullptr;	//�ǂ��ֈڂ�

		//Condition����
		std::vector<AnimationCondition*> conditions;

		bool canTransition();	//�����𖞂�����true

		//Condition���쐬
		void AddCondition(std::string name, float value, AnimationCondition::Mode mode);
};