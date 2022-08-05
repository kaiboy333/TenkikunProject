#pragma once

#include <iostream>
#include <vector>
#include "GameObject.h"
#include "Camera.h"
#include "ImageRenderer.h"
#include "WindowManager.h"
#include "Window.h"

class TreeList;
class Scene : public SceneInfo
{
	public:
		std::vector<GameObject*> gameobjects;	//GameObjectたち

		TreeList* treeList = nullptr;

		std::filesystem::path scenePath;

		//std::vector<function<void()>> addAndRemoveEvents;	//追加、削除の関数をいれる

		void Init();

		void Update();

		void Draw();

		GameObject* CreateEmpty();	//空のゲームオブジェクトを作成
		GameObject* CreateSquare();	//四角い画像のゲームオブジェクトを作成
		GameObject* CreateCircle();	//円の画像のゲームオブジェクトを作成
		GameObject* CreateCamera();	//カメラゲームオブジェクトを作成
		GameObject* CreateTenkikun();	//天気くんの画像のゲームオブジェクトを作成
		GameObject* CreateUnityChan();	//アニメーションがついたUnityちゃんのゲームオブジェクト作成

		void Destroy(GameObject* gameobject);	//指定のGameObjectを削除

		void SetNowCamera(Camera* camera);	//カメラをセット
		Camera* GetNowCamera();	//カメラを取得

		void AddCamera(Camera* camera);	//カメラを追加

		std::vector<Camera*> GetCameras();

		std::string GetName();
		void SetName(std::string name, bool isForce);	//名前を変える(強制でその名前にする)

	private:
		std::string name = "";	//Sceneの名前

		Camera* nowCamera = nullptr;

		std::vector<Camera*> cameras;	//Cameraたち
};

