#include "AnimationTransition.h"

AnimationTransition::AnimationTransition(AnimationState* fromState, AnimationState* toState, AnimatorController* ac)
{
	this->fromState = fromState;
	this->toState = toState;
	this->ac = ac;
}

bool AnimationTransition::canTransition()
{
	//intでの条件判定
	for (IntCondition* intCondition : intConditions) {
		auto iter = ac->intParamaters.find(intCondition->name);
		//見つかったら
		if (iter != ac->intParamaters.end()) {
			//条件に合わなかったら
			if (!intCondition->isMeetCondition(iter->second)) {
				return false;
			};
		}
		
	}
	//floatでの条件判定
	for (FloatCondition* floatCondition : floatConditions) {
		auto iter = ac->floatParamaters.find(floatCondition->name);
		//見つかったら
		if (iter != ac->floatParamaters.end()) {
			//条件に合わなかったら
			if (!floatCondition->isMeetCondition(iter->second)) {
				return false;
			};
		}

	}
	//boolでの条件判定
	for (BoolCondition* boolCondition : boolConditions) {
		auto iter = ac->boolParamaters.find(boolCondition->name);
		//見つかったら
		if (iter != ac->boolParamaters.end()) {
			//条件に合わなかったら
			if (!boolCondition->isMeetCondition(iter->second)) {
				return false;
			};
		}

	}
	return true;
}

void AnimationTransition::AddIntCondition(std::string name)
{
	IntCondition* intCondition = new IntCondition(name);	//Condition作成
	intConditions.emplace_back(intCondition);	//リストに追加
}

void AnimationTransition::AddFloatCondition(std::string name)
{
	FloatCondition* floatCondition = new FloatCondition(name);	//Condition作成
	floatConditions.emplace_back(floatCondition);	//リストに追加
}

void AnimationTransition::AddBoolCondition(std::string name)
{
	BoolCondition* boolCondition = new BoolCondition(name);	//Condition作成
	boolConditions.emplace_back(boolCondition);	//リストに追加
}

void AnimationTransition::ChangeIntCondition(std::string name, int value, int index)
{
	for (IntCondition* intCondition : intConditions) {
		//nameを持つConditionがあったら
		if (intCondition->name == name) {
			intCondition->value = value;
			//サイズを超えていないなら
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
		//nameを持つConditionがあったら
		if (floatCondition->name == name) {
			floatCondition->value = value;
			//サイズを超えていないなら
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
		//nameを持つConditionがあったら
		if (boolCondition->name == name) {
			boolCondition->value = value;
			//サイズを超えていないなら
			if (boolCondition->types.size() > index) {
				boolCondition->index = index;
			}
			return;
		}
	}
	return;
}
