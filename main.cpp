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
	int mode = 0;

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
		// ���[�h�`�F���W
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
		// �w�i�X�N���[��
		backX--;
		if (backX <= -WIN_WIDTH) {
			backX += WIN_WIDTH;
		}
#pragma endregion �X�V����

#pragma region �`�揈��
		for (int i = 0; i < 2; i++)
		{
			DrawGraph(backX + i * WIN_WIDTH, 0, graphBack[i], FALSE);
		}
		// ���@����̎O�p�`
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