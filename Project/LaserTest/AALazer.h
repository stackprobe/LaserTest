#define LZSIZE 64

typedef struct LzPos_st
{
	double X;
	double Y;
}
LzPos_t;

LzPos_t MakeLzPos(double x, double y);

typedef struct Lazer_st
{
	int Color; // 0 - 6
	autoList<LzPos_t> *Track;
	int PosIndex;
}
Lazer_t;

Lazer_t *CreateLazer(int pic_resno, autoList<LzPos_t> *track_bind);
void ReleaseLazer(Lazer_t *i);

extern double LzR;

int LazerFrame(Lazer_t *i);
