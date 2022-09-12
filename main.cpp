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

#pragma endregion �X�V����

#pragma region �`�揈��
		// ��ʒ������_�̕`��e�X�g
		DrawPixel(WIN_WIDTH / 2, WIN_HEIGHT / 2, GetColor(255, 255, 255));
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