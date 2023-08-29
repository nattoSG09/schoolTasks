#include "Controller.h"
#include "Engine/Camera.h"
#include "Engine/Input.h"

Controller::Controller(GameObject* parent)
	:GameObject(parent,"Contoroller")
{
}

void Controller::Initialize()
{
}

void Controller::Update()
{
    //□＝＝＝＝＝＝ TankBody：移動処理 ＝＝＝＝＝＝＝□
    //「D」キーを押すと右回転
    if (Input::IsKey(DIK_LEFT))
    {
        transform_.rotate_.y += 2.0f;
    }
    //「A」キーを押すと左回転
    if (Input::IsKey(DIK_RIGHT))
    {
        transform_.rotate_.y -= 2.0f;
    }

    //戦車の現在地をベクトル型に変換
    XMVECTOR VectorPos = XMLoadFloat3(&transform_.position_);

    //１フレームの移動ベクトル
    XMVECTOR VectorMoveZ = { 0.0f,0.0f,0.1f,0.0f };
    XMVECTOR VectorMoveX = { 0.1f,0.0f,0.0f };

    //transform_.rotate_.y度回転させる行列を作成
    XMMATRIX RotateMatY = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
    //移動ベクトルを変形(戦車と同じ向きに回転)
    VectorMoveZ = XMVector3TransformCoord(VectorMoveZ, RotateMatY);

    //「W」キーを押すと向いている方向に進む
    if (Input::IsKey(DIK_W))
    {
        //向いている方向に進む処理
        //移動
        VectorPos += VectorMoveZ;
        //現在地をベクトルからいつものtransform.position_にもどす
        XMStoreFloat3(&transform_.position_, VectorPos);
    }

    //「A」キーを押すと向いている方向に進む
    if (Input::IsKey(DIK_A))
    {
        //向いている方向に進む処理
        //移動
        VectorPos -= VectorMoveX;
        //現在地をベクトルからいつものtransform.position_にもどす
        XMStoreFloat3(&transform_.position_, VectorPos);
    }

    //「S」キーを押すと向いている方向の後ろに進む
    if (Input::IsKey(DIK_S))
    {
        //向いている方向に進む処理
        //移動
        VectorPos -= VectorMoveZ;
        //現在地をベクトルからいつものtransform.position_にもどす
        XMStoreFloat3(&transform_.position_, VectorPos);
    }

    //「D」キーを押すと向いている方向の後ろに進む
    if (Input::IsKey(DIK_D))
    {
        //向いている方向に進む処理
        //移動
        VectorPos += VectorMoveX;
        //現在地をベクトルからいつものtransform.position_にもどす
        XMStoreFloat3(&transform_.position_, VectorPos);
    }
    //□＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝□

    //焦点の位置
    XMFLOAT3 CamTarget = { 0,0,0 };
    //一人称カメラの位置
    XMFLOAT3 CamPosition = { 0,0,0 };
    //３人称カメラの位置
    XMVECTOR CamVector = { 0,5,-10,0 };
    CamVector = XMVector3TransformCoord(CamVector, RotateMatY);
    XMVECTOR FPSup = { 0,2,0 };

    //視点の移動
    CamTarget = transform_.position_;
    XMStoreFloat3(&CamPosition, VectorPos + CamVector);
       
    Camera::SetTarget(CamTarget);
    Camera::SetPosition(CamPosition);

}

void Controller::Draw()
{
}

void Controller::Release()
{
}
