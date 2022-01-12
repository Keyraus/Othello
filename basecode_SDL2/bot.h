#pragma once
#include "utils.h"

typedef struct BotNode_s
{
	Board* actualGame;
	int value;
	int depth;

	struct BotNode_s* childs;

}BotNode;