#include "Stdinc.h"

typedef struct DerInfo_st
{
	int ParentPic;
	int X;
	int Y;
	int W;
	int H;
	int Handle; // HANDLE_CLOSED == 未ロード
}
DerInfo_t;

static int DerListInited;
static DerInfo_t DerList[D_MAX];
static int DerIndex;

static void AddDerInfo(int parent_pic, int x, int y, int w, int h)
{
	errorCase(D_MAX <= DerIndex);

	DerInfo_t *i = DerList + DerIndex;

	i->ParentPic = parent_pic;
	i->X = x;
	i->Y = y;
	i->W = w;
	i->H = h;
	i->Handle = HANDLE_CLOSED;

	DerIndex++;
}
static void CreateDerList(void)
{
	AddDerInfo(P_DUMMY, 0, 0, 100, 100);

	// App >

	for(int c = 0; c < 7; c++)
	for(int d = 0; d < LZSIZE; d++)
	{
		AddDerInfo(P_LAZER, c * 20, d * (256 / LZSIZE), 20, (256 / LZSIZE));
	}

	// < App

	errorCase(DerIndex != D_MAX);
}
int Der(int derno)
{
	if(!DerListInited) {
		DerListInited = 1;
		CreateDerList();
	}
	errorCase(derno < 0 || D_MAX <= derno);

	DerInfo_t *i = DerList + derno;

	if(i->Handle == HANDLE_CLOSED)
	{
		i->Handle = DerivationGraph(i->X, i->Y, i->W, i->H, Pic(i->ParentPic));
		errorCase(i->Handle == HANDLE_CLOSED);
	}
	EnableTrans = S_EnableTransList()->GetElement(i->ParentPic);
	return i->Handle;
}
void ReleaseDer(int parent_pic)
{
	if(DerListInited)
	{
		for(int derno = 0; derno < D_MAX; derno++)
		{
			DerInfo_t *i = DerList + derno;

			if(i->ParentPic == parent_pic && i->Handle != HANDLE_CLOSED)
			{
				if(DeleteGraph(i->Handle) != 0) // ? エラー
				{
					error();
				}
				i->Handle = HANDLE_CLOSED;
			}
		}
	}
}
