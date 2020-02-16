#include "Stdinc.h"

LzPos_t MakeLzPos(double x, double y)
{
	LzPos_t i;

	cb_(&i, LzPos_t);

	i.X = x;
	i.Y = y;

	return i;
}

Lazer_t *CreateLazer(int color, autoList<LzPos_t> *track_bind)
{
	Lazer_t *i = nb_(Lazer_t);

	i->Color = color;
	i->Track = track_bind;

	return i;
}
void ReleaseLazer(Lazer_t *i)
{
	delete i->Track;
	memFree(i);
}

typedef struct Shape_st
{
	LzPos_t Ctr1;
	LzPos_t Ctr2;
	LzPos_t Pos11;
	LzPos_t Pos12;
	LzPos_t Pos21;
	LzPos_t Pos22;
}
Shape_t;

double LzR = 10.0;

#define LZ_R LzR

static Shape_t MakeShape(LzPos_t *lzp1, LzPos_t *lzp2)
{
	Shape_t shp;

	P2Vector(lzp1->X, lzp1->Y, lzp2->X, lzp2->Y, LZ_R);
	double xa = Vect_X;
	double ya = Vect_Y;

	shp.Ctr1 = *lzp1;
	shp.Ctr2 = *lzp2;
	shp.Pos11 = MakeLzPos(lzp1->X - ya, lzp1->Y + xa);
	shp.Pos12 = MakeLzPos(lzp1->X + ya, lzp1->Y - xa);
	shp.Pos21 = MakeLzPos(lzp2->X - ya, lzp2->Y + xa);
	shp.Pos22 = MakeLzPos(lzp2->X + ya, lzp2->Y - xa);

	return shp;
}
static void JoinPoint(LzPos_t *lzp1, LzPos_t *lzp2, LzPos_t *ctr)
{
	double x = (lzp1->X + lzp2->X) / 2.0;
	double y = (lzp1->Y + lzp2->Y) / 2.0;

	P2Vector(ctr->X, ctr->Y, x, y, LZ_R);
	x = ctr->X + Vect_X;
	y = ctr->Y + Vect_Y;

	lzp1->X = x;
	lzp1->Y = y;
	lzp2->X = x;
	lzp2->Y = y;
}
static void JoinShape(Shape_t *shp1, Shape_t *shp2)
{
	JoinPoint(&shp1->Pos21, &shp2->Pos11, &shp2->Ctr1);
	JoinPoint(&shp1->Pos22, &shp2->Pos12, &shp2->Ctr1);
}
static void ExpShape(Shape_t *shp)
{
	P2Vector(shp->Ctr2.X, shp->Ctr2.Y, shp->Ctr1.X, shp->Ctr1.Y, 1.0);
	shp->Pos11.X += Vect_X;
	shp->Pos11.Y += Vect_Y;
	shp->Pos12.X += Vect_X;
	shp->Pos12.Y += Vect_Y;
}
static void DrawShape(Shape_t *shp, int color, int c)
{
	SetDrawMode(DX_DRAWMODE_BILINEAR); // ギャザ対策
#if 1
	DrawModiGraphF(
		(float)shp->Pos11.X, (float)shp->Pos11.Y,
		(float)shp->Pos12.X, (float)shp->Pos12.Y,
		(float)shp->Pos22.X, (float)shp->Pos22.Y,
		(float)shp->Pos21.X, (float)shp->Pos21.Y,
		Pic((D_LAZER_00_00 + color * LZSIZE + (LZSIZE - c - 1)) | DTP),
		1
		);
#else // old (ところどころ切れ目が入ってしまう)
	DrawModiGraph(
		m_d2i(shp->Pos11.X), m_d2i(shp->Pos11.Y),
		m_d2i(shp->Pos12.X), m_d2i(shp->Pos12.Y),
		m_d2i(shp->Pos22.X), m_d2i(shp->Pos22.Y),
		m_d2i(shp->Pos21.X), m_d2i(shp->Pos21.Y),
		Pic((D_LAZER_00_00 + color * LZSIZE + (LZSIZE - c - 1)) | DTP),
		1
		);
#endif
	SetDrawMode(DX_DRAWMODE_NEAREST); // デフォに戻す。
}
int LazerFrame(Lazer_t *i)
{
	const int MARGIN = 10;

	if(i->Track->GetCount() + LZSIZE + MARGIN < i->PosIndex)
	{
		return 0;
	}
	int index = i->PosIndex;

	for(int c = 0; c < LZSIZE; c++)
	{
		if(index + 3 < i->Track->GetCount())
		{
			LzPos_t *lzp1 = i->Track->ElementAt(index);
			LzPos_t *lzp2 = i->Track->ElementAt(index + 1);
			LzPos_t *lzp3 = i->Track->ElementAt(index + 2);
			LzPos_t *lzp4 = i->Track->ElementAt(index + 3);

			Shape_t shp1 = MakeShape(lzp1, lzp2);
			Shape_t shp2 = MakeShape(lzp2, lzp3);
			Shape_t shp3 = MakeShape(lzp3, lzp4);

			JoinShape(&shp1, &shp2);
			JoinShape(&shp2, &shp3);

//			ExpShape(&shp2); // 却って見苦しい。

			DrawShape(&shp2, i->Color, c);
		}
		index--;
		if(index < 0)
			break;
	}
	i->PosIndex++;
	return 1;
}
