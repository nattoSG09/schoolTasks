#include "Stage.h"
#include "Engine/Model.h"

Stage::Stage(GameObject* parent)
    :GameObject(parent, "Stage")
{
    for (int i = 0; i < BLOCK_MAX; i++)hModel_[i] = -1;

    for (int x = 0; x < XSIZE; x++){
        for (int z = 0; z < ZSIZE; z++)table_[x][z] = 0;
    }
}

void Stage::Initialize()
{
    string modelFileName[BLOCK_MAX] = {
        "BoxDefault.fbx",
        "BoxBrick.fbx",
        "BoxGrass.fbx",
        "BoxSand.fbx",
        "BoxWater.fbx"
    };
    string FilePath = "Assets/MapEditor/";

    for (int i = 0; i < BLOCK_MAX; i++) {
        hModel_[i] = Model::Load(FilePath + modelFileName[i]);
        assert(hModel_[i] >= 0);
    }

    //table_にブロックのタイプをセットしてやろう
    for (int x = 0; x < XSIZE; x++) {
        for (int z = 0; z < ZSIZE; z++)SetBlock(x,z,(x+z%5));
    }
}

void Stage::Update()
{
}

void Stage::Draw()
{
    Transform BlockTrans;//Transform型の変数を作る
    //Transform型は、位置向き大きさなどを扱う型

    for (int width = 0; width < 15; width++)
    {
        for (int depth = 0; depth < 15; depth++)
        {
            BlockTrans.position_.x = width;
            BlockTrans.position_.z = depth;
            int type = table_[width][depth];

            Model::SetTransform(hModel_[type], BlockTrans);
            Model::Draw(hModel_[type]);

        }
    }
}

void Stage::Release()
{
}
