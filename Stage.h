#pragma once
#include "Engine/GameObject.h"

enum BLOCK_TYPE{
	DEFAULT,
	BRICK,
	GRASS,
	SAND,
	WATER,
	BLOCK_MAX,
};

namespace {
	const int MODEL_NUM{ 5 };
	const int XSIZE{ 15 };
	const int ZSIZE{ 15 };
}

class Stage : public GameObject
{
private:
	int hModel_[BLOCK_MAX];
	int table_[XSIZE][ZSIZE];

public:
	Stage(GameObject* parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

	void SetBlock(int x, int z, BLOCK_TYPE _type) { table_[x][z] = _type; }
	void SetBlock(int x, int z, int _type) { table_[x][z] = _type; }

};

