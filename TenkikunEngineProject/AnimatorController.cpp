#include "AnimatorController.h"

AnimatorController::AnimatorController(std::filesystem::path path) : Info(path)
{

}

AnimationParamater* AnimatorController::GetParamater(std::string name)
{
	for (AnimationParamater* paramater : paramaters) {
		if (paramater->name == name) {
			return paramater;
		}
	}

	return nullptr;
}

void AnimatorController::PreparationLibrate()
{
	paramaters.clear();

	states.clear();
}

//
//AnimatorController::AnimatorController(const AnimatorController& ac)
//{
//	//名前をコピー
//	this->name = ac.name;
//
//	//nowStateをコピー
//	this->nowState = new AnimationState(*ac.nowState);
//
//	//statesをコピー
//	for (AnimationState* state : ac.states) {
//		this->states.push_back(new AnimationState(*state));
//	}
//}

//void AnimatorController::Update(Animator* animator)
//{
//	//Stateの更新
//	if (nowState != nullptr) {
//		nowState->Update(animator);
//	}
//}

//AnimationState* AnimatorController::AddState(Animation* animation, std::string stateName)
//{
//	AnimationState* state = new AnimationState();	//Stateを作成
//	//state->ac = animator->GetAnimatorController();	//StateにAnimationControllerをセット
//	state->name = stateName;	//nameセット
//	state->animation = animation;	//StateにAnimationをセット
//	states.emplace_back(state);	//Stateをリストに追加
//	//最初の場所がnullなら
//	if (nowState == nullptr) {
//		nowState = state;	//追加
//	}
//	return state;	//返す
//}

void AnimatorController::AddIntParamater(std::string name, int value = 0)
{
	AnimationParamater* animationParamater = new AnimationParamater();
	animationParamater->name = name;
	animationParamater->type = AnimationParamater::Type::Int;
	animationParamater->intValue = value;

	paramaters.push_back(animationParamater);
}

void AnimatorController::AddFloatParamater(std::string name, float value = 0.0f)
{
	AnimationParamater* animationParamater = new AnimationParamater();
	animationParamater->name = name;
	animationParamater->type = AnimationParamater::Type::Float;
	animationParamater->floatValue = value;

	paramaters.push_back(animationParamater);
}

void AnimatorController::AddBoolParamater(std::string name, bool value = false)
{
	AnimationParamater* animationParamater = new AnimationParamater();
	animationParamater->name = name;
	animationParamater->type = AnimationParamater::Type::Bool;
	animationParamater->boolValue = value;

	paramaters.push_back(animationParamater);
}