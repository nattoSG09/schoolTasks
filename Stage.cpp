#include "Stage.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Camera.h"
#include "resource.h"
//#include <DirectXMath.h>
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
    if (Input::IsMouseButtonDown(0))return;

    float w = (float)Direct3D::scrWidth_/2.0f;
    float h = (float)Direct3D::scrHeight_/2.0f;


    XMMATRIX vp =
    {
        w,0,0,0,
        0,-h,0,0,
        0,0,1,0,
        w,h,0,1
    };

    //ビューポート行列
    XMMATRIX invVp = XMMatrixInverse(nullptr, vp);
    
    //プロジェクション行列
    XMMATRIX invProj = XMMatrixInverse(nullptr,Camera::GetProjectionMatrix());

    //ビュー変換
    XMMATRIX invView = XMMatrixInverse(nullptr, Camera::GetViewMatrix());

    //ワールド行列
    XMMATRIX inyW;

    //マウス座標(手前、奥を取得
    XMFLOAT3 mousePosFront = Input::GetMousePosition();
    mousePosFront.z = 0.0f;
    XMFLOAT3 mousePosBack = Input::GetMousePosition();
    mousePosBack.z = 1.0f;

    //�@ mousePosFrontをベクトルに変換
    //�A �@にinvVP,invPrj,invViewをかける
    XMVECTOR vMPF = XMVector3Transform(XMLoadFloat3(&mousePosFront), invVp* invProj* invView);

    //�B mousePosBackをベクトルに変換
    //�C �BにinvVP,invPrj,invViewをかける
    XMVECTOR vMPB = XMVector3Transform(XMLoadFloat3(&mousePosBack), invVp * invProj * invView);

    //table_上のモデルすべてとのレイキャスト判定を行う
    for (int x = 0; x < 15; x++) {
        for (int z = 0; z < 15; z++){
            for (int y = 0; y < table_[x][z].height_ + 1; y++) {
                RayCastData data;
                XMStoreFloat3(&data.start, vMPF);
                data.dir = vMPB - vMPF;
                Model::RayCast(hModel_[0],data);

                if (data.hit) {
                    int a = 0;
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
