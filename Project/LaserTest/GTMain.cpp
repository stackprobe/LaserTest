#include "Stdinc.h"

static int DxLibInited;

void termination(int errorLevel)
{
	if(DxLibInited)
	{
		DxLib_End();
	}
	exit(errorLevel);
}
void EndProc(void)
{
	// PROC_FNLZ >

	ExportSaveData();
	ReleaseResources();

	// < PROC_FNLZ

	termination(0);
}
int GTMain(char *title, void (*appMain)(void))
{
	char *tmp;

	// PROC_INIT >

	initrnd((int)time(NULL));
	ImportSaveData();

	// Core >

	SetOutApplicationLogValidFlag(false); 
	SetAlwaysRunFlag(true); // �t�H�[�J�X�O������Atrue: ����, false: �~�܂�B

	/*
		fixme:
		���̃\�[�X���R���p�C�����Ȃ��Ɠ��t���ς��Ȃ��B
		�����[�X�O�͕K�����r���h���Ă�!!
	*/
	SetMainWindowText(tmp = xcout("%s - Blt: " __DATE__ " " __TIME__, title)); memFree(tmp);

	SetGraphMode(800, 600, 32);
	ChangeWindowMode(Sd.FullScreenMode ? 0 : 1); // 0: �S���, 1: ��

	if(DxLib_Init())
	{
		return 1;
	}
	DxLibInited = 1;

	SetMouseDispFlag(Sd.DispMouseCursorMode ? 1 : 0); // 0: �}�E�X����, 1: �}�E�X�\��
	SetVSyncFlag(1);

	/*
		�E�B���h�E�̉E�����h���b�O�ŁA�E�B���h�E�L�k true: ��, false: �s��
		�ɂ���� SetWindowSizeExtendRate() �̍ő�T�C�Y�ɉe������B
	*/
	SetWindowSizeChangeEnableFlag(true);

	// < Core

	// < PROC_INIT

	appMain();

	EndProc();
}

void ApplyDispMouseCursorMode(void)
{
	SetMouseDispFlag(Sd.DispMouseCursorMode ? 1 : 0);
}
void ApplyWindowSize(void)
{
	SetWindowSizeExtendRate(Sd.WindowZoom);
	ApplyDispMouseCursorMode();
}
void ApplyScreenMode(void)
{
	int bk_vsf = VSyncFlag;

	ReleasePictures();

	/*
		�E�B���h�E����A�N�e�B�u�Ȏ��ɃX�N���[�����[�h��ύX����ƃt���[�Y����B
		������Ăяo���O�� IsWindowActive() �ŃA�N�e�B�u�ł��邱�Ƃ��m�F���ĂˁB
		�Ƃ肠���� IsWindowActive() == 0 �̎��̓L�[�E�p�b�h���͂�}�~���āA
		��A�N�e�B�u���ɂ�����Ăяo���󋵂����Ȃ��悤�ɂ���B
		�V�r�A�ȃ^�C�~���O�ŃA�N�e�B�u��Ԃ��ω�������ʖڂ��낤���ǁA�����܂ōl���Ȃ��B
	*/
	ChangeWindowMode(Sd.FullScreenMode ? 0 : 1);

	ApplyDispMouseCursorMode();
	SetVSyncFlag(bk_vsf);
}
void ReleaseResources(void)
{
	ReleasePictures();
	ReleaseMusics();
	ReleaseSoundEffects();
	ReleasePads();
}
