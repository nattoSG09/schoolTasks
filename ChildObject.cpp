#include "ChildObject.h"
#include "Engine/Model.h"
#include"Engine/Input.h"
#include "Engine/SphereCollider.h"

ChildObject::ChildObject(GameObject* parent) : GameObject(parent, "Player"), pFbx(nullptr)
{
}

ChildObject::~ChildObject()
{

}

void ChildObject::Initialize()
{
	hModel_ = Model::Load("Assets/Oden.fbx");
	assert(hModel_ >= 0);
	this->transform_.position_.x = 4.0f;
	this->transform_.scale_ = { 0.1f,0.1f ,0.1f };

	SphereCollider* Col = new SphereCollider(1.0);
	AddCollider(Col);
}

void ChildObject::Update()
{
	transform_.scale_.x+= 0.01f;
	transform_.scale_.y+= 0.01f;
	transform_.scale_.z+= 0.01f;
	if (transform_.position_.z > 50) {
		transform_.position_.y++;
		if (transform_.position_.y > 50) {
			KillMe();
		}
	}
	else {
		transform_.position_.z++;
		static float s = 0; s += 0.2;
		transform_.position_.x += sin(s);
	}
}

void ChildObject::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void ChildObject::Release()
{
	
}

