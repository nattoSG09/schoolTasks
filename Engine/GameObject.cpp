#include "GameObject.h"
#include "SphereCollider.h"

GameObject::GameObject()
	:pParent_(nullptr)
{
}

GameObject::GameObject(GameObject* parent, const std::string& name)
	:pParent_(parent),objectName_(name),isDead_(false)
{
	if(parent)
		this->transform_.pParent_ = &(parent)->transform_;
}

GameObject::~GameObject()
{
}

void GameObject::DrawSub()
{
	Draw();
	for (auto itr = childList_.begin(); itr != childList_.end(); itr++)
	{
		(*itr)->DrawSub();
	}
}

void GameObject::UpdateSub()
{
	Update();
	RoundRobin(GetRootJob());
	for (auto itr = childList_.begin(); itr != childList_.end(); itr++)
	{
		(*itr)->UpdateSub();
	}

	for (auto itr = childList_.begin(); itr != childList_.end();)
	{
		if ((*itr)->isDead_) {
			ReleaseSub();
			delete* itr;
			itr = childList_.erase(itr);
		}
		else
		{
			itr++;
		}
	}
}

void GameObject::ReleaseSub()
{
	for (auto itr = childList_.begin(); itr != childList_.end(); itr++)
	{
		(*itr)->ReleaseSub();
	}
	Release();
}

void GameObject::KillMe()
{
	isDead_ = true;
}

void GameObject::SetTransform(Transform _transform)
{
	this->transform_ = _transform;
}

void GameObject::SetPosition(XMFLOAT3 _position)
{
	this->transform_.position_ = _position;
}

void GameObject::SetPosition(float _x, float _y, float _z)
{
	SetPosition(XMFLOAT3(_x,_y,_z));
}

void GameObject::SetRotate(XMFLOAT3 _rotate)
{
	this->transform_.rotate_ = _rotate;
}

void GameObject::SetRotate(float _x, float _y, float _z)
{
	SetRotate(XMFLOAT3(_x, _y, _z));
}

void GameObject::SetScale(XMFLOAT3 _scale)
{
	this->transform_.scale_ = _scale;
}

void GameObject::SetScale(float _x, float _y, float _z)
{
	SetScale(XMFLOAT3(_x, _y, _z));
}

void GameObject::MirrorPosition(GameObject* _object)
{
	SetPosition(-_object->GetPosition().x, -_object->GetPosition().y, -_object->GetPosition().z);
}

GameObject* GameObject::FindChildObject(string _objName)
{
	if (_objName == this->objectName_) return(this);
	else {
		for (auto itr : childList_) {
			GameObject* obj = itr->FindChildObject(_objName);
			if (obj)return obj;
		}
	}
	return nullptr;
}

GameObject* GameObject::GetRootJob()
{
	if(!pParent_)return this;
	return pParent_->GetRootJob();
}

GameObject* GameObject::FindObject(string _objName)
{
	return this->GetRootJob()->FindChildObject(_objName);
}

void GameObject::AddCollider(SphereCollider* _pCollider)
{
	pCollider_ = _pCollider;
}

float GetVectorLength(const XMVECTOR& vector)
{
	DirectX::XMVECTOR squaredLength = DirectX::XMVector3LengthSq(vector);

	float length;
	DirectX::XMStoreFloat(&length, DirectX::XMVectorSqrt(squaredLength));

	return length;
}
void GameObject::Collision(GameObject* _pTarget)
{
	//ターゲットにコライダーがアタッチされていない
	if (_pTarget == this || _pTarget->pCollider_ == nullptr) return;

	//もし、自分のコライダーとターゲットがぶつかっていたら...
	float dist = GetVectorLength(XMVectorSubtract(XMLoadFloat3(&_pTarget->transform_.position_),XMLoadFloat3(&this->transform_.position_)));
	float rDist = (this->pCollider_->GetRadius() + _pTarget->pCollider_->GetRadius()) * (this->pCollider_->GetRadius() + _pTarget->pCollider_->GetRadius());
	if (dist <= rDist) {
		float p = 5;
	}
}

void GameObject::RoundRobin(GameObject* pTarget)
{
	if(pCollider_ == nullptr)return;
	if (pTarget->pCollider_ != nullptr)Collision(pTarget);

	//自分の子供全部とターゲット
	for (auto itr : pTarget->childList_)RoundRobin(itr);
}

