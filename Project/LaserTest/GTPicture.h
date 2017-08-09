enum
{
	P_DUMMY,
	P_WHITECIRCLE,
	P_WHITEBOX,

	// App >

	P_LAZER,

	// < App

	P_MAX, // num of member
};

void SILoadPixel(int h, int x, int y);
void SISavePixel(int h, int x, int y);

int Pic_Load(int resno, autoList<uchar> *image);
void Pic_Unload(int resno, int h);
Resource_t *Pic_Res(void);

void ReleasePictures(void);

autoList<void (*)(int, int, int)> *S_SoftImageFilterList(void);
autoList<void (*)(int)> *S_GraphicHandleFilterList(void);
autoList<int> *S_EnableTransList(void);

extern int EnableTrans;

/*
	Pic(D_* | DTP) Ç±ÇÒÇ»ä¥Ç∂Ç≈égÇ§ÅB
*/
#define DTP 0x40000000 // D_* To P_*

int Pic(int resno);

void SetAlpha(double a);
void SetBlendAdd(double a);
void SetBlendInv(double a = 1.0);
void ResetBlend(void);
void SetBright(double r, double g, double b);
void ResetBright(void);

void CheckPicSize(int h);
extern int Pic_W;
extern int Pic_H;

extern int ScreenSlip_X;
extern int ScreenSlip_Y;

void SimpleDrawPic(int x, int y, int h);
void SimpleDrawPic(double x, double y, int h);
void DrawPic(double x, double y, int h);
void DrawPicRect(int x, int y, int w, int h, int hdl);

void DrawBegin(double x, double y, int h);
void DrawRotate(double rot);
void DrawRotate(int numer, int denom);
void DrawXZoom(double zoom);
void DrawYZoom(double zoom);
void DrawZoom(double zoom);
void DrawEnd(void);
