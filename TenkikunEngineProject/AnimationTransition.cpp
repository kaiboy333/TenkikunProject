#include "AnimationTransition.h"

AnimationTransition::AnimationTransition(AnimationState* fromState, AnimationState* toState, AnimatorController* ac)
{
	this->fromState = fromState;
	this->toState = toState;
	this->ac = ac;
}

bool AnimationTransition::canTransition()
{
	//条件判定
	for (AnimationCondition* condition : conditions) {
		auto iter = ac->paramaters.find(condition->name);
		//見つかったら
		if (iter != ac->paramaters.end()) {
			//条件に合わなかったら
			if (!condition->isMeetCondition(iter->second->GetValue())) {
				return false;
			};
		}

	}
	return true;
}

void AnimationTransition::AddCondition(std::string name, float value, AnimationCondition::Mode mode)
{
	AnimationCondition* condition = new AnimationCondition(name, value, mode);	//Condition作成
	conditions.emplace_back(condition);	//リストに追加
}

//void AnimationTransition::ChangeIntCondition(std::string name, int value, int index)
//{
//	for (IntCondition* intCondition : intConditions) {
//		//nameを持つConditionがあったら
//		if (intCondition->name == name) {
//			intCondition->value = value;
//			//サイズを超えていないなら
//			if (intCondition->types.size() > index) {
//				intCondition->index = index;
//			}
//			return;
//		}
//	}
//	return;
//}
