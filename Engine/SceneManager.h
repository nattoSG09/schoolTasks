#pragma once
#include "GameObject.h"
#define SAFE_DELETE(p) if(p != nullptr){ delete p; p = nullptr;}

enum SCENE_ID{
    SCENE_ID_TEST=0,
};

class SceneManager : public GameObject
{
public:
    SCENE_ID currentSceneID_;
    SCENE_ID nextSceneID_;

	SceneManager(GameObject* parent);
	~SceneManager();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

    /// <summary>
    /// �V�[����؂�ւ���
    /// </summary>
    /// <param name="_next">�؂�ւ����ID</param>
    void ChangeScene(SCENE_ID _next);
    void SceneMove() { this->currentSceneID_ = this->nextSceneID_; }
};

