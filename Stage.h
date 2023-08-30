#pragma once
#include "Engine/GameObject.h"



namespace {
	const int MODEL_NUM{ 5 };
	const int XSIZE{ 15 };
	const int ZSIZE{ 15 };

	enum BLOCK_TYPE {
		DEFAULT, BRICK, GRASS, SAND, WATER, MAX,
	};
	
}

class Stage : public GameObject
{
private:
	int hModel_[MAX];
	struct BlockData {
		int type_;
		int height_;
	}table_[XSIZE][ZSIZE];

public:
	Stage(GameObject* parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

	/// <summary>
	/// 指定した位置にブロックを設定する
	/// </summary>
	/// <param name="x">テーブル座標X</param>
	/// <param name="z">テーブル座標Y</param>
	/// <param name="_type">ブロックタイプ</param>
	void SetBlock(int x, int z, int _type) { table_[x][z].type_ = _type; }

	void SetBlockHeight(int x,int z,int _height){ table_[x][z].height_ = _height; }

};

