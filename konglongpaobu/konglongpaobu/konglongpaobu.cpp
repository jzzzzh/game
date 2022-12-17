
#include <stdio.h>
#include <graphics.h>
#include "conio.h"
#include "EasyXPng.h"
#include "MyEasyPng.h"
#define WIDTH 640
#define HEIGHT 480

int speed_1 = 2, speed_2 = 3;
int dx_1 = 0, dx_2 = 0;
int dx3 = 300;
int x = WIDTH / 4;
int cnt;

int main()
{
	IMAGE im_bk, im_house, im_hill;
	initgraph(WIDTH, HEIGHT);

	int i;
	TCHAR filename[20];
	IMAGE img[8];

	for (i = 0; i < 8; i++)
	{
		_stprintf_s(filename, _T("d%d.png"), i);
		loadimage(&img[i], filename);
	}

	loadimage(&im_bk, _T("bg0.png"));
	loadimage(&im_house, _T("house.png"));
	// loadimage(&im_hill, _T("hill.png"));

	i = 0;
	BeginBatchDraw();
	while (1)
	{
		putimage(0, 0, dx_1, 300, &im_bk, WIDTH - dx_1, 0, SRCCOPY);
		putimage(dx_1, 0, WIDTH - dx_1, 300, &im_bk, 0, 0, SRCCOPY);

		putimage(0, 300, dx_2, 480, &im_bk, WIDTH - dx_2, 300, SRCCOPY);
		putimage(dx_2, 300, WIDTH - dx_2, 480, &im_bk, 0, 300, SRCCOPY);

		MyputimagePng(0, 250, dx3, 200, &im_house, WIDTH - dx3, 0);
		MyputimagePng(dx3, 250, WIDTH - dx3, 200, &im_house, 0, 0);
		putimagePng(WIDTH * 2 / 3, 360, &img[i]);
		i++;
		if (i > 7)
			i = 0;

		Sleep(60);
		FlushBatchDraw();

		dx_1 = dx_1 + speed_1;
		if (dx_1 >= WIDTH)
			dx_1 = speed_1;

		dx_2 = dx_2 + speed_2;
		dx3 = dx3 + speed_2;
		if (dx_2 >= WIDTH) {
			dx_2 = speed_2;
			//dx3 = speed_2;
		}
		if (dx3 >= WIDTH) {
			//dx_2 = speed_2;
			dx3 = speed_2;
		}
	}

	_getch();
	return 0;
}
