#include "Model.h"
#define SAFE_DELETE(p) if(p != nullptr){ delete p; p = nullptr;}

namespace Model
{
	
	std::vector<ModelData*> modelList_;
}

int Model::Load(string _fileName)
{
	//モデルデータを設定
	ModelData* pData;
	pData = new ModelData;
	
	//モデル::ファイルネームを設定
	pData->fileName_ = _fileName;


	//モデル::ｆｂｘデータを設定
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

	//モデルリストに追加
	modelList_.push_back(pData);

	//リスｔの何番目に追加されたのかを返す
	return (modelList_.size()-1);
}

void Model::SetTransform(int _hModel, Transform _transform)
{
	//トランスフォームを設定
	modelList_[_hModel]->transform_ = _transform;
}

void Model::Draw(int _hModel)
{
	//描画
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
