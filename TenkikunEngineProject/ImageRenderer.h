#pragma once

#include "ImageManager.h"
#include "DrawComponent.h"
#include "Camera.h"
#include "Window.h"
#include "Image.h"

class Camera;
class Image;
class ImageRenderer :  public DrawComponent
{
	public:
		bool isFlipX = false;	//���E���]��
		bool isFlipY = false;	//�㉺���]��
		//bool isCameraAffected = true;	//Camera�̈ړ��Ō��������ς�邩

		Image* image = nullptr;	//�摜

		ImageRenderer(GameObject* gameobject);

		void Update() override;

		void Draw();	//�摜��`��
};

