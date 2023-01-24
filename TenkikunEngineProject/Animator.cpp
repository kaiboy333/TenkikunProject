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
				auto iter = animation->animationKeys.begin();
				for (int i = 0; i < index; i++) {
					iter++;
				}
				//カウントが指定のカウントより超えているなら
				if ((*iter).first <= (int)count) {
					//最後の要素なら
					if ((int)animation->animationKeys.size() - 1 == index) {
						//繰り返しアニメーションを動かすなら
						if (animation->isLoop) {
							count = 0;	//カウンタリセット
							index = 0;
						}
						else {
							count = (float)((*iter).first);	//最後のカウントにする
						}
						return;
					}
					Image* image = iter->second;
					int gh = image->GetGH();
					ir->image = image;	//新しい画像をセット
					index++;	//次の要素へ
				}
				////無かったら
				//else {
				//	iter--;	//最後の要素を見る
				//	//もし、今見ているのが最後の場所だったら(最後のフレームを過ぎていたら)
				//	int lastCount;
				//	if ((lastCount = iter->first) <= (int)count) {
				//	}
				//}
				count += nowState->speed;			//時間の更新
			}
		}

		//Transitionの更新
		for (AnimationTransition* transition : nowState->transitions) {
			//もし次の場所に行くのなら
			if (transition->canTransition(this)) {
				nowState = transition->toState;	//AnimationControllerのnowStateを次のさすStateにする
				count = 0;	//カウンタリセット
				index = 0;
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

void Animator::PreparationLibrate()
{
	ac = nullptr;
	nowState = nullptr;

	//自身の解放準備
	Component::PreparationLibrate();
}
