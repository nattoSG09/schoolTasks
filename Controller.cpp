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
    //�������������� TankBody�F�ړ����� ����������������
    //�uD�v�L�[�������ƉE��]
    if (Input::IsKey(DIK_LEFT))
    {
        transform_.rotate_.y += 2.0f;
    }
    //�uA�v�L�[�������ƍ���]
    if (Input::IsKey(DIK_RIGHT))
    {
        transform_.rotate_.y -= 2.0f;
    }

    //��Ԃ̌��ݒn���x�N�g���^�ɕϊ�
    XMVECTOR VectorPos = XMLoadFloat3(&transform_.position_);

    //�P�t���[���̈ړ��x�N�g��
    XMVECTOR VectorMoveZ = { 0.0f,0.0f,0.1f,0.0f };
    XMVECTOR VectorMoveX = { 0.1f,0.0f,0.0f };

    //transform_.rotate_.y�x��]������s����쐬
    XMMATRIX RotateMatY = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
    //�ړ��x�N�g����ό`(��ԂƓ��������ɉ�])
    VectorMoveZ = XMVector3TransformCoord(VectorMoveZ, RotateMatY);

    //�uW�v�L�[�������ƌ����Ă�������ɐi��
    if (Input::IsKey(DIK_W))
    {
        //�����Ă�������ɐi�ޏ���
        //�ړ�
        VectorPos += VectorMoveZ;
        //���ݒn���x�N�g�����炢����transform.position_�ɂ��ǂ�
        XMStoreFloat3(&transform_.position_, VectorPos);
    }

    //�uA�v�L�[�������ƌ����Ă�������ɐi��
    if (Input::IsKey(DIK_A))
    {
        //�����Ă�������ɐi�ޏ���
        //�ړ�
        VectorPos -= VectorMoveX;
        //���ݒn���x�N�g�����炢����transform.position_�ɂ��ǂ�
        XMStoreFloat3(&transform_.position_, VectorPos);
    }

    //�uS�v�L�[�������ƌ����Ă�������̌��ɐi��
    if (Input::IsKey(DIK_S))
    {
        //�����Ă�������ɐi�ޏ���
        //�ړ�
        VectorPos -= VectorMoveZ;
        //���ݒn���x�N�g�����炢����transform.position_�ɂ��ǂ�
        XMStoreFloat3(&transform_.position_, VectorPos);
    }

    //�uD�v�L�[�������ƌ����Ă�������̌��ɐi��
    if (Input::IsKey(DIK_D))
    {
        //�����Ă�������ɐi�ޏ���
        //�ړ�
        VectorPos += VectorMoveX;
        //���ݒn���x�N�g�����炢����transform.position_�ɂ��ǂ�
        XMStoreFloat3(&transform_.position_, VectorPos);
    }
    //��������������������������������������������������

    //�œ_�̈ʒu
    XMFLOAT3 CamTarget = { 0,0,0 };
    //��l�̃J�����̈ʒu
    XMFLOAT3 CamPosition = { 0,0,0 };
    //�R�l�̃J�����̈ʒu
    XMVECTOR CamVector = { 0,5,-10,0 };
    CamVector = XMVector3TransformCoord(CamVector, RotateMatY);
    XMVECTOR FPSup = { 0,2,0 };

    //���_�̈ړ�
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
