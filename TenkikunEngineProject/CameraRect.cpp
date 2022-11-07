#include "CameraRect.h"
#include "Debug.h"

CameraRect::CameraRect(float startX, float startY, Component* component) : ComponentRect(startX, startY, component, 1)
{
	Camera* camera = static_cast<Camera*>(component);

	//zoom
	textRects.push_back(new TextRect(startX, startDrawY, "Zoom"));
	textBoxes.push_back(new TextBox(GetRightRectX(textRects.back()), startDrawY, textBoxWidth, FontManager::systemFont->GetFontHeight(), true, "", TextBox::InputType::Number));

	//zoom
	textBoxes[0]->pushEnterEvents.push_back(std::make_pair(textBoxes[0]->GetEventNo(), [this, camera]() {
		//textが変わったなら
		if (textBoxes[0]->IsTextChange()) {
			try {
				camera->zoom = stof(textBoxes[0]->GetText());
			}
			catch (const std::invalid_argument& e) {
				Debug::Log("数字ではありません。");
			}
		}
	}));
}

void CameraRect::Update()
{
	Camera* camera = static_cast<Camera*>(component);	//キャスト変換

	stringstream ss;

	float value[1] = {};
	value[0] = camera->zoom;

	for (int i = 0; i < 1; i++) {
		stringstream ss;
		ss << std::fixed << std::setprecision(2) << value[i];
		textBoxes[i]->SetText(ss.str());
	}
}

void CameraRect::PreparationLibrate()
{
	ComponentRect::PreparationLibrate();
}
