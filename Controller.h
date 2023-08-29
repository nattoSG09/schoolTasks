#pragma once
#include "Engine/GameObject.h"
class Controller : public GameObject
{
	XMFLOAT3 CamPosition_;
	XMFLOAT3 CamTarget_;
public:
	Controller();
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
};

