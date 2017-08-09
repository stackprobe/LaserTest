#include "Stdinc.h"

int FrameCount; // 192.9日くらいでカンスト
int LFrmCnt; // ローカルカウンタ、シーン毎に初期化する。(初期化のタイミングはアプリ側で任意)

int WindowIsActive;

int Hz;
int VSyncFlag; // ? グラボで同期する。
int SyncWaitMillis = 1;
int SyncNextTimeMillis;
int FRDLevel;
int MaxFRDLevel;
int FRDCount;

void SetVSyncFlag(int flag)
{
	SetDrawScreen(DX_SCREEN_BACK);
	SetWaitVSyncFlag(flag ? true : false);

	VSyncFlag = flag;
}
static void CheckHz(void)
{
	static int lasttimems;
	int timems = GetNowCount();

	if(lasttimems + 16 != timems && lasttimems + 17 != timems) // 16, 17 [ms] ではない。-> 異常
	{
		FRDLevel += 10;

		if(100 <= FRDLevel) // ? 処理落ち確定
		{
			if(FrameCount <= 600) // ? 開始 10 [s] 以内 -> 様子見
			{
				if(VSyncFlag)
				{
					SetVSyncFlag(0);
				}
			}
			else
			{
				FRDCount++;
			}
			FRDLevel = 0;
		}
	}
	else
		m_decrement(FRDLevel);

	// Update Hz
	{
		static int hzcnt;
		const int CYCLE = 1000;
		int diffsec = timems / CYCLE - lasttimems / CYCLE;

		hzcnt++;

		if(diffsec)
		{
			errorCase(diffsec < 0);

			Hz = hzcnt / diffsec;
			hzcnt = 0;
		}
	}
	lasttimems = timems;
}
static void SyncFrame(void)
{
	if(!VSyncFlag)
	{
		int timems = GetNowCount();

		if(SyncNextTimeMillis < timems)
		{
			SyncNextTimeMillis = timems;
		}
		else
		{
			do
			{
				Sleep(SyncWaitMillis);
			}
			while(GetNowCount() < SyncNextTimeMillis);
		}
		SyncNextTimeMillis += FrameCount % 3 == 0 ? 17 : 16;
	}
}
void EndFrame(void)
{
	if(!SEFrame())
	{
		MusicFrame();
	}

	// Core >

	ScreenFlip();
	SyncFrame();

	if(CheckHitKey(KEY_INPUT_ESCAPE) == 1 || ProcessMessage() == -1)
	{
		EndProc();
	}

	// < Core

	CheckHz();

	FrameCount++;
	errorCase(TSLD < FrameCount); // まさかのカンスト
	LFrmCnt++;

	WindowIsActive = IsWindowActive();

	PadFrame();
	KeyFrame();
}
