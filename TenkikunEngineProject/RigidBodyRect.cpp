#include "RigidBodyRect.h"
#include "RigidBody.h"
#include "Debug.h"
#include "ProjectFileManager.h"

RigidBodyRect::RigidBodyRect(float startX, float startY, Component* component) : ComponentRect(startX, startY, component, 9)
{
	//bodyType
	textRects.push_back(new TextRect(startX, startDrawY, "BodyType"));
	selectRects.push_back(new SelectRect(GetRightRectX(textRects.back()), startDrawY, textBoxWidth, FontManager::systemFont->GetFontHeight(), { "Dynamic", "Static" }));

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

	StartNewLine();	//改行

	//FreezePosition
	textRects.push_back(new TextRect(startX, startDrawY, "FreezePosition"));

	textRects.push_back(new TextRect(rightStartDrawX, startDrawY, "x:"));
	checkButtons.push_back(new CheckButton(GetRightRectX(textRects.back()), startDrawY, textBoxHeight, textBoxHeight, { static_cast<Image*>(ProjectFileManager::pathAndInfo[ProjectFileManager::resourceFilePath.string() + "\\NotCheck.png"]), static_cast<Image*>(ProjectFileManager::pathAndInfo[ProjectFileManager::resourceFilePath.string() + "\\Check.png"]) }));
	textRects.push_back(new TextRect(GetRightRectX(checkButtons.back()), startDrawY, "y:"));
	checkButtons.push_back(new CheckButton(GetRightRectX(textRects.back()), startDrawY, textBoxHeight, textBoxHeight, { static_cast<Image*>(ProjectFileManager::pathAndInfo[ProjectFileManager::resourceFilePath.string() + "\\NotCheck.png"]), static_cast<Image*>(ProjectFileManager::pathAndInfo[ProjectFileManager::resourceFilePath.string() + "\\Check.png"]) }));

	StartNewLine();	//改行

	//FreezeRotation
	textRects.push_back(new TextRect(startX, startDrawY, "FreezePosition"));

	textRects.push_back(new TextRect(rightStartDrawX, startDrawY, "z:"));
	checkButtons.push_back(new CheckButton(GetRightRectX(textRects.back()), startDrawY, textBoxHeight, textBoxHeight, { static_cast<Image*>(ProjectFileManager::pathAndInfo[ProjectFileManager::resourceFilePath.string() + "\\NotCheck.png"]), static_cast<Image*>(ProjectFileManager::pathAndInfo[ProjectFileManager::resourceFilePath.string() + "\\Check.png"]) }));


	RigidBody* rigidBody = static_cast<RigidBody*>(component);

	//bodyType
	selectRects[0]->mouseClickDownEvents.push_back(std::make_pair(selectRects[0]->GetEventNo(), [this, rigidBody]() {
		for (auto choice : selectRects[0]->choices) {
			//マウスをクリックしたら
			choice->mouseClickDownEvents.push_back(std::make_pair(choice->GetEventNo(), [this, rigidBody]() {
				rigidBody->bodyType = static_cast<RigidBody::BodyType>(selectRects[0]->GetNowNo());
			}));
		}
	}));

	int i = 0;
	for (i = 0; i < 4; i++) {

		switch (i) {
			case 0:
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
			case 1:
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
			case 2:
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
			case 3:
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

	for (int i = 0; i < 3; i++) {
		switch (i) {
			case 0:
				checkButtons[i]->onClickEvents.push_back(std::make_pair(checkButtons[i]->GetEventNo(), [this, i, rigidBody]() {
					rigidBody->constraints.freezePosition.x = checkButtons[i]->GetIsChecked();
				}));
				break;
			case 1:
				checkButtons[i]->onClickEvents.push_back(std::make_pair(checkButtons[i]->GetEventNo(), [this, i, rigidBody]() {
					rigidBody->constraints.freezePosition.y = checkButtons[i]->GetIsChecked();
				}));
				break;
			case 2:
				checkButtons[i]->onClickEvents.push_back(std::make_pair(checkButtons[i]->GetEventNo(), [this, i, rigidBody]() {
					rigidBody->constraints.freezeRotation.z = checkButtons[i]->GetIsChecked();
				}));
				break;
			default:
				break;
		}
	}
}

void RigidBodyRect::Update()
{
	RigidBody* rigidBody = static_cast<RigidBody*>(component);	//キャスト変換

	int value1 = static_cast<int>(rigidBody->bodyType);

	stringstream ss;
	selectRects[0]->SetNowNo(value1);

	float values2[10] = {};
	values2[0] = rigidBody->gravityScale;
	values2[1] = rigidBody->mass;
	values2[2] = rigidBody->restritution;
	values2[3] = rigidBody->friction;
	Vector3 velocity = rigidBody->velocity;
	values2[4] = velocity.x;
	values2[5] = velocity.y;
	values2[6] = velocity.z;
	Vector3 angularVelocity = rigidBody->angularVelocity;
	values2[7] = angularVelocity.x;
	values2[8] = angularVelocity.y;
	values2[9] = angularVelocity.z;

	for (int i = 0; i < 10; i++) {
		stringstream ss;
		ss << std::fixed << std::setprecision(2) << values2[i];
		textBoxes[i]->SetText(ss.str());
	}

	bool values3[3] = {};
	auto constraints = rigidBody->constraints;
	values3[0] = constraints.freezePosition.x;
	values3[1] = constraints.freezePosition.y;
	values3[2] = constraints.freezeRotation.z;

	for (int i = 0; i < 3; i++) {
		stringstream ss;
		checkButtons[i]->SetIsChecked(values3[i]);
	}
}

void RigidBodyRect::PreparationLibrate()
{
	//自身の解放準備
	ComponentRect::PreparationLibrate();
}
