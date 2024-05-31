#include <Windows.h>
#include <time.h>
#include <stdio.h>
#include <string>
#include <vector>
#include "main.h"
#include "Console.h"
#include "Rendering.h"
#include "StageInfo.h"
#include <cmath>


void	UpdateTitle()
{
	int idx = 0;
	const char* message = "Bounce Ball!";
	std::string current_display = "";


	// Ű���� �Է�
	for (int key = 8; key <= 255; key++)
	{
		//���� �����ִ� Ű Ȯ�� 
		if (GetAsyncKeyState(key) & 0x8000)
		{
			cs_ClearScreen();
			cs_MoveCursor(0, 0);
			g_scene = LOAD;
		}
	}
	// �޴� ������
	while (idx < strlen(message))
	{
		clock_t	current_time = clock();
		if ((current_time / CLOCKS_PER_SEC) >= idx * 0.1)
		{
			current_display += message[idx];
			//cs_ClearScreen();
			//cs_MoveCursor((dfSCREEN_WIDTH - strlen(message)) / 2, dfSCREEN_HEIGHT / 2);
			Buffer_Clear();
			int x = (dfSCREEN_WIDTH - current_display.length()) / 2;
			int y = dfSCREEN_HEIGHT / 2;
			for (int i = 0; i < current_display.length(); i++)
			{
				Sprite_Draw(x + i, y, current_display[i]);
			}
			Buffer_Flip();
			idx++;
		}
	}
	// ���ӽ���! �޴� ���ý� ���Ӿ� ��ȯ
	cs_MoveCursor((dfSCREEN_WIDTH - strlen("======== = Game Start!==========")) / 2, dfSCREEN_HEIGHT / 2 + 1);
	printf("========= Game Start! ==========\n");
	cs_MoveCursor((dfSCREEN_WIDTH - strlen("====== = Press any key.... ======")) / 2, dfSCREEN_HEIGHT / 2 + 2);
	printf("======= Press any key.... ======\n");
}

void	UpdateGame()
{
	bool leftPressed = false;
	bool rightPressed = false;
	/*************************
				INPUT
	**************************/
	leftPressed = GetAsyncKeyState(VK_LEFT) & 0x8000;
	rightPressed = GetAsyncKeyState(VK_RIGHT) & 0x8000;
	/*************************
				LOGIC
	**************************/
	//Physics Engine
	// �߷� ����
    ball.vy += gravity;

    // Ű �Է¿� ���� �ӵ� ����
    if (leftPressed) ball.vx -= 0.2f;
    if (rightPressed) ball.vx += 0.2f;

    // ��ġ ������Ʈ
    ball.x += ball.vx;
    ball.y += ball.vy;

    // ������ �浹 ���� �� ź�� ����
    if (ball.x < 1) {
        ball.x = 1;
        ball.vx = -ball.vx * elasticity;
    }
    if (ball.x > dfSCREEN_WIDTH - 3)
	{
        ball.x = dfSCREEN_WIDTH - 3;
        ball.vx = -ball.vx * elasticity;
    }

    // �ٴڰ��� �浹 ���� �� ź��, ������ ����
    if (ball.y > dfSCREEN_HEIGHT - 2) {
        ball.y = dfSCREEN_HEIGHT - 2;
		//ball.vy = -ball.vy * elasticity;
        ball.vy = -ball.vy;
        ball.vx *= friction; // �ٴڰ��� ������ ����
    }

    // õ����� �浹 ����
    if (ball.y < 0) {
        ball.y = 0;
        ball.vy = -ball.vy * elasticity;
    }

	/*************************
			RENDERING
	**************************/
	Buffer_Clear();
	Draw_Ball();
	Draw_Wall();
	Buffer_Flip();
}

//�������� Ŭ���� ��
void	UpdateClear()
{
	Buffer_Clear();
	int idx = 0;
	const char* message = "VICTORY!!!!!";
	std::string current_display = "";

	clock_t start_time = clock();
	Buffer_Clear();
	while (idx < strlen(message))
	{
		clock_t	current_time = clock();
		if (((current_time - start_time) / CLOCKS_PER_SEC) >= idx * 0.7)
		{
			current_display += message[idx];
			cs_ClearScreen();
			cs_MoveCursor((dfSCREEN_WIDTH - strlen(message)) / 2, dfSCREEN_HEIGHT / 2);
			printf("%s\n", current_display);
			idx++;
		}
	}


	for (int key = 8; key <= 255; key++)
	{
		//���� �����ִ� Ű Ȯ�� 
		if (GetAsyncKeyState(key) & 0x8000)
		{
			cs_ClearScreen();
			cs_MoveCursor(0, 0);
			g_scene = CLEAR;
		}
	}
	Buffer_Flip();
}

//���� ����
void	UpdateOver()
{
	Buffer_Clear();
	int idx = 0;
	const char* message = "GAME OVER!!!";
	std::string current_display = "";

	clock_t start_time = clock();
	Buffer_Clear();
	while (idx < strlen(message))
	{
		clock_t	current_time = clock();
		if (((current_time - start_time) / CLOCKS_PER_SEC) >= idx * 0.5)
		{
			current_display += message[idx];
			cs_ClearScreen();
			cs_MoveCursor((dfSCREEN_WIDTH - strlen(message)) / 2, dfSCREEN_HEIGHT / 2);
			printf("%s\n", current_display);
			idx++;
		}
	}

	for (int key = 8; key <= 255; key++)
	{
		//���� �����ִ� Ű Ȯ�� 
		if (GetAsyncKeyState(key) & 0x8000)
		{
			cs_ClearScreen();
			cs_MoveCursor(0, 0);
			g_scene = GAMEOVER;
		}
	}
}
