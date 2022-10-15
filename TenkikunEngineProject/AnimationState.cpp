#include "AnimationState.h"
#include <algorithm>

AnimationTransition* AnimationState::AddTransition(AnimationState* toState)
{
	AnimationTransition* transition = new AnimationTransition();	//Transition作成
	//transition->ac = ac;
	transition->fromState = this;
	transition->toState = toState;
	transitions.emplace_back(transition);	//リストに追加
	return transition;
}

void AnimationState::PreparationLibrate()
{
	animation = nullptr;

	transitions.clear();
}

//AnimationState::AnimationState()
//{
//}
//
//AnimationState::AnimationState(const AnimationState& state)
//{
//	//name
//	this->name = state.name;
//
//	//animation
//	this->animation = new Animation(*state.animation);
//
//	//speed
//	this->speed = state.speed;
//
//	//count
//	this->count = state.count;
//}

void AnimationState::Update(Animator* animator)
{
	////Animationの更新
	////ImageRendererの取得
	//ImageRenderer* ir = animator->gameobject->GetComponent<ImageRenderer>();
	////ImageRendererがあるのであれば
	//if (ir != nullptr) {
	//	auto iter = animation->animationKeys.find((int)count);
	//	//見つかったら
	//	if (iter != animation->animationKeys.end()) {
	//		Image* image = iter->second;
	//		int gh = image->GetGH();
	//		ir->image = image;	//新しい画像をセット
	//	}
	//	//無かったら
	//	else {
	//		iter--;	//最後の要素を見る
	//		//もし、今見ているのが最後の場所だったら(最後のフレームを過ぎていたら)
	//		int lastCount;
	//		if ((lastCount = iter->first) <= (int)count) {
	//			//繰り返しアニメーションを動かすなら
	//			if (animation->isLoop) {
	//				count = 0;	//カウンタリセット
	//			}
	//			else {
	//				count = (float)lastCount;	//最後のカウントにする
	//			}
	//		}
	//	}
	//	count += 1 * speed;			//時間の更新
	//}

	////Transitionの更新
	//for (AnimationTransition* transition : transitions) {
	//	//もし次の場所に行くのなら
	//	if (transition->canTransition(animator)) {
	//		animator->ac->nowState = transition->toState;	//AnimationControllerのnowStateを次のさすStateにする
	//		count = 0;	//カウンタリセット
	//		break;	//終わり(他のは見ない)
	//	}
	//}
}
