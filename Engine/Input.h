#pragma once
#include <DirectXMath.h>
#include "Direct3D.h"


#include <dInput.h>

#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dInput8.lib")

#define SAFE_RELEASE(p) if(p != nullptr){ p->Release(); p = nullptr;}

namespace Input
{
	void Initialize(HWND hWnd);
	void Update();
	bool IsKey(int keyCode);
	bool IsKeyDown(int keyCode);
	bool IsKeyUp(int keyCode);
	void Release();

	///////////////////////////　マウス　//////////////////////////////////
	//マウスのボタンが押されているか調べる
	//引数：buttonCode	調べたいボタンの番号
	//戻値：押されていればtrue
	bool IsMouseButton(int buttonCode);

	//マウスのボタンを今押したか調べる（押しっぱなしは無効）
	//引数：buttonCode	調べたいボタンの番号
	//戻値：押した瞬間だったらtrue
	bool IsMouseButtonDown(int buttonCode);

	//マウスのボタンを今放したか調べる
	//引数：buttonCode	調べたいボタンの番号
	//戻値：放した瞬間だったらtrue
	bool IsMouseButtonUp(int buttonCode);


	//マウスカーソルの位置を取得
	//戻値：マウスカーソルの位置
	XMFLOAT3 GetMousePosition();

	//マウスカーソルの位置をセット
	//引数：マウスカーソルの位置
	void SetMousePosition(int x, int y);

	//そのフレームでのマウスの移動量を取得
	//戻値：X,Y マウスの移動量　／　Z,ホイールの回転量
	XMFLOAT3 GetMouseMove();
};