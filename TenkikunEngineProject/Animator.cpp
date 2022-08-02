#include "Animator.h"

Animator::Animator(GameObject* gameobject) : Component(gameobject)
{
	
}

void Animator::Update()
{
	//AnimationControllerの更新
	if (ac != nullptr) {
		//Animationの更新
		//ImageRendererの取得
		ImageRenderer* ir = gameobject->GetComponent<ImageRenderer>();
		//ImageRendererがあるのであれば
		if (ir != nullptr) {
			Animation* animation = nowState->animation;
			//要素があるなら
			if ((int)animation->animationKeys.size() != 0) {
				auto iter = animation->animationKeys.find((int)count);
				//見つかったら
				if (iter != animation->animationKeys.end()) {
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
							return;
						}
						else {
							count = (float)lastCount;	//最後のカウントにする
						}
					}
				}
				count += 1 * nowState->speed;			//時間の更新
			}
		}

		//Transitionの更新
		for (AnimationTransition* transition : nowState->transitions) {
			//もし次の場所に行くのなら
			if (transition->canTransition(this)) {
				nowState = transition->toState;	//AnimationControllerのnowStateを次のさすStateにする
				count = 0;	//カウンタリセット
				break;	//終わり(他のは見ない)
			}
		}
	}
}

AnimationState* Animator::AddState(Animation* animation, std::string stateName)
{
	AnimationState* state = new AnimationState();	//Stateを作成
	//state->ac = animator->GetAnimatorController();	//StateにAnimationControllerをセット
	state->name = stateName;	//nameセット
	state->animation = animation;	//StateにAnimationをセット
	ac->states.emplace_back(state);	//Stateをリストに追加
	//最初の場所がnullなら
	if (nowState == nullptr) {
		nowState = state;	//追加
		//ImageRendererを取得
		ImageRenderer* imageRenderer = gameobject->GetComponent<ImageRenderer>();
		//animationKeyの最初の画像をImageに設定
		imageRenderer->image = animation->animationKeys.begin()->second;
	}
	return state;	//返す
}
