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
	int playerX = WIN_WIDTH / 2;
	int playerY = WIN_HEIGHT / 2;
	int mode = 0;

	int graphBack[2];
	graphBack[0] = LoadGraph("background.png");
	graphBack[1] = LoadGraph("background.png");
	int backX = 0;
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
		// モードチェンジ
		if (keys[KEY_INPUT_R] == 1 || keys[KEY_INPUT_G] == 1 || keys[KEY_INPUT_B] == 1) {
			if (keys[KEY_INPUT_R] == 1 && oldkeys[KEY_INPUT_R] == 0) {
				mode = 0;
			}
			else if (keys[KEY_INPUT_G] == 1 && oldkeys[KEY_INPUT_G] == 0) {
				mode = 1;
			}
			else if (keys[KEY_INPUT_B] == 1 && oldkeys[KEY_INPUT_B] == 0) {
				mode = 2;
			}
		}
		// 背景スクロール
		backX--;
		if (backX <= -WIN_WIDTH) {
			backX += WIN_WIDTH;
		}
#pragma endregion 更新処理

#pragma region 描画処理
		for (int i = 0; i < 2; i++)
		{
			DrawGraph(backX + i * WIN_WIDTH, 0, graphBack[i], FALSE);
		}
		// 自機代わりの三角形
		if (mode == 0) {
			DrawTriangle(
				playerX - 10, playerY + 10,
				playerX - 10, playerY - 10,
				playerX + 10, playerY,
				GetColor(255, 128, 128), TRUE
			);
		}
		if (mode == 1) {
			DrawTriangle(
				playerX - 10, playerY + 10,
				playerX - 10, playerY - 10,
				playerX + 10, playerY,
				GetColor(128, 255, 128), TRUE
			);
		}
		if (mode == 2) {
			DrawTriangle(
				playerX - 10, playerY + 10,
				playerX - 10, playerY - 10,
				playerX + 10, playerY,
				GetColor(128, 128, 255), TRUE
			);
		}
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