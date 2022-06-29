#include "AnimationState.h"
#include "IntCondition.h"
#include <algorithm>

AnimationTransition* AnimationState::AddTransition(AnimationState* toState)
{
	AnimationTransition* transition = new AnimationTransition(this, toState, ac);	//Transition作成
	transitions.emplace_back(transition);	//リストに追加
	return transition;
}

AnimationState::AnimationState(AnimatorController* ac)
{
	this->ac = ac;
}

void AnimationState::Update()
{
	//Animationの更新
	//アニメーションコントローラーにアニメーターが紐づいていれば
	if (ac->animator != nullptr) {
		ImageRenderer* ir = ac->animator->gameobject->GetComponent<ImageRenderer>();	//ImageRenderer取得
		//ImageRendererがあるのであれば
		if (ir != nullptr) {
			auto iter = animation->frameAndImages.find((int)count);
			//見つかったら
			if (iter != animation->frameAndImages.end()) {
				Image* image = iter->second;
				int gh = image->GetGH();
				ir->image = image;	//新しい画像をセット
			}
			//無かったら
			else {
				iter--;	//最後の要素を見る
				//もし、今見ているのが最後の場所だったら(最後のフレームを過ぎていたら)
				int lastCount;
				if ((lastCount = iter->first) <= (int)count) {
					//繰り返しアニメーションを動かすなら
					if (animation->isLoop) {
						count = 0;	//カウンタリセット
					}
					else {
						count = (float)lastCount;	//最後のカウントにする
					}
				}
			}
			count += 1 * speed;			//時間の更新
		}
	}

	//Transitionの更新
	for (AnimationTransition* transition : transitions) {
		//もし次の場所に行くのなら
		if (transition->canTransition()) {
			ac->nowState = transition->toState;	//AnimationControllerのnowStateを次のさすStateにする
			count = 0;	//カウンタリセット
			break;	//終わり(他のは見ない)
		}
	}
}
