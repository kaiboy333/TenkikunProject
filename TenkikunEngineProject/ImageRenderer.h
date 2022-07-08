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
		bool isFlipX = false;	//ถEฝ]ฉ
		bool isFlipY = false;	//ใบฝ]ฉ
		//bool isCameraAffected = true;	//Cameraฬฺฎลฉฆ๛ชฯํ้ฉ

		Image* image = nullptr;	//ๆ

		void Update() override;

		void Draw(Window* parentWindow, Camera* camera);	//ๆ๐`ๆ
};

