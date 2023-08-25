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
	//�V�[����؂�ւ���
	//���݂̃V�[���ƃl�N�X�g�V�[�����ʂ������ꍇ��
	if (currentSceneID_ != nextSceneID_) 
	{
		currentSceneID_ = nextSceneID_;

		//���݂̃V�[���C���X�^���X���폜
		auto scene = childList_.begin();
		(*scene)->ReleaseSub();
		SAFE_DELETE(*scene);
		childList_.clear();
		Model::Release();

		//�V�����V�[���̏���
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
