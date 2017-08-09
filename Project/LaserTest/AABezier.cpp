#include "Stdinc.h"

void Bezierize(autoList<LzPos_t> *track, double t, int c_max, double mimi_r)
{
	for(int c = 0; c < c_max; c++)
	{
		LzPos_t lzp1 = track->GetElement(0);
		LzPos_t lzp2;

		for(int index = 0; index < track->GetCount(); index++)
		{
			lzp2 = track->GetElement(index);

			m_approx(lzp1.X, lzp2.X, t, 0.0);
			m_approx(lzp1.Y, lzp2.Y, t, 0.0);

			track->SetElement(index, lzp1);
			lzp1 = lzp2;
		}
		track->AddElement(lzp1);
	}
	
	// Cut lead-mimi
	{
		LzPos_t *top = track->ElementAt(0);
		int index;

		for(index = 1; ; index++)
		{
			LzPos_t *lzp = track->ElementAt(index);

			if(!m_isnear(top->X, top->Y, lzp->X, lzp->Y, 1.0))
			{
				break;
			}
		}
		track->RemoveRange(0, index);
	}
	// Cut trail-mimi
	{
		LzPos_t *end = track->ElementAt(track->GetCount() - 1);
		int index;

		for(index = track->GetCount() - 2; ; index--)
		{
			LzPos_t *lzp = track->ElementAt(index);

			if(!m_isnear(end->X, end->Y, lzp->X, lzp->Y, 1.0))
			{
				break;
			}
		}
		track->SetCount(index + 1);
	}
}
