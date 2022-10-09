#include "TransformRect.h"
#include "Transform.h"
#include "Debug.h"
#include "Transform.h"
#include "Vector3.h"
#include <sstream>
#include <iomanip>
#include "TextRect.h"
#include "TextBox.h"

TransformRect::TransformRect(float startX, float startY, Component* component) : ComponentRect(startX, startY, component, 3)
{
	//Position
	textRects.push_back(new TextRect(startX, startDrawY, "Position"));

	textRects.push_back(new TextRect(rightStartDrawX, startDrawY, "x:"));
	textBoxes.push_back(new TextBox(GetRightRectX(textRects.back()), startDrawY, textBoxWidth, FontManager::systemFont->GetFontHeight(), true, "", TextBox::InputType::Number));
	textRects.push_back(new TextRect(GetRightRectX(textBoxes.back()), startDrawY, "y:"));
	textBoxes.push_back(new TextBox(GetRightRectX(textRects.back()), startDrawY, textBoxWidth, FontManager::systemFont->GetFontHeight(), true, "", TextBox::InputType::Number));
	textRects.push_back(new TextRect(GetRightRectX(textBoxes.back()), startDrawY, "z:"));
	textBoxes.push_back(new TextBox(GetRightRectX(textRects.back()), startDrawY, textBoxWidth, FontManager::systemFont->GetFontHeight(), true, "", TextBox::InputType::Number));

	StartNewLine();	//改行

	//Rotation
	textRects.push_back(new TextRect(startX, startDrawY, "Rotation"));

	textRects.push_back(new TextRect(rightStartDrawX, startDrawY, "x:"));
	textBoxes.push_back(new TextBox(GetRightRectX(textRects.back()), startDrawY, textBoxWidth, FontManager::systemFont->GetFontHeight(), true, "", TextBox::InputType::Number));
	textRects.push_back(new TextRect(GetRightRectX(textBoxes.back()), startDrawY, "y:"));
	textBoxes.push_back(new TextBox(GetRightRectX(textRects.back()), startDrawY, textBoxWidth, FontManager::systemFont->GetFontHeight(), true, "", TextBox::InputType::Number));
	textRects.push_back(new TextRect(GetRightRectX(textBoxes.back()), startDrawY, "z:"));
	textBoxes.push_back(new TextBox(GetRightRectX(textRects.back()), startDrawY, textBoxWidth, FontManager::systemFont->GetFontHeight(), true, "", TextBox::InputType::Number));

	StartNewLine();	//改行

	//Scale
	textRects.push_back(new TextRect(startX, startDrawY, "Scale"));

	textRects.push_back(new TextRect(rightStartDrawX, startDrawY, "x:"));
	textBoxes.push_back(new TextBox(GetRightRectX(textRects.back()), startDrawY, textBoxWidth, FontManager::systemFont->GetFontHeight(), true, "", TextBox::InputType::Number));
	textRects.push_back(new TextRect(GetRightRectX(textBoxes.back()), startDrawY, "y:"));
	textBoxes.push_back(new TextBox(GetRightRectX(textRects.back()), startDrawY, textBoxWidth, FontManager::systemFont->GetFontHeight(), true, "", TextBox::InputType::Number));
	textRects.push_back(new TextRect(GetRightRectX(textBoxes.back()), startDrawY, "z:"));
	textBoxes.push_back(new TextBox(GetRightRectX(textRects.back()), startDrawY, textBoxWidth, FontManager::systemFont->GetFontHeight(), true, "", TextBox::InputType::Number));

	Transform* transform = static_cast<Transform*>(component);
	for (int i = 0; i < 9; i++) {
		int j = i / 3;
		switch (j) {
			case 0:
				textBoxes[i]->pushEnterEvents.push_back(std::make_pair(1, [this, transform, j]() {
					try {
						Vector3 pos = Vector3(stof(textBoxes[3 * j]->GetText()), stof(textBoxes[3 * j + 1]->GetText()), stof(textBoxes[3 * j + 2]->GetText()));
						transform->localPosition = pos;
					}
					catch (const std::invalid_argument& e) {
						Debug::Log("数字ではありません。");
					}
				}));
				break;
			case 1:
				textBoxes[i]->pushEnterEvents.push_back(std::make_pair(1, [this, transform, j]() {
					try {
						Vector3 rote = Vector3(stof(textBoxes[3 * j]->GetText()), stof(textBoxes[3 * j + 1]->GetText()), stof(textBoxes[3 * j + 2]->GetText()));
						transform->localRotation = rote;
					}
					catch (const std::invalid_argument& e) {
						Debug::Log("数字ではありません。");
					}
				}));
				break;
			case 2:
				textBoxes[i]->pushEnterEvents.push_back(std::make_pair(1, [this, transform, j]() {
					try {
						Vector3 scale = Vector3(stof(textBoxes[3 * j]->GetText()), stof(textBoxes[3 * j + 1]->GetText()), stof(textBoxes[3 * j + 2]->GetText()));
						transform->localScale = scale;
					}
					catch (const std::invalid_argument& e) {
						Debug::Log("数字ではありません。");
					}
				}));
				break;
			default:
				break;
		}
	}
}

void TransformRect::Update()
{
	Transform* transform = static_cast<Transform*>(component);	//キャスト変換

	stringstream ss;

	float value[9] = {};
	Vector3 position = transform->localPosition;
	value[0] = position.x;
	value[1] = position.y;
	value[2] = position.z;
	Vector3 rotation = transform->localRotation;
	value[3] = rotation.x;
	value[4] = rotation.y;
	value[5] = rotation.z;
	Vector3 scale = transform->localScale;
	value[6] = scale.x;
	value[7] = scale.y;
	value[8] = scale.z;

	for (int i = 0; i < 9; i++) {
		stringstream ss;
		ss << std::fixed << std::setprecision(2) << value[i];
		textBoxes[i]->SetText(ss.str());
	}
}

void TransformRect::Draw()
{
	ComponentRect::Draw();	//最初に名前描画

	//テキスト描画
	for (TextRect* textRect : textRects) {
		textRect->Draw();
	}
	//テキストボックス描画
	for (TextBox* textBox : textBoxes) {
		textBox->Draw();
	}
}

void TransformRect::RemoveAllTriggerRect()
{
	//テキストボックス削除
	for (TextBox* textBox : textBoxes) {
		WindowManager::RemoveTriggerRect(textBox);
	}
}
