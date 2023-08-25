#pragma once
//�C���N���[�h
#include <string>
#include <vector>
#include "Transform.h"
#include "Fbx.h"

//using�錾
using std::string;

namespace Model
{
	struct  ModelData
	{
		string fileName_;
		Transform transform_;
		Fbx* fbx_;
	};

	/// <summary>
	/// ���f���̓ǂݍ���
	/// </summary>
	/// <param name="_fileName">�t�@�C����</param>
	/// <returns>���f���n���h��</returns>
	int Load(string _fileName);

	/// <summary>
	/// �ϊ��s���ݒ�
	/// </summary>
	/// <param name="_hModel">���f���n���h��</param>
	/// <param name="_transform">�ϊ��s��</param>
	void SetTransform(int _hModel, Transform _transform);

	/// <summary>
	/// �`��
	/// </summary>
	/// <param name="_hModel">���f���n���h��</param>
	void Draw(int _hModel);

	/// <summary>
	/// ���
	/// </summary>
	void Release();


}