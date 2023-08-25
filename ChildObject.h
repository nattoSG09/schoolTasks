#pragma once
#include "Engine/GameObject.h"

class Fbx;

class ChildObject :
    public GameObject
{
    Fbx* pFbx;
    int hModel_;
public:
    //コンストラクタ
    ChildObject(GameObject* parent);

    //デストラクタ
    ~ChildObject();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

   
};

