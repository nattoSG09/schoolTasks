//インクルード
#include <Windows.h>
#include <stdlib.h>
#include "resource.h"

#include "Engine/Direct3D.h"
#include "Engine/Camera.h"
#include "Engine/Input.h"
#include "Engine/Model.h"
#include "Engine/RootJob.h"
#include "Stage.h"

#pragma comment(lib, "winmm.lib")

//定数宣言
const char* WIN_CLASS_NAME = "SampleGame";  //ウィンドウクラス名
const int WINDOW_WIDTH = 800;  //ウィンドウの幅
const int WINDOW_HEIGHT = 600; //ウィンドウの高さ

RootJob* pRootJob = nullptr;

//プロトタイプ宣言
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK DialogProc(HWND hDig, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK MenuProc(HWND hMenu, UINT msg, WPARAM wParam, LPARAM lParam);



//エントリーポイント
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
	//ウィンドウクラス（設計図）を作成
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);             //この構造体のサイズ
	wc.hInstance = hInstance;                   //インスタンスハンドル
	wc.lpszClassName = WIN_CLASS_NAME;            //ウィンドウクラス名
	wc.lpfnWndProc = WndProc;                   //ウィンドウプロシージャ
	wc.style = CS_VREDRAW | CS_HREDRAW;         //スタイル（デフォルト）
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); //アイコン
	wc.hIconSm = LoadIcon(NULL, IDI_WINLOGO);   //小さいアイコン
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);   //マウスカーソル
	wc.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);                     //メニュー（なし）
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //背景（白）
	RegisterClassEx(&wc); //クラスを登録

	//ウィンドウサイズの計算
	RECT winRect = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
	AdjustWindowRect(&winRect, WS_OVERLAPPEDWINDOW, TRUE);
	int winW = winRect.right - winRect.left;     //ウィンドウ幅
	int winH = winRect.bottom - winRect.top;     //ウィンドウ高さ

	//ウィンドウを作成
	HWND hWnd = CreateWindow(
		WIN_CLASS_NAME,         //ウィンドウクラス名
		"サンプルゲーム",     //タイトルバーに表示する内容
		WS_OVERLAPPEDWINDOW, //スタイル（普通のウィンドウ）
		CW_USEDEFAULT,       //表示位置左（おまかせ）
		CW_USEDEFAULT,       //表示位置上（おまかせ）
		winW,               //ウィンドウ幅
		winH,               //ウィンドウ高さ
		NULL,                //親ウインドウ（なし）
		NULL,                //メニュー（なし）
		hInstance,           //インスタンス
		NULL                 //パラメータ（なし）
	);

	//ウィンドウを表示
	ShowWindow(hWnd, nCmdShow);

	//Direct3D初期化
	HRESULT hr;
	hr = Direct3D::Initialize(winW, winH, hWnd);
	if (FAILED(hr))
	{
		PostQuitMessage(0); //エラー起きたら強制終了
	}


	//レイキャストに関する処理
	{
		/*Fbx* pFbx = new Fbx;
		pFbx->Load("Assets/MapEditor/BoxDefault.fbx");
		RayCastData ray;
		ray.start = { 0,10,0 };
		ray.dir = { 0,-1,0,0 };
		pFbx->RayCast(ray);

		if (ray.hit)
			MessageBox(NULL, "レイキャストがヒットしました", "hit!!", MB_OK);
		else {
			MessageBox(NULL, "レイキャストがヒットしませんでした", "not hit!!", MB_OK);
		}*/
	}

	
	//カメラの初期化
	Camera::Initialize();

	//DirectInputの初期化
	Input::Initialize(hWnd);

	pRootJob = new RootJob(nullptr);
	pRootJob->Initialize();

	//ダイアログウィンドウを作成
	HWND hDlg = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_DIALOG1),hWnd, (DLGPROC)DialogProc);
	ShowWindow(hDlg,false);

	//メッセージループ（何か起きるのを待つ）
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	while (msg.message != WM_QUIT)
	{
		//メッセージあり
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		//メッセージなし
		else
		{
			//GetTimeの精度向上
			timeBeginPeriod(1);

			static DWORD countFps = 0;

			//ウィンドウ起動後、何mm秒かかったかを取得
			static DWORD startTime = timeGetTime();
			DWORD nowTime = timeGetTime();
			static DWORD lastUpdateTime = nowTime;
			if (nowTime - startTime >= 1000)
			{
				char str[16];
				wsprintf(str, "%u", countFps);
				SetWindowText(hWnd, str);

				countFps = 0;
				startTime = nowTime;
			}

			if ((nowTime - lastUpdateTime)*60 <= 1000)
			{
				continue;
			}
			lastUpdateTime = nowTime;

			countFps++;

			//debug用
			//SetWindowText(hWnd, str);
			
			timeEndPeriod(1);

			//▼ゲームの処理
			//カメラの更新
			Camera::Update();

			//入力の処理
			Input::Update();
			pRootJob->UpdateSub();

			//▼描画
			Direct3D::BeginDraw();

			//ルートジョブから、すべてのオブジェクトのドローを呼ぶ
			pRootJob->DrawSub();

			Direct3D::EndDraw();
		}
	}

	Model::Release();
	pRootJob->ReleaseSub();
	SAFE_DELETE(pRootJob);
	
	Input::Release();
	Direct3D::Release();

	return 0;
}

//ウィンドウプロシージャ（何かあった時によばれる関数）
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);  //プログラム終了
		return 0;
	case WM_MOUSEMOVE:
		Input::SetMousePosition(LOWORD(lParam), HIWORD(lParam));
		return 0;
	case WM_COMMAND:
		Stage* ps = ((Stage*)pRootJob->FindObject("Stage"));
		ps->MenuProc(hWnd, msg, wParam, lParam);
		return 0;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

//ダイアログプロシージャ―（本物）
BOOL CALLBACK DialogProc(HWND hDig, UINT msg, WPARAM wParam, LPARAM lParam)
{
	//return dynamic_cast<Stage*>(pRootJob->FindObject("Stage"))->DialogProc(hDig, msg, wParam, lParam);
	Stage* ps = ((Stage*)pRootJob->FindObject("Stage"));
	return ps->DialogProc(hDig, msg, wParam, lParam);
}