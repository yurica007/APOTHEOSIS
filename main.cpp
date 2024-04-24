#include "GameData.h"
#include "Scene/SceneManager.h"
#include "Scene/SceneTitle.h"
#include "InputState.h"
#include <DxLib.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	//------------------------------------------------------
	// �E�C���h�E�ݒ��DX���C�u�����̏�����
	//------------------------------------------------------
	// Windows���[�h�ɂ���
	ChangeWindowMode(Data::kWindowMode);

	// ��ʃT�C�Y�̐ݒ�
	SetGraphMode(Data::kScreenWidth, Data::kScreenHeight, Data::kColorData);
	SetWindowText(L"APOTHEOSIS");

	// DX���C�u����������
	//ChangeWindowMode��SetWindowText�́A��O�I��DxLib_Init()�̑O�ɏ����Ă��邪
	//��{�I��Dxlib�̊֐���DxLib_Init()���s��ɏ����Ă�������
	if (DxLib_Init() == -1)
	{
		//�������Ɏ��s
		return -1;
	}
	// �_�u���o�b�t�@���[�h
	SetDrawScreen(DX_SCREEN_BACK);

	InputState input;
	SceneManager sceneManager;
	sceneManager.ChangeScene(new SceneTitle(sceneManager));

	//------------------------------------------------------
	// �Q�[������
	//------------------------------------------------------
	// ���C�����[�v����
	while (ProcessMessage() == 0)
	{
		LONGLONG  time = GetNowHiPerformanceCount();

		//����ʏ���
		ClearDrawScreen();

		input.Update();

		sceneManager.Update(input);
		sceneManager.Draw();

		//����ʂ�\��ʂ����ւ���
		ScreenFlip();

		//ESCAPE����������I������
		if (CheckHitKey(KEY_INPUT_ESCAPE))
		{
			break;
		}
		// fps��60�ɌŒ�
		while (GetNowHiPerformanceCount() - time < 16667)
		{
		}
	}
	//------------------------------------------------------
	// DX���C�u�����I���ƃv���O�����I��
	//------------------------------------------------------
	DxLib_End();
	return 0;
}