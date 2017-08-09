#include "Stdinc.h"

int IsWindowActive(void) // ret: ? �E�B���h�E���A�N�e�B�u���
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
	DrawZoom(r / 50.0); // P_WHITECIRCLE �̕��ƍ����� 100 
	DrawEnd();

	ResetBlend();
	ResetBright();
}

/*
	��ʍ���̃h�b�g�̐�΍��W
	��΍��W (x, y) �̉�ʏ�̍��W�� (x - GTCameraX, y - GTCameraY) �ɂȂ�B
*/
double GTCameraX;
double GTCameraY;
