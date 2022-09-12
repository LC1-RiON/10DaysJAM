#include "DxLib.h"

const char TITLE[] = "GAME TITLE";

const int WIN_WIDTH = 1280;

const int WIN_HEIGHT = 720;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// ウィンドウモード
	ChangeWindowMode(TRUE);

	// ウィンドウタイトル
	SetMainWindowText(TITLE);

	// 解像度とカラービット
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);

	// 背景色
	SetBackgroundColor(0, 0, 0);

	// DXライブラリ初期化起動
	if (DxLib_Init() == -1) {
		return -1;
	}

	// 裏面描画
	SetDrawScreen(DX_SCREEN_BACK);

	// 現キー情報と旧キー情報
	char keys[256] = {};
	char oldkeys[256] = {};

#pragma region 変数及びリソースの宣言・定義

#pragma endregion 変数及びリソースの宣言・定義
	// ゲームループ
	while (1)
	{
		// キー情報更新
		for (int i = 0; i < 256; i++)
		{
			oldkeys[i] = keys[i];
		}
		GetHitKeyStateAll(keys);

		// スクリーンクリア
		ClearDrawScreen();

#pragma region 更新処理

#pragma endregion 更新処理

#pragma region 描画処理
		// 画面中央白点の描画テスト
		DrawPixel(WIN_WIDTH / 2, WIN_HEIGHT / 2, GetColor(255, 255, 255));
#pragma endregion 描画処理

		// スクリーンフリップ
		ScreenFlip();

		// ウィンドウメッセージ処理
		if (ProcessMessage() == -1) {
			break;
		}
	}

	// DXライブラリ終了
	DxLib_End();

	// メイン正常終了
	return 0;
}