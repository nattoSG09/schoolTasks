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
    //遠藤先生：参照
    {
        //左回転
        if (Input::IsKey(DIK_LEFT)) {
            transform_.rotate_.y -= 1.0f;
        }

        //右回転
        if (Input::IsKey(DIK_RIGHT)) {
            transform_.rotate_.y += 1.0f;
        }

        //transform_.rotate_.yの値に合わせてＹ軸回転させる行列
        XMMATRIX mRotateY = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));

        //上回転
       if (Input::IsKey(DIK_UP)) {
           if (transform_.rotate_.x < 89.0f)transform_.rotate_.x += 1.0f;
       }

       //下回転
       if (Input::IsKey(DIK_DOWN)) {
           if (transform_.rotate_.x > 0.0f)transform_.rotate_.x -= 1.0f;
       }
        
        //transform_.rotate_.xの値に合わせてＸ軸回転させる行列
        XMMATRIX mRotateX = XMMatrixRotationX(XMConvertToRadians(transform_.rotate_.x));

        //現在位置をベクトルにしておく
        XMVECTOR vPos = XMLoadFloat3(&transform_.position_);

        XMVECTOR vMove;//移動ベクトル

        //前後移動ベクトル
        {
            XMFLOAT3 frontMove = { 0, 0, 0.1f };                //奥向きのXMFLOAT3構造体を用意し
            vMove = XMLoadFloat3(&frontMove);                //それをベクトルにする
            vMove = XMVector3TransformCoord(vMove,mRotateY);    //戦車の向きに合わせて回転
       

            if (Input::IsKey(DIK_W)) {
                vPos += vMove;
                XMStoreFloat3(&transform_.position_, vPos);
            }
            if (Input::IsKey(DIK_S)) {
                vPos -= vMove;
                XMStoreFloat3(&transform_.position_, vPos);
            }
        }
       
        //左右移動ベクトル
        {
            XMFLOAT3 rightMove = { 0.1f, 0, 0 };                //右向きのXMFLOAT3構造体を用意し
            vMove = XMLoadFloat3(&rightMove);               //それをベクトルにする
            vMove = XMVector3TransformCoord(vMove, mRotateY);    //戦車の向きに合わせて回転


            if (Input::IsKey(DIK_D)) {
                vPos += vMove;
                XMStoreFloat3(&transform_.position_, vPos);
            }
            if (Input::IsKey(DIK_A)) {
                vPos -= vMove;
                XMStoreFloat3(&transform_.position_, vPos);
            }
        }
        
        //カメラ
        XMVECTOR vCam = XMVectorSet(0, 0, -10, 0);
        vCam = XMVector3TransformCoord(vCam, mRotateX * mRotateY);

        XMFLOAT3 camPos;
        XMStoreFloat3(&camPos, vPos + vCam);
        Camera::SetPosition(XMLoadFloat3(&camPos));
        Camera::SetTarget(transform_.position_);        //カメラの焦点はプレイヤーの位置

    }
}

void Controller::Draw()
{
}

void Controller::Release()
{
}
