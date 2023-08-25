#include "Player.h"
#include "Engine/Model.h"
#include "ChildObject.h"
#include "Engine/Input.h"
#include "Engine/SphereCollider.h"

Player::Player(GameObject* parent)
	:GameObject(parent,"Player"),hModel_(-1)
{
}

Player::~Player()
{

}

void Player::Initialize()
{
	hModel_ = Model::Load("Assets/Oden.fbx");
	assert(hModel_ >= 0);

	this->transform_.scale_.x = 0.5;
	this->transform_.scale_.y = 0.5;
	this->transform_.scale_.z = 0.5;
	
}

void Player::Update()
{
	this->transform_.rotate_.y ++;
	if (Input::IsKey(DIK_D)) {
		transform_.position_.x += 0.1f;
	}

	if (Input::IsKey(DIK_A)) {
		transform_.position_.x -= 0.1f;
	}

	if (Input::IsKeyDown(DIK_SPACE))
	{
		GameObject* pBullet = Instantiate<ChildObject>(pParent_);
		pBullet->SetPosition(transform_.position_);
	}
}

void Player::Draw()
{
	Model::SetTransform(hModel_,transform_);
	Model::Draw(hModel_);
}

void Player::Release()
{
}
