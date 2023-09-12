﻿#include "Model.h"
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

void Model::RayCast(int _hModel, RayCastData& _rayData)
{
	//できなかったやつ
	{
		////モデルのトランスフォームをカリキュレーション
	//modelList_[_hModel]->transform_.Calclation();

	////①ワールド行列の逆行列
	//XMMATRIX wInv = XMMatrixInverse(nullptr, modelList_[_hModel]->transform_.GetWorldMatrix());

	////②レイの通過点を求める(モデル空間での例の方向ベクトルを求める)
	//XMFLOAT4 start = { _rayData.start.x,_rayData.start.y,_rayData.start.z,1.0f };
	//XMFLOAT4 dir = { _rayData.dir.x,_rayData.dir.y,_rayData.dir.z,1.0f };
	//XMVECTOR vPass{ start.x + dir.x,
	//				start.y + dir.y,
	//				start.z + dir.z,
	//				start.w + dir.w };

	////③rayData.startをモデル空間に変換(①をかける)
	//XMVECTOR vStart = XMLoadFloat4(&start);
	//vStart = XMVector3TransformCoord(vStart, wInv);
	//XMStoreFloat3(&_rayData.start, vStart);
	////④（始点から方向ベクトルをちょい伸ばした先）通過点（②）に①をかける
	//vPass = XMVector3TransformCoord(vPass, wInv);
	////⑤rayData.dir③から④に向かうベクトルにする（引き算）
	//vPass = vPass - vStart;
	//XMStoreFloat4(&dir, vPass);
	//
	////指定したモデル番号のFBXにレイキャスト！
	//modelList_[_hModel]->fbx_->RayCast(_rayData);
	}
	
	//⓪モデルのトランスフォームをカリキュレーション
	modelList_[_hModel]->transform_.Calclation();
	//①ワールド行列の逆行列
	XMMATRIX wInv = XMMatrixInverse(nullptr,
		modelList_[_hModel]->transform_.GetWorldMatrix());

	//②レイの通過点を求める(モデル空間での例の方向ベクトルを求める）
	XMVECTOR vpass{ _rayData.start.x + _rayData.dir.x,
					_rayData.start.y + _rayData.dir.y,
					_rayData.start.z + _rayData.dir.z,
					_rayData.start.w + _rayData.dir.w };

	//③rayData.startをモデル空間に変換（①をかける）
	XMVECTOR vstart = XMLoadFloat4(&_rayData.start);
	vstart = XMVector3TransformCoord(vstart, wInv); //tarnsformcoordはw要素を無視してくれるらしい
	XMStoreFloat4(&_rayData.start, vstart);

	//④（始点から方向ベクトルをちょい伸ばした先）通過点（②）に①をかける
	vpass = XMVector3TransformCoord(vpass, wInv);

	//⑤rayData.dirを③から④に向かうベクトルにする（引き算）
	vpass = vpass - vstart;
	XMStoreFloat4(&_rayData.dir, vpass);

	//指定したモデル番号のFBXにレイキャスト！
	modelList_[_hModel]->fbx_->RayCast(_rayData);
}
