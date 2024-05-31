#ifndef STAGEINFO_H
# define STAGEINFO_H

#include <string>
#include <vector>
#include "Console.h"
#include <functional>


struct Ball {
	float		x, y;
	float		vx, vy;
	const char	sprite = 'O';
};

extern Ball ball;
const float gravity = 0.1f;
const float elasticity = 0.7f;
const float friction = 0.9f;

#endif
