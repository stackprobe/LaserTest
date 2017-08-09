enum
{
	// Dummy >

	MUSIC_DCF,

	// < Dummy

	// App >

	// < App

	MUSIC_MAX, // num of member
};

autoList<double> *S_MusicVolumeList(void);

int Mus_Load(int resno, autoList<uchar> *image);
void Mus_Unload(int resno, int h);
Resource_t *Mus_Res(void);

void ReleaseMusics(void);
int GetMusicRequestCount(void);

void MusicFrame(void);

void MusicPlay(int resno, int endless_mode = 1, int from_top = 1);
void MusicFadeout(int frmcnt);
void MusicStop(void);
void UpdateMusicVolume(void);
