#include "Stage.h"
#include "Engine/Model.h"
#include "Engine/Input.h"

#include "resource.h"

Stage::Stage(GameObject* parent)
    :GameObject(parent, "Stage")
{
    for (int i = 0; i < MAX; i++)hModel_[i] = -1;

    for (int x = 0; x < XSIZE; x++){
        for (int z = 0; z < ZSIZE; z++) {
            SetBlock(x, z,DEFAULT);
            SetBlockHeight(x, z, 1);
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
   
}

void Stage::Draw()
{
    Transform BlockTrans;

    for (int width = 0; width < 15; width++){
        for (int depth = 0; depth < 15; depth++){
            for (int height = 0; height < table_[width][depth].height_; height++) {

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
