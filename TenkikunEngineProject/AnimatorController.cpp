#include "AnimatorController.h"

void AnimatorController::Update()
{
	//Stateの更新
	if (nowState != nullptr) {
		nowState->Update();
	}
}

AnimationState* AnimatorController::AddAnimation(Animation* animation)
{
	AnimationState* state = new AnimationState(this);	//Stateを作成
	state->animation = animation;	//StateにAnimationをセット
	this->states.emplace_back(state);	//Stateをリストに追加
	//最初の場所がnullなら
	if (nowState == nullptr) {
		nowState = state;	//追加
	}
	return state;	//返す
}

void AnimatorController::AddIntParamater(std::string name, int value = 0)
{
	intParamaters.insert_or_assign(name, value);
}

void AnimatorController::AddFloatParamater(std::string name, float value = 0.0f)
{
	floatParamaters.insert_or_assign(name, value);
}

void AnimatorController::AddBoolParamater(std::string name, bool value = false)
{
	boolParamaters.insert_or_assign(name, value);
}