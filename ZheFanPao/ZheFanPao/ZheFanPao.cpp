#include <graphics.h>
#include <conio.h>
#include <time.h>
#include "EasyXPng.h" //用于显示带透明通道的png图/
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)
#define WIDTH 640  //画面宽度
#define HEIGHT 480 //画面高度
int x = WIDTH / 2;
int y = HEIGHT / 2;
int v = 10;
int main()
{
	initgraph(WIDTH, HEIGHT);
	int i = 0;
	int to = 1;
	IMAGE bkground;
	TCHAR filename[20];
	loadimage(&bkground, _T("bg.png"));
	IMAGE imgd[7];
	IMAGE imgw[7];
	IMAGE imgs[7];
	IMAGE imga[7];
	for (i = 0; i < 7; i++)
	{
		_stprintf(filename, _T("./girl/gd%d.png"), i);
		loadimage(&imgd[i], filename);
		_stprintf(filename, _T("./girl/gl%d.png"), i);
		loadimage(&imga[i], filename);
		_stprintf(filename, _T("./girl/gr%d.png"), i);
		loadimage(&imgs[i], filename);
		_stprintf(filename, _T("./girl/gu%d.png"), i);
		loadimage(&imgw[i], filename);
	}
	i = 0;
	while (1)
	{
		putimage(0, 0, &bkground);
			
			
			if (x <= v)
			{
				to = 2;
			
			}
			if (x >= WIDTH - v - imgd->getwidth())
			{
				to = 1;
			}
		
			if (to == 1)
			{
				x = x - v;
				putimagePng(x, y, &imga[i]);
		    }
			else if (to == 2)
			{
				x = x + v;
				putimagePng(x, y, &imgs[i]);
			}
			
		Sleep(200);
		i += 1;

		cleardevice();

		if (i == 7)
			i = 0;

	}
	_getch();
	return 0;
}