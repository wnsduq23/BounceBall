#include "Rendering.h"
#include "main.h"
#include "Console.h"
#include <Windows.h>
#include "StageInfo.h"
#include <time.h>

int g_scene = 0;

void main(void)
{
	cs_Initial();

	//--------------------------------------------------------------------
	// 게임의 메인 루프
	// 이 루프가  1번 돌면 1프레임이다.
	//--------------------------------------------------------------------
	while (1)
	{
		switch (g_scene)
		{
		case TITLE:
			UpdateTitle();
			break;
		case LOAD:
		{
			//로딩 씬 렌더링
			int idx = 0;
			const char* message = "Next Stage";
			std::string current_display = "";

			clock_t start_time = clock();
			Buffer_Clear();
			while (idx < strlen(message))
			{
				clock_t	current_time = clock();
				if (((current_time - start_time) / CLOCKS_PER_SEC) >= idx * 0.2)
				{
					current_display += message[idx];
					cs_ClearScreen();
					cs_MoveCursor((dfSCREEN_WIDTH - strlen(message)) / 2, dfSCREEN_HEIGHT / 2);
					printf("%s\n", current_display);
					idx++;
				}
			}

			g_scene = INGAME;
		}
		break;
		case INGAME:
			UpdateGame();
			break;
		case CLEAR:
			UpdateClear();
			break;
		case GAMEOVER:
			UpdateOver();
			break;
		}
		Sleep(50);
	}
}
