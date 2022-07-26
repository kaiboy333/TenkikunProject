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
		auto iter = ac->paramaters.find(condition->name);
		//����������
		if (iter != ac->paramaters.end()) {
			//�����ɍ���Ȃ�������
			if (!condition->isMeetCondition(iter->second->GetValue())) {
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
