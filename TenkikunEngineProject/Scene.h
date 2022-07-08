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
		std::string sceneName = "Scene1";	//Sceneの名前
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

		//void RemoveGameObject(GameObject* gameobject);	//指定のGameObjectをリストから削除

		Camera* GetNowCamera();

		void WriteToSceneFile();	//現在のシーンの情報をシーンファイルに書き込む

	private:
		int drawCameraNo = 0;
};

