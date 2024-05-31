#include "StageInfo.h"
#include "Rendering.h"

Ball ball = { 40.0f, 12.0f, 0.0f, 0.0f };

void Draw_Ball()
{
	Sprite_Draw(ball.x, ball.y, ball.sprite);
}

void Draw_Wall()
{
	for (int y = 0; y < dfSCREEN_HEIGHT; y++)
	{
		for (int x = 0; x < dfSCREEN_WIDTH; x++)
		{
			if (y == dfSCREEN_HEIGHT - 1)
			{
				Sprite_Draw(x, y, '-');
			}

			if (x == dfSCREEN_WIDTH - 1 || x == 0)
			{
				Sprite_Draw(x, y, '|');
			}
		}

	}
}
