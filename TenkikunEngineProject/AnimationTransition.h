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
		//AnimationTransition(const AnimationTransition& transition);	//�R�s�[�R���X�g���N�^

		AnimationState* fromState = nullptr;	//�ǂ�����
		AnimationState* toState = nullptr;	//�ǂ��ֈڂ�

		//Condition����
		std::vector<AnimationCondition*> conditions;

		bool canTransition(Animator* animator);	//�����𖞂�����true

		//Condition���쐬
		void AddCondition(std::string name, float value, AnimationCondition::Mode mode);
};