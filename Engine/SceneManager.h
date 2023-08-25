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

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

    /// <summary>
    /// シーンを切り替える
    /// </summary>
    /// <param name="_next">切り替え先のID</param>
    void ChangeScene(SCENE_ID _next);
    void SceneMove() { this->currentSceneID_ = this->nextSceneID_; }
};

