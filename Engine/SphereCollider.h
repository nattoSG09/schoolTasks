#pragma once

/// <summary>
/// ���`��̃R���C�_�[(�����蔻��)
/// </summary>
class SphereCollider
{
private:
	float radius_;	//���a
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="_r">���̂̔��a</param>
	SphereCollider(float _r);

	/// <summary>
	/// ���̂̔��a�̎擾
	/// </summary>
	/// <returns>���̂̔ɔ��a</returns>
	float GetRadius() { return radius_; }

};

