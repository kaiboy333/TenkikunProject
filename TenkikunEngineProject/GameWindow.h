#pragma once

#include "Window.h"
#include "Scene.h"
#include "Camera.h"

class Scene;
class Camera;
class GameWindow :  public Window
{
	public:
		GameWindow();

		virtual void Update() override;	//Scene更新
		virtual void Draw() override;	//Scene上のGameObjectを描画
};

