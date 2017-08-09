#include "Stdinc.h"

void noop(void)
{
	// noop
}
void noop_v_vp(void *vp)
{
	// noop
}

int atoi_x(char *line)
{
	int value = atoi(line);

	memFree(line);
	return value;
}
char *xcout(char *format, ...)
{
	char *buffer;
	va_list marker;

	va_start(marker, format);

	for(int size = strlen(format) + 128; ; size *= 2)
	{
		buffer = (char *)memAlloc(size + 20);
		int retval = _vsnprintf(buffer, size + 10, format, marker);
		buffer[size + 10] = '\0'; // 念のため閉じる。

		if(0 <= retval && retval <= size)
		{
			break;
		}
		memFree(buffer);

		errorCase(TSLD / 2 < size);
	}
	va_end(marker);

	return buffer;
}
char *strx(char *line)
{
	return (char *)memClone(line, strlen(line) + 1);
}

char *q_readLine(autoQueue<uchar> *i)
{
	errorCase(!i);

	autoList<char> *buffer = new autoList<char>();

	for(; ; )
	{
		int chr = i->Dequeue('\n');

		if(chr == '\r')
		{
			chr = i->Dequeue();
			errorCase(chr != '\n');
			break;
		}
		if(chr == '\n')
		{
			break;
		}
		buffer->AddElement(chr);
	}
	buffer->AddElement('\0');

	char *line = buffer->UnbindList(NULL);

	delete buffer;
	return line;
}
void q_writeLine(autoList<uchar> *i, char *line)
{
	errorCase(!i);
	errorCase(!line);

	for(char *p = line; *p; p++)
	{
		i->AddElement(*p);
	}
	i->AddElement('\r');
	i->AddElement('\n');
}
void q_writeLine_x(autoList<uchar> *i, char *line)
{
	q_writeLine(i, line);
	memFree(line);
}

void trimResourceLines(autoList<char *> *lines)
{
	for(int index = 0; index < lines->GetCount(); index++)
	{
		char *line = lines->GetElement(index);

		if(line[0] == ';') // ? Comment
		{
			line[0] = '\0';
		}
		if(line[0] == '\0')
		{
			memFree(lines->DesertElement(index--));
		}
	}
}

autoList<double> *makeDRndList(int count, int seed)
{
	localizeRnd();
	initrnd(seed);

	autoList<double> *list = new autoList<double>();

	for(int index = 0; index < count; index++)
	{
		list->AddElement(drnd());
	}
	unlocalizeRnd();

	return list;
}
autoList<int> *makeRRndList(int count, int seed, int minval, int maxval)
{
	localizeRnd();
	initrnd(seed);

	autoList<int> *list = new autoList<int>();

	for(int index = 0; index < count; index++)
	{
		list->AddElement(rrnd(minval, maxval));
	}
	unlocalizeRnd();

	return list;
}
endlessQueue<double> *makeDRndSet(int count, int seed)
{
	return new endlessQueue<double>(makeDRndList(count, seed));
}
endlessQueue<int> *makeRRndSet(int count, int seed, int minval, int maxval)
{
	return new endlessQueue<int>(makeRRndList(count, seed, minval, maxval));
}

int RGB2I(int r, int g, int b, int a)
{
	m_range(r, 0, 0xff);
	m_range(g, 0, 0xff);
	m_range(b, 0, 0xff);
	m_range(a, 0, 0xff);

	return (int)(
		((uint)r << 24) |
		((uint)g << 16) |
		((uint)b <<  8) |
		((uint)a <<  0)
		);
}
int Color_R;
int Color_G;
int Color_B;
int Color_A;
void I2RGB(int color)
{
	Color_R = (int)(((uint)color >> 24) & 0xff);
	Color_G = (int)(((uint)color >> 16) & 0xff);
	Color_B = (int)(((uint)color >>  8) & 0xff);
	Color_A = (int)(((uint)color >>  0) & 0xff);
}

int IsCrashed_Box(double x1, double y1, double w1, double h1, double x2, double y2, double w2, double h2)
{
	return x2 < x1 + w1 && x1 < x2 + w2 && y2 < y1 + h1 && y1 < y2 + h2;
}
int IsCrashed_BoxCircle(double x1, double y1, double w1, double h1, double x2, double y2, double r2)
{
	if(x2      < x1 && y2      < y1) return m_pow2(x1      - x2) + m_pow2(y1      - y2) < m_pow2(r2);
	if(x2      < x1 && y1 + h1 < y2) return m_pow2(x1      - x2) + m_pow2(y1 + h1 - y2) < m_pow2(r2);
	if(x1 + w1 < x2 && y2      < y1) return m_pow2(x1 + w1 - x2) + m_pow2(y1      - y2) < m_pow2(r2);
	if(x1 + w1 < x2 && y1 + h1 < y2) return m_pow2(x1 + w1 - x2) + m_pow2(y1 + h1 - y2) < m_pow2(r2);

	return
		x1 - r2 < x2 && x2 < x1 + w1 + r2 &&
		y1 - r2 < y2 && y2 < y1 + h1 + r2;
}
int IsCrashed_Circle(double x1, double y1, double r1, double x2, double y2, double r2)
{
	return m_pow2(x1 - x2) + m_pow2(y1 - y2) < m_pow2(r1 + r2);
}

/*
	(x1, y1) -> (x2, y2) の長さ r のベクトルを Vect_X, Vect_Y に格納する。
*/
void P2Vector(double x1, double y1, double x2, double y2, double r)
{
	errorCase(r == 0.0);

	Vect_X = x2 - x1;
	Vect_Y = y2 - y1;

	double rrd = sqrt(m_pow2(Vect_X) + m_pow2(Vect_Y));

	if(rrd != 0.0)
	{
		r /= rrd;

		Vect_X *= r;
		Vect_Y *= r;
	}
}
double Vect_X;
double Vect_Y;

/*
	r は GetAngle(cos(r), sin(r)) とだいたい同じ。
*/
static double GetAngle(double x, double y)
{
	if(y < 0.0) return 2.0 * PI - GetAngle(x, -y);
	if(x < 0.0) return PI - GetAngle(-x, y);

	if(x == 0.0) return PI / 2.0;
	if(y == 0.0) return 0.0;

	double r1 = 0.0;
	double r2 = 0.5 * PI;
	double rm;
	double t = y / x;

	for(int count = 10; ; count--) // 10回でだいたい0.000767以下の誤差
	{
		rm = (r1 + r2) / 2.0;

		if(!count)
			break;

		if(t < tan(rm))
			r2 = rm;
		else
			r1 = rm;
	}
	return rm;
}
/*
	(x1, y1) -> (x1 + 1, y1) から (x1, y1) -> (x2, y2) が時計廻りに何度傾いているか返す。
	一周 == 2 * PI
	時計の3時の方向からであることに注意 (画面の座標系は、yが下方向にプラスのため)
*/
double P2Angle(double x1, double y1, double x2, double y2)
{
	return GetAngle(x2 - x1, y2 - y1);
}
void DRanger(double &d, double range, int c_max)
{
	if(d < 0.0)
	{
		for(int c = 0; c < c_max; c++)
		{
			d += range;

			if(0.0 <= d)
				break;
		}
	}
	else if(range < d)
	{
		for(int c = 0; c < c_max; c++)
		{
			d -= range;

			if(d <= range)
				break;
		}
	}
	m_range(d, 0.0, range); // 2bs
}

int fs_count;
int fs_max;
double fs_rate;
