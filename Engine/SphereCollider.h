#pragma once

/// <summary>
/// 球形状のコライダー(当たり判定)
/// </summary>
class SphereCollider
{
private:
	float radius_;	//半径
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_r">球体の半径</param>
	SphereCollider(float _r);

	/// <summary>
	/// 球体の半径の取得
	/// </summary>
	/// <returns>球体の繁半径</returns>
	float GetRadius() { return radius_; }

};

