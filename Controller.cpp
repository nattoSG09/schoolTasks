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
    //����]
    if (Input::IsKey(DIK_LEFT)){
        transform_.rotate_.y -= 1.0f;
    }

    //�E��]
    if (Input::IsKey(DIK_RIGHT)){
        transform_.rotate_.y += 1.0f;
    }

    //transform_.rotate_.y�̒l�ɍ��킹�Ăx����]������s��
    XMMATRIX mRotate = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));

    //���݈ʒu���x�N�g���ɂ��Ă���
    XMVECTOR vPos = XMLoadFloat3(&transform_.position_);

    //�O��ړ��x�N�g��
    XMFLOAT3 frontMove = { 0, 0, 0.1f };                //��������XMFLOAT3�\���̂�p�ӂ�
    XMVECTOR vMove = XMLoadFloat3(&frontMove);          //������x�N�g���ɂ���
    vMove = XMVector3TransformCoord(vMove, mRotate);    //��Ԃ̌����ɍ��킹�ĉ�]


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

    //���E�ړ��x�N�g��
    XMFLOAT3 rightMove = { 0.1f, 0, 0 };                //�E������XMFLOAT3�\���̂�p�ӂ�
    vMove = XMLoadFloat3(&rightMove);               //������x�N�g���ɂ���
    vMove = XMVector3TransformCoord(vMove, mRotate);    //��Ԃ̌����ɍ��킹�ĉ�]


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


    //�J����
    XMVECTOR vCam = XMVectorSet(0, 10, -10, 0);
    vCam = XMVector3TransformCoord(vCam, mRotate);
    XMFLOAT3 camPos;
    XMStoreFloat3(&camPos, vPos + vCam);
    Camera::SetPosition(XMLoadFloat3(&camPos));
    Camera::SetTarget(XMLoadFloat3(&transform_.position_));        //�J�����̏œ_�̓v���C���[�̈ʒu







    ////�������������� TankBody�F�ړ����� ����������������
    ////�uD�v�L�[�������ƉE��]
    //if (Input::IsKey(DIK_RIGHT))
    //{
    //    transform_.rotate_.y += 1.0f;
    //}
    ////�uA�v�L�[�������ƍ���]
    //if (Input::IsKey(DIK_LEFT))
    //{
    //    transform_.rotate_.y -= 1.0f;
    //}

    ////��Ԃ̌��ݒn���x�N�g���^�ɕϊ�
    //XMVECTOR VectorPos = XMLoadFloat3(&transform_.position_);

    ////�P�t���[���̈ړ��x�N�g��
    //XMVECTOR VectorMoveZ = { 0.0f,0.0f,0.1f,0.0f };
    //XMVECTOR VectorMoveX = { 0.1f,0.0f,0.0f };

    ////transform_.rotate_.y�x��]������s����쐬
    //XMMATRIX RotateMatY = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
    ////�ړ��x�N�g����ό`(��ԂƓ��������ɉ�])
    //VectorMoveZ = XMVector3TransformCoord(VectorMoveZ, RotateMatY);

    ////�uW�v�L�[�������ƌ����Ă�������ɐi��
    //if (Input::IsKey(DIK_W))
    //{
    //    //�����Ă�������ɐi�ޏ���
    //    //�ړ�
    //    VectorPos += VectorMoveZ;
    //    //���ݒn���x�N�g�����炢����transform.position_�ɂ��ǂ�
    //    XMStoreFloat3(&transform_.position_, VectorPos);
    //}

    ////�uA�v�L�[�������ƌ����Ă�������ɐi��
    //if (Input::IsKey(DIK_A))
    //{
    //    //�����Ă�������ɐi�ޏ���
    //    //�ړ�
    //    VectorPos -= VectorMoveX;
    //    //���ݒn���x�N�g�����炢����transform.position_�ɂ��ǂ�
    //    XMStoreFloat3(&transform_.position_, VectorPos);
    //}

    ////�uS�v�L�[�������ƌ����Ă�������̌��ɐi��
    //if (Input::IsKey(DIK_S))
    //{
    //    //�����Ă�������ɐi�ޏ���
    //    //�ړ�
    //    VectorPos -= VectorMoveZ;
    //    //���ݒn���x�N�g�����炢����transform.position_�ɂ��ǂ�
    //    XMStoreFloat3(&transform_.position_, VectorPos);
    //}

    ////�uD�v�L�[�������ƌ����Ă�������̌��ɐi��
    //if (Input::IsKey(DIK_D))
    //{
    //    //�����Ă�������ɐi�ޏ���
    //    //�ړ�
    //    VectorPos += VectorMoveX;
    //    //���ݒn���x�N�g�����炢����transform.position_�ɂ��ǂ�
    //    XMStoreFloat3(&transform_.position_, VectorPos);
    //}

    ////��������������������������������������������������

    ////�œ_�̈ʒu
    //XMFLOAT3 CamTarget = { 0,0,0 };
    ////��l�̃J�����̈ʒu
    //XMFLOAT3 CamPosition = { 0,0,0 };
    ////�R�l�̃J�����̈ʒu
    //XMVECTOR CamVector = { 0,6,-5,0 };
    //CamVector = XMVector3TransformCoord(CamVector, RotateMatY);
    //XMVECTOR FPSup = { 0,2,0 };

    ////���_�̈ړ�
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
