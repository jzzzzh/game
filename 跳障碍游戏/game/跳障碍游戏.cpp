// game.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include <stdio.h>
#include <conio.h>
#include <graphics.h>
#include <iostream>
#include <string>
#include <math.h>
using namespace std;
float getVy(float Vy, float g)
{
    Vy = Vy + g;
    return Vy;
}
float getPointLength(float x1, float y1, float x2, float y2)
{
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}
boolean isLineTouched(float x1, float y1, float x2, float y2, int x, int y, int r)
{
    if (getPointLength(x1, y1, x, y) <= r || getPointLength(x2, y2, x, y) <= r)
        return false;
    else
    {
        return true;
    }
}
boolean isTouched(float rleft, float rright, float rtop, float rbottom, int x, int y, int r)
{
    if (rleft <= x + r && rright >= x - r && rtop <= y + r && rbottom >= y - r)
        return true;
    else
    {
        return false;
    }
}
int main()
{
    int times = 0;
    int w = 600, h = 600;
    int x = 300, y = 0, r = 20;
    float vx = 0, vy = 0;
    float rvx = 3;
    float rleft = 600, rright = 620, rtop = 500, rbottom = 600;
    int tt = 0;
    // int max = 0;
    char ch;
    TCHAR Ts[] = _T("请按空格键，每10个会提高速度");
    TCHAR s[] = _T("次数");
    TCHAR ss[5];
    TCHAR su[] = _T("速度提升");
    int xx = 0;
    initgraph(w, h);
    while (1)
    {
        if (y < h - r - 10)
        {
            vy = getVy(vy, 1);
        }
        if (x <= r)
        {
            vx = abs(vx);
        }
        if (x >= w - r)
        {
            vx = -abs(vx);
        }
        if (y >= h - r)
            vy = 0;
        // cleardevice();

        if (_kbhit())
        {                       //如果有按键按下，则_kbhit()函数返回真
            ch = _getch(); //使用_getch()获取按下的键值
            if (ch == 32)
            {
                if (vy == 0)
                {
                    vy = vy - 30;
                }
            }
        }
        rleft = rleft - rvx;
        rright = rright - rvx;
        if (tt == 0 && rleft <= 0)
        {
            times++;
            rleft = 600;
            tt = 5;
            rright = rleft + 20;
            //rright = rleft + int(rand() % 30 + 20);
            // rvx = -abs(rvx);
            rtop = rtop + int(rand() % 60 - 30);
            rvx = abs(rvx);
        }
        if (tt > 0)
        {
            tt--;
            
        }

        // if (rleft >= 580)
        // {
        //     rvx = abs(rvx);
        // }
        if (3 * times - int(rvx) * 10 > 0)
        {
            rvx += 2;
           
            xx = 100;
        }
        if (xx > 0)
        {
            xx--;
            outtextxy(300, 300, su);
        }
        
        // swprintf_s(s, _T("%d"), int(rleft));
        // outtextxy(10, 40, s);
       
        swprintf_s(ss, _T("%d"), int(times));
        // outtextxy(10, 60, ss);
        bool flag = isTouched(rleft, rright, rtop, rbottom, x, y, r);
        if (flag == true)
        {
            break;
        }
        // fillrectangle(rleft, rtop, rright, rbottom);
        y = y + vy;
        x = x + vx;
        outtextxy(10, 20, Ts);
        outtextxy(10, 40, s);
        outtextxy(10, 60, ss);
        fillrectangle(rleft, rtop, rright, rbottom);
        fillcircle(x, y, r);
        Sleep(10);
        cleardevice();
    }
    TCHAR ssss[] = _T("你失败了");
    // swprintf_s(s, _T("%d"), int(rleft));
    outtextxy(300, 300, ssss);
    _getch();
    closegraph();
    return 0;
}
