#include "SceneManager.h"
#include "Model.h"

#include "../TestScene.h"

SceneManager::SceneManager(GameObject* parent)
	:GameObject(parent,"SceneManager"),currentSceneID_(SCENE_ID_TEST),nextSceneID_(SCENE_ID_TEST)
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::Initialize()
{
	currentSceneID_ = SCENE_ID_TEST;
	nextSceneID_ = currentSceneID_;
	Instantiate<TestScene>(this);
}

void SceneManager::Update()
{
	//シーンを切り替える
	//現在のシーンとネクストシーンが別だった場合に
	if (currentSceneID_ != nextSceneID_) 
	{
		currentSceneID_ = nextSceneID_;

		//現在のシーンインスタンスを削除
		auto scene = childList_.begin();
		(*scene)->ReleaseSub();
		SAFE_DELETE(*scene);
		childList_.clear();
		Model::Release();

		//新しいシーンの準備
		switch (nextSceneID_)
		{
		case SCENE_ID_TEST:Instantiate<TestScene>(this); break;
		}
	}
	currentSceneID_ = nextSceneID_;
}

void SceneManager::Draw()
{
}

void SceneManager::Release()
{
}

void SceneManager::ChangeScene(SCENE_ID _next)
{
	nextSceneID_ = _next; 
}
