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
		���\�[�X�ŗL���ʂ̃f�t�H�� 0.5 �Ȃ̂ŁA�ő� 2.0
	*/
	double MusicMasterVolume; // 0.0 - 2.0 == ���� - (�ő� * 2)
	double SEMasterVolume;    // 0.0 - 2.0 == ���� - (�ő� * 2)

	// < Classic

	// App >

	// < App
}
Sd_t;

extern Sd_t Sd;

void ImportSaveData(void);
void ExportSaveData(void);
