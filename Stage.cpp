#include "Stage.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Camera.h"
#include "resource.h"

#include <string>
#include <fstream>
#include <sstream>

Stage::Stage(GameObject* parent)
    :GameObject(parent, "Stage")
{
    for (int i = 0; i < MAX; i++)hModel_[i] = -1;

    for (int x = 0; x < XSIZE; x++){
        for (int z = 0; z < ZSIZE; z++) {
            SetBlock(x, z,DEFAULT);
        }
    }
}

void Stage::Initialize()
{
    string modelFileName[MAX] = {
        "BoxDefault.fbx",
        "BoxBrick.fbx",
        "BoxGrass.fbx",
        "BoxSand.fbx",
        "BoxWater.fbx"
    };
    string FilePath = "Assets/MapEditor/";

    for (int i = 0; i < MAX; i++) {
        hModel_[i] = Model::Load(FilePath + modelFileName[i]);
        assert(hModel_[i] >= 0);
    }

    //table_�Ƀu���b�N�̃^�C�v���Z�b�g���Ă�낤
    for (int x = 0; x < XSIZE; x++) {
        for (int z = 0; z < ZSIZE; z++) {
            SetBlock(x, z, (x%MAX));
            //SetBlockHeight(x, z, (x%3+1));
        }
    }
}

void Stage::Update()
{
    //�ł��Ȃ��������
    {
        //if (!Input::IsMouseButtonDown(0))return;

        //float w = (float)Direct3D::scrWidth_ / 2.0f;
        //float h = (float)Direct3D::scrHeight_ / 2.0f;


        //XMMATRIX vp =
        //{
        //    w,0,0,0,
        //    0,-h,0,0,
        //    0,0,1,0,
        //    w,h,0,1
        //};

        ////�r���[�|�[�g�s��
        //XMMATRIX invVp = XMMatrixInverse(nullptr, vp);

        ////�v���W�F�N�V�����s��
        //XMMATRIX invProj = XMMatrixInverse(nullptr, Camera::GetProjectionMatrix());

        ////�r���[�ϊ�
        //XMMATRIX invView = XMMatrixInverse(nullptr, Camera::GetViewMatrix());

        ////�}�E�X���W(��O�A�����擾
        //XMFLOAT3 mousePosFront = Input::GetMousePosition();
        //mousePosFront.z = 0.0f;
        //XMFLOAT3 mousePosBack = Input::GetMousePosition();
        //mousePosBack.z = 1.0f;

        ////�@ mousePosFront���x�N�g���ɕϊ�
        ////�A �@��invVP,invPrj,invView��������
        //XMVECTOR vMPF = XMVector3Transform(XMLoadFloat3(&mousePosFront), invVp * invProj * invView);

        ////�B mousePosBack���x�N�g���ɕϊ�
        ////�C �B��invVP,invPrj,invView��������
        //XMVECTOR vMPB = XMVector3Transform(XMLoadFloat3(&mousePosBack), invVp * invProj * invView);

        ////table_��̃��f�����ׂĂƂ̃��C�L���X�g������s��
        //for (int x = 0; x < 15; x++) {
        //    for (int z = 0; z < 15; z++) {
        //        for (int y = 0; y < table_[x][z].height_ + 1; y++) {
        //            RayCastData data;
        //            XMStoreFloat3(&data.start, vMPF);
        //            XMStoreFloat3(&data.dir, XMVector3Normalize(vMPB - vMPF));
        //            Transform t;
        //            t.position_ = { (float)x,(float)y,(float)z };
        //            Model::SetTransform(hModel_[0], t);
        //            Model::RayCast(hModel_[0], data);
        //            if (data.hit) {
        //                table_[x][z].height_++;
        //                break;
        //            }
        //        }
        //    }
        //}
    }
    
    
    if (!Input::IsMouseButtonDown(0)) {
        return;
    }
    float w = (float)(Direct3D::scrWidth_ / 2.0f);
    float h = (float)(Direct3D::scrHeight_ / 2.0f);
    //Offsetx,y ��0
    //minZ =0 maxZ = 1

    XMMATRIX vp =
    {
         w,  0,  0, 0,
         0, -h,  0, 0,
         0,  0,  1, 0,
         w,  h,  0, 1
    };

    //�r���[�|�[�g
    XMMATRIX invVP = XMMatrixInverse(nullptr, vp);

    //�v���W�F�N�V�����ϊ�
    XMMATRIX invProj = XMMatrixInverse(nullptr, Camera::GetProjectionMatrix());
    
    //�r���[�ϊ�
    XMMATRIX invView = XMMatrixInverse(nullptr, Camera::GetViewMatrix());
    
    //�}�E�X���W(��O�A�����擾
    XMFLOAT3 mousePosFront = Input::GetMousePosition();
    mousePosFront.z = 0.0f;
    XMFLOAT3 mousePosBack = Input::GetMousePosition();
    mousePosBack.z = 1.0f;

    //�@�@mousePosFront���x�N�g���ɕϊ�
    //�A�@�@��invVP�AinvPrj�AinvView��������
    XMVECTOR vMouseFront = XMVector3TransformCoord(XMLoadFloat3(&mousePosFront), invVP * invProj * invView);

    //�B�@mousePosBack���x�N�g���ɕϊ�
    //�C�@�B��invVP�AinvPrj�AinvView��������
    XMVECTOR vMouseBack = XMVector3TransformCoord(XMLoadFloat3(&mousePosBack), invVP * invProj * invView);

    for (int x = 0; x < 15; x++)
    {
        for (int z = 0; z < 15; z++)
        {
            for (int y = 0; y < table_[x][z].height_ + 1; y++)
            {
                //�D�@�A����C�Ɍ������ă��C�����i�Ƃ肠�������f���ԍ���hModel_[0]�j
                RayCastData data;
                XMStoreFloat4(&data.start, vMouseFront);
                XMStoreFloat4(&data.dir, vMouseBack - vMouseFront);

                //�E�@���ۂ̈ʒu�ɓK������
                Transform trans;
                trans.position_ = { (float)x,(float)y,(float)z };
                Model::SetTransform(hModel_[0], trans);

                //���C�L���X�g��ł�
                Model::RayCast(hModel_[0], data);

                //�E�@���C������������u���[�N�|�C���g�Ŏ~�߂�
                if (data.hit)
                {
                    table_[x][z].height_++;
                    break;
                }

            }

        }
    }
}

void Stage::Draw()
{
    Transform BlockTrans;

    for (int width = 0; width < 15; width++){
        for (int depth = 0; depth < 15; depth++){
            for (int height = 0; height < table_[width][depth].height_ + 1; height++) {

                BlockTrans.position_ = { (float)width,(float)height,(float)depth };
                int type = table_[width][depth].type_;

                Model::SetTransform(hModel_[type], BlockTrans);
                Model::Draw(hModel_[type]);
            }
        }
    }
}

void Stage::Release()
{
}

//�_�C�A���O�v���V�[�W���\(�U��)
BOOL Stage::DialogProc(HWND hDig, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_INITDIALOG://�_�C�A���O�쐬����

        //���W�I�{�^��������
        SendMessage(GetDlgItem(hDig, IDC_RADIO_UP), BM_SETCHECK, BST_CHECKED, 0);

        //�R���{�{�b�N�X������
        SendMessage(GetDlgItem(hDig, IDC_COMBO3), CB_ADDSTRING, 0, (LPARAM)"Default");
        SendMessage(GetDlgItem(hDig, IDC_COMBO3), CB_ADDSTRING, 0, (LPARAM)"Brick");
        SendMessage(GetDlgItem(hDig, IDC_COMBO3), CB_ADDSTRING, 0, (LPARAM)"Grass");
        SendMessage(GetDlgItem(hDig, IDC_COMBO3), CB_ADDSTRING, 0, (LPARAM)"Sand");
        SendMessage(GetDlgItem(hDig, IDC_COMBO3), CB_ADDSTRING, 0, (LPARAM)"Water");
        SendMessage(GetDlgItem(hDig, IDC_COMBO3), CB_SETCURSEL, 0, 0);

        return TRUE;
    }
    return FALSE;
}

BOOL Stage::MenuProc(HWND hMenu, UINT msg, WPARAM wParam, LPARAM lParam)
{
    int wmId = LOWORD(wParam); // ���j���[�܂��͐���̎��ʎq
    switch (msg)
    {
    case WM_COMMAND:
        switch (wmId)
        {
        case ID_MENU_NEW:New(); return 0;
        case ID_MENU_SAVE:Save(); return 0;
        case ID_MENU_OPEN:Load(); return 0;
        }
    }
    return 0;
}

void Stage::New()
{
    for (int x = 0; x < XSIZE; x++) {
        for (int z = 0; z < ZSIZE; z++) {
            SetBlock(x, z, DEFAULT);
            SetBlockHeight(x, z, DEFAULT);
        }
    }
}

void Stage::Save()
{
    std::fstream oFile("Assets/blockData.csv",std::ios::out);

    string outStr;
    for (int x = 0; x < XSIZE; x++) {
        for (int z = 0; z < ZSIZE; z++) {
            outStr += (std::to_string(GetBlock(x, z)) + ',');
            outStr += (std::to_string(GetBlockHeight(x, z))+',');
        }
        outStr += "\n";
    }

    oFile << outStr;

    oFile.close();
}

void Stage::Load()
{
    std::fstream iFile("Assets/blockData.csv", std::ios::in);

    std::string line;
    int x = 0, z = 0;

    while (std::getline(iFile, line)) {
        std::stringstream ss(line);
        std::string cell;

        while (std::getline(ss, cell, ',')) {
            // CSV����ǂݎ�����f�[�^��K�؂Ȍ^�ɕϊ����A
            SetBlock(x, z, std::stoi(cell));
            std::getline(ss, cell, ',');
            SetBlockHeight(x, z, std::stoi(cell));

            z++; // ���̗�ɐi��
        }

        x++; // ���̍s�ɐi��
        z = 0; // ������Z�b�g
    }

    iFile.close();
}
