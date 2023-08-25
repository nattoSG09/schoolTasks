#pragma once

#include <list>
#include <string>
#include "Transform.h"

class SphereCollider;

using std::string;
using std::list;
class GameObject
{
	bool isDead_;
protected:
	list<GameObject *>	childList_;
	Transform			transform_;
	GameObject*			pParent_;
	string				objectName_;
	SphereCollider*		pCollider_;

public:
	GameObject();
	GameObject(GameObject* parent, const std::string& name);
	~GameObject();

	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void Release() = 0;
	
	void DrawSub();
	void UpdateSub();
	void ReleaseSub();

	void KillMe();

	//�ʒu�E�p�x�E�傫����ݒ肷��
	void SetTransform(Transform _transform);
	void SetPosition(XMFLOAT3 _position);
	void SetPosition(float _x, float _y, float _z);
	void SetRotate(XMFLOAT3 _rotate);
	void SetRotate(float _x,float _y,float _z);
	void SetScale(XMFLOAT3 _scale);
	void SetScale(float _x, float _y, float _z);

	void MirrorPosition(GameObject* _object);

	//�ʒu�E�p�x�E�傫�����擾����
	Transform GetTransform() { return this->transform_; }
	XMFLOAT3  GetPosition() { return this->transform_.position_; }
	XMFLOAT3  GetRotate() { return this->transform_.rotate_; }
	XMFLOAT3  GetScale() { return this->transform_.scale_; }

	GameObject* FindChildObject(string _objName);

	/// <summary>
	/// �ċN�Ăяo����RootJob��T���Ă��̃A�h���X��Ԃ�
	/// </summary>
	/// <returns>RootJob�̃A�h���X(GameObject* �^)</returns>
	GameObject* GetRootJob();
	GameObject* FindObject(string _objName);

	/// <summary>
	/// �R���C�_�[��t�^����
	/// </summary>
	/// <param name="pCollider">�t�^����R���C�_�[</param>
	void AddCollider(SphereCollider* _pCollider);

	/// <summary>
	/// �����A�����̃R���C�_�[�ƃ^�[�Q�b�g���Ԃ����Ă�����...
	/// </summary>
	/// <param name="_pTarget">�^�[�Q�b�g</param>
	void Collision(GameObject* _pTarget);

	/// <summary>
	///	
	/// </summary>
	/// <param name="pTarget"></param>
	void RoundRobin(GameObject* pTarget);

	//�����ɓ�������
	//�����FpTarget ������������
	virtual void OnCollision(GameObject* pTarget){}

	template <class T>
	T* Instantiate(GameObject* parent)
	{
		T* pObject;
		pObject = new T(parent);
		pObject->Initialize();
		childList_.push_back(pObject);
		return pObject;
	}
};