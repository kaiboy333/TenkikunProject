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
	AnimationCondition* condition = new AnimationCondition();	//Condition作成
	condition->name = name;
	condition->value = value;
	condition->mode = mode;
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
