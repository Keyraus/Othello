#include "bot.h"

int Bot_doAFlip(Board* original, Pawn playedColor, int depth)
{
	BotNode* root = Bot_newNode(original, depth, true);
	int childTabSize = Board_getCountPlays(original);

	root->childs = calloc(childTabSize, sizeof(BotNode*));
	assert(root->childs);

	BoardPlay* gainPlay = calloc(childTabSize, sizeof(BoardPlay));
	assert(gainPlay);

	int i = 0;
	for (int y = 0; y < 8; ++y)
		for (int x = 0; x < 8; x++)
			if (original->gain[x][y])
			{
				gainPlay[i].value = Bot_addChild(root, x, y, i);
				gainPlay[i].x = x;
				gainPlay[i++].y = y;
			}

	int max = 0;
	for (int j = 0; j < childTabSize; j++)
	{
		if (gainPlay[j].value > gainPlay[max].value)
		{
			max = j;
		}
	}

	Board_addPawn(original, gainPlay[max].x, gainPlay[max].y, playedColor);

	return 0;
}

int Bot_addChild(BotNode* parent, int x, int y, int tabPos) 
{
	int mode = (1 + -2 * (parent->max));
	int gain = parent->actualGame->gain[x][y] * mode;//if goes boom
	if (!parent->depth)
	{
		return gain;
	}
	//TODO CALCULER SI AUCUNES POSSIBILITER
	BotNode* node = Bot_newNode(parent->actualGame, parent->depth-1, !parent->max);
	parent->childs[tabPos] = node;
	Board_addPawn(parent->actualGame, x, y, parent->playedColor);
	
	node->value = gain ;
	node->playedColor = node->playedColor % 2 + 1;
	
	int childTabSize = Board_getCountPlays(parent->actualGame);
	node->childs = calloc(childTabSize, sizeof(BotNode*));
	assert(node->childs);

	int* gainLeaves = calloc(childTabSize, sizeof(int));
	assert(gainLeaves);

	int i = 0;
	for (int y = 0; y < 8; ++y)
		for (int x = 0; x < 8; x++)
			if (parent->actualGame->gain[x][y])
			{
				gainLeaves[i] = Bot_addChild(node, x, y, i++);
			}
	int min_max = 0;
	for (int j = 0; j < childTabSize; j++)
	{
		if (gainLeaves[j] * !mode > gainLeaves[min_max] * !mode)
		{
			min_max = j;
		}
	}
	return node->childs[min_max]->value + gain;
}


BotNode* Bot_newNode(Board* toCopy, int depth, bool mode)
{
	BotNode* node = calloc(1, sizeof(BotNode));
	assert(node);

	Board* newBoard = calloc(1, sizeof(Board));
	assert(newBoard);

	SDL_memcpy(newBoard, toCopy, sizeof(Board));
	
	node->depth = depth;
	node->max = mode;

	return node;
}
void Bot_freeNode(BotNode* node)
{

	free(node);
	return;
}
