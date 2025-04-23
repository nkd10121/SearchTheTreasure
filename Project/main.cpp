#include "DxLib.h"
#include "SceneManager.h"
#include "SceneBase.h"
#include "SceneTitle.h"
#include "Input.h"
#include <cmath>
#include <memory>

namespace
{
	//�E�B���h�E�T�C�Y
	constexpr int kWindowWidth = 1280;
	constexpr int kWindowHeight = 720;
}

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// window���[�h�ݒ�
	// �ꕔ�̊֐���DxLib_Init()�̑O�Ɏ��s����K�v������
	SetGraphMode(kWindowWidth, kWindowHeight, 32);
	ChangeWindowMode(true);

	//�E�B���h�E����ύX
	SetWindowText("SearchTheTreasure");

	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}


	SetUseZBuffer3D(true);
	SetWriteZBuffer3D(true);
	SetUseBackCulling(true);

	// �_�u���o�b�t�@���[�h
	SetDrawScreen(DX_SCREEN_BACK);

	SceneManager sceneManager;
	sceneManager.ChangeScene(std::make_shared<SceneTitle>(sceneManager));


	Input input;

	while (ProcessMessage() == 0)
	{
		LONGLONG  time = GetNowHiPerformanceCount();
		// ��ʂ̃N���A
		ClearDrawScreen();
		
		input.Update();
		sceneManager.Update(input);
		sceneManager.Draw();

		//����ʂ�\��ʂ����ւ���
		ScreenFlip();

		// esc�L�[����������I������
		if (CheckHitKey(KEY_INPUT_ESCAPE))	break;

		// fps��60�ɌŒ�
		while (GetNowHiPerformanceCount() - time < 16667)
		{
		}
	}

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}