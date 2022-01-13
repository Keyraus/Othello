#pragma once
#include "utils.h"

typedef struct BotNode_s
{
	Board* actualGame;
	Pawn playedColor;
	int value;
	int x;
	int y;
	int depth;
	bool max;

	int childTabSize;
	struct BotNode_s** childs;

}BotNode;

typedef struct BoardPlay_s
{
	int value;
	int x;
	int y;
}BoardPlay;

int Bot_doAFlip(Board* original, Pawn playedColor, int depth);
int Bot_addChild(BotNode* parent, int x, int y, int tabPos);
BotNode* Bot_newNode(Board* toCopy, int depth, bool mode);
void Bot_freeNode(BotNode* node);
