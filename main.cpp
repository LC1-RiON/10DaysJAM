#include "DxLib.h"

const char TITLE[] = "3066_TypeFlight";

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
	// 乱数初期化
	DATEDATA nowTime;
	GetDateTime(&nowTime);
	int randSeed = nowTime.Sec + nowTime.Min + nowTime.Hour + nowTime.Day + nowTime.Mon + nowTime.Year;
	srand(randSeed);

	// 自機ステ
	int playerX = 100;
	int playerY = WIN_HEIGHT / 2;
	int playerMode = 0;
	int playerRange = 200;
	const int playerCT = 10;
	int playerChange = playerCT;
	int playerRail = 1;

	// 敵機ステ
	const int enemyNum = 50;
	int enemyX[enemyNum];
	int enemyY[enemyNum];
	int enemyAlive[enemyNum];
	int enemyMode[enemyNum];
	int enemySpeed[enemyNum];
	int enemySpawn[enemyNum];
	int enemyRail[enemyNum];
	int enemyLimit = 1;

	for (int i = 0; i < enemyNum; i++)
	{
		enemyX[i] = WIN_WIDTH + 10;
		enemyY[i] = WIN_HEIGHT / 2;
		enemyAlive[i] = 0;
		enemyMode[i] = rand() % 3;
		enemySpeed[i] = 4;
		enemySpawn[i] = rand() % 150 + 30;
		enemyRail[i] = 1;
	}

	int gateX = WIN_WIDTH + 5;
	int gateY = playerY;
	int gateFlag = 0;
	int gateType = rand() % 3;
	int gateRail = rand() % 2 * 2;/*0:上中、1:上下、2:中下*/
	int score = 0;
	int flight = 0;

	int graphBack[2];
	graphBack[0] = LoadGraph("background.png");
	graphBack[1] = LoadGraph("background.png");
	int backX = 0;
	int graphTitle;
	graphTitle = LoadGraph("title.png");
	int graphPlayer[3];
	graphPlayer[0] = LoadGraph("playerR.png");
	graphPlayer[1] = LoadGraph("playerG.png");
	graphPlayer[2] = LoadGraph("playerB.png");
	int graphEnemy[3];
	graphEnemy[0] = LoadGraph("enemyR.png");
	graphEnemy[1] = LoadGraph("enemyG.png");
	graphEnemy[2] = LoadGraph("enemyB.png");
#pragma endregion 変数及びリソースの宣言・定義

	enum Scene {
		TITLE, PLAY, RESULT
	};
	int scene = TITLE;

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
		switch (scene) {
		case TITLE:
			if (CheckHitKeyAll(DX_CHECKINPUT_KEY)) {
				scene = PLAY;
			}
			break;

		case PLAY:
			flight++;
			// モードチェンジ
			if (playerChange > 0)
				playerChange--;
			else if (playerChange <= 0) {
				if (keys[KEY_INPUT_R] == 1 || keys[KEY_INPUT_G] == 1 || keys[KEY_INPUT_B] == 1) {
					if (keys[KEY_INPUT_R] == 1 && oldkeys[KEY_INPUT_R] == 0 && playerMode != 0) {
						playerMode = 0;
						playerChange = playerCT;
					}
					else if (keys[KEY_INPUT_G] == 1 && oldkeys[KEY_INPUT_G] == 0 && playerMode != 1) {
						playerMode = 1;
						playerChange = playerCT;
					}
					else if (keys[KEY_INPUT_B] == 1 && oldkeys[KEY_INPUT_B] == 0 && playerMode != 2) {
						playerMode = 2;
						playerChange = playerCT;
					}
				}
			}
			for (int i = 0; i < enemyLimit; i++) {
				// 生存時挙動
				if (enemyAlive[i] == 1) {
					enemyX[i] -= enemySpeed[i];
					// 自機射程内捕捉
					if (enemyX[i] - playerX <= playerRange) {
						// 有効属性
						if (playerMode == enemyMode[i]) {
							score += 100 + (playerRange - (enemyX[i] - playerX));
							enemyAlive[i] = 0;
							enemySpawn[i] = rand() % 150 + 30;
						}
					}
					// 敵機直撃
					if (enemyX[i] - playerX <= 5) {
						enemyAlive[i] = 0;
						enemySpawn[i] = rand() % 150 + 30;
					}
				}
				// 出現時挙動
				else if (enemyAlive[i] == 0) {
					enemySpawn[i]--;
					if (enemySpawn[i] <= 0) {
						enemyAlive[i] = 1;
						enemyRail[i] = playerRail;
						enemyX[i] = WIN_WIDTH + 10;
						enemyMode[i] = rand() % 3;
					}
				}
			}
			enemyLimit = 1 + score / 1000;
			// ゲート挙動
			if (score >= 10000) {
				if (gateFlag == 0) {
					if (rand() % 6000 == 0) {
						gateFlag = 1;
						switch (playerRail) {
						case 0:
							// 0or1
							gateRail = rand() % 2;
							break;
						case 1:
							// 0or2
							gateRail = rand() % 2 * 2;
							break;
						case 2:
							// 1or2
							gateRail = rand() % 2 + 1;
							break;
						}
					}
				}
				else if (gateFlag == 1) {
					gateX -= 4;
				}
			}
			// 背景スクロール
			backX--;
			if (backX <= -WIN_WIDTH) {
				backX += WIN_WIDTH;
			}
			break;

		case RESULT:
			break;
		}
#pragma endregion 更新処理

#pragma region 描画処理
		switch (scene) {
		case TITLE:
			DrawGraph(0, 0, graphTitle, FALSE);
			break;

		case PLAY:
			// スクロール背景
			for (int i = 0; i < 2; i++)
			{
				DrawGraph(backX + i * WIN_WIDTH, 0, graphBack[i], FALSE);
			}
			for (int i = 0; i < enemyNum; i++) {
				// 仮敵機、自機よりはっきりRGB
				if (enemyAlive[i] == 1) {
					if (enemyMode[i] == 0) {
						DrawGraph(enemyX[i]-32, enemyY[i]-32, graphEnemy[0], TRUE);
					}
					else if (enemyMode[i] == 1) {
						DrawGraph(enemyX[i]-32, enemyY[i]-32, graphEnemy[1], TRUE);
					}
					else if (enemyMode[i] == 2) {
						DrawGraph(enemyX[i]-32, enemyY[i]-32, graphEnemy[2], TRUE);
					}
				}
			}
			// 自機代わりの三角形、とモードチェンジのなんか波動
			if (playerMode == 0) {
				DrawCircle(playerX, playerY, playerChange * 3, GetColor(255, 128, 128), FALSE);
				DrawGraph(playerX - 32, playerY - 32, graphPlayer[0], TRUE);
			}
			else if (playerMode == 1) {
				DrawCircle(playerX, playerY, playerChange * 3, GetColor(128, 255, 128), FALSE);
				DrawGraph(playerX - 32, playerY - 32, graphPlayer[1], TRUE);
			}
			else if (playerMode == 2) {
				DrawCircle(playerX, playerY, playerChange * 3, GetColor(128, 128, 255), FALSE);
				DrawGraph(playerX - 32, playerY - 32, graphPlayer[2], TRUE);
			}
			// 自機レティクル
			DrawCircle(playerX + playerRange, playerY, 5, GetColor(255, 255, 255), false);
			break;

		case RESULT:
			break;
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