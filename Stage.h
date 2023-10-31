#pragma once
#include "Engine/GameObject.h"
#include <Windows.h>
#include "Memento.h"

namespace {
	const int MODEL_NUM{ 5 };
	const int XSIZE{ 15 };
	const int ZSIZE{ 15 };

	enum BLOCK_TYPE {
		DEFAULT, BRICK, GRASS, SAND, WATER, MAX,
	};
	
	struct BlockData{
		int type_;
		int height_;
	};
}

class Stage : public GameObject
{
private:
	int hModel_[MAX];

	BlockData table_[XSIZE][ZSIZE];

	// 変更前のテーブルの状態を保存する変数
	BlockData prevTable_[XSIZE][ZSIZE];

	Memento saveMemento_;

	int mode_;		//0:上げる,1:下げる,2:変える
	int select_;	//種類
public:
	Stage(GameObject* parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

	BOOL DialogProc(HWND hDig, UINT msg, WPARAM wParam, LPARAM lParam);
	void New();
	
	void Save();
	void Load();

	void UndoChanges();

	BlockData GetBlockData(int x, int y) { return table_[x][y]; }
	void SetBlockData(int x, int y, BlockData b) { table_[x][y] = b; }
	/// <summary>
	/// 指定した位置にブロックを設定する
	/// </summary>
	/// <param name="x">テーブル座標X</param>
	/// <param name="z">テーブル座標Y</param>
	/// <param name="_type">ブロックタイプ</param>
	void SetBlock(int x, int z, int _type) { table_[x][z].type_ = _type; }
	int GetBlock(int x, int y) { return table_[x][y].type_; }

	/// <summary>
	/// 指定した位置のブロックな高さを設定する
	/// </summary>
	/// <param name="x">テーブル座標ｘ</param>
	/// <param name="z">テーブル座標ｚ</param>
	/// <param name="_height">高さ</param>
	void SetBlockHeight(int x,int z,int _height){ table_[x][z].height_ = _height; }
	int GetBlockHeight(int x, int z) { return table_[x][z].height_; }


// Memento
	Memento CreateMemento() const {
		BlockData copiedTable[XSIZE][ZSIZE];
		for (int x = 0; x < XSIZE; ++x) {
			for (int z = 0; z < ZSIZE; ++z) {
				copiedTable[x][z] = table_[x][z];
			}
		}
		return Memento(copiedTable);
	}

	void RestoreMemento(const Memento& memento) {
		for (int x = 0; x < XSIZE; ++x) {
			for (int z = 0; z < ZSIZE; ++z) {
				table_[x][z] = memento.GetState(x, z);
			}
		}
	}

	void SaveMemento()
	{
		saveMemento_ = CreateMemento();
	}
};

