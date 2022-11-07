#include "SelectRect.h"
#include "WindowManager.h"

SelectRect::SelectRect(float startX, float startY, float width, float height, std::vector<std::string> strs) : TriggerRect(startX, startY, width, height, 1)
{
	//strsセットしてTextButton作成
	SetStrs(strs);

	//クリックしたら
	mouseClickDownEvents.push_back(std::make_pair(GetEventNo(), [this] {
		//入力中ではないなら
		if (!GetIsSelected()) {
			//マウスをクリックしたら
			for (auto choice : choices) {
				//反応するようにする
				choice->isActive = true;
			}
			WindowManager::SetSelectedTriggerRect(this);	//自身を選択対象にする
		}
	}));
}

void SelectRect::Draw()
{
	RECT beforeDrawRect;
	//描画領域を記憶
	GetDrawArea(&beforeDrawRect);

	//有効化範囲内なら
	if (activeRect) {
		//描画制限
		SetDrawArea((int)activeRect->startX, (int)activeRect->startY, (int)(activeRect->startX + activeRect->width), (int)(activeRect->startY + activeRect->height));
		//マウスが乗っていたら
		if (GetIsTopOn()) {
			//四角の描画
			DrawBoxAA(startX, startY, startX + width, startY + height, GetColor(200, 200, 200), TRUE);
		}
		DrawBoxAA(startX, startY, startX + width, startY + height, GetColor(0, 0, 0), FALSE);	//枠の描画

		//choiceの文字列描画
		DrawStringFToHandle(startX, startY, choices[nowNo]->GetText().c_str(), GetColor(0, 0, 0), FontManager::systemFont->GetFH());
		//前回の描画領域に戻す
		SetDrawArea(beforeDrawRect.left, beforeDrawRect.top, beforeDrawRect.right, beforeDrawRect.bottom);
	}

	for (auto choice : choices) {
		choice->Draw();
	}
}

void SelectRect::PreparationLibrate()
{
	//enumChoicesの解放準備
	for (auto choice : choices) {
		//解放準備
		choice->PreparationLibrate();
		//解放
		delete(choice);
	}
	choices.clear();

	TriggerRect::PreparationLibrate();
}

void SelectRect::SetStrs(std::vector<std::string> strs)
{
	//リストリセット
	choices.clear();

	//TextButton作成
	for (int i = 0, len = (int)strs.size(); i < len; i++) {
		TextButton* choice = new TextButton(this->startX, this->startY + this->height * i, this->width, this->height, 2, strs[i]);
		//マウスをクリックしたら
		choice->mouseClickDownEvents.push_back(std::make_pair(choice->GetEventNo(), [this, choice, i]() {
			//textに何番目かをいれる
			nowNo = i;
			//自身を選択対象から外す
			WindowManager::SetSelectedTriggerRect(nullptr);
			//すべて非表示にする
			for (auto choice_t : choices) {
				//反応しないようにする
				choice_t->isActive = false;
			}
		}));
		//反応しないようにする
		choice->isActive = false;
		//リストに追加
		choices.push_back(choice);
	}
}

int SelectRect::GetNo()
{
	return nowNo;
}
