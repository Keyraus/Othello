#pragma once
#include "utils.h"

typedef struct BotNode_s
{
	Board* actualGame;
	Pawn playedColor;
	int value;
	int depth;
	bool max;

	struct BotNode_s* childs;

}BotNode;

int Bot_doAFlip(Board* original, Pawn playedColor);
BotNode* Bot_newNode(Board* toCopy, int depth, bool mode);
