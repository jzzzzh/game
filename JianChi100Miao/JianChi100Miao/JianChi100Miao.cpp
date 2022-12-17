//实现了碰撞检测、爆炸效果贴图、血量显示（左上）、坚持时间显示（右上）
//进阶：添加只能飞碟（朝着火箭方向飞）

//#include "stdafx.h"
#pragma warning(default: 4996)

#include <graphics.h>  
#include <conio.h>
#include <time.h>
#include <math.h>
#include "EasyXPng.h"  // 用于显示带透明通道的png图片
#define  WIDTH 560 // 画面宽度
#define  HEIGHT 800 // 画面高度
#define	 MaxBulletNum 200        // 最多子弹个数
const int MAXLIFE = 10;
const int TIME = 100;
int GameTime = 0;

class Heart  // 定义火箭类
{
public:
	IMAGE im_heart;             // 火箭图像
	float x, y;                  // 火箭坐标
	float width, height;         // 火箭图片的宽度、高度
	int life;
	int space = 10;
	void draw()                  // 显示火箭相关信息	
	{
		for (int i = 0; i < life; i++)
		{
			putimagePng(x - width / 2 + i * (width+space), y - height / 2, &im_heart);
		}
		
		// 游戏中显示火箭
	}

	void update() // 根据输入的坐标更新火箭的位置
	{
		life--;
	}
};


class Rocket  // 定义火箭类
{
public:
	IMAGE im_rocket;             // 火箭图像
	float x, y;                  // 火箭坐标
	float width, height;         // 火箭图片的宽度、高度

	void draw()                  // 显示火箭相关信息	
	{
		putimagePng(x - width / 2, y - height / 2, &im_rocket);
		// 游戏中显示火箭
	}

	void update(float mx, float my) // 根据输入的坐标更新火箭的位置
	{
		x = mx;
		y = my;
	}
};

int UFOvy = 1;
int UFOvx = 1;

class UFO  // 定义火箭类
{
public:
	IMAGE im_ufo;             // 火箭图像
	float x, y;                  // 火箭坐标
	float width, height;         // 火箭图片的宽度、高度

	void draw()                  // 显示火箭相关信息	
	{
		putimagePng(x - width / 2, y - height / 2, &im_ufo);
		// 游戏中显示火箭
	}

	void update(float mx, float my) // 根据输入的坐标更新火箭的位置
	{
		x = mx;
		y = my;
	}
};
IMAGE im_bk, im_rocket, im_ufo, im_heart;  // 定义图像对象	
Rocket rocket;  // 定义火箭对象
UFO ufo;
Heart heart;

class Bullet                    // 定义子弹类
{
public:
	IMAGE im_bullet;            // 子弹图像
	float x, y;                 // 子弹坐标
	float vx, vy;               // 子弹速度
	float radius;               // 接近球体的子弹半径大小
	bool is_dead;
	void draw()                 // 显示子弹	
	{
		putimagePng(x - radius, y - radius, &im_bullet);
	}

	void update()               // 更新子弹的位置、速度
	{
		x += vx;
		y += vy;
		if (x <= 0 || x >= WIDTH)
			vx = -vx;
		if (y <= 0 || y >= HEIGHT)
			vy = -vy;
	}
};

IMAGE im_bullet;  // 定义图像对象	
Bullet bullet[MaxBulletNum];                   // 定义子弹对象数组
IMAGE im_bomb;
int bulletNum = 0;                             // 已有子弹的个数

int ufo_pos_x = 0;
int ufo_pos_y = 0;
TCHAR s[5];
auto ss = _T("秒");
static int lastSecond = 0;         // 记录前一次程序运行了多少秒
static int nowSecond = 0;
void updateWithoutInput()              // 和输入无关的更新
{
        // 记录当前程序运行了多少秒
	static clock_t start = clock();    // 记录第一次运行时刻
	clock_t now = clock();             // 获得当前时刻
									   // 计算程序目前一共运行了多少秒
	
	nowSecond = (int(now - start) / CLOCKS_PER_SEC);
	swprintf_s(s, _T("%d"), int(nowSecond));
	
	if (nowSecond == lastSecond + 2)   // 时间过了2秒钟，新增一颗子弹
	{
		lastSecond = nowSecond;        // 更新下lastSecond变量
									   // 如果没有超出最大子弹数目的限制，增加一颗新的子弹
		if (bulletNum < MaxBulletNum)
		{
			bullet[bulletNum].x = WIDTH / 2; // 子弹初始位置
			bullet[bulletNum].y = 10;
			bullet[bulletNum].is_dead = false;
			float angle = (rand() / double(RAND_MAX) - 0.5) * 0.9 * PI;
			float scalar = 2 * rand() / double(RAND_MAX) + 2;
			bullet[bulletNum].vx = scalar * sin(angle); // 子弹随机速度
			bullet[bulletNum].vy = scalar * cos(angle);
			bullet[bulletNum].im_bullet = im_bullet;  // 设置子弹图像
			bullet[bulletNum].radius = im_bullet.getwidth() / 2; // 子弹半径为图片宽度一半
		}
		bulletNum++; // 子弹数目加一
	}

	for (int i = 0; i < bulletNum; i++) // 对所有已有的子弹
		bullet[i].update(); // 更新子弹的位置、速度		
	if (ufo.x < rocket.x)
	{
		ufo_pos_x = ufo.x + UFOvx;
		if (ufo.y < rocket.y)
		{
			ufo_pos_y = ufo.y + UFOvy;
		}
		else
		{
			ufo_pos_y = ufo.y - UFOvy;
		}
	}
	else
	{
		ufo_pos_x = ufo.x - UFOvx;
		if (ufo.y < rocket.y)
		{
			ufo_pos_y = ufo.y + UFOvy;
		}
		else
		{
			ufo_pos_y = ufo.y - UFOvy;
		}
	}
	ufo.update(ufo_pos_x, ufo_pos_y);
}

bool is_touched()
{
	bool flag = false;
	for (int i = 0; i < bulletNum; i++)
	{
		if ( bullet[i].is_dead == false && fabs(rocket.x - bullet[i].x) <= (rocket.width) && fabs(rocket.y - bullet[i].y) < (rocket.height) )
		{
			//flag = true;
			bullet[i].is_dead = true;
			heart.update();
			return flag;
		}
	}
	if (fabs(rocket.x - ufo.x) <= ( ufo.width) && fabs(rocket.y - ufo.y) < (ufo.height))
	{
		flag = true;
		//heart.update();
		return flag;
	}
	return flag;
}

void startup()  //  初始化函数
{
	srand(time(0)); // 初始化随机种子
	loadimage(&im_bk, _T("background.png")); // 导入背景图片
	loadimage(&im_rocket, _T("rocket.png")); // 导入火箭图片
	loadimage(&im_bullet, _T("bullet.png"));
	loadimage(&im_ufo, _T("ufo.png"));
	loadimage(&im_heart, _T("heart.png"));
	loadimage(&im_bomb, _T("blowup.png"));
	heart.x = 30;
	heart.y = 30;
	heart.height = im_heart.getheight();
	heart.width = im_heart.getwidth();
	heart.im_heart = im_heart;
	heart.life = MAXLIFE;
	ufo.im_ufo = im_ufo;  // 设置火箭图片
	ufo.width = im_ufo.getwidth(); // 设置火箭宽度
	ufo.height = im_ufo.getheight(); // 设置火箭高度
	ufo.x = rand() % WIDTH;
	ufo.y = rand() % HEIGHT;
	// 对rocket一些成员变量初始化
	rocket.im_rocket = im_rocket;  // 设置火箭图片
	rocket.width = im_rocket.getwidth(); // 设置火箭宽度
	rocket.height = im_rocket.getheight(); // 设置火箭高度

	initgraph(WIDTH, HEIGHT); // 新开一个画面
	BeginBatchDraw(); // 开始批量绘制
}

void show()  // 绘制函数
{
	putimage(0, 0, &im_bk);	// 显示背景	
	for (int i = 0; i < bulletNum; i++)
		if(bullet[i].is_dead == false )
		bullet[i].draw();               // 显示已有的子弹

	rocket.draw();  // 显示火箭及相关信息
	ufo.draw();
	settextstyle(40, 0, _T("微软雅黑"));
	outtextxy(470, 50, s);
	outtextxy(520, 50, ss);
	heart.draw();
	FlushBatchDraw(); // 批量绘制
	Sleep(10); // 暂停
}

void updateWithInput()               // 和输入相关的更新
{
	MOUSEMSG m;		                 // 定义鼠标消息
	while (MouseHit())               // 检测当前是否有鼠标消息
	{
		m = GetMouseMsg();
		if (m.uMsg == WM_MOUSEMOVE)  // 到鼠标移动时			
			rocket.update(m.x, m.y); // 火箭的位置等于鼠标所在的位置
	}
}

int main() // 主函数
{
	startup();  // 初始化	
	while (1)  // 重复运行
	{
		show();  // 绘制
		updateWithoutInput();
		updateWithInput();  // 和输入相关的更新
		if (is_touched() || heart.life == 0 || nowSecond == 100)
		{
			
			putimage(0, 0, &im_bk);	// 显示背景	
			for (int i = 0; i < bulletNum; i++)
				if (bullet[i].is_dead == false)
					bullet[i].draw();               // 显示已有的子弹

			rocket.draw();  // 显示火箭及相关信息
			ufo.draw();
			heart.draw();
			settextstyle(40, 0, _T("微软雅黑"));
			outtextxy(470, 50, s);
			outtextxy(520, 50, ss);
			putimagePng(rocket.x - rocket.width / 2, rocket.y - rocket.height / 2, &im_bomb);
			FlushBatchDraw(); // 批量绘制
			Sleep(10); // 暂停
			break;
		};
	}
	_getch();
	return 0;
}