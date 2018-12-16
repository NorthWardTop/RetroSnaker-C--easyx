
//----------------------------------------------------------------------包含头文件，库文件
#include <graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <mmsystem.h>
#include "Snake.h"
#pragma comment(lib,"winmm.lib")

//----------------------------------------------------------------------函数声明
void Welcome();			//欢迎界面（主界面）
void GameInit();		//游戏加载（初始化）
void GameWindow();		//游戏界面
void Food();
void DrawSnake();		//根据当前坐标画蛇
void MoveSnake();		//移动蛇（的坐标）

//----------------------------------------------------------------------全局变量声明
IMAGE bgimg1;			//存放欢迎界面背景
IMAGE bgimg2;			//存放其他背景
int score;				//存放当前分数
SNAKE snake;			//定义一条蛇（结构体变量）
MOUSEMSG msg;			//定义鼠标消息（结构体变量）
int time;				//难度
int die=1;
FOOD food;				//食物结构体

//----------------------------------------------------------------------宏定义


int main(int argc, char* argv[])
{
	initgraph(800, 600);
	while (1)
	{
		GameInit();
		Welcome();				//欢迎界面内可进入游戏


		GameWindow();

		DrawSnake();

		cleardevice();
		settextcolor(RGB(255, 0, 0));
		settextstyle(100, 0, "微软雅黑");
		outtextxy(300, 200, "you die");
		Sleep(1000);
		die = 1;
	}

	getchar();
	closegraph();
	return 0;
}


//欢迎界面
void Welcome()
{
	putimage(0, 0, &bgimg1);					//展示图片
	setbkmode(TRANSPARENT);						//设置背景模式(透明)
	settextstyle(60, 0, "微软雅黑");			//设置字体风格
	settextcolor(RGB(255, 0, 0));
	outtextxy(320, 100, "贪  吃  蛇");
	settextstyle(40, 0, "微软雅黑");
	
	while (1)
	{
		msg = GetMouseMsg();
		if (msg.x > 325 && msg.x<500 && msg.y>300 && msg.y < 340)		//此处应该用switch（）{ if }语句，						
		{																//当时没想到，用了级联if语句，
			settextcolor(RGB(255, 255, 0));								//现在没改，看起来费劲，望谅解
			outtextxy(325, 300, "★开始游戏★");
			if (msg.uMsg == WM_LBUTTONDOWN)
			{
				break;						//直接到主函数开始游戏
			}
		}
		else
		{
			if (msg.x > 325 && msg.x<500 && msg.y>350 &&msg.y < 390)
			{
				settextcolor(RGB(255, 255, 0));
				outtextxy(325, 350, "★游戏设置★");
				if (msg.uMsg == WM_LBUTTONDOWN)
				{
					cleardevice();
					putimage(0, 0, &bgimg2);
					settextcolor(RGB(255, 0, 0));
					outtextxy(200, 200, "暂时不支持，老子稍后添加,重新选择");
					continue;

				}
			}
			else
			{
				if (msg.x>325 &&msg.x<500 && msg.y>400 && msg.y < 440)
				{
					settextcolor(RGB(255, 255, 0));
					outtextxy(325, 400, "★游戏说明★");
					if (msg.uMsg == WM_LBUTTONDOWN)
					{
						cleardevice();
						putimage(0, 0, &bgimg2);
						settextcolor(RGB(255, 0, 0));
						outtextxy(200, 200, "你可能过了个假童年");
						continue;
					}
				}
				else
				{
					if (msg.x>325 && msg.x<500 &&msg.y>450 &&msg.y < 490)
					{
						settextcolor(RGB(255, 255, 0));
						outtextxy(325, 450, "★版本信息★");
						if (msg.uMsg == WM_LBUTTONDOWN)
						{
							cleardevice();
							putimage(0, 0, &bgimg2);
							settextcolor(RGB(255, 0, 0));
							outtextxy(20, 100, "版本：v1.0");
							outtextxy(20, 150, "编写时间：2017-2-26 -> 2017-3-11:23:39");
							outtextxy(20, 200, "编写者：李永辉");
							continue;
						}
					}
					else
					{
						settextcolor(RGB(0, 255, 0));
						outtextxy(325, 300, "★开始游戏★");
						settextcolor(RGB(32, 147, 244));
						outtextxy(325, 350, "★游戏设置★");
						settextcolor(RGB(54, 107, 15));
						outtextxy(325, 400, "★游戏说明★");
						settextcolor(RGB(103, 32, 121));
						outtextxy(325, 450, "★版本信息★");
					}
				}
			}
		}
	}
}


//移动蛇（的每节坐标）程序核心
void MoveSnake()
{
	char keyboard;
	if (kbhit())						//有输入返回非0值，否则返回0
	{
		keyboard=getch();
		switch (keyboard)					//依据键盘的输入改变蛇头方向
		{
		case up:
			if (snake.dir != down)			//当蛇头不是向下时，按“上”才能向上，其他同理
			{
				snake.dir = up;
				for (int i = (snake.len - 1); i > 0; i--)						//后一节蛇坐标赋给前一节,由后向前,最后等于蛇头
				{
					snake.scr[i].x = snake.scr[i - 1].x;
					snake.scr[i].y = snake.scr[i - 1].y;
				}
				snake.scr[0].y -= 20;
			}
			break;
		case down:
			if (snake.dir != up)
			{
				snake.dir = down;
				for (int i = (snake.len - 1); i > 0; i--)						//后一节蛇坐标赋给前一节,由后向前,最后等于蛇头
				{
					snake.scr[i].x = snake.scr[i - 1].x;
					snake.scr[i].y = snake.scr[i - 1].y;
				}
				snake.scr[0].y += 20;
			}
			break;
		case right:
			if (snake.dir != left)
			{
				snake.dir = right;
				for (int i = (snake.len - 1); i > 0; i--)						//后一节蛇坐标赋给前一节,由后向前,最后等于蛇头
				{
					snake.scr[i].x = snake.scr[i - 1].x;
					snake.scr[i].y = snake.scr[i - 1].y;
				}
				snake.scr[0].x += 20;
			}
			break;
		case left:
			if (snake.dir != right)
			{
				snake.dir = left;
				for (int i = (snake.len - 1); i > 0; i--)						//后一节蛇坐标赋给前一节,由后向前,最后等于蛇头
				{
					snake.scr[i].x = snake.scr[i - 1].x;
					snake.scr[i].y = snake.scr[i - 1].y;
				}
				snake.scr[0].x -= 20;
			}
			break;
		}
	}
	else
	{
		switch (snake.dir)					//依据键盘的输入改变蛇头方向
		{
		case up:
			if (snake.dir != down)			//当蛇头不是向下时，按“上”才能向上，其他同理
			{		
				for (int i = (snake.len - 1); i > 0; i--)						//后一节蛇坐标赋给前一节,由后向前,最后等于蛇头
				{
					snake.scr[i].x = snake.scr[i - 1].x;
					snake.scr[i].y = snake.scr[i - 1].y;
				}
				snake.scr[0].y -= 20;
			}
			break;
		case down:
			if (snake.dir != up)
			{
				for (int i = (snake.len - 1); i > 0; i--)						//后一节蛇坐标赋给前一节,由后向前,最后等于蛇头
				{
					snake.scr[i].x = snake.scr[i - 1].x;
					snake.scr[i].y = snake.scr[i - 1].y;
				}
				snake.scr[0].y += 20;
			}
			break;
		case right:
			if (snake.dir != left)
			{
				for (int i = (snake.len - 1); i > 0; i--)						//后一节蛇坐标赋给前一节,由后向前,最后等于蛇头
				{
					snake.scr[i].x = snake.scr[i - 1].x;
					snake.scr[i].y = snake.scr[i - 1].y;
				}
				snake.scr[0].x += 20;
			}
			break;
		case left:
			if (snake.dir != right)
			{
				for (int i = (snake.len - 1); i > 0; i--)						//后一节蛇坐标赋给前一节,由后向前,最后等于蛇头
				{
					snake.scr[i].x = snake.scr[i - 1].x;
					snake.scr[i].y = snake.scr[i - 1].y;
				}
				snake.scr[0].x -= 20;
			}
			break;
		}
	}
}



//根据当前坐标画蛇（与MoveSnake()配合使用,先由MoveSnake()来确定每节蛇坐标）
void DrawSnake()
{
		mciSendString("play 甩葱歌.mp3", 0, 0, 0);	//播放音乐
		while (die)
		{

			if (snake.scr[0].x == food.fd.x&&snake.scr[0].y == food.fd.y)
			{
				food.eat = 0;
				snake.len++;
				GameWindow();
			}
			if (!food.eat)
			{
				Food();
			}
			MoveSnake();											//用MoveSnake（）移动蛇的坐标
			if (!(snake.scr[0].x >= 20 && snake.scr[0].x <= 580 && snake.scr[0].y >= 20 && snake.scr[0].y <= 580))		//是否出界
			{
				die = 0;
			}

			//for (int i = 2; i < snake.len; i++)						//遍历除蛇头外全部蛇节，
			//{
			//	if (snake.scr[0].x == snake.scr[i].x&&snake.scr[0].y == snake.scr[i].y)		//当蛇头等于任何蛇节坐标，死亡
			//	{
			//		die = 0;
			//	}
			//}

			setfillcolor(RGB(0, 122, 204));							//设置画蛇颜色
			for (int i = 0; i < snake.len; i++)						//画蛇
			{
				solidcircle(snake.scr[i].x, snake.scr[i].y, 10);
			}
			Sleep(time);

			for (int i = 0; i < snake.len; i++)						//清除蛇
			{
				clearcircle(snake.scr[i].x, snake.scr[i].y, 10);
			}
		}
}


//食物产生与吃食物
void Food()
{
	food.fd.x = (rand() % (29-2 ) + 2) * 20, food.fd.y = (rand() % (29-2 ) + 2) * 20;
	setfillcolor(RGB(103, 32, 121));								//设置画食物颜色
	solidcircle(food.fd.x, food.fd.y, 10); 
	food.eat = 1;
	for (int i = 1; i < snake.len; i++)
	{
		if (snake.scr[i].x == food.fd.x&&snake.scr[i].y == food.fd.y)
		{
			food.eat = 0;
		}
	}
}


//玩游戏界面
void GameWindow()
{
	cleardevice();
	
	setlinestyle(0, 5);							//设置画线风格
	setlinecolor(RGB(255, 204, 0));
	roundrect(10, 10, 590, 590, 10, 10);				//画圆角矩形
	settextstyle(40, 0, "微软雅黑");
	settextcolor(RGB(53, 131, 88));
	outtextxy(650, 100, "分  数");
	char score[5];
	sprintf(score, "%d", (snake.len-3)*10);
	outtextxy(660, 200, score);
	outtextxy(630, 300, "当前难度");

//	Sleep(time);
	for (int i = 0; i < snake.len; i++)							//清除蛇（）
	{
		clearcircle(snake.scr[i].x, snake.scr[i].y, 10);
	}
}


//游戏初始化（加载图片音乐等）
void GameInit()
{

	loadimage(&bgimg2, "11.jpg", 1200, 1450);
	loadimage(&bgimg1, "2.jpg", 800, 600);				//加载图片
	mciSendString("open 甩葱歌.mp3", 0, 0, 0);			//加载音乐


	//初始化一条蛇
	snake.len = 3;												//设置初始长度
	snake.dir = right;											//设置初始方向
	time = 100;												//设置初始难度
	setfillcolor(RGB(103, 32, 121));							//
	food.eat = 0;												//无食物
	for (int i = 0; i < snake.len; i++)							//画长度为len的蛇
	{
		snake.scr[i].x = 300 + i * 20;								//初始位置为(300,300),画每节蛇x+=20，y不变
		snake.scr[i].y = 300;
	}
}
