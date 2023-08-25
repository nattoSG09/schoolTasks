#include "Model.h"
#define SAFE_DELETE(p) if(p != nullptr){ delete p; p = nullptr;}

namespace Model
{
	
	std::vector<ModelData*> modelList_;
}

int Model::Load(string _fileName)
{
	//���f���f�[�^��ݒ�
	ModelData* pData;
	pData = new ModelData;
	
	//���f��::�t�@�C���l�[����ݒ�
	pData->fileName_ = _fileName;


	//���f��::�������f�[�^��ݒ�
	pData->fbx_ = nullptr;
	for (auto& e : modelList_) {
		if (e->fileName_ == _fileName){
			pData->fbx_ = e->fbx_;
			break;
		}
	}

	if (!pData->fbx_) {
		pData->fbx_ = new Fbx;
		pData->fbx_->Load(_fileName);
	}

	//���f�����X�g�ɒǉ�
	modelList_.push_back(pData);

	//���X���̉��Ԗڂɒǉ����ꂽ�̂���Ԃ�
	return (modelList_.size()-1);
}

void Model::SetTransform(int _hModel, Transform _transform)
{
	//�g�����X�t�H�[����ݒ�
	modelList_[_hModel]->transform_ = _transform;
}

void Model::Draw(int _hModel)
{
	//�`��
	modelList_[_hModel]->fbx_->Draw(modelList_[_hModel]->transform_);
}

void Model::Release()
{
	bool isReffered = false;
	for (int i = 0; i < modelList_.size(); i++) {
		for (int j = i + 1; j < modelList_.size(); j++) {
			if (modelList_[i]->fbx_ == modelList_[j]->fbx_) {
				isReffered = true;
				break;
			}
		}
		if (!isReffered) {
			SAFE_DELETE(modelList_[i]->fbx_);
			SAFE_DELETE(modelList_[i]);
		}
	}
	modelList_.clear();
}
