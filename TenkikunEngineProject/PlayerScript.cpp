#include "PlayerScript.h"
#include "AnimationState.h"
#include "Input.h"

void PlayerScript::ScriptStart()
{
	ImageRenderer* imageRenderer = gameobject->AddComponent<ImageRenderer>();
	//�A�j���[�V�����̍쐬
	Animator* animator = gameobject->AddComponent<Animator>();
	AnimatorController* ac = new AnimatorController();
	animator->SetAnimationController(ac);	//Animator��ac���Z�b�g
	ac->AddFloatParamater("isSpeed", 0.0f);

	//�ҋ@�A�j���[�V�����̃Z�b�g
	//�ҋ@�摜�̍쐬
	std::vector<Image*> idleImages;
	for (int i = 0; i < 3; i++) {
		std::stringstream ss;
		ss << "image/" << "UnityChan_Idle" << i << ".png";
		idleImages.emplace_back(new Image(ss.str()));	//Image��ǉ�
	}
	//�ҋ@�A�j���[�V�����̍쐬
	Animation* idleAnim = new Animation(idleImages, 7);
	//ac�ɃA�j���[�V�������Z�b�g����State���擾
	AnimationState* idleState = ac->AddAnimation(idleAnim);

	//����A�j���[�V�����̃Z�b�g
	//����摜�̍쐬
	std::vector<Image*> runImages;
	for (int i = 0; i < 8; i++) {
		std::stringstream ss;
		ss << "image/" << "UnityChan_Run" << i << ".png";
		runImages.emplace_back(new Image(ss.str()));	//Image��ǉ�
	}
	//����A�j���[�V�����̍쐬
	Animation* runAnim = new Animation(runImages, 3);
	//ac�ɃA�j���[�V�������Z�b�g����State���擾
	AnimationState* runState = ac->AddAnimation(runAnim);

	//Transition�쐬
	//�ҋ@State��Transition�ǉ�
	AnimationTransition* idleToRun = idleState->AddTransition(runState);
	idleToRun->AddFloatCondition("isSpeed");
	idleToRun->ChangeFloatCondition("isSpeed", 1.0, 0);
	//����State��Transition�ǉ�
	AnimationTransition* runToIdle = runState->AddTransition(idleState);
	runToIdle->AddFloatCondition("isSpeed");
	runToIdle->ChangeFloatCondition("isSpeed", 1.0, 1);
}

void PlayerScript::ScriptUpdate()
{
	ImageRenderer* imageRenderer = gameobject->GetComponent<ImageRenderer>();

	Animator* animator = gameobject->GetComponent<Animator>();
	AnimatorController* ac = animator->GetAnimatorController();

	if (Input::GetKey(Input::KeyCode::D)) {
		gameobject->transform->localPosition += Vector3::Right() * speed;
		ac->AddFloatParamater("isSpeed", speed);
		imageRenderer->isFlipX = false;
	}
	else if (Input::GetKey(Input::KeyCode::A)) {
		gameobject->transform->localPosition += Vector3::Left() * speed;
		ac->AddFloatParamater("isSpeed", speed);
		imageRenderer->isFlipX = true;
	}
	else {
		ac->AddFloatParamater("isSpeed", 0.0f);
	}

	gameobject->transform->localRotation += Vector3::Forward() * 1.0f;
}

