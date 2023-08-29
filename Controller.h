#pragma once
#include "Engine/GameObject.h"
class Controller : public GameObject
{
public:
	Controller(GameObject* parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
};

