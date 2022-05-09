#include "AnimationTransition.h"

AnimationTransition::AnimationTransition(AnimationState* fromState, AnimationState* toState, AnimatorController* ac)
{
	this->fromState = fromState;
	this->toState = toState;
	this->ac = ac;
}

bool AnimationTransition::canTransition()
{
	//int�ł̏�������
	for (IntCondition* intCondition : intConditions) {
		auto iter = ac->intParamaters.find(intCondition->name);
		//����������
		if (iter != ac->intParamaters.end()) {
			//�����ɍ���Ȃ�������
			if (!intCondition->isMeetCondition(iter->second)) {
				return false;
			};
		}
		
	}
	//float�ł̏�������
	for (FloatCondition* floatCondition : floatConditions) {
		auto iter = ac->floatParamaters.find(floatCondition->name);
		//����������
		if (iter != ac->floatParamaters.end()) {
			//�����ɍ���Ȃ�������
			if (!floatCondition->isMeetCondition(iter->second)) {
				return false;
			};
		}

	}
	//bool�ł̏�������
	for (BoolCondition* boolCondition : boolConditions) {
		auto iter = ac->boolParamaters.find(boolCondition->name);
		//����������
		if (iter != ac->boolParamaters.end()) {
			//�����ɍ���Ȃ�������
			if (!boolCondition->isMeetCondition(iter->second)) {
				return false;
			};
		}

	}
	return true;
}

void AnimationTransition::AddIntCondition(std::string name)
{
	IntCondition* intCondition = new IntCondition(name);	//Condition�쐬
	intConditions.emplace_back(intCondition);	//���X�g�ɒǉ�
}

void AnimationTransition::AddFloatCondition(std::string name)
{
	FloatCondition* floatCondition = new FloatCondition(name);	//Condition�쐬
	floatConditions.emplace_back(floatCondition);	//���X�g�ɒǉ�
}

void AnimationTransition::AddBoolCondition(std::string name)
{
	BoolCondition* boolCondition = new BoolCondition(name);	//Condition�쐬
	boolConditions.emplace_back(boolCondition);	//���X�g�ɒǉ�
}

void AnimationTransition::ChangeIntCondition(std::string name, int value, int index)
{
	for (IntCondition* intCondition : intConditions) {
		//name������Condition����������
		if (intCondition->name == name) {
			intCondition->value = value;
			//�T�C�Y�𒴂��Ă��Ȃ��Ȃ�
			if (intCondition->types.size() > index) {
				intCondition->index = index;
			}
			return;
		}
	}
	return;
}

void AnimationTransition::ChangeFloatCondition(std::string name, float value, int index)
{
	for (FloatCondition* floatCondition : floatConditions) {
		//name������Condition����������
		if (floatCondition->name == name) {
			floatCondition->value = value;
			//�T�C�Y�𒴂��Ă��Ȃ��Ȃ�
			if (floatCondition->types.size() > index) {
				floatCondition->index = index;
			}
			return;
		}
	}
	return;
}

void AnimationTransition::ChangeBoolCondition(std::string name, bool value, int index)
{
	for (BoolCondition* boolCondition : boolConditions) {
		//name������Condition����������
		if (boolCondition->name == name) {
			boolCondition->value = value;
			//�T�C�Y�𒴂��Ă��Ȃ��Ȃ�
			if (boolCondition->types.size() > index) {
				boolCondition->index = index;
			}
			return;
		}
	}
	return;
}
