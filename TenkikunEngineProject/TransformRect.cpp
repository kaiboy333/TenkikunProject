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
	textBoxes.push_back(new TextBox(GetRightRectX(textRects.back()), startDrawY, textBoxWidth, (float)GetFontLineSpace()));
	textRects.push_back(new TextRect(GetRightRectX(textBoxes.back()), startDrawY, "y:"));
	textBoxes.push_back(new TextBox(GetRightRectX(textRects.back()), startDrawY, textBoxWidth, (float)GetFontLineSpace()));
	textRects.push_back(new TextRect(GetRightRectX(textBoxes.back()), startDrawY, "z:"));
	textBoxes.push_back(new TextBox(GetRightRectX(textRects.back()), startDrawY, textBoxWidth, (float)GetFontLineSpace()));

	StartNewLine();	//改行

	//Rotation
	textRects.push_back(new TextRect(startX, startDrawY, "Rotation"));

	textRects.push_back(new TextRect(rightStartDrawX, startDrawY, "x:"));
	textBoxes.push_back(new TextBox(GetRightRectX(textRects.back()), startDrawY, textBoxWidth, (float)GetFontLineSpace()));
	textRects.push_back(new TextRect(GetRightRectX(textBoxes.back()), startDrawY, "y:"));
	textBoxes.push_back(new TextBox(GetRightRectX(textRects.back()), startDrawY, textBoxWidth, (float)GetFontLineSpace()));
	textRects.push_back(new TextRect(GetRightRectX(textBoxes.back()), startDrawY, "z:"));
	textBoxes.push_back(new TextBox(GetRightRectX(textRects.back()), startDrawY, textBoxWidth, (float)GetFontLineSpace()));

	StartNewLine();	//改行

	//Scale
	textRects.push_back(new TextRect(startX, startDrawY, "Scale"));

	textRects.push_back(new TextRect(rightStartDrawX, startDrawY, "x:"));
	textBoxes.push_back(new TextBox(GetRightRectX(textRects.back()), startDrawY, textBoxWidth, (float)GetFontLineSpace()));
	textRects.push_back(new TextRect(GetRightRectX(textBoxes.back()), startDrawY, "y:"));
	textBoxes.push_back(new TextBox(GetRightRectX(textRects.back()), startDrawY, textBoxWidth, (float)GetFontLineSpace()));
	textRects.push_back(new TextRect(GetRightRectX(textBoxes.back()), startDrawY, "z:"));
	textBoxes.push_back(new TextBox(GetRightRectX(textRects.back()), startDrawY, textBoxWidth, (float)GetFontLineSpace()));

	Transform* transform = static_cast<Transform*>(component);
	textBoxes[0]->pushEnterEvents.push_back([this, transform]() {
		transform->position = Vector3(stof(textBoxes[0]->GetText()), stof(textBoxes[1]->GetText()), stof(textBoxes[2]->GetText()));
		});
	textBoxes[1]->pushEnterEvents.push_back([this, transform]() {
		transform->position = Vector3(stof(textBoxes[0]->GetText()), stof(textBoxes[1]->GetText()), stof(textBoxes[2]->GetText()));
		});
	textBoxes[2]->pushEnterEvents.push_back([this, transform]() {
		transform->position = Vector3(stof(textBoxes[0]->GetText()), stof(textBoxes[1]->GetText()), stof(textBoxes[2]->GetText()));
		});
	textBoxes[3]->pushEnterEvents.push_back([this, transform]() {
		transform->rotation = Vector3(stof(textBoxes[3]->GetText()), stof(textBoxes[4]->GetText()), stof(textBoxes[5]->GetText()));
		});
	textBoxes[4]->pushEnterEvents.push_back([this, transform]() {
		transform->rotation = Vector3(stof(textBoxes[3]->GetText()), stof(textBoxes[4]->GetText()), stof(textBoxes[5]->GetText()));
		});
	textBoxes[5]->pushEnterEvents.push_back([this, transform]() {
		transform->rotation = Vector3(stof(textBoxes[3]->GetText()), stof(textBoxes[4]->GetText()), stof(textBoxes[5]->GetText()));
		});
	textBoxes[6]->pushEnterEvents.push_back([this, transform]() {
		transform->scale = Vector3(stof(textBoxes[6]->GetText()), stof(textBoxes[7]->GetText()), stof(textBoxes[8]->GetText()));
		});
	textBoxes[7]->pushEnterEvents.push_back([this, transform]() {
		transform->scale = Vector3(stof(textBoxes[6]->GetText()), stof(textBoxes[7]->GetText()), stof(textBoxes[8]->GetText()));
		});
	textBoxes[8]->pushEnterEvents.push_back([this, transform]() {
		transform->scale = Vector3(stof(textBoxes[6]->GetText()), stof(textBoxes[7]->GetText()), stof(textBoxes[8]->GetText()));
		});
	//catch (const invalid_argument& e) {

	//}
}

void TransformRect::Update()
{
	Transform* transform = static_cast<Transform*>(component);	//キャスト変換

	stringstream ss;

	float value[9] = {};
	Vector3 position = transform->position;
	value[0] = position.x;
	value[1] = position.y;
	value[2] = position.z;
	Vector3 rotation = transform->rotation;
	value[3] = rotation.x;
	value[4] = rotation.y;
	value[5] = rotation.z;
	Vector3 scale = transform->scale;
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
