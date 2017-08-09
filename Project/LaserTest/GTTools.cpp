#include "Stdinc.h"

int IsWindowActive(void) // ret: ? ウィンドウがアクティブ状態
{
	return GetActiveFlag() ? 1 : 0;
}

void GTWaitFadeout(int resno_wallpic, double whiteLevel, int frmcnt)
{
	GTSetCurtain(whiteLevel, frmcnt);

	while(GTActWhiteLevel != whiteLevel)
	{
		SimpleDrawPic(0, 0, Pic(resno_wallpic));
		EndFrame();
	}
}

void GTDrawBox(int x, int y, int w, int h, int color)
{
	I2RGB(color);

	SetAlpha(Color_A / 255.0);
	SetBright(
		Color_R / 255.0,
		Color_G / 255.0,
		Color_B / 255.0
		);

	DrawPicRect(x, y, w, h, Pic(P_WHITEBOX));

	ResetBlend();
	ResetBright();
}
void GTDrawCircle(double x, double y, double r, int color)
{
	I2RGB(color);

	SetAlpha(Color_A / 255.0);
	SetBright(
		Color_R / 255.0,
		Color_G / 255.0,
		Color_B / 255.0
		);

	DrawBegin(x, y, Pic(P_WHITECIRCLE));
	DrawZoom(r / 50.0); // P_WHITECIRCLE の幅と高さは 100 
	DrawEnd();

	ResetBlend();
	ResetBright();
}

/*
	画面左上のドットの絶対座標
	絶対座標 (x, y) の画面上の座標は (x - GTCameraX, y - GTCameraY) になる。
*/
double GTCameraX;
double GTCameraY;
