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
    //左回転
    if (Input::IsKey(DIK_LEFT)){
        transform_.rotate_.y -= 1.0f;
    }

    //右回転
    if (Input::IsKey(DIK_RIGHT)){
        transform_.rotate_.y += 1.0f;
    }

    //transform_.rotate_.yの値に合わせてＹ軸回転させる行列
    XMMATRIX mRotate = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));

    //現在位置をベクトルにしておく
    XMVECTOR vPos = XMLoadFloat3(&transform_.position_);

    //前後移動ベクトル
    XMFLOAT3 frontMove = { 0, 0, 0.1f };                //奥向きのXMFLOAT3構造体を用意し
    XMVECTOR vMove = XMLoadFloat3(&frontMove);          //それをベクトルにする
    vMove = XMVector3TransformCoord(vMove, mRotate);    //戦車の向きに合わせて回転


    if (Input::IsKey(DIK_W))
    {
        vPos += vMove;
        XMStoreFloat3(&transform_.position_, vPos);
    }
    if (Input::IsKey(DIK_S))
    {
        vPos -= vMove;
        XMStoreFloat3(&transform_.position_, vPos);
    }

    //左右移動ベクトル
    XMFLOAT3 rightMove = { 0.1f, 0, 0 };                //右向きのXMFLOAT3構造体を用意し
    vMove = XMLoadFloat3(&rightMove);               //それをベクトルにする
    vMove = XMVector3TransformCoord(vMove, mRotate);    //戦車の向きに合わせて回転


    if (Input::IsKey(DIK_D))
    {
        vPos += vMove;
        XMStoreFloat3(&transform_.position_, vPos);
    }
    if (Input::IsKey(DIK_A))
    {
        vPos -= vMove;
        XMStoreFloat3(&transform_.position_, vPos);
    }


    //カメラ
    XMVECTOR vCam = XMVectorSet(0, 10, -10, 0);
    vCam = XMVector3TransformCoord(vCam, mRotate);
    XMFLOAT3 camPos;
    XMStoreFloat3(&camPos, vPos + vCam);
    Camera::SetPosition(XMLoadFloat3(&camPos));
    Camera::SetTarget(XMLoadFloat3(&transform_.position_));        //カメラの焦点はプレイヤーの位置







    ////□＝＝＝＝＝＝ TankBody：移動処理 ＝＝＝＝＝＝＝□
    ////「D」キーを押すと右回転
    //if (Input::IsKey(DIK_RIGHT))
    //{
    //    transform_.rotate_.y += 1.0f;
    //}
    ////「A」キーを押すと左回転
    //if (Input::IsKey(DIK_LEFT))
    //{
    //    transform_.rotate_.y -= 1.0f;
    //}

    ////戦車の現在地をベクトル型に変換
    //XMVECTOR VectorPos = XMLoadFloat3(&transform_.position_);

    ////１フレームの移動ベクトル
    //XMVECTOR VectorMoveZ = { 0.0f,0.0f,0.1f,0.0f };
    //XMVECTOR VectorMoveX = { 0.1f,0.0f,0.0f };

    ////transform_.rotate_.y度回転させる行列を作成
    //XMMATRIX RotateMatY = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
    ////移動ベクトルを変形(戦車と同じ向きに回転)
    //VectorMoveZ = XMVector3TransformCoord(VectorMoveZ, RotateMatY);

    ////「W」キーを押すと向いている方向に進む
    //if (Input::IsKey(DIK_W))
    //{
    //    //向いている方向に進む処理
    //    //移動
    //    VectorPos += VectorMoveZ;
    //    //現在地をベクトルからいつものtransform.position_にもどす
    //    XMStoreFloat3(&transform_.position_, VectorPos);
    //}

    ////「A」キーを押すと向いている方向に進む
    //if (Input::IsKey(DIK_A))
    //{
    //    //向いている方向に進む処理
    //    //移動
    //    VectorPos -= VectorMoveX;
    //    //現在地をベクトルからいつものtransform.position_にもどす
    //    XMStoreFloat3(&transform_.position_, VectorPos);
    //}

    ////「S」キーを押すと向いている方向の後ろに進む
    //if (Input::IsKey(DIK_S))
    //{
    //    //向いている方向に進む処理
    //    //移動
    //    VectorPos -= VectorMoveZ;
    //    //現在地をベクトルからいつものtransform.position_にもどす
    //    XMStoreFloat3(&transform_.position_, VectorPos);
    //}

    ////「D」キーを押すと向いている方向の後ろに進む
    //if (Input::IsKey(DIK_D))
    //{
    //    //向いている方向に進む処理
    //    //移動
    //    VectorPos += VectorMoveX;
    //    //現在地をベクトルからいつものtransform.position_にもどす
    //    XMStoreFloat3(&transform_.position_, VectorPos);
    //}

    ////□＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝□

    ////焦点の位置
    //XMFLOAT3 CamTarget = { 0,0,0 };
    ////一人称カメラの位置
    //XMFLOAT3 CamPosition = { 0,0,0 };
    ////３人称カメラの位置
    //XMVECTOR CamVector = { 0,6,-5,0 };
    //CamVector = XMVector3TransformCoord(CamVector, RotateMatY);
    //XMVECTOR FPSup = { 0,2,0 };

    ////視点の移動
    //CamTarget = transform_.position_;
    //XMStoreFloat3(&CamPosition, VectorPos + CamVector);
    //   
    //Camera::SetTarget(CamTarget);
    //Camera::SetPosition(CamPosition);

}

void Controller::Draw()
{
}

void Controller::Release()
{
}
