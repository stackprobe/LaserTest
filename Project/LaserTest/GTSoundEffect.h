enum
{
	SE_PAUSE,

	SE_MAX, // num of member
};

autoList<int> *S_SELoadedList(void);
autoList<double> *S_SEVolumeList(void);

int SE_Load(int resno, autoList<uchar> *image);
void SE_Unload(int resno, int h);
Resource_t *SE_Res(void);

void ReleaseSoundEffects(void);
int GetSERequestCount(void);

int SEFrame(void);

void SEPlay(int resno);
void SEPlayEcho(int resno);
void SEStopEcho(void);
void UpdateSEVolume(void);
