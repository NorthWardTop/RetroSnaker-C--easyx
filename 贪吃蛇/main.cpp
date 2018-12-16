
//----------------------------------------------------------------------����ͷ�ļ������ļ�
#include <graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <mmsystem.h>
#include "Snake.h"
#pragma comment(lib,"winmm.lib")

//----------------------------------------------------------------------��������
void Welcome();			//��ӭ���棨�����棩
void GameInit();		//��Ϸ���أ���ʼ����
void GameWindow();		//��Ϸ����
void Food();
void DrawSnake();		//���ݵ�ǰ���껭��
void MoveSnake();		//�ƶ��ߣ������꣩

//----------------------------------------------------------------------ȫ�ֱ�������
IMAGE bgimg1;			//��Ż�ӭ���汳��
IMAGE bgimg2;			//�����������
int score;				//��ŵ�ǰ����
SNAKE snake;			//����һ���ߣ��ṹ�������
MOUSEMSG msg;			//���������Ϣ���ṹ�������
int time;				//�Ѷ�
int die=1;
FOOD food;				//ʳ��ṹ��

//----------------------------------------------------------------------�궨��


int main(int argc, char* argv[])
{
	initgraph(800, 600);
	while (1)
	{
		GameInit();
		Welcome();				//��ӭ�����ڿɽ�����Ϸ


		GameWindow();

		DrawSnake();

		cleardevice();
		settextcolor(RGB(255, 0, 0));
		settextstyle(100, 0, "΢���ź�");
		outtextxy(300, 200, "you die");
		Sleep(1000);
		die = 1;
	}

	getchar();
	closegraph();
	return 0;
}


//��ӭ����
void Welcome()
{
	putimage(0, 0, &bgimg1);					//չʾͼƬ
	setbkmode(TRANSPARENT);						//���ñ���ģʽ(͸��)
	settextstyle(60, 0, "΢���ź�");			//����������
	settextcolor(RGB(255, 0, 0));
	outtextxy(320, 100, "̰  ��  ��");
	settextstyle(40, 0, "΢���ź�");
	
	while (1)
	{
		msg = GetMouseMsg();
		if (msg.x > 325 && msg.x<500 && msg.y>300 && msg.y < 340)		//�˴�Ӧ����switch����{ if }��䣬						
		{																//��ʱû�뵽�����˼���if��䣬
			settextcolor(RGB(255, 255, 0));								//����û�ģ��������Ѿ������½�
			outtextxy(325, 300, "�￪ʼ��Ϸ��");
			if (msg.uMsg == WM_LBUTTONDOWN)
			{
				break;						//ֱ�ӵ���������ʼ��Ϸ
			}
		}
		else
		{
			if (msg.x > 325 && msg.x<500 && msg.y>350 &&msg.y < 390)
			{
				settextcolor(RGB(255, 255, 0));
				outtextxy(325, 350, "����Ϸ���á�");
				if (msg.uMsg == WM_LBUTTONDOWN)
				{
					cleardevice();
					putimage(0, 0, &bgimg2);
					settextcolor(RGB(255, 0, 0));
					outtextxy(200, 200, "��ʱ��֧�֣������Ժ����,����ѡ��");
					continue;

				}
			}
			else
			{
				if (msg.x>325 &&msg.x<500 && msg.y>400 && msg.y < 440)
				{
					settextcolor(RGB(255, 255, 0));
					outtextxy(325, 400, "����Ϸ˵����");
					if (msg.uMsg == WM_LBUTTONDOWN)
					{
						cleardevice();
						putimage(0, 0, &bgimg2);
						settextcolor(RGB(255, 0, 0));
						outtextxy(200, 200, "����ܹ��˸���ͯ��");
						continue;
					}
				}
				else
				{
					if (msg.x>325 && msg.x<500 &&msg.y>450 &&msg.y < 490)
					{
						settextcolor(RGB(255, 255, 0));
						outtextxy(325, 450, "��汾��Ϣ��");
						if (msg.uMsg == WM_LBUTTONDOWN)
						{
							cleardevice();
							putimage(0, 0, &bgimg2);
							settextcolor(RGB(255, 0, 0));
							outtextxy(20, 100, "�汾��v1.0");
							outtextxy(20, 150, "��дʱ�䣺2017-2-26 -> 2017-3-11:23:39");
							outtextxy(20, 200, "��д�ߣ�������");
							continue;
						}
					}
					else
					{
						settextcolor(RGB(0, 255, 0));
						outtextxy(325, 300, "�￪ʼ��Ϸ��");
						settextcolor(RGB(32, 147, 244));
						outtextxy(325, 350, "����Ϸ���á�");
						settextcolor(RGB(54, 107, 15));
						outtextxy(325, 400, "����Ϸ˵����");
						settextcolor(RGB(103, 32, 121));
						outtextxy(325, 450, "��汾��Ϣ��");
					}
				}
			}
		}
	}
}


//�ƶ��ߣ���ÿ�����꣩�������
void MoveSnake()
{
	char keyboard;
	if (kbhit())						//�����뷵�ط�0ֵ�����򷵻�0
	{
		keyboard=getch();
		switch (keyboard)					//���ݼ��̵�����ı���ͷ����
		{
		case up:
			if (snake.dir != down)			//����ͷ��������ʱ�������ϡ��������ϣ�����ͬ��
			{
				snake.dir = up;
				for (int i = (snake.len - 1); i > 0; i--)						//��һ�������긳��ǰһ��,�ɺ���ǰ,��������ͷ
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
				for (int i = (snake.len - 1); i > 0; i--)						//��һ�������긳��ǰһ��,�ɺ���ǰ,��������ͷ
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
				for (int i = (snake.len - 1); i > 0; i--)						//��һ�������긳��ǰһ��,�ɺ���ǰ,��������ͷ
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
				for (int i = (snake.len - 1); i > 0; i--)						//��һ�������긳��ǰһ��,�ɺ���ǰ,��������ͷ
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
		switch (snake.dir)					//���ݼ��̵�����ı���ͷ����
		{
		case up:
			if (snake.dir != down)			//����ͷ��������ʱ�������ϡ��������ϣ�����ͬ��
			{		
				for (int i = (snake.len - 1); i > 0; i--)						//��һ�������긳��ǰһ��,�ɺ���ǰ,��������ͷ
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
				for (int i = (snake.len - 1); i > 0; i--)						//��һ�������긳��ǰһ��,�ɺ���ǰ,��������ͷ
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
				for (int i = (snake.len - 1); i > 0; i--)						//��һ�������긳��ǰһ��,�ɺ���ǰ,��������ͷ
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
				for (int i = (snake.len - 1); i > 0; i--)						//��һ�������긳��ǰһ��,�ɺ���ǰ,��������ͷ
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



//���ݵ�ǰ���껭�ߣ���MoveSnake()���ʹ��,����MoveSnake()��ȷ��ÿ�������꣩
void DrawSnake()
{
		mciSendString("play ˦�и�.mp3", 0, 0, 0);	//��������
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
			MoveSnake();											//��MoveSnake�����ƶ��ߵ�����
			if (!(snake.scr[0].x >= 20 && snake.scr[0].x <= 580 && snake.scr[0].y >= 20 && snake.scr[0].y <= 580))		//�Ƿ����
			{
				die = 0;
			}

			//for (int i = 2; i < snake.len; i++)						//��������ͷ��ȫ���߽ڣ�
			//{
			//	if (snake.scr[0].x == snake.scr[i].x&&snake.scr[0].y == snake.scr[i].y)		//����ͷ�����κ��߽����꣬����
			//	{
			//		die = 0;
			//	}
			//}

			setfillcolor(RGB(0, 122, 204));							//���û�����ɫ
			for (int i = 0; i < snake.len; i++)						//����
			{
				solidcircle(snake.scr[i].x, snake.scr[i].y, 10);
			}
			Sleep(time);

			for (int i = 0; i < snake.len; i++)						//�����
			{
				clearcircle(snake.scr[i].x, snake.scr[i].y, 10);
			}
		}
}


//ʳ��������ʳ��
void Food()
{
	food.fd.x = (rand() % (29-2 ) + 2) * 20, food.fd.y = (rand() % (29-2 ) + 2) * 20;
	setfillcolor(RGB(103, 32, 121));								//���û�ʳ����ɫ
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


//����Ϸ����
void GameWindow()
{
	cleardevice();
	
	setlinestyle(0, 5);							//���û��߷��
	setlinecolor(RGB(255, 204, 0));
	roundrect(10, 10, 590, 590, 10, 10);				//��Բ�Ǿ���
	settextstyle(40, 0, "΢���ź�");
	settextcolor(RGB(53, 131, 88));
	outtextxy(650, 100, "��  ��");
	char score[5];
	sprintf(score, "%d", (snake.len-3)*10);
	outtextxy(660, 200, score);
	outtextxy(630, 300, "��ǰ�Ѷ�");

//	Sleep(time);
	for (int i = 0; i < snake.len; i++)							//����ߣ���
	{
		clearcircle(snake.scr[i].x, snake.scr[i].y, 10);
	}
}


//��Ϸ��ʼ��������ͼƬ���ֵȣ�
void GameInit()
{

	loadimage(&bgimg2, "11.jpg", 1200, 1450);
	loadimage(&bgimg1, "2.jpg", 800, 600);				//����ͼƬ
	mciSendString("open ˦�и�.mp3", 0, 0, 0);			//��������


	//��ʼ��һ����
	snake.len = 3;												//���ó�ʼ����
	snake.dir = right;											//���ó�ʼ����
	time = 100;												//���ó�ʼ�Ѷ�
	setfillcolor(RGB(103, 32, 121));							//
	food.eat = 0;												//��ʳ��
	for (int i = 0; i < snake.len; i++)							//������Ϊlen����
	{
		snake.scr[i].x = 300 + i * 20;								//��ʼλ��Ϊ(300,300),��ÿ����x+=20��y����
		snake.scr[i].y = 300;
	}
}
