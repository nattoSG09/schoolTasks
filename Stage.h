#pragma once
#include "Engine/GameObject.h"
#include <Windows.h>


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

	int mode_;		//0:上げる,1:下げる,2:変える
	int select_;	//種類

public:
	Stage(GameObject* parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

	BOOL DialogProc(HWND hDig, UINT msg, WPARAM wParam, LPARAM lParam);

	/// <summary>
	/// 指定した位置にブロックを設定する
	/// </summary>
	/// <param name="x">テーブル座標X</param>
	/// <param name="z">テーブル座標Y</param>
	/// <param name="_type">ブロックタイプ</param>
	void SetBlock(int x, int z, int _type) { table_[x][z].type_ = _type; }


	/// <summary>
	/// 指定した位置のブロックな高さを設定する
	/// </summary>
	/// <param name="x">テーブル座標ｘ</param>
	/// <param name="z">テーブル座標ｚ</param>
	/// <param name="_height">高さ</param>
	void SetBlockHeight(int x,int z,int _height){ table_[x][z].height_ = _height; }

};

