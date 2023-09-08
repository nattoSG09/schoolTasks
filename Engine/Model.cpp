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

void Model::RayCast(int _hModel, RayCastData& _rayData)
{
	//���f���̃g�����X�t�H�[�����J���L�����[�V����
	modelList_[_hModel]->transform_.Calclation();
	//�@���[���h�s��̋t�s��
	XMMATRIX wInv = XMMatrixInverse(nullptr, modelList_[_hModel]->transform_.GetWorldMatrix());
	//�A���C�̒ʉߓ_�����߂�(���f����Ԃł̗�̕����x�N�g�������߂�)
	XMFLOAT4 start = { _rayData.start.x,_rayData.start.y,_rayData.start.z,1.0f };
	XMFLOAT4 dir;XMStoreFloat4(&dir, _rayData.dir);

	XMVECTOR vPass{ start.x + dir.x,
					start.y + dir.y,
					start.z + dir.z,
					start.w + dir.w };

	//�BrayData.start�����f����Ԃɕϊ�(�@��������)
	XMVECTOR vStart = XMLoadFloat4(&start);
	vStart = XMVector3TransformCoord(vStart, wInv);
	//�C�i�n�_��������x�N�g�������傢�L�΂�����j�ʉߓ_�i�A�j�ɇ@��������
	vPass = XMVector2TransformCoord(vPass, wInv);
	//�DrayData.dir�B����C�Ɍ������x�N�g���ɂ���i�����Z�j
	vPass = vPass - vStart;
	XMStoreFloat4(&dir, vPass);

	//�w�肵�����f���ԍ���FBX�Ƀ��C�L���X�g�I
	modelList_[_hModel]->fbx_->RayCast(_rayData);
}
