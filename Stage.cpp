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

    //table_にブロックのタイプをセットしてやろう
    for (int x = 0; x < XSIZE; x++) {
        for (int z = 0; z < ZSIZE; z++) {
            SetBlock(x, z, (x%MAX));
            //SetBlockHeight(x, z, (x%3+1));
        }
    }
}

void Stage::Update()
{
    //できなかったやつ
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

        ////ビューポート行列
        //XMMATRIX invVp = XMMatrixInverse(nullptr, vp);

        ////プロジェクション行列
        //XMMATRIX invProj = XMMatrixInverse(nullptr, Camera::GetProjectionMatrix());

        ////ビュー変換
        //XMMATRIX invView = XMMatrixInverse(nullptr, Camera::GetViewMatrix());

        ////マウス座標(手前、奥を取得
        //XMFLOAT3 mousePosFront = Input::GetMousePosition();
        //mousePosFront.z = 0.0f;
        //XMFLOAT3 mousePosBack = Input::GetMousePosition();
        //mousePosBack.z = 1.0f;

        ////�@ mousePosFrontをベクトルに変換
        ////�A �@にinvVP,invPrj,invViewをかける
        //XMVECTOR vMPF = XMVector3Transform(XMLoadFloat3(&mousePosFront), invVp * invProj * invView);

        ////�B mousePosBackをベクトルに変換
        ////�C �BにinvVP,invPrj,invViewをかける
        //XMVECTOR vMPB = XMVector3Transform(XMLoadFloat3(&mousePosBack), invVp * invProj * invView);

        ////table_上のモデルすべてとのレイキャスト判定を行う
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
    //Offsetx,y は0
    //minZ =0 maxZ = 1

    XMMATRIX vp =
    {
         w,  0,  0, 0,
         0, -h,  0, 0,
         0,  0,  1, 0,
         w,  h,  0, 1
    };

    //ビューポート
    XMMATRIX invVP = XMMatrixInverse(nullptr, vp);

    //プロジェクション変換
    XMMATRIX invProj = XMMatrixInverse(nullptr, Camera::GetProjectionMatrix());
    
    //ビュー変換
    XMMATRIX invView = XMMatrixInverse(nullptr, Camera::GetViewMatrix());
    
    //マウス座標(手前、奥を取得
    XMFLOAT3 mousePosFront = Input::GetMousePosition();
    mousePosFront.z = 0.0f;
    XMFLOAT3 mousePosBack = Input::GetMousePosition();
    mousePosBack.z = 1.0f;

    //�@　mousePosFrontをベクトルに変換
    //�A　�@にinvVP、invPrj、invViewをかける
    XMVECTOR vMouseFront = XMVector3TransformCoord(XMLoadFloat3(&mousePosFront), invVP * invProj * invView);

    //�B　mousePosBackをベクトルに変換
    //�C　�BにinvVP、invPrj、invViewをかける
    XMVECTOR vMouseBack = XMVector3TransformCoord(XMLoadFloat3(&mousePosBack), invVP * invProj * invView);

    for (int x = 0; x < 15; x++)
    {
        for (int z = 0; z < 15; z++)
        {
            for (int y = 0; y < table_[x][z].height_ + 1; y++)
            {
                //�D　�Aから�Cに向かってレイをうつ（とりあえずモデル番号はhModel_[0]）
                RayCastData data;
                XMStoreFloat4(&data.start, vMouseFront);
                XMStoreFloat4(&data.dir, vMouseBack - vMouseFront);

                //�E　実際の位置に適応する
                Transform trans;
                trans.position_ = { (float)x,(float)y,(float)z };
                Model::SetTransform(hModel_[0], trans);

                //レイキャストを打つ
                Model::RayCast(hModel_[0], data);

                //�E　レイが当たったらブレークポイントで止める
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

//ダイアログプロシージャ―(偽物)
BOOL Stage::DialogProc(HWND hDig, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_INITDIALOG://ダイアログ作成直後

        //ラジオボタン初期化
        SendMessage(GetDlgItem(hDig, IDC_RADIO_UP), BM_SETCHECK, BST_CHECKED, 0);

        //コンボボックス初期化
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


void Stage::New()
{
    for (int x = 0; x < XSIZE; x++) {
        for (int z = 0; z < ZSIZE; z++) {
            SetBlock(x, z, DEFAULT);
            SetBlockHeight(x, z, DEFAULT);
        }
    }
}

void Stage::Save(HWND hWnd)
{
    char fileName[MAX_PATH] = "無題.map";
    std::string buffer;
    std::stringstream oss;

    OPENFILENAME ofn; {
        ZeroMemory(&ofn, sizeof(ofn));
        ofn.lStructSize = sizeof(OPENFILENAME);
        ofn.lpstrFilter = TEXT("マップデータ(*.map)\0*.map\0");
        ofn.lpstrFile = fileName;
        ofn.nMaxFile = MAX_PATH;
        ofn.Flags = OFN_OVERWRITEPROMPT;
        ofn.lpstrDefExt = TEXT("map");
        ofn.lpstrDefExt;
    }
    if (GetSaveFileName(&ofn)) {
        std::ofstream outputFile(fileName);
        for (int x = 0; x < XSIZE; x++)
        {
            for (int z = 0; z < ZSIZE; z++)
            {
                oss << GetBlock(x, z);
                oss << GetBlockHeight(x, z);
            }
        }

        outputFile << oss.str();
        outputFile.close();
    }

    /*std::fstream oFile("fileName.csv", std::ios::out);

    string outStr;
    for (int x = 0; x < XSIZE; x++) {
        for (int z = 0; z < ZSIZE; z++) {
            outStr += (std::to_string(GetBlock(x, z)) + ',');
            outStr += (std::to_string(GetBlockHeight(x, z))+',');
        }
        outStr += "\n";
    }

    oFile << outStr;

    oFile.close();*/
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
            // CSVから読み取ったデータを適切な型に変換し、
            SetBlock(x, z, std::stoi(cell));
            std::getline(ss, cell, ',');
            SetBlockHeight(x, z, std::stoi(cell));

            z++; // 次の列に進む
        }

        x++; // 次の行に進む
        z = 0; // 列をリセット
    }

    iFile.close();
}