#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include<math.h>
float getPointLength(float x1, float y1, float x2, float y2)
{
	return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}
boolean isLineTouched(float x1, float y1, float x2, float y2, int x, int y, int r)
{
	if (getPointLength(x1, y1, x, y) <= r || getPointLength(x2, y2, x, y) <= r)
		return false;
	else {
		return true;
	}
}
boolean isTouched(float rleft, float rright, float rtop, float rbottom, int x, int y, int r)
{
	if (rleft <= x+r && rright >= x-r && rtop <= y+r && rbottom >= y-r)
		return true;
	else
	{
		return false;
	}
}
int main()
{
	int x, y;
	int vx = 0, vy = 0;
	float v = 30;
	int g = 1;
	int r = 15;
	int p, vp;
	bool f = false;
	int flag = 0;
	initgraph(600, 800);
	setbkcolor(RGB(50, 50, 50));
	int time = 0;
	cleardevice();
	p = 50;
	const float Pi = 3.1415926;
	float lineLength = 30;
	float xEnd, yEnd;
	float angle = 0;
	float rotateSpeed = Pi / 180;
	x = 0;
	y = 600;
	vp = 3;
	int randy = 0;
	int h = 60;
	TCHAR s[] = _T("次数");
	TCHAR ss[5];
	char input;
	while (1)
	{
		angle = angle + rotateSpeed;
		if (angle > Pi / 2 || angle < 0)
		{
			rotateSpeed = -rotateSpeed;
		}
		//随机速度
		//vp = int(rand() % 10 + 1);
		//randy = int(rand() % 30 - 15);
		xEnd = lineLength * cos(-angle);
		yEnd = lineLength * sin(-angle) + 600;
		setlinecolor(RED);
		line(0, 600, xEnd, yEnd);
		fillrectangle(580, p, 600, p + h);
		p = p + vp;
		if (p >= 800 - h || p <= 0) {
			if (p <= 0)
			{
				vp = int(rand() % 20 + 1);
			}
			else
			{
				vp = -int(rand() % 20 + 1);
			}
			h = p + int(rand() % 100 + 30);
		}
			

		if (_kbhit())
		{
			input = _getch();
			if (input == ' ' && f == false)
			{
				f = true;
				vx = v * cos(-angle);
				vy = v* sin(-angle);
			}
		}
		if (f)
		{
			vy = vy + g;
			x = x + vx;
			y = y + vy;
		}
		else
		{
			x = 0;
			y = 600;
		}

		if (x >= 600 || y >= 800)
		{
			x = 0;
			y = 600;
			f = false;
		}
		setlinecolor(RED);
		fillcircle(x, y, r);
		if (time == 0 && isTouched(580, 600, p, p + h, x, y, r))
		{
			time = 5;
			flag++;
		}
		if (time > 0)
			time--;
		
		swprintf_s(ss, _T("%d"), int(flag));
		outtextxy(40, 40, ss);
		//TCHAR sss[5];
		//swprintf_s(sss, _T("%d"), int(h));
		//outtextxy(40, 90, sss);
		
		outtextxy(40, 40, ss);
		outtextxy(40, 60, s);
		Sleep(40);
		cleardevice();
	}

	_getch();
	return 0;

}
