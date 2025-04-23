#include "DxLib.h"
#include "SceneManager.h"
#include "SceneBase.h"
#include "SceneTitle.h"
#include "Input.h"
#include <cmath>
#include <memory>

namespace
{
	//ウィンドウサイズ
	constexpr int kWindowWidth = 1280;
	constexpr int kWindowHeight = 720;
}

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// windowモード設定
	// 一部の関数はDxLib_Init()の前に実行する必要がある
	SetGraphMode(kWindowWidth, kWindowHeight, 32);
	ChangeWindowMode(true);

	//ウィンドウ名を変更
	SetWindowText("SearchTheTreasure");

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}


	SetUseZBuffer3D(true);
	SetWriteZBuffer3D(true);
	SetUseBackCulling(true);

	// ダブルバッファモード
	SetDrawScreen(DX_SCREEN_BACK);

	SceneManager sceneManager;
	sceneManager.ChangeScene(std::make_shared<SceneTitle>(sceneManager));


	Input input;

	while (ProcessMessage() == 0)
	{
		LONGLONG  time = GetNowHiPerformanceCount();
		// 画面のクリア
		ClearDrawScreen();
		
		input.Update();
		sceneManager.Update(input);
		sceneManager.Draw();

		//裏画面を表画面を入れ替える
		ScreenFlip();

		// escキーを押したら終了する
		if (CheckHitKey(KEY_INPUT_ESCAPE))	break;

		// fpsを60に固定
		while (GetNowHiPerformanceCount() - time < 16667)
		{
		}
	}

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}