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

	int mode_;		//0:�グ��,1:������,2:�ς���
	int select_;	//���

public:
	Stage(GameObject* parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

	BOOL DialogProc(HWND hDig, UINT msg, WPARAM wParam, LPARAM lParam);

	/// <summary>
	/// �w�肵���ʒu�Ƀu���b�N��ݒ肷��
	/// </summary>
	/// <param name="x">�e�[�u�����WX</param>
	/// <param name="z">�e�[�u�����WY</param>
	/// <param name="_type">�u���b�N�^�C�v</param>
	void SetBlock(int x, int z, int _type) { table_[x][z].type_ = _type; }


	/// <summary>
	/// �w�肵���ʒu�̃u���b�N�ȍ�����ݒ肷��
	/// </summary>
	/// <param name="x">�e�[�u�����W��</param>
	/// <param name="z">�e�[�u�����W��</param>
	/// <param name="_height">����</param>
	void SetBlockHeight(int x,int z,int _height){ table_[x][z].height_ = _height; }

};

