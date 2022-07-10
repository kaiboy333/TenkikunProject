#pragma once

#include <iostream>
#include <vector>
#include "GameObject.h"
#include "Camera.h"
#include "ImageRenderer.h"
#include "WindowManager.h"
#include "Window.h"

class TreeList;
class Scene
{
	public:
		std::vector<GameObject*> gameobjects;	//GameObjectたち
		std::vector<Camera*> cameras;	//Cameraたち

		TreeList* treeList = nullptr;

		int generateNum = 0;

		std::filesystem::path scenePath;	//シーンファイルパス

		Scene();

		void Init();

		void Update();

		void Draw(Window* parentWindow);

		GameObject* CreateEmpty();	//空のゲームオブジェクトを作成
		GameObject* CreateSquare();	//四角い画像のゲームオブジェクトを作成
		GameObject* CreateCamera();	//カメラゲームオブジェクトを作成

		void Destroy(GameObject* gameobject);	//指定のGameObjectを削除

		Camera* GetNowCamera();

		std::string GetName();
		void SetName(std::string name);

	private:
		std::string name = "";	//Sceneの名前

		int drawCameraNo = 0;
};

