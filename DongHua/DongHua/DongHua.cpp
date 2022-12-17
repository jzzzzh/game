#include <graphics.h>
#include <conio.h>
#include <time.h>
#include "EasyXPng.h" //用于显示带透明通道的png图/
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)
#define WIDTH 640  //画面宽度
#define HEIGHT 480 //画面高度
int main()
{
	initgraph(WIDTH, HEIGHT);
	int i = 0;
	TCHAR filename[20];
	IMAGE img[7];
	for (i = 0; i < 7; i++)
	{
		_stprintf(filename, _T("girl%d.png"), i);
		loadimage(&img[i], filename);
	}
	i = 0;
	while (1)
	{
		putimage(0, 0, &img[i]);
		Sleep(200);
		i += 1;
		if (i == 7)
			i = 0;
	}
	_getch();
	return 0;
}
