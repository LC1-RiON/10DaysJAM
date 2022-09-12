#include "DxLib.h"

const char TITLE[] = "GAME TITLE";

const int WIN_WIDTH = 1280;

const int WIN_HEIGHT = 720;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// �E�B���h�E���[�h
	ChangeWindowMode(TRUE);

	// �E�B���h�E�^�C�g��
	SetMainWindowText(TITLE);

	// �𑜓x�ƃJ���[�r�b�g
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);

	// �w�i�F
	SetBackgroundColor(0, 0, 0);

	// DX���C�u�����������N��
	if (DxLib_Init() == -1) {
		return -1;
	}

	// ���ʕ`��
	SetDrawScreen(DX_SCREEN_BACK);

	// ���L�[���Ƌ��L�[���
	char keys[256] = {};
	char oldkeys[256] = {};

#pragma region �ϐ��y�у��\�[�X�̐錾�E��`
	int playerX = WIN_WIDTH / 2;
	int playerY = WIN_HEIGHT / 2;
	int playerMode = 0;
	int playerRange = 200;

	int enemyX = WIN_WIDTH - 20;
	int enemyY = WIN_HEIGHT / 2;
	int enemyMode = 2;
	int enemySpeed = 4;

	int flight = 0;

	int graphBack[2];
	graphBack[0] = LoadGraph("background.png");
	graphBack[1] = LoadGraph("background.png");
	int backX = 0;
#pragma endregion �ϐ��y�у��\�[�X�̐錾�E��`

	// �Q�[�����[�v
	while (1)
	{
		// �L�[���X�V
		for (int i = 0; i < 256; i++)
		{
			oldkeys[i] = keys[i];
		}
		GetHitKeyStateAll(keys);

		// �X�N���[���N���A
		ClearDrawScreen();

#pragma region �X�V����
		flight++;
		// ���[�h�`�F���W
		if (keys[KEY_INPUT_R] == 1 || keys[KEY_INPUT_G] == 1 || keys[KEY_INPUT_B] == 1) {
			if (keys[KEY_INPUT_R] == 1 && oldkeys[KEY_INPUT_R] == 0) {
				playerMode = 0;
			}
			else if (keys[KEY_INPUT_G] == 1 && oldkeys[KEY_INPUT_G] == 0) {
				playerMode = 1;
			}
			else if (keys[KEY_INPUT_B] == 1 && oldkeys[KEY_INPUT_B] == 0) {
				playerMode = 2;
			}
		}
		enemyX -= enemySpeed;
		// ���@�˒����ߑ�
		if (enemyX - playerX <= playerRange) {
			// �L������
			if (playerMode == enemyMode) {
				enemyX = WIN_WIDTH + 20;
				enemyMode = rand() % 3;
			}
		}
		// �G�@����
		if (enemyX - playerX <= 5) {
			enemyX = WIN_WIDTH + 20;
			enemyMode = rand() % 3;
		}
		// �w�i�X�N���[��
		backX--;
		if (backX <= -WIN_WIDTH) {
			backX += WIN_WIDTH;
		}
#pragma endregion �X�V����

#pragma region �`�揈��
		// �X�N���[���w�i
		for (int i = 0; i < 2; i++)
		{
			DrawGraph(backX + i * WIN_WIDTH, 0, graphBack[i], FALSE);
		}
		// ���G�@�A���@���͂�����RGB
		if (enemyMode == 0) {
			DrawTriangle(
				enemyX + 10, enemyY + 10,
				enemyX + 10, enemyY - 10,
				enemyX - 10, enemyY,
				GetColor(255, 0, 0), TRUE
			);
		}
		else if (enemyMode == 1) {
			DrawTriangle(
				enemyX + 10, enemyY + 10,
				enemyX + 10, enemyY - 10,
				enemyX - 10, enemyY,
				GetColor(0, 255, 0), TRUE
			);
		}
		else if (enemyMode == 2) {
			DrawTriangle(
				enemyX + 10, enemyY + 10,
				enemyX + 10, enemyY - 10,
				enemyX - 10, enemyY,
				GetColor(0, 0, 255), TRUE
			);
		}
		// ���@����̎O�p�`
		if (playerMode == 0) {
			DrawTriangle(
				playerX - 10, playerY + 10,
				playerX - 10, playerY - 10,
				playerX + 10, playerY,
				GetColor(255, 128, 128), TRUE
			);
		}
		else if (playerMode == 1) {
			DrawTriangle(
				playerX - 10, playerY + 10,
				playerX - 10, playerY - 10,
				playerX + 10, playerY,
				GetColor(128, 255, 128), TRUE
			);
		}
		else if (playerMode == 2) {
			DrawTriangle(
				playerX - 10, playerY + 10,
				playerX - 10, playerY - 10,
				playerX + 10, playerY,
				GetColor(128, 128, 255), TRUE
			);
		}
		// ���@���e�B�N��
		DrawCircle(playerX + playerRange, playerY, 5, GetColor(255, 255, 255), false);
#pragma endregion �`�揈��

		// �X�N���[���t���b�v
		ScreenFlip();

		// �E�B���h�E���b�Z�[�W����
		if (ProcessMessage() == -1) {
			break;
		}
	}

	// DX���C�u�����I��
	DxLib_End();

	// ���C������I��
	return 0;
}