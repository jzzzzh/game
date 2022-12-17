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
    int to = 0;
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
        if (_kbhit())
        {
            if (GetAsyncKeyState(VK_UP))
            {
                to = 0;
                if (y >= v)
                    y -= v;
            }
            if (GetAsyncKeyState(VK_LEFT))
            {
                to = 1;
                if (x >= v)
                    x -= v;
            }
            if (GetAsyncKeyState(VK_RIGHT))
            {
                to = 2;
                if (x <= WIDTH - v - imgd->getwidth())
                    x += v;
            }
            if (GetAsyncKeyState(VK_DOWN))
            {
                to = 3;
                if (y <= HEIGHT - v - imgs->getheight())
                    y += v;
            }
        }
        if (to == 3)
            putimagePng(x, y, &imgd[i]);
        else if (to == 1)
            putimagePng(x, y, &imga[i]);
        else if (to == 0)
            putimagePng(x, y, &imgw[i]);
        else if (to == 2)
            putimagePng(x, y, &imgs[i]);
        Sleep(200);
        i += 1;

        cleardevice();

        if (i == 7)
            i = 0;
    }
    _getch();
    return 0;
}