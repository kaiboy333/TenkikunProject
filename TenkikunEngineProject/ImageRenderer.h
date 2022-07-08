#pragma once

#include "ImageManager.h"
#include "Component.h"
#include "Camera.h"
#include "Window.h"
#include "Image.h"

class Camera;
class ImageRenderer :  public Component
{
	public:
		bool isFlipX = false;	//���E���]��
		bool isFlipY = false;	//�㉺���]��
		//bool isCameraAffected = true;	//Camera�̈ړ��Ō��������ς�邩

		Image* image = nullptr;	//�摜

		void Update() override;

		void Draw(Window* parentWindow, Camera* camera);	//�摜��`��
};

