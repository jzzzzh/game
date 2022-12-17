//实现了敌机的移动。BOSS已经BOSS的移动
//实现了BOSS发射子弹连续时间随机，连续子弹个数随机
//实现了BOSS和人血量显示
//实现了BOSS扣血10，小怪扣血1，小怪没打死就过了扣血20
//实现了飞机不飞出去
#include <stdio.h>
#include <conio.h>
#include <graphics.h>
#include <time.h>
#include <list>
#include "EasyXPng.h"

using namespace std;
//#pragma comment(lib,"winmm.lib")
//#pragma warning(disable:4996);

//Define area
#define WIN_WIDTH	600
#define	WIN_HEIGHT	600
const int MONMAXLIFE = 10;
const int MAXLIFE = 100;
int life = MAXLIFE;
int mon_life = MONMAXLIFE;
bool DJ_flag = false;
int died_num = 0;
bool mon_flag = false;
time_t t;
int boss_time = 3;
int boss_restime = 10;
bool boss_att = true;
//Definition of coordinate of both planes and bullets
class Node {
public:
	Node(int xx, int yy) {
		x = xx;
		y = yy;
	}
	int x;
	int y;
};


class Node_enemy {
public:
	Node_enemy(int xx, int yy) {
		x = xx;
		y = yy;
	}
	Node_enemy(int xx, int yy, list<Node> bulletList) {
		x = xx;
		y = yy;
		bulletList = bulletList;
	}
	int x;
	int y;
	list<Node> bulletList;
};


//Create List
/*
1��The enemy planes come from the top to the bottom
2, The bullets fired by our plane come from bottom to the top
*/

Node myPlane(260, 540);
Node_enemy BOSS(300, 40);
list<Node_enemy> enemyPlaneList;
list<Node> bulletList;
TCHAR died[5];

void draw_life()
{
	setlinecolor(RGB(255, 255, 255));
	fillrectangle(9, 9, 11+ MAXLIFE, 31);
	setfillcolor(RGB(18, 150, 70));
	fillrectangle(10, 10, 10 + life, 30);
	setfillcolor(RGB(255,255,255));
	setlinecolor(RGB(255, 255, 255));
	if (mon_flag == true)
	{
		setlinecolor(RGB(255, 255, 255));
		fillrectangle(450, 9, 551, 31);
		setfillcolor(RGB(106, 20, 20));
		fillrectangle(450, 10, 500 + 5 * mon_life, 30);
		setfillcolor(RGB(255, 255, 255));
		setlinecolor(RGB(255, 255, 255));
	}
}
//	Detection of keyboard pressing
void IsPressKey()
{
	if (_kbhit())			//	If a key is pressed
	{
		char key;
		key = _getch();		//	Obtain key info

		if (GetAsyncKeyState(VK_UP) && myPlane.y >= 0)     //Up
			myPlane.y -= 8;
		if (GetAsyncKeyState(VK_DOWN) && myPlane.y <= 600 - 20)   //Down
			myPlane.y += 8;
		if (GetAsyncKeyState(VK_LEFT) && myPlane.x >= 0)   //Left
			myPlane.x -= 6;
		if (GetAsyncKeyState(VK_RIGHT) && myPlane.x <= 600 - 35)  //Right
			myPlane.x += 6;
	}
}




//	Detection of Collision
void Shoot() {
	srand((unsigned)time(&t));
	list<Node_enemy>::iterator pDj = enemyPlaneList.begin();
	list<Node>::iterator pZd = bulletList.begin();

	//	Iterate all planes 
	bool flag = false;
	while (pDj != enemyPlaneList.end()) {
		if ((*pDj).y > 600 - 20)
		{
			//DJ_flag = true;
			//break;
			life -= 20;
			enemyPlaneList.erase(pDj);
			break;
		}
		if (rand() % 5 == 0)
		{
			int ttmp = rand() % 2;
			if (ttmp == 0 && (*pDj).x > 0)
			{
				(*pDj).x--;
			}
			else if (ttmp == 1 && (*pDj).x < 600 - 30)
			{
				(*pDj).x++;
			}
		}
		pZd = bulletList.begin();

		//	Iterate all bullets
		while (pZd != bulletList.end()) {
			//	Detection of Collision
			if ((*pZd).x >= ((*pDj).x - 10) && (*pZd).x <= ((*pDj).x + 50) &&
				(*pZd).y >= ((*pDj).y - 15) && (*pZd).y <= ((*pDj).y + 30)
				) {
				//	If collide, them eliminate both the plane and the bullet
				enemyPlaneList.erase(pDj);
				bulletList.erase(pZd);
				flag = true;
				died_num++;
				break;
			}
			else if (mon_flag == true)
			{
				if ((*pZd).x >= (BOSS.x - 40) && (*pZd).x <= (BOSS.x + 60) &&
					(*pZd).y >= (BOSS.y - 15) && (*pZd).y <= (BOSS.y + 30)
					) 
				{
					//	If collide, them eliminate both the plane and the bullet
					mon_life--;
					if (mon_life <= 0)
					{
						mon_flag = false;
						BOSS.bulletList.clear();
						died_num++;
					}
					bulletList.erase(pZd);
					flag = true;
					break;
				}
				else {
					++pZd;
				}
			}
			else {
				++pZd;
			}
		}


		if (flag) {
			break;
		}
		++pDj;
	}
}


void Dj_shot()
{
	list<Node_enemy>::iterator pDj = enemyPlaneList.begin();
	bool flag = false;
	while (pDj != enemyPlaneList.end()) {
		list<Node>::iterator pDjBt = (*pDj).bulletList.begin();
		while (pDjBt != (*pDj).bulletList.end())
		{
			if (((*pDjBt).x >= (myPlane.x)) && ((*pDjBt).x <= (myPlane.x + 32)) && ((*pDjBt).y >= (myPlane.y)) && ((*pDjBt).y <= (myPlane.y + 18)))
			{
				(*pDj).bulletList.erase(pDjBt);
				flag = true;
				life--;
				break;
			}
			pDjBt++;
		}
		if (flag) {
			break;
		}
		++pDj;
	}
	if (mon_flag == true)
	{
		list<Node>::iterator pDjBtx = BOSS.bulletList.begin();
		while (pDjBtx != BOSS.bulletList.end())
		{
			if (((*pDjBtx).x >= (myPlane.x)) && ((*pDjBtx).x <= (myPlane.x + 32)) && ((*pDjBtx).y >= (myPlane.y)) && ((*pDjBtx).y <= (myPlane.y + 18)))
			{
				BOSS.bulletList.erase(pDjBtx);
				life-=10;
				break;
			}
			pDjBtx++;
		}
	}
}



int main()
{
	// Random seed
	srand((unsigned int)time(NULL));
	//	Create the screen
	initgraph(WIN_WIDTH, WIN_HEIGHT, SHOWCONSOLE);

	DWORD t1, t2;			//	Speed of enemy planes
	DWORD tt1, tt2;			//	Speed of the bullets
	DWORD ttt1, ttt2;
	t1 = GetTickCount();			//	Starting time of the plane
	tt1 = GetTickCount();			//	Starting time of the bullet
	ttt1 = GetTickCount();

	IMAGE im_bk, im_myplane, im_xb, im_boss, im_myb, im_db, im_bossd;
	loadimage(&im_myplane, _T("me11.png"));
	loadimage(&im_boss, _T("boss1.png"));
	loadimage(&im_xb, _T("enemy1.png"));
	loadimage(&im_bk, _T("me11.png"));
	loadimage(&im_myb, _T("bomb1.png"));
	loadimage(&im_db, _T("db.png"));
	loadimage(&im_bossd, _T("bssd.png"));
	while (life > 0 && DJ_flag == false)
	{
		//	Add an enemy plane every 1000ms
		t2 = GetTickCount();
		if (t2 - t1 >= 1000) {
			int tmp = rand() % (WIN_WIDTH - 50);
			enemyPlaneList.push_back(Node_enemy(tmp, 0));
			t1 = t2;
		}

		//	Add a bullet every 500ms
		tt2 = GetTickCount();
		if (tt2 - tt1 >= 500) {
			bulletList.push_back(Node(myPlane.x + 17, myPlane.y - 20));

			for (auto& p : enemyPlaneList) {
				p.bulletList.push_back(Node(p.x + 17, p.y + 20));
			}
			tt1 = tt2;
		}

		ttt2 = GetTickCount();
		if (ttt2 - ttt1 >= 500 && mon_flag == true) {
			if (boss_att == true)
			{
				BOSS.bulletList.push_back(Node(BOSS.x + 17, BOSS.y - 20));
			}
			ttt1 = ttt2;
			boss_time--;
			if (boss_time <= 0)
			{
				boss_att = !boss_att;
				boss_time = rand()%5;
			}
		}
		BeginBatchDraw();		  //Starting batchdraw
		cleardevice();

		//show our plane at (x=260, y=740)
		//setfillcolor(RGB(0, 150, 0));
		//setlinecolor(RGB(255, 255, 255));
		//fillrectangle(myPlane.x, myPlane.y, myPlane.x + 32, myPlane.y + 18);
		//setfillcolor(RGB(255, 255, 255));
		//setlinecolor(RGB(255, 255, 255));
		putimagePng(myPlane.x, myPlane.y, &im_myplane);
		
		//show our bullet
		for (auto& p : bulletList) {
			//Print the bullet
			//setfillcolor(RGB(0, 150, 0));
			//setlinecolor(RGB(255, 255, 255));
			//fillcircle(p.x, p.y, 5);
			//setfillcolor(RGB(255, 255, 255));
			//setlinecolor(RGB(255, 255, 255));
			putimagePng(p.x+20, p.y, &im_myb);
			//	moving upwards
			p.y--;
		}
		if (mon_flag == true)
		{
			for (auto& p : BOSS.bulletList) {
				//Print the bullet
				//setfillcolor(RGB(106, 0, 0));
				//setlinecolor(RGB(255, 255, 255));
				//fillcircle(p.x, p.y, 10);
				//setfillcolor(RGB(255, 255, 255));
				//setlinecolor(RGB(255, 255, 255));
				putimagePng(p.x + 20, p.y, &im_bossd);
				
				//	moving upwards
				p.y+=2;
			}
		}
		// Show the enemy plane
		for (auto& p : enemyPlaneList) {
			//Print the plane
			//roundrect(p.x, p.y, p.x + 30, p.y + 20, 5, 5);
			putimagePng(p.x, p.y, &im_xb);
			// Moving downwards
			p.y++;
			for (auto& pp : p.bulletList) {
				//Print the bullet
				//circle(pp.x, pp.y, 5);
				 putimagePng(pp.x+ 5, pp.y, &im_db);
				//	moving upwards
				pp.y+=2;
			}
		}
		if (mon_flag == true)
		{
			//setfillcolor(RGB(106, 0, 0));
			//setlinecolor(RGB(255, 255, 255));
			//fillrectangle(BOSS.x - 40, BOSS.y-15, BOSS.x + 60, BOSS.y + 30);
			//setfillcolor(RGB(255, 255, 255));
			//setlinecolor(RGB(255, 255, 255));
			putimagePng(BOSS.x, BOSS.y, &im_boss);
			if (rand() % 5 == 0)
			{
				int ttmp = rand() % 2;
				if (ttmp == 0 && BOSS.x > 0)
				{
					BOSS.x--;
				}
				else if (ttmp == 1 && BOSS.x < 600 - 30)
				{
					BOSS.x++;
				}
			}
		}

		if (died_num > 0 && died_num % 10 == 0 && mon_flag == false)
		{
			mon_flag = true;
		}
		swprintf_s(died, _T("%d"), int(died_num));
		outtextxy(40, 40, died);
		Sleep(5);

		Shoot(); // detection of collision
		Dj_shot();
		draw_life();
		EndBatchDraw(); // end batchdraw

		IsPressKey(); // detection of keyboard signal

	}
	getchar();
	return 0;
}