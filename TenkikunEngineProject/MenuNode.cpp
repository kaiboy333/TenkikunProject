#include "MenuNode.h"
#include "FontManager.h"
#include "MenuList.h"
#include "ProjectFileManager.h"

MenuNode::MenuNode(float startX, float startY, std::string element) : TriggerRect(startX, startY, MenuList::WIDTH, FontManager::systemFont->GetFontHeight())
{
	//�摜���擾
	arrawImage = static_cast<Image*>(ProjectFileManager::pathAndInfo[ProjectFileManager::resourceFilePath.string() + "\\RightArrow.png"]);
	//���̕�������
	arrawWidth = height;
}

void MenuNode::Draw()
{
	//�l�p�̕`��(�h��Ԃ�)
	DrawBoxAA(startX, startY, startX + width, startY + height, GetColor(255, 255, 255), TRUE);
	//�l�p�̕`��(���̕`��)
	DrawBoxAA(startX, startY, startX + width, startY + height, GetColor(255, 255, 255), FALSE);

	//���j���[���X�g�������Ă���Ȃ�
	if (menuList) {
		//����`��
		if (arrawImage->GetGH()) {
			float drawCenterX = startX + width - arrawWidth / 2;
			float drawCenterY = startY + arrawWidth / 2;
			DrawRotaGraph3F(drawCenterX, drawCenterY, arrawImage->GetWidth() / 2, arrawImage->GetHeight() / 2, arrawWidth / arrawImage->GetWidth(), arrawWidth / arrawImage->GetHeight(), 0, arrawImage->GetGH(), TRUE);
		}
	}
}
