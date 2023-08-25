#include "TestScene.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"

TestScene::TestScene(GameObject* parent)
	:GameObject(parent,"TestScene")
{
}

void TestScene::Initialize()
{
}

void TestScene::Update()
{
	if (Input::IsKeyDown(DIK_SPACE)) {
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_PLAY);
	}
}

void TestScene::Draw()
{
}

void TestScene::Release()
{
}
