#include "GameData.h"
#include "Scene/SceneManager.h"
#include "Scene/SceneTitle.h"
#include "InputState.h"
#include <DxLib.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	//------------------------------------------------------
	// ウインドウ設定とDXライブラリの初期化
	//------------------------------------------------------
	// Windowsモードにする
	ChangeWindowMode(Data::kWindowMode);

	// 画面サイズの設定
	SetGraphMode(Data::kScreenWidth, Data::kScreenHeight, Data::kColorData);
	SetWindowText(L"APOTHEOSIS");

	// DXライブラリ初期化
	//ChangeWindowModeとSetWindowTextは、例外的にDxLib_Init()の前に書いているが
	//基本的にDxlibの関数はDxLib_Init()実行後に書いてください
	if (DxLib_Init() == -1)
	{
		//初期化に失敗
		return -1;
	}
	// ダブルバッファモード
	SetDrawScreen(DX_SCREEN_BACK);

	InputState input;
	SceneManager sceneManager;
	sceneManager.ChangeScene(new SceneTitle(sceneManager));

	//------------------------------------------------------
	// ゲーム部分
	//------------------------------------------------------
	// メインループ処理
	while (ProcessMessage() == 0)
	{
		LONGLONG  time = GetNowHiPerformanceCount();

		//裏画面消す
		ClearDrawScreen();

		input.Update();

		sceneManager.Update(input);
		sceneManager.Draw();

		//裏画面を表画面を入れ替える
		ScreenFlip();

		//ESCAPEを押したら終了する
		if (CheckHitKey(KEY_INPUT_ESCAPE))
		{
			break;
		}
		// fpsを60に固定
		while (GetNowHiPerformanceCount() - time < 16667)
		{
		}
	}
	//------------------------------------------------------
	// DXライブラリ終了とプログラム終了
	//------------------------------------------------------
	DxLib_End();
	return 0;
}