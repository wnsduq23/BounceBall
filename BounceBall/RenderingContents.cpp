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


	// 키보드 입력
	for (int key = 8; key <= 255; key++)
	{
		//현재 눌려있는 키 확인 
		if (GetAsyncKeyState(key) & 0x8000)
		{
			cs_ClearScreen();
			cs_MoveCursor(0, 0);
			g_scene = LOAD;
		}
	}
	// 메뉴 랜더링
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
	// 게임시작! 메뉴 선택시 게임씬 전환
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
	// 중력 적용
    ball.vy += gravity;

    // 키 입력에 따른 속도 변경
    if (leftPressed) ball.vx -= 0.2f;
    if (rightPressed) ball.vx += 0.2f;

    // 위치 업데이트
    ball.x += ball.vx;
    ball.y += ball.vy;

    // 벽과의 충돌 판정 및 탄성 적용
    if (ball.x < 1) {
        ball.x = 1;
        ball.vx = -ball.vx * elasticity;
    }
    if (ball.x > dfSCREEN_WIDTH - 3)
	{
        ball.x = dfSCREEN_WIDTH - 3;
        ball.vx = -ball.vx * elasticity;
    }

    // 바닥과의 충돌 판정 및 탄성, 마찰력 적용
    if (ball.y > dfSCREEN_HEIGHT - 2) {
        ball.y = dfSCREEN_HEIGHT - 2;
		//ball.vy = -ball.vy * elasticity;
        ball.vy = -ball.vy;
        ball.vx *= friction; // 바닥과의 마찰력 적용
    }

    // 천장과의 충돌 판정
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

//스테이지 클리어 씬
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
		//현재 눌려있는 키 확인 
		if (GetAsyncKeyState(key) & 0x8000)
		{
			cs_ClearScreen();
			cs_MoveCursor(0, 0);
			g_scene = CLEAR;
		}
	}
	Buffer_Flip();
}

//게임 끝남
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
		//현재 눌려있는 키 확인 
		if (GetAsyncKeyState(key) & 0x8000)
		{
			cs_ClearScreen();
			cs_MoveCursor(0, 0);
			g_scene = GAMEOVER;
		}
	}
}
