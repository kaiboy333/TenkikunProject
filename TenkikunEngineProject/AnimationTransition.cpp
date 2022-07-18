#include "AnimationTransition.h"

AnimationTransition::AnimationTransition(AnimationState* fromState, AnimationState* toState, AnimatorController* ac)
{
	this->fromState = fromState;
	this->toState = toState;
	this->ac = ac;
}

bool AnimationTransition::canTransition()
{
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
	AnimationCondition* condition = new AnimationCondition(name, value, mode);	//Condition�쐬
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
