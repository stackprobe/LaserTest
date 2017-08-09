#include "Stdinc.h"

#define LOGFILE "C:\\tmp\\Log.txt"

void error2(char *source, int lineno, char *function)
{
	static int callcnt;

	if(callcnt)
	{
		exit(2);
	}
	callcnt++;

	DrawBox(0, 0, 800, 600, GetColor(0, 0, 64), 1);

	printfDx("----\n");
	printfDx("致命的なエラーが発生しました。\n");
	printfDx("画面に表示されているメッセージと併せてご連絡いただけると幸いです。\n");
	printfDx("エスケープキーを押して、このアプリケーションを終了して下さい。\n");
	printfDx("----\n");
	printfDx("%s (%d) %s\n", source, lineno, function);

	ScreenFlip();

	while(CheckHitKey(KEY_INPUT_ESCAPE) == 0 && ProcessMessage() != -1)
	{
		ScreenFlip();
	}
	termination(1);
}
void l2_x(char *source, int lineno, char *function, char *message)
{
	static int outed;
	FILE *fp = fileOpen(LOGFILE, outed ? "at" : "wt");

	fprintf(fp, "%s (%d) %s: %s\n", source, lineno, function, message);
	fileClose(fp);
	outed = 1;
	memFree(message);
}

void *memAlloc(int size)
{
	errorCase(size < 0 || TSLD < size);
	void *block = malloc(m_max(size, 1));
	errorCase(!block);

	return block;
}
void *memCalloc(int size)
{
	void *block = memAlloc(size);

	memset(block, 0x00, size);
	return block;
}
void *memRealloc(void *block, int size)
{
	errorCase(size < 0 || TSLD < size);
	block = realloc(block, m_max(size, 1));
	errorCase(!block);

	return block;
}
void memFree(void *block)
{
	free(block);
}
void *memClone(void *block, int size)
{
	void *newBlock = memAlloc(size);

	memcpy(newBlock, block, size);
	return newBlock;
}
