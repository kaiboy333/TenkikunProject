#include "RigidBodyRect.h"
#include "RigidBody.h"
#include "Debug.h"

RigidBodyRect::RigidBodyRect(float startX, float startY, Component* component) : ComponentRect(startX, startY, component, 7)
{
	//bodyType
	textRects.push_back(new TextRect(startX, startDrawY, "BodyType"));
	textBoxes.push_back(new TextBox(GetRightRectX(textRects.back()), startDrawY, textBoxWidth, FontManager::systemFont->GetFontHeight(), true, "", TextBox::InputType::Enum, { "Dynamic", "Static" }));

	StartNewLine();	//改行

	//gravityScale
	textRects.push_back(new TextRect(startX, startDrawY, "GravityScale"));
	textBoxes.push_back(new TextBox(GetRightRectX(textRects.back()), startDrawY, textBoxWidth, FontManager::systemFont->GetFontHeight(), true, "", TextBox::InputType::Number));

	StartNewLine();	//改行

	//mass
	textRects.push_back(new TextRect(startX, startDrawY, "Mass"));
	textBoxes.push_back(new TextBox(GetRightRectX(textRects.back()), startDrawY, textBoxWidth, FontManager::systemFont->GetFontHeight(), true, "", TextBox::InputType::Number));

	StartNewLine();	//改行

	//restritution
	textRects.push_back(new TextRect(startX, startDrawY, "Restritution"));
	textBoxes.push_back(new TextBox(GetRightRectX(textRects.back()), startDrawY, textBoxWidth, FontManager::systemFont->GetFontHeight(), true, "", TextBox::InputType::Number));

	StartNewLine();	//改行

	//friction
	textRects.push_back(new TextRect(startX, startDrawY, "Friction"));
	textBoxes.push_back(new TextBox(GetRightRectX(textRects.back()), startDrawY, textBoxWidth, FontManager::systemFont->GetFontHeight(), true, "", TextBox::InputType::Number));

	StartNewLine();	//改行

	//velocity
	textRects.push_back(new TextRect(startX, startDrawY, "Velocity"));

	textRects.push_back(new TextRect(rightStartDrawX, startDrawY, "x:"));
	textBoxes.push_back(new TextBox(GetRightRectX(textRects.back()), startDrawY, textBoxWidth, FontManager::systemFont->GetFontHeight(), true, "", TextBox::InputType::Number));
	textRects.push_back(new TextRect(GetRightRectX(textBoxes.back()), startDrawY, "y:"));
	textBoxes.push_back(new TextBox(GetRightRectX(textRects.back()), startDrawY, textBoxWidth, FontManager::systemFont->GetFontHeight(), true, "", TextBox::InputType::Number));
	textRects.push_back(new TextRect(GetRightRectX(textBoxes.back()), startDrawY, "z:"));
	textBoxes.push_back(new TextBox(GetRightRectX(textRects.back()), startDrawY, textBoxWidth, FontManager::systemFont->GetFontHeight(), true, "", TextBox::InputType::Number));

	StartNewLine();	//改行

	//angularVelocity
	textRects.push_back(new TextRect(startX, startDrawY, "AngularVelocity"));

	textRects.push_back(new TextRect(rightStartDrawX, startDrawY, "x:"));
	textBoxes.push_back(new TextBox(GetRightRectX(textRects.back()), startDrawY, textBoxWidth, FontManager::systemFont->GetFontHeight(), true, "", TextBox::InputType::Number));
	textRects.push_back(new TextRect(GetRightRectX(textBoxes.back()), startDrawY, "y:"));
	textBoxes.push_back(new TextBox(GetRightRectX(textRects.back()), startDrawY, textBoxWidth, FontManager::systemFont->GetFontHeight(), true, "", TextBox::InputType::Number));
	textRects.push_back(new TextRect(GetRightRectX(textBoxes.back()), startDrawY, "z:"));
	textBoxes.push_back(new TextBox(GetRightRectX(textRects.back()), startDrawY, textBoxWidth, FontManager::systemFont->GetFontHeight(), true, "", TextBox::InputType::Number));


	RigidBody* rigidBody = static_cast<RigidBody*>(component);

	int i = 0;
	for (i = 0; i < 5; i++) {

		switch (i) {
			case 0:
				//bodyTypeのenumChoices
				for (int j = 0, len = (int)textBoxes[i]->enumChoices.size(); j < len; j++) {
					auto enumChoice = textBoxes[i]->enumChoices[j];
					//choiceへマウスをクリックしたら
					enumChoice->mouseClickDownEvents.push_back(std::make_pair(enumChoice->GetEventNo(), [enumChoice, this, i, rigidBody]() {
						try {
							auto text = textBoxes[i]->GetText();
							//何番目かを取得
							int index = stoi(text);
							//セット
							rigidBody->bodyType = static_cast<RigidBody::BodyType>(index);
						}
						catch (const std::invalid_argument& e) {
							//Debug::Log("数字ではありません。");
						}
					}));
				}
				break;
			case 1:
				//gravityScale
				textBoxes[i]->pushEnterEvents.push_back(std::make_pair(textBoxes[i]->GetEventNo(), [this, rigidBody, i]() {
					//textが変わったなら
					if (textBoxes[i]->IsTextChange()) {
						try {
							rigidBody->gravityScale = stof(textBoxes[i]->GetText());
						}
						catch (const std::invalid_argument& e) {
							Debug::Log("数字ではありません。");
						}
					}
				}));
				break;
			case 2:
				//mass
				textBoxes[i]->pushEnterEvents.push_back(std::make_pair(textBoxes[i]->GetEventNo(), [this, rigidBody, i]() {
					//textが変わったなら
					if (textBoxes[i]->IsTextChange()) {
						try {
							rigidBody->mass = stof(textBoxes[i]->GetText());
						}
						catch (const std::invalid_argument& e) {
							Debug::Log("数字ではありません。");
						}
					}
				}));
				break;
			case 3:
				//restritution
				textBoxes[i]->pushEnterEvents.push_back(std::make_pair(textBoxes[i]->GetEventNo(), [this, rigidBody, i]() {
					//textが変わったなら
					if (textBoxes[i]->IsTextChange()) {
						try {
							rigidBody->restritution = stof(textBoxes[i]->GetText());
						}
						catch (const std::invalid_argument& e) {
							Debug::Log("数字ではありません。");
						}
					}
				}));
				break;
			case 4:
				//friction
				textBoxes[i]->pushEnterEvents.push_back(std::make_pair(textBoxes[i]->GetEventNo(), [this, rigidBody, i]() {
					//textが変わったなら
					if (textBoxes[i]->IsTextChange()) {
						try {
							rigidBody->friction = stof(textBoxes[i]->GetText());
						}
						catch (const std::invalid_argument& e) {
							Debug::Log("数字ではありません。");
						}
					}
				}));
				break;
			default:
				break;
		}
	}

	for (int k = i; k < 6 + i; k++) {
		//変えられないようにする
		textBoxes[k]->canChange = false;
	}
}

void RigidBodyRect::Update()
{
	RigidBody* rigidBody = static_cast<RigidBody*>(component);	//キャスト変換

	stringstream ss;

	float value[11] = {};
	value[0] = static_cast<float>(rigidBody->bodyType);
	value[1] = rigidBody->gravityScale;
	value[2] = rigidBody->mass;
	value[3] = rigidBody->restritution;
	value[4] = rigidBody->friction;
	Vector3 velocity = rigidBody->velocity;
	value[5] = velocity.x;
	value[6] = velocity.y;
	value[7] = velocity.z;
	Vector3 angularVelocity = rigidBody->angularVelocity;
	value[8] = angularVelocity.x;
	value[9] = angularVelocity.y;
	value[10] = angularVelocity.z;

	for (int i = 0; i < 11; i++) {
		stringstream ss;
		ss << std::fixed << std::setprecision(2) << value[i];
		textBoxes[i]->SetText(ss.str());
	}
}

void RigidBodyRect::PreparationLibrate()
{
	//自身の解放準備
	ComponentRect::PreparationLibrate();
}
