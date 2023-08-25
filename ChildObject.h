#pragma once
#include "Engine/GameObject.h"

class Fbx;

class ChildObject :
    public GameObject
{
    Fbx* pFbx;
    int hModel_;
public:
    //�R���X�g���N�^
    ChildObject(GameObject* parent);

    //�f�X�g���N�^
    ~ChildObject();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

   
};

