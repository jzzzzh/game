#include <graphics.h>
#include <conio.h>
#include <stdio.h>


const int b_x = 6;
const int b_y = 5;
bool b_exist[b_x][b_y] = { 0 };
int r = 10;
int x = 300, y = 650;
int vx = 8, vy = -10;
int i, j;
int w = 90, h = 40;
int xs, ys;
int gap = 5;
int bx = 250, len = 100, th = 15;
bool s = false;
bool f = false;
bool gift_drop = false;
bool win = false;
//bool win = true;
int vb = 30;
int giftvy = 10;
bool gift_flag = false;
int giftx = 300;
int gifty = 0;
int giftyy = 0;
int giftsize = 10;
int kbx = 300;
int kby = 0;
bool is_hold = false;
int ttime = 200;
bool gift_show = true;
TCHAR word[5];
class track
{
public:
	track();
	~track();
	track(int x, int y, bool f, int gift);
	int x;
	int y;
	bool is_touched;
	int is_gift;
private:
	
};

track::track()
{
}
track::track(int x, int y, bool f, int gift):x(x),y(y),is_touched(f),is_gift(gift)
{
}
track::~track()
{
}



boolean isTouched(float rleft, float rtop, float rright,  float rbottom, int x, int y, int r)
{
	if (rleft <= x + r && rright >= x - r && rtop <= y + r && rbottom >= y - r)
		return true;
	else
	{
		return false;
	}
}

track touch(int x, int y, track& myTrack) 
{
	int i, j;
	for (i = b_x-1; i >= 0; i--) // create a 6 * 5 matrix
		for (j = b_y-1; j >= 0; j--)
		{
			xs = i * w;
			ys = j * h;
			if (b_exist[i][j] == false && isTouched(gap * (i + 1) + xs, gap * (j + 1) + ys, gap * (i + 1) + xs + w, gap * (j + 1) + ys + h, x, y, r) == true)
			{
				myTrack.is_touched = true;
				myTrack.x = i;
				myTrack.y = j;
				b_exist[i][j] = true;
				myTrack.is_gift = rand() % 4;
				return myTrack;
			}
		}
		
	return myTrack;
}

bool is_ok()
{
	for (int i_i = 0; i_i < b_x; i_i++)
	{
		for (int j_j = 0; j_j < b_y; j_j++)
		{
			if (b_exist[i_i][j_j] == 0)
				return false;
		}
	}
	return true;
}
int main()
{
	track tr(-1, -1, false, 1);
	initgraph(600, 600);
	setbkcolor(RGB(200, 200, 200));
	setlinecolor(RGB(0, 128, 128));
	setfillcolor(RGB(0, 128, 128));
	cleardevice();
	BeginBatchDraw();
	while (1)
	{
		setfillcolor(RGB(0, 128, 128));
		
		for (i = 0; i < b_x; i++) // create a 6 * 5 matrix
			for (j = 0; j < b_y; j++)
			{
				if(b_exist[i][j] == false){
					xs = i * w;
					ys = j * h;
					fillrectangle(gap * (i + 1) + xs, gap * (j + 1) + ys, gap * (i + 1) + xs + w, gap * (j + 1) + ys + h);
				}
			}
		if (is_ok())
		{
			settextcolor(RGB(0, 0, 255));
			settextstyle(60, 0, _T("Arial"));
			outtextxy(270, 400, _T("Win"));
			win = true;
			//_getch();
		}
		setfillcolor(RGB(0, 0, 128));
		fillrectangle(bx, 560, bx + len, 560 + th); // draw the board
		//swprintf_s(word, _T("%d"), int(ttime));
		//outtextxy(100, 100, word);

		if (gift_flag == true)
		{
			if (gift_drop == false) {
				giftx = kbx;
				gifty = kby;
				gift_drop = true;
			}
			setfillcolor(RGB(128, 0, 0));
			fillrectangle(giftx, gifty, giftx + giftsize, gifty + giftsize);
			setfillcolor(RGB(0, 0, 128));
			gifty = gifty + giftvy;
			if (gifty >= 560 && gifty <= 560 + th && giftx >= bx && giftx + giftsize <= bx + len && gift_show == true) {
				is_hold = true;
				gift_show = false;
			}
			if (gifty > 600)
			{
				gift_flag = false;
				gift_drop = false;
				giftx = kbx;
				gifty = kby;
				tr.is_gift = 1;
			}
		}
		if (is_hold == true && ttime > 0)
		{
			ttime--;
			len = 200;
		}
		if (ttime <= 0)
		{
			is_hold = false;
			ttime = 200;
			len = 100;
		}

		if (_kbhit())
		{
			char input = _getch();
			if (input == ' ')
			{
				s = true; // game start
				f = true;
				for (int i_i = 0; i_i < b_x; i_i++)
				{
					for (int j_j = 0; j_j < b_y; j_j++)
					{
						b_exist[i_i][j_j] = 0;
					}
				}
			}
			if (GetAsyncKeyState(VK_LEFT))
			{
				bx = bx - vb;
				if (bx <= 0)
					bx = 0;
			}
			if (GetAsyncKeyState(VK_RIGHT))
			{
				bx = bx + vb;
				if (bx >= 500)
					bx = 500;
			}
		}
		if (!s)  //  before game has been started
		{
			setfillcolor(RGB(128, 0, 0));
			fillcircle(bx + len / 2, 560 - r, r);
		}
		else  //  after game has been started
		{
			if ((((y > 550) && (y < 600)) &&(win|| (x + r >= bx) && (x - r <= bx + len))) || (touch(x,y,tr).is_touched == true) || (y < 0)) 
			{
				if(tr.is_touched == true)
				tr.is_touched = false;
				if (tr.is_gift == 0)
				{
					gift_flag = true;
					gift_show = true;
				}
				kbx = (tr.x + 1) * gap + (tr.x) * w + w/2;
				kby = (tr.y + 1) * gap + tr.y * h + h / 2;
				vy = -vy;
			}
			if ((x > 600 - r) || (x < r))
				vx = -vx;
			if (f) // initial position of the ball
			{
				x = bx + len / 2;
				y = 560 - r;
				f = !f;
			}
			else  // the position of the ball during the game
			{
				x = x + vx;
				y = y + vy;
				if (y >= 600 && win == false)
				{
					settextcolor(RGB(0, 0, 255));
					settextstyle(60, 0, _T("Arial"));
					outtextxy(270, 400, _T("Lose"));
					for (int i_i = 0; i_i < b_x; i_i++)
					{
						for (int j_j = 0; j_j < b_y; j_j++)
						{
							b_exist[i_i][j_j] = 0;
						}
					}
					// break;
				}
			}
			setfillcolor(RGB(128, 0, 0));
			fillcircle(x, y, r);
		}

		FlushBatchDraw();
		Sleep(30);
		cleardevice();
	}
	closegraph();
	return 0;
}