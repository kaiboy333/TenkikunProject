#include "AnimationTransition.h"

//AnimationTransition::AnimationTransition(AnimationState* fromState, AnimationState* toState, AnimatorController* ac)
//{
//	this->fromState = fromState;
//	this->toState = toState;
//	this->ac = ac;
//}

//AnimationTransition::AnimationTransition()
//{
//}
//
//AnimationTransition::AnimationTransition(const AnimationTransition& transition)
//{
//	//fromState
//	this->fromState = new AnimationState(*transition.fromState);
//
//	//toState
//	this->toState = new AnimationState(*transition.toState);
//
//	//conditions
//	for (AnimationCondition* condition : transition.conditions) {
//		this->conditions.push_back(new AnimationCondition(*condition));
//	}
//}

bool AnimationTransition::canTransition(Animator* animator)
{
	AnimatorController* ac = animator->ac;

	//��������
	for (AnimationCondition* condition : conditions) {
		AnimationParamater* paramater = ac->GetParamater(condition->name);
		//����������
		if (paramater) {
			//�����ɍ���Ȃ�������
			if (!condition->isMeetCondition(paramater->GetValue())) {
				return false;
			};
		}

	}
	return true;
}

void AnimationTransition::AddCondition(std::string name, float value, AnimationCondition::Mode mode)
{
	AnimationCondition* condition = new AnimationCondition();	//Condition�쐬
	condition->name = name;
	condition->value = value;
	condition->mode = mode;
	conditions.emplace_back(condition);	//���X�g�ɒǉ�
}

void AnimationTransition::PreparationLibrate()
{
	fromState = nullptr;
	toState = nullptr;

	conditions.clear();
}

//void AnimationTransition::ChangeIntCondition(std::string name, int value, int index)
//{
//	for (IntCondition* intCondition : intConditions) {
//		//name������Condition����������
//		if (intCondition->name == name) {
//			intCondition->value = value;
//			//�T�C�Y�𒴂��Ă��Ȃ��Ȃ�
//			if (intCondition->types.size() > index) {
//				intCondition->index = index;
//			}
//			return;
//		}
//	}
//	return;
//}
