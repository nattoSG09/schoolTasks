#include "Controller.h"
#include "Engine/Camera.h"
#include "Engine/Input.h"

Controller::Controller()
{
}

void Controller::Initialize()
{
	CamPosition_ = {0,5,-10};
	CamTarget_ = transform_.position_;
	Camera::SetPosition(CamPosition_);
	Camera::SetTarget(CamTarget_);

}

void Controller::Update()
{
	float speed = 0.1f;

	//HandleInput
	if (Input::IsKey(DIK_W)) {
		CamPosition_.z += speed;
		CamTarget_.z += speed;
	}
	Camera::SetPosition(CamPosition_);
	Camera::SetTarget(CamTarget_);

	/*if (Input::IsKey(DIK_A));
	if (Input::IsKey(DIK_S));
	if (Input::IsKey(DIK_D));

	if (Input::IsKey(DIK_UP));
	if (Input::IsKey(DIK_DOWN));
	if (Input::IsKey(DIK_RIGHT));
	if (Input::IsKey(DIK_LEFT));*/
}

void Controller::Draw()
{
}

void Controller::Release()
{
}
