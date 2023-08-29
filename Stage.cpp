#include "Stage.h"
#include "Engine/Model.h"

Stage::Stage(GameObject* parent)
	:GameObject(parent,"Stage"),hModel_(-1)
{
}

void Stage::Initialize()
{
	hModel_ = Model::Load("Assets/MapEditor/BoxDefault.fbx");
	assert(hModel_ >= 0);
}

void Stage::Update()
{
}

void Stage::Draw()
{
    Transform BlockTrans;//TransformŒ^‚Ì•Ï”‚ğì‚é
    //TransformŒ^‚ÍAˆÊ’uŒü‚«‘å‚«‚³‚È‚Ç‚ğˆµ‚¤Œ^

    for (int Width_ = 0; Width_ < 15; Width_++)
    {
        for (int Depth_ = 0; Depth_ < 15; Depth_++)
        {
            BlockTrans.position_.x = Width_;
            BlockTrans.position_.z = Depth_;

            Model::SetTransform(hModel_, BlockTrans);
            Model::Draw(hModel_);

        }
    }
}

void Stage::Release()
{
}
