#pragma once

#include <iostream>
#include <vector>
#include "GameObject.h"
#include "Camera.h"
#include "ImageRenderer.h"

class Scene
{
	public:
		enum SceneState
		{
			EDIT,	//エンジンの編集時
			PLAY,	//Playモード
			STOP	//Playモードでの一時停止
		};

		std::string sceneName = "Scene1";	//Sceneの名前
		std::vector<GameObject*> gameobjects;	//GameObjectたち
		std::vector<Camera*> cameras;	//Cameraたち

		void Init();

		void Update();

		void Draw(Window* window);

		GameObject* CreateEmpty();	//空のゲームオブジェクトを作成
		GameObject* CreateSquare();	//四角い画像のゲームオブジェクトを作成
		GameObject* CreateCamera();	//カメラゲームオブジェクトを作成

		//void DestroyGameObject(GameObject* gameobject);	//指定のGameObjectを削除

		void RemoveGameObject(GameObject* gameobject);	//指定のGameObjectをリストから削除

		Camera* GetNowCamera();

	private:
		int drawCameraNo = 0;
};

