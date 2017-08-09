#include "Stdinc.h"

static singleton(LazerList, autoList<Lazer_t *>, new autoList<Lazer_t *>())

double LzOrigX;
double LzOrigY;

double LzDestX;
double LzDestY;

static int BzrPNum   = 5; // 1 - 9
static int BzrCMax   = 5; // 1 - 9 as 100 - 900
static int BzrTVal   = 5; // 1 - 9 as 0.1 - 0.9
static int BzrPScale = 5; // 1 - 9 as 1000.0 - 9000.0
static int LzWidth   = 5; // 1 - 9

const double LzRList[] =
{
	0.0, // not used
	2.0,
	4.0,
	6.0,
	8.0,
	10.0,
	20.0,
	40.0,
	100.0,
	200.0,
};

void AARoot(void)
{
	MusicPlay(MUSIC_DCF);

//	LzOrigX = 100.0;
//	LzOrigY = 100.0;
	LzOrigX = 400.0;
	LzOrigY = 300.0;

	LzDestX = 700.0;
	LzDestY = 500.0;

	const int SELECT_MAX = 5;
	int selectIndex = 0;
	int printOff = 0;

	for(; ; )
	{
		if(GTGetInput(INP_C, INP_HIT)) // test @ 2013.2.21
		{
			autoList<LzPos_t> *track = new autoList<LzPos_t>();

			// make track
			{
				track->AddElement(MakeLzPos(0.0, 0.0));

				{
					double r1 = PI * 2.0 * drnd();
					double r2 = r1 + (PI * 0.5 + PI * 0.25 * ernd()) * srnd();

					double z1 = (500.0 + 10000.0 * drnd()) * 2.0;
					double z2 = (500.0 + 10000.0 * drnd()) * 5.0;
					double z3r = -0.2;

					track->AddElement(MakeLzPos(
						cos(r1) * z1,
						sin(r1) * z1
						));
					track->AddElement(MakeLzPos(
						cos(r2) * z2,
						sin(r2) * z2
						));
					track->AddElement(MakeLzPos(
						track->GetLastElement().X * z3r,
						track->GetLastElement().Y * z3r
						));
				}

#if 0
				{
					double r1 = PI * 2.0 * drnd();
					double r2 = r1 + (PI * 0.5 + PI * 0.25 * ernd()) * srnd();

					double z1 = (500.0 + 10000.0 * drnd()) * 2.0;
					double z2 = (500.0 + 10000.0 * drnd()) * 5.0;
					double z3r = -0.2;

					track->AddElement(MakeLzPos(
						cos(r1) * z1,
						sin(r1) * z1
						));
					track->AddElement(MakeLzPos(
						cos(r2) * z2,
						sin(r2) * z2
						));
					track->AddElement(MakeLzPos(
						track->GetLastElement().X * z3r,
						track->GetLastElement().Y * z3r
						));
				}
#endif

#if 0
				{
					track->AddElement(MakeLzPos(
						(450.0 + 2 * 8000.0 * drnd()) * srnd(),
						(350.0 + 2 * 6000.0 * drnd()) * srnd()
						));
					track->AddElement(MakeLzPos(
						(450.0 + 80000.0 * drnd()) * srnd(),
						(350.0 + 60000.0 * drnd()) * srnd()
						));
					track->AddElement(MakeLzPos(
						track->GetLastElement().X * -0.1,
						track->GetLastElement().Y * -0.1
						));
				}
#endif

printOff = 1;
clsDx();
				for(int c = 0; c < track->GetCount(); c++)
				{
					LzPos_t *lzp = track->ElementAt(c);
printfDx("[%d] %f %f\n", c, lzp->X, lzp->Y);

					lzp->X += LzOrigX;
					lzp->Y += LzOrigY;
				}
				Bezierize(track, 0.9, 900, 1.0);
			}

			S_LazerList()->AddElement(CreateLazer(rnd(7), track));
		}

		if(GTGetInput(INP_A, INP_HIT))
		{
			autoList<LzPos_t> *track = new autoList<LzPos_t>();

			// make track
			{
				track->AddElement(MakeLzPos(LzOrigX, LzOrigY));

				for(int c = 0; c < BzrPNum; c++)
				{
					track->AddElement(MakeLzPos(
						400.0 + ernd() * BzrPScale * 1000.0,
						300.0 + ernd() * BzrPScale * 1000.0
						));
				}
				track->AddElement(MakeLzPos(LzDestX, LzDestY));

				Bezierize(track, BzrTVal * 0.1, BzrCMax * 100, 1.0);
			}

			S_LazerList()->AddElement(CreateLazer(rnd(7), track));
		}

		// SELECT
		{
			if(GTGetInput(INP_B, INP_HIT))
			{
				selectIndex = (selectIndex + 1) % SELECT_MAX;
			}
			int sel_add = 0;

			if(GTGetInput(INP_L, INP_HIT))
			{
				sel_add = -1;
			}
			if(GTGetInput(INP_R, INP_HIT))
			{
				sel_add = 1;
			}
			if(sel_add)
			{
				int *p;

				switch(selectIndex)
				{
				case 0: p = &BzrPNum; break;
				case 1: p = &BzrCMax; break;
				case 2: p = &BzrTVal; break;
				case 3: p = &BzrPScale; break;
				case 4: p = &LzWidth; break;

				default:
					error();
				}
				*p += sel_add;

				m_range(*p, 1, 9);
			}

			// apply
			{
				LzR = LzRList[LzWidth];
			}
		}

		const double lzdspan = 30.0;

		if(GetKeyHit(KEY_INPUT_NUMPAD2)) LzOrigY += lzdspan;
		if(GetKeyHit(KEY_INPUT_NUMPAD4)) LzOrigX -= lzdspan;
		if(GetKeyHit(KEY_INPUT_NUMPAD6)) LzOrigX += lzdspan;
		if(GetKeyHit(KEY_INPUT_NUMPAD8)) LzOrigY -= lzdspan;

		m_range(LzOrigX, 0.0, 800.0);
		m_range(LzOrigY, 0.0, 600.0);

		if(GTGetInput(INP_DIR_2, INP_HIT)) LzDestY += lzdspan;
		if(GTGetInput(INP_DIR_4, INP_HIT)) LzDestX -= lzdspan;
		if(GTGetInput(INP_DIR_6, INP_HIT)) LzDestX += lzdspan;
		if(GTGetInput(INP_DIR_8, INP_HIT)) LzDestY -= lzdspan;

		m_range(LzDestX, 0.0, 800.0);
		m_range(LzDestY, 0.0, 600.0);

		GTDrawBlackWall();
		GTDrawCircle(LzOrigX, LzOrigY, 30.0, RGB2I(  0, 128, 255, 128));
		GTDrawCircle(LzDestX, LzDestY, 30.0, RGB2I(255, 128,   0, 128));

		for(int index = 0; index < S_LazerList()->GetCount(); index++)
		{
			Lazer_t *i = S_LazerList()->GetElement(index);

			if(!LazerFrame(i)) // ? I—¹
			{
				ReleaseLazer(S_LazerList()->FastDesertElement(index));
				index--;
			}
		}

		if(!printOff)
		{
			clsDx();
			printfDx("%d\n", S_LazerList()->GetCount());

			// SELECT
			{
				int si = 0;

				printfDx("%c BzrPNum:%d\n",   si++ == selectIndex ? '>' : ' ', BzrPNum);
				printfDx("%c BzrCMax:%d\n",   si++ == selectIndex ? '>' : ' ', BzrCMax * 100);
				printfDx("%c BzrTVal:%f\n",   si++ == selectIndex ? '>' : ' ', BzrTVal * 0.1);
				printfDx("%c BzrPScale:%d\n", si++ == selectIndex ? '>' : ' ', BzrPScale * 1000);
				printfDx("%c LzWidth:%f\n",   si++ == selectIndex ? '>' : ' ', LzR);
			}
		}

		GTEndFrame();
	}
}
