typedef struct Sd_st
{
	// Classic >

	int FullScreenMode;
	double WindowZoom; // 0.5 - 10.0
	int DispMouseCursorMode;

	struct
	{
		int Dir2;
		int Dir4;
		int Dir6;
		int Dir8;
		int A;
		int B;
		int C;
		int D;
		int E;
		int F;
		int L;
		int R;
		int Pause;
		int Select;
	}
	PadBtn;

	/*
		リソース固有音量のデフォが 0.5 なので、最大 2.0
	*/
	double MusicMasterVolume; // 0.0 - 2.0 == 無音 - (最大 * 2)
	double SEMasterVolume;    // 0.0 - 2.0 == 無音 - (最大 * 2)

	// < Classic

	// App >

	// < App
}
Sd_t;

extern Sd_t Sd;

void ImportSaveData(void);
void ExportSaveData(void);
