//实现了怪物的主动追踪功能，人在哪，怪物就有一定概率追着人走（可以站着不动试试看，会发现会死）
//实现了保证出生地不会卡死的问题
//实现了模块话设计，只需要修改参数就可以调整游戏难度
//空格实现炸弹功能eiJ
#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <time.h>
class Mon
{
public:
	int x;
	int y;
	bool is_dead;
	Mon();
	Mon(int x, int y, bool is_dead);
};
Mon::Mon() {}
Mon::Mon(int x, int y, bool is_dead) : x(x), y(y), is_dead(is_dead) {}
time_t t;
const int map_width = 850;
const int map_height = 650;
const int zhuansize = 50;
const int size = 50;
const int block_width = map_width / size;
const int block_height = map_height / size;
const int r = 25;
const int mon_num = 10;
const int mon_v = size;
const int man_v = size;
const int flash_v = 50;
const int easy = 10;
const int boom_time = 40;
bool boom_died = false;
int boom_pos_x = 0;
int boom_pos_y = 0;
int v = 10;
int mon2manX = 0;
int mon2manY = 0;
Mon mon[mon_num];
bool boom_flag = false;
int Btime = boom_time;
int perxi = 0;
int peryi = 0;
int perx = 0;
int pery = 0;
// 0为空 1为石头 2为砖块
int on[block_height][block_width] = {0};
TCHAR word[5];
TCHAR word2[5];
int pos2point(int pos)
{
	if ((pos - size / 2) % size == 0)
		return (pos - size / 2) / size;
	else
	{
		return -1;
	}
}
void init_mon()
{
	for (int i = 0; i < mon_num; i++)
	{
		int x = 0;
		int y = 0;
		do
		{
			x = rand() % block_width;
			y = rand() % block_height;
		} while (on[y][x] != 0 || (perxi == x && peryi == y));
		mon[i].x = x * size + size / 2;
		mon[i].y = y * size + size / 2;
		mon[i].is_dead = false;
	}
}
void init_man()
{
	do
	{
		perxi = rand() % block_width;
		peryi = rand() % block_height;
	} while (!((on[peryi][perxi] == 0) && ((on[peryi][perxi + 1] == 0 &&
											perxi + 1 < block_width) &&
										   (on[peryi][perxi - 1] == 0 && perxi > 0) &&
										   (on[peryi - 1][perxi] == 0 && peryi > 0) &&
										   (on[peryi + 1][perxi] == 0 && peryi + 1 < block_height))));
	perx = perxi * size + size / 2;
	pery = peryi * size + size / 2;
}
void man_point2pos()
{
	perx = perxi * size + size / 2;
	pery = peryi * size + size / 2;
}
void init_rock()
{
	for (int i = 1; i < block_height; i += 2)
	{
		for (int j = 1; j < block_width; j += 2)
		{
			on[i][j] = 1;
		}
	}
}
void init_zhuankuai()
{
	for (int i = 0; i < block_height; i += 2)
	{
		for (int j = 0; j < block_width; j += 2)
		{
			on[i][j] = (rand() % 3 == 0) ? 2 : 0;
		}
	}
}
void draw_rock(int i, int j)
{
	setlinecolor(RGB(0, 128, 128));
	setfillcolor(RGB(0, 128, 128));
	fillrectangle(j * size, i * size, (j + 1) * size, (i + 1) * size);
}
void draw_person(int x, int y)
{
	setlinecolor(RGB(0, 128, 0));
	setfillcolor(RGB(0, 128, 0));
	fillcircle(x, y, r);
}
void draw_monster(int x, int y)
{
	setlinecolor(RGB(128, 0, 0));
	setfillcolor(RGB(128, 0, 0));
	fillcircle(x, y, r);
}
void draw_zhuankuai(int i, int j)
{
	setlinecolor(RGB(128, 0, 128));
	setfillcolor(RGB(128, 0, 128));
	fillrectangle(j * zhuansize, i * zhuansize, (j + 1) * zhuansize, (i + 1) * zhuansize);
}
void draw_boom()
{
	if (boom_flag == true)
	{
		setlinecolor(RGB(66, 66, 30));
		setfillcolor(RGB(66, 66, 30));
		fillcircle(boom_pos_x, boom_pos_y, r);
	}
}
void draw()
{
	for (int i = 0; i < block_height; i++)
	{
		for (int j = 0; j < block_width; j++)
		{
			if (on[i][j] == 1)
			{
				draw_rock(i, j);
			}
			else if (on[i][j] == 2)
			{
				draw_zhuankuai(i, j);
			}
		}
	}
	draw_person(perx, pery);
	draw_boom();
	for (int i = 0; i < mon_num; i++)
	{
		if (mon[i].is_dead == false)
		{
			draw_monster(mon[i].x, mon[i].y);
		}
	}
}
void how2run(int i, int mon2manXX, int mon2manYY)
{
	if (rand() % flash_v == 0)
	{
		int monx = pos2point(mon[i].y);
		int mony = pos2point(mon[i].x);
		if ((monx <= 0 || on[monx - 1][mony] != 0) && (monx >= block_height - 1 || on[monx + 1][mony] != 0))
		{
			//左右都不行
			if ((mony <= 0 || on[monx][mony - 1] != 0) && (mony >= block_width - 1 || on[monx][mony + 1] != 0))
			{
				//上下都不行
			}
			else if (!(mony <= 0 || on[monx][mony - 1] != 0) && (mony >= block_width - 1 || on[monx][mony + 1] != 0))
			{
				//可以上 不可以下
				mon[i].x = mon[i].x - mon_v;
			}
			else if ((mony <= 0 || on[monx][mony - 1] != 0) && !(mony >= block_width - 1 || on[monx][mony + 1] != 0))
			{
				mon[i].x = mon[i].x + mon_v;
				//可以下不可以上
			}
			else
			{
				if (mon2manXX < 0)
				{
					mon[i].x = mon[i].x + mon_v;
				}
				else if (mon2manXX > 0)
				{
					mon[i].x = mon[i].x - mon_v;
				}
				else
				{
					rand() % 2 == 0 ? mon[i].x = mon[i].x - mon_v : mon[i].x = mon[i].x + mon_v;
				}
				//都可以
			}
		}
		else if (!(monx <= 0 || on[monx - 1][mony] != 0) && (monx >= block_height - 1 || on[monx + 1][mony] != 0))
		{
			//可以左 不可以右
			if ((mony <= 0 || on[monx][mony - 1] != 0) && (mony >= block_width - 1 || on[monx][mony + 1] != 0))
			{
				mon[i].y = mon[i].y - mon_v;
				//上下都不行
			}
			else if (!(mony <= 0 || on[monx][mony - 1] != 0) && (mony >= block_width - 1 || on[monx][mony + 1] != 0))
			{
				//可以上 不可以下
				if (mon2manXX > 0)
				{
					mon[i].x = mon[i].x - mon_v;
				}
				else if (mon2manYY > 0)
				{
					mon[i].y = mon[i].y - mon_v;
				}
				else
				{
					rand() % 2 == 0 ? mon[i].x = mon[i].x - mon_v : mon[i].y = mon[i].y - mon_v;
				}
			}
			else if ((mony <= 0 || on[monx][mony - 1] != 0) && !(mony >= block_width - 1 || on[monx][mony + 1] != 0))
			{
				//可以下不可以上
				if (mon2manXX < 0)
				{
					mon[i].x = mon[i].x + mon_v;
				}
				else if (mon2manYY > 0)
				{
					mon[i].y = mon[i].y - mon_v;
				}
				else
				{
					rand() % 2 == 0 ? mon[i].x = mon[i].x + mon_v : mon[i].y = mon[i].y - mon_v;
				}
			}
			else
			{
				//都可以
				if (mon2manXX > 0)
				{
					mon[i].x = mon[i].x - mon_v;
				}
				else if (mon2manYY > 0)
				{
					mon[i].y = mon[i].y - mon_v;
				}
				else if (mon2manXX < 0)
				{
					mon[i].x = mon[i].x + mon_v;
				}
				else
				{
					int tmp = rand() % 3;
					if (tmp == 0)
					{
						mon[i].x = mon[i].x - mon_v;
					}
					else if (tmp == 1)
					{
						mon[i].y = mon[i].y - mon_v;
					}
					else
					{
						mon[i].x = mon[i].x + mon_v;
					}
				}
			}
		}
		else if ((monx <= 0 || on[monx - 1][mony] != 0) && !(monx >= block_height - 1 || on[monx + 1][mony] != 0))
		{
			//可以右不可以左
			if ((mony <= 0 || on[monx][mony - 1] != 0) && (mony >= block_width - 1 || on[monx][mony + 1] != 0))
			{
				mon[i].y = mon[i].y + mon_v;
				//上下都不行
			}
			else if (!(mony <= 0 || on[monx][mony - 1] != 0) && (mony >= block_width - 1 || on[monx][mony + 1] != 0))
			{
				//可以上 不可以下
				if (mon2manXX > 0)
				{
					mon[i].x = mon[i].x - mon_v;
				}
				else if (mon2manYY < 0)
				{
					mon[i].y = mon[i].y + mon_v;
				}
				else
				{
					rand() % 2 == 0 ? mon[i].x = mon[i].x - mon_v : mon[i].y = mon[i].y + mon_v;
				}
			}
			else if ((mony <= 0 || on[monx][mony - 1] != 0) && !(mony >= block_width - 1 || on[monx][mony + 1] != 0))
			{
				//可以下不可以上
				if (mon2manXX < 0)
				{
					mon[i].x = mon[i].x + mon_v;
				}
				else if (mon2manYY < 0)
				{
					mon[i].y = mon[i].y + mon_v;
				}
				else
				{
					rand() % 2 == 0 ? mon[i].x = mon[i].x + mon_v : mon[i].y = mon[i].y + mon_v;
				}
			}
			else
			{
				//都可以
				if (mon2manXX > 0)
				{
					mon[i].x = mon[i].x - mon_v;
				}
				else if (mon2manYY < 0)
				{
					mon[i].y = mon[i].y + mon_v;
				}
				else if (mon2manXX < 0)
				{
					mon[i].x = mon[i].x + mon_v;
				}
				else
				{
					int tmp = rand() % 3;
					if (tmp == 0)
					{
						mon[i].x = mon[i].x - mon_v;
					}
					else if (tmp == 1)
					{
						mon[i].y = mon[i].y + mon_v;
					}
					else
					{
						mon[i].x = mon[i].x + mon_v;
					}
				}
			}
		}
		else
		{
			//都可以
			if ((mony <= 0 || on[monx][mony - 1] != 0) && (mony >= block_width - 1 || on[monx][mony + 1] != 0))
			{
				//上下都不行
				rand() % 2 == 0 ? mon[i].y = mon[i].y - mon_v : mon[i].y = mon[i].y + mon_v;
			}
			else if (!(mony <= 0 || on[monx][mony - 1] != 0) && (mony >= block_width - 1 || on[monx][mony + 1] != 0))
			{
				//可以上 不可以下
				if (mon2manYY > 0)
				{
					mon[i].y = mon[i].y - mon_v;
				}
				else if (mon2manYY < 0)
				{
					mon[i].y = mon[i].y + mon_v;
				}
				else if (mon2manXX > 0)
				{
					mon[i].x = mon[i].x - mon_v;
				}
				else
				{
					int tmp = rand() % 3;
					if (tmp == 0)
					{
						mon[i].x = mon[i].y - mon_v;
					}
					else if (tmp == 1)
					{
						mon[i].y = mon[i].y + mon_v;
					}
					else
					{
						mon[i].x = mon[i].x - mon_v;
					}
				}
			}
			else if ((mony <= 0 || on[monx][mony - 1] != 0) && !(mony >= block_width - 1 || on[monx][mony + 1] != 0))
			{
				//可以下不可以上
				if (mon2manYY > 0)
				{
					mon[i].y = mon[i].y - mon_v;
				}
				else if (mon2manYY < 0)
				{
					mon[i].y = mon[i].y + mon_v;
				}
				else if (mon2manXX < 0)
				{
					mon[i].x = mon[i].x + mon_v;
				}
				else
				{
					int tmp = rand() % 3;
					if (tmp == 0)
					{
						mon[i].x = mon[i].y - mon_v;
					}
					else if (tmp == 1)
					{
						mon[i].y = mon[i].y + mon_v;
					}
					else
					{
						mon[i].x = mon[i].x + mon_v;
					}
				}
			}
			else
			{
				if (mon2manYY > 0)
				{
					mon[i].y = mon[i].y - mon_v;
				}
				else if (mon2manYY < 0)
				{
					mon[i].y = mon[i].y + mon_v;
				}
				else if (mon2manXX < 0)
				{
					mon[i].x = mon[i].x + mon_v;
				}
				else if (mon2manXX > 0)
				{
					mon[i].x = mon[i].x - mon_v;
				}
				else
				{
					//都可以
					int tmp = rand() % 4;
					if (tmp == 0)
					{
						mon[i].x = mon[i].x - mon_v;
					}
					else if (tmp == 1)
					{
						mon[i].y = mon[i].y - mon_v;
					}
					else if (tmp == 2)
					{
						mon[i].x = mon[i].x + mon_v;
					}
					else
					{
						mon[i].y = mon[i].y + mon_v;
					}
				}
			}
		}
	}
}
void mon_run()
{
	for (int i = 0; i < mon_num; i++)
	{
		if (mon[i].is_dead == false)
		{
			int randd = rand() % easy;
			if (randd == 0)
			{
				mon2manX = mon[i].x - perx;
				mon2manY = mon[i].y - pery;
				how2run(i, mon2manX, mon2manY);
			}
			else
			{
				mon2manX = 0;
				mon2manY = 0;
				how2run(i, mon2manX, mon2manY);
			}
		}
	}
}
bool is_died()
{
	for (int i = 0; i < mon_num; i++)
	{
		if (mon[i].x == perx && mon[i].y == pery && mon[i].is_dead == false)
		{
			return false;
		}
	}
	return true;
}
bool is_win()
{
	for (int i = 0; i < mon_num; i++)
	{
		if (mon[i].is_dead == false)
			return false;
	}
	return true;
}
void died()
{
	auto ss = _T("die");
	if (is_died() && boom_died == false)
	{
		ss = _T("win");
	}
	cleardevice();
	settextcolor(RED);
	outtextxy(map_width / 2, map_height / 2, ss);
	FlushBatchDraw();
	_getch();
	closegraph();
}
void init()
{
	srand((unsigned)time(&t));
	init_rock();
	init_zhuankuai();
	init_man();
	init_mon();
	initgraph(850, 650);
	setbkcolor(RGB(200, 200, 200));
	cleardevice();
	BeginBatchDraw();
	draw();
}
void ctrl_per_walk()
{
	if (_kbhit())
	{
		perxi = pos2point(perx);
		peryi = pos2point(pery);
		char input = _getch();
		if (GetAsyncKeyState(VK_UP))
		{
			if (peryi > 0 && on[peryi - 1][perxi] == 0)
			{
				// peryi--;
				pery -= man_v;
			}
		}
		if (GetAsyncKeyState(VK_LEFT))
		{
			if (perxi > 0 && on[peryi][perxi - 1] == 0)
			{
				// perxi--;
				perx -= man_v;
			}
		}
		if (GetAsyncKeyState(VK_RIGHT))
		{
			if (perxi < block_width - 1 && on[peryi][perxi + 1] == 0)
			{
				// perxi++;
				perx += man_v;
			}
		}
		if (GetAsyncKeyState(VK_DOWN))
		{
			if (peryi < block_height - 1 && on[peryi + 1][perxi] == 0)
			{
				// peryi++;
				pery += man_v;
			}
		}
		if (GetAsyncKeyState(VK_SPACE))
		{
			if (boom_flag == false)
			{
				setlinecolor(RGB(66, 66, 0));
				setfillcolor(RGB(66, 66, 0));
				fillcircle(perx, pery, r);
				boom_pos_x = perx;
				boom_pos_y = pery;
				boom_flag = true;
			}
			//_getch();
		}
	}
}
void booming()
{
	if (boom_flag == true)
	{
		Btime--;
		if (Btime <= 0)
		{
			boom_flag = false;
			Btime = boom_time;
			for (int i = 0; i < mon_num; i++)
			{
				if ((mon[i].x == boom_pos_x) || mon[i].y == boom_pos_y)
				{
					mon[i].is_dead = true;
				}
			}
			for (int i = 0; i < block_height; i++)
			{
				if (on[i][pos2point(boom_pos_x)] == 2)
				{
					on[i][pos2point(boom_pos_x)] = 0;
				}
			}
			for (int i = 0; i < block_width; i++)
			{
				if (on[pos2point(boom_pos_y)][i] == 2)
				{
					on[pos2point(boom_pos_y)][i] = 0;
				}
			}
			if (boom_pos_y == pery || boom_pos_x == perx)
			{
				boom_died = true;
			}
		}
	}
}
void flash()
{
	mon_run();
	booming();
	FlushBatchDraw();
	Sleep(100);
	cleardevice();
	draw();
}
int main()
{
	init();
	while (is_died() && !is_win() && !boom_died)
	{
		ctrl_per_walk();
		flash();
	}
	died();
	return 0;
}