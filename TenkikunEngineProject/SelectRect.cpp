#include "SelectRect.h"
#include "WindowManager.h"

SelectRect::SelectRect(float startX, float startY, float width, float height, std::vector<std::string> strs) : TriggerRect(startX, startY, width, height, 1)
{
	//strs�Z�b�g����TextButton�쐬
	SetStrs(strs);

	//�N���b�N������
	mouseClickDownEvents.push_back(std::make_pair(GetEventNo(), [this] {
		//���͒��ł͂Ȃ��Ȃ�
		if (!GetIsSelected()) {
			//�}�E�X���N���b�N������
			for (auto choice : choices) {
				//��������悤�ɂ���
				choice->isActive = true;
			}
			WindowManager::SetSelectedTriggerRect(this);	//���g��I��Ώۂɂ���
		}
	}));
}

void SelectRect::Draw()
{
	RECT beforeDrawRect;
	//�`��̈���L��
	GetDrawArea(&beforeDrawRect);

	//�L�����͈͓��Ȃ�
	if (activeRect) {
		//�`�搧��
		SetDrawArea((int)activeRect->startX, (int)activeRect->startY, (int)(activeRect->startX + activeRect->width), (int)(activeRect->startY + activeRect->height));
		//�}�E�X������Ă�����
		if (GetIsTopOn()) {
			//�l�p�̕`��
			DrawBoxAA(startX, startY, startX + width, startY + height, GetColor(200, 200, 200), TRUE);
		}
		DrawBoxAA(startX, startY, startX + width, startY + height, GetColor(0, 0, 0), FALSE);	//�g�̕`��

		//choice�̕�����`��
		DrawStringFToHandle(startX, startY, choices[nowNo]->GetText().c_str(), GetColor(0, 0, 0), FontManager::systemFont->GetFH());
		//�O��̕`��̈�ɖ߂�
		SetDrawArea(beforeDrawRect.left, beforeDrawRect.top, beforeDrawRect.right, beforeDrawRect.bottom);
	}

	for (auto choice : choices) {
		choice->Draw();
	}
}

void SelectRect::PreparationLibrate()
{
	//enumChoices�̉������
	for (auto choice : choices) {
		//�������
		choice->PreparationLibrate();
		//���
		delete(choice);
	}
	choices.clear();

	TriggerRect::PreparationLibrate();
}

void SelectRect::SetStrs(std::vector<std::string> strs)
{
	//���X�g���Z�b�g
	choices.clear();

	//TextButton�쐬
	for (int i = 0, len = (int)strs.size(); i < len; i++) {
		TextButton* choice = new TextButton(this->startX, this->startY + this->height * i, this->width, this->height, 2, strs[i]);
		//�}�E�X���N���b�N������
		choice->mouseClickDownEvents.push_back(std::make_pair(choice->GetEventNo(), [this, choice, i]() {
			//text�ɉ��Ԗڂ��������
			nowNo = i;
			//���g��I��Ώۂ���O��
			WindowManager::SetSelectedTriggerRect(nullptr);
			//���ׂĔ�\���ɂ���
			for (auto choice_t : choices) {
				//�������Ȃ��悤�ɂ���
				choice_t->isActive = false;
			}
		}));
		//�������Ȃ��悤�ɂ���
		choice->isActive = false;
		//���X�g�ɒǉ�
		choices.push_back(choice);
	}
}

int SelectRect::GetNo()
{
	return nowNo;
}
