
#include <stdio.h>
#include <graphics.h>
#include "conio.h"
#include "EasyXPng.h"

#define WIDTH  800
#define HEIGHT 600
const int Vy = -10;
const int g = 1;
int dx_1 = 0, dx_2 = 0;
bool fly = false;
int vy = Vy;

int main()
{
	IMAGE im_bk, im_land, img[8], img_j;
	initgraph(WIDTH, HEIGHT);

	int i, j;
	int height = img[0].getheight();;
	int man_y = HEIGHT * 2 / 3 - height;
	TCHAR filename[20];

	for (i = 0; i < 8; i++)
	{
		_stprintf_s(filename, _T("runright%d.png"), i);
		loadimage(&img[i], filename);
	}
	height = img[0].getheight();

	loadimage(&im_bk, _T("landscape1.png"));
	loadimage(&im_land, _T("land.png"));
	loadimage(&img_j, _T("jumpleft.png"));
	i = 0;
	BeginBatchDraw();
	while (1)
	{
		putimage(dx_1, 0, &im_bk);
		dx_1 -= 2;
		if (dx_1 <= -1200)
			dx_1 = 0;

		for (j = 0; j < 9; j++)

			putimage(j * 100 + dx_2, HEIGHT * 2 / 3, &im_land);
		dx_2 -= 3;
		if (dx_2 <= -100)
			dx_2 = 0;
	
		if (i > 7) i = 0;
		if (fly == true)
		{

			if (man_y <= HEIGHT * 2 / 3 - height)
			{
				man_y = man_y + vy;
				vy += g;
			}
			else
			{
				fly = false;
			}
			putimagePng(WIDTH / 4, man_y, &img_j);
		}
		else
		putimagePng(WIDTH / 4, HEIGHT * 2 / 3 - height, &img[i]);
		if (_kbhit())
		{
			if (_getch() == ' ')
			{
				fly = true;
				vy = Vy;
				man_y = HEIGHT * 2 / 3 - height;
			}
		}
	
		Sleep(65);
		i++;

		FlushBatchDraw();
	}

	_getch();
	return 0;
}

