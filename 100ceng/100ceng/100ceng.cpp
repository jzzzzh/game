#include <graphics.h>  
#include <conio.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

struct Board
{
	int x, y;
	int speed;
	int muban;
	bool exist;
	bool used;
};
int w = 600, h = 600;
int bw = 100, bh = 10;
int speed = 5;
int x, y = 590;
int i = 0;
int r = 10;
int ballvy = 0;
int ballvx = 10;
int ac = 2;
bool isTouched = false;
int block_n;
TCHAR s[5];
TCHAR sc[5];
TCHAR ss[] = _T("up");
TCHAR sss[5];
Board board[6];
int lifeTime = 5;
int lowBlock = 5;
int ttime = 10;
int score = 0;
int n = 0;
int sscore = 0;
int lastBlock = 0;
auto sms1 = _T("红色为朽木，碰到太久会消失");
auto sms2 = _T("蓝色为冰块，速度会加快");
auto sms3 = _T("青色为加分点，可以加一生命");
bool if_hold(int ballx, int &bally,int r, int boardx, int boardy,int bw, bool flag, bool exist)
{
	if (ballx >= boardx && ballx <= boardx + bw && bally + r <= boardy && bally + r + ballvy >= boardy - speed && exist) 
	{
		bally = boardy - r;
		return true;
	}
	else
	{
		return false;
	}
}

int if_touched(int ballx, int &bally, bool flag)
{
	for (int ii = 0; ii < 6; ii++)
	{
		if (if_hold(ballx, bally, r, board[ii].x, board[ii].y, bw, flag, board[ii].exist))
		{
			return ii;
		}
	}
	return -1;
}
int main()
{
	
	srand((unsigned int)time(NULL));
	initgraph(w, h);
	setfillcolor(RGB(0, 0, 0));
	//speed = 5;
	for (i = 0; i < 6; i++)
	{
		board[i].x = rand() % 500;
		board[i].y = 590;
		if (i == 0)
		{
			board[i].muban = 9;
		}
		else {
			board[i].muban = rand() % 10;
		}
		board[i].exist = true;
		board[i].used = true;
		score++;
	}

	BeginBatchDraw();
	int ballx = board[0].x + bw / 2;
	int bally = board[0].y - r;
	fillcircle(ballx, bally, r);
	while (1)
	{
		
		outtextxy(300, 40, sms1);
		
		outtextxy(300, 60, sms2);
		
		outtextxy(300, 80, sms3);
		if (lifeTime > 0) 
		{
			if (bally > h || bally + r < 30)
			{
				lifeTime--;
				ballx = board[lowBlock].x + bw/2;
				bally = board[lowBlock].y - r;
				ballvy = -speed;
			}
			auto ssss = _T("剩余生命");
			outtextxy(100, 80, ssss);
			fillcircle(ballx, bally, r);
			swprintf_s(s, _T("%d"), int(lifeTime));
			outtextxy(100, 100, s);

			auto ssssl = _T("成绩");
			outtextxy(100, 40, ssssl);
			fillcircle(ballx, bally, r);
			swprintf_s(sc, _T("%d"), int(sscore));
			outtextxy(100, 60, sc);
			if (_kbhit())
			{
				char input = _getch();
				if (GetAsyncKeyState(VK_UP))
				{
					if (block_n != -1)
					{
						ballvy += -15;
					}
				}
				if (GetAsyncKeyState(VK_LEFT))
				{
					ballx = ballx - ballvx;
					if (ballx < r)
						ballx = r;
				}
				if (GetAsyncKeyState(VK_RIGHT))
				{
					ballx = ballx + ballvx;
					if (ballx > w - r)
						ballx = w - r;
				}
			}

			
			block_n = if_touched(ballx, bally, isTouched);
			if (block_n != -1) {
					sscore = (block_n-lastBlock >= 0)? sscore+ block_n - lastBlock: sscore + block_n - lastBlock + 6;
					lastBlock = block_n;
			}


			swprintf_s(sss, _T("%d"), int(block_n));
			if (block_n == -1)
			{
				isTouched = false;
			}
			else
			{
				if (ballvy > -speed)
					ballvy = -speed;
				isTouched = true;
			}
			if (isTouched != true || (ballvy < -speed))
			{
				bally += ballvy;
				ballvy += ac;
				ttime = 10;
			}
			else
			{
				ballvy = -speed;
				bally -= speed;
				
				
				if (board[block_n].muban == 0)
				{
					ttime--;
				}
				else if (board[block_n].muban == 1)
				{
					ballvx = 25;
				}
				else if (board[block_n].muban == 2 && board[block_n].used == true)
				{
					board[block_n].used = false;
					lifeTime ++;
				}
				else
				{
					ballvx = 10;
				}
				if (board[block_n].muban == 0 && ttime <= 0)
				{
					ttime = 10;
					board[block_n].exist = false;
				}
			}
			
			for (i = 0; i < 20; i++)
			{
				line(30 * i, 0, 30 * i + 15, 30);
				line(30 * i + 15, 30, 30 * (i + 1), 0);
			}
			for (i = 0; i < 6; i++)
			{
				if (i == 0 || board[i].y - board[i - 1].y > 100 || board[i].y <= 100)
				{
					if (board[i].exist == true) {
						if (board[i].muban == 0)
						{
							setfillcolor(RGB(128, 0, 0));
							fillrectangle(board[i].x, board[i].y, board[i].x + bw, board[i].y + bh);
							setfillcolor(RGB(0, 0, 0));
						}
						else if (board[i].muban == 1)
						{
							setfillcolor(RGB(0, 0, 128));
							fillrectangle(board[i].x, board[i].y, board[i].x + bw, board[i].y + bh);
							setfillcolor(RGB(0, 0, 0));
						}
						else if (board[i].muban == 2)
						{
							setfillcolor(RGB(0, 128, 128));
							fillrectangle(board[i].x, board[i].y, board[i].x + bw, board[i].y + bh);
							setfillcolor(RGB(0, 0, 0));
						}
						else
						{
							fillrectangle(board[i].x, board[i].y, board[i].x + bw, board[i].y + bh);
						}
						
					}
					board[i].y = board[i].y - speed;
				}
				if (board[i].y < 0)
				{
					if (i == 5)
						n++;
					board[i].y = h - bh;
					board[i].speed = rand() % 3 + 3;
					board[i].x = rand() % 500;
					board[i].exist = true;
					board[i].used = true;
					board[i].muban = rand() % 5;
					lowBlock = i;
				}
			}
			FlushBatchDraw();
			Sleep(100);
			cleardevice();
		}
		else
		{
			FlushBatchDraw();
			Sleep(100);
			cleardevice();
			auto sssss = _T("good game");
			outtextxy(300, 300, sssss);
		}
	}
	_getch();
	closegraph();
	return 0;
}