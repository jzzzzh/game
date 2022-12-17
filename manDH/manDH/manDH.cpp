#include <graphics.h>
#include <conio.h>
#include <time.h>
#include "EasyXPng.h" //用于显示带透明通道的png图/
#include"mmsystem.h"
#define _CRT_SECURE_NO_WARNINGS
#pragma warning (disable: 4996)
#pragma comment(lib, "Winmm.lib")
#define WIDTH 888 //画面宽度
#define HEIGHT 500 //画面高度
int main()
{
	mciSendString(_T("open Market.mp3 alias bkmusic"), NULL, 0, NULL);
	mciSendString(_T("play bkmusic repeat"), NULL, 0, NULL);
	initgraph(WIDTH, HEIGHT);
	int i = 0;
	TCHAR filename[20];
	IMAGE img[8];
	for (i = 0; i < 8; i++) {
		_stprintf(filename, _T("man%d.png"), i);
		loadimage(&img[i], filename);
	}
	i = 0;
	IMAGE bkgound;
	loadimage(&bkgound, _T("bkground.png"));

	while (1) {
		putimagePng(0, 0, &bkgound);
		putimagePng(120, 20, &img[i]);
		Sleep(200);
		i += 1;
		if (i == 7) i = 0;
	}
	_getch();
	return 0;
}
