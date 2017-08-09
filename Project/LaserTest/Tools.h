void noop(void);
void noop_v_vp(void *);

int atoi_x(char *line);
char *xcout(char *format, ...);
char *strx(char *line);

char *q_readLine(autoQueue<uchar> *i);
void q_writeLine(autoList<uchar> *i, char *line);
void q_writeLine_x(autoList<uchar> *i, char *line);

void trimResourceLines(autoList<char *> *lines);

template <class Element_t>
autoList<Element_t> *makeList(int count, Element_t initValue)
{
	errorCase(count < 0 || TSLD < count);

	autoList<Element_t> *list = new autoList<Element_t>();

	for(int index = 0; index < count; index++)
	{
		list->AddElement(initValue);
	}
	return list;
}

autoList<double> *makeDRndList(int count, int seed);
autoList<int> *makeRRndList(int count, int seed, int minval, int maxval);
endlessQueue<double> *makeDRndSet(int count, int seed);
endlessQueue<int> *makeRRndSet(int count, int seed, int minval, int maxval);

int RGB2I(int r, int g, int b, int a = 0xff);
extern int Color_R;
extern int Color_G;
extern int Color_B;
extern int Color_A;
void I2RGB(int color);

int IsCrashed_Box(double x1, double y1, double w1, double h1, double x2, double y2, double w2, double h2);
int IsCrashed_BoxCircle(double x1, double y1, double w1, double h1, double x2, double y2, double r2);
int IsCrashed_Circle(double x1, double y1, double r1, double x2, double y2, double r2);

void P2Vector(double x1, double y1, double x2, double y2, double r);
extern double Vect_X;
extern double Vect_Y;

double P2Angle(double x1, double y1, double x2, double y2);
void DRanger(double &d, double range = 2.0 * PI, int c_max = 1);

extern int fs_count;
extern int fs_max;
extern double fs_rate; // 0.0 - 1.0

#define forscene(frmmax) \
	for(fs_max = (frmmax), fs_count = 0; fs_count <= (frmmax) && (fs_rate = (double)fs_count / fs_max, 1); fs_count++)

#define ifsceneBegin(frmcnt, frmmax) \
	if(fs_count = (frmcnt), 0) {} ifscene((frmmax))

// frmmax: 1 -
#define ifscene(frmmax) \
	else if(fs_count <= (frmmax) ? (fs_max = (frmmax), fs_rate = (double)fs_count / (frmmax), 1) : (fs_count -= (frmmax) + 1, 0))

#define ifsceneEnd \
	else
