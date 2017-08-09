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
	SetAlwaysRunFlag(true); // フォーカス外したら、true: 動く, false: 止まる。

	/*
		fixme:
		このソースをコンパイルしないと日付が変わらない。
		リリース前は必ずリビルドしてね!!
	*/
	SetMainWindowText(tmp = xcout("%s - Blt: " __DATE__ " " __TIME__, title)); memFree(tmp);

	SetGraphMode(800, 600, 32);
	ChangeWindowMode(Sd.FullScreenMode ? 0 : 1); // 0: 全画面, 1: 窓

	if(DxLib_Init())
	{
		return 1;
	}
	DxLibInited = 1;

	SetMouseDispFlag(Sd.DispMouseCursorMode ? 1 : 0); // 0: マウス消し, 1: マウス表示
	SetVSyncFlag(1);

	/*
		ウィンドウの右下をドラッグで、ウィンドウ伸縮 true: 可, false: 不可
		可にすると SetWindowSizeExtendRate() の最大サイズに影響する。
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
		ウィンドウが非アクティブな時にスクリーンモードを変更するとフリーズする。
		これを呼び出す前に IsWindowActive() でアクティブであることを確認してね。
		とりあえず IsWindowActive() == 0 の時はキー・パッド入力を抑止して、
		非アクティブ時にこれを呼び出す状況を作らないようにする。
		シビアなタイミングでアクティブ状態が変化したら駄目だろうけど、そこまで考えない。
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
