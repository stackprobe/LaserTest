enum
{
	// input >

	INP_DIR_2,
	INP_DIR_4,
	INP_DIR_6,
	INP_DIR_8,
	INP_A,
	INP_B,
	INP_C,
	INP_D,
	INP_E,
	INP_F,
	INP_L,
	INP_R,
	INP_PAUSE,
	INP_SELECT,

	// < input

	INP_MAX, // num of 'input' member

	// mode >

	INP_PRESS,
	INP_DOWN,
	INP_PRESSCOUNT,
	INP_HIT,

	// < mode
};

extern int GTPrimaryPadno;

int GTGetInput(int input, int mode);
void GTFreezeInput(void);
