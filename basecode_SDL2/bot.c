#include "bot.h"

int Bot_doAFlip(Board* original, Pawn playedColor, int depth)
{
	BotNode* root = Bot_newNode(original, depth, true);
	int childTabSize = Board_getCountPlays(original);

	root->actualGame = original;
	root->playedColor = playedColor;
	root->depth = depth;
	root->max = true;
	root->childs = calloc(childTabSize, sizeof(BotNode*));
	assert(root->childs);

	int i = 0;
	for (int y = 0; y < 8; ++y)
		for (int x = 0; x < 8; x++)
			if (original->gain[x][y])
			{
				Bot_addChild(root, x, y, i++);
			}

	int max = 0;
	for (int j = 0; j < childTabSize; j++)
	{
		if (root->childs[j]->value > root->childs[max]->value)
		{
			max = j;
		}
	}

	Board_addPawn(original, root->childs[max]->x, root->childs[max]->y, playedColor);

	return 0;
}

int Bot_addChild(BotNode* parent, int x, int y, int tabPos) 
{
	int mode = (1 + -2 * (parent->max));
	int gain = parent->actualGame->gain[x][y] * mode;//if goes boom
	if (!parent->depth)
	{
		BotNode* node = calloc(1, sizeof(BotNode));
		assert(node);
		parent->childs[tabPos] = node;
		node->value = gain;
		return gain;
	}
	//TODO CALCULER SI AUCUNES POSSIBILITER
	BotNode* node = Bot_newNode(parent->actualGame, parent->depth-1, !parent->max);
	parent->childs[tabPos] = node;
	Board_addPawn(node->actualGame, x, y, parent->playedColor);
	
	node->value = gain ;
	node->playedColor = node->playedColor % 2 + 1;
	
	int childTabSize = Board_getCountPlays(node->actualGame);
	node->childs = calloc(childTabSize, sizeof(BotNode*));
	assert(node->childs);

	int* gainLeaves = calloc(childTabSize, sizeof(int));
	assert(gainLeaves);

	int i = 0;
	for (int y = 0; y < 8; ++y)
		for (int x = 0; x < 8; x++)
			if (parent->actualGame->gain[x][y])
			{
				Bot_addChild(node, x, y, i++);
				
			}
	int min_max = 0;
	for (int j = 0; j < childTabSize; j++)
	{
		if (gainLeaves[j] * !mode > gainLeaves[min_max] * !mode)
		{
			min_max = j;
		}
	}
	node->value = node->childs[min_max]->value + gain;
	node->childs[min_max]->x = x;
	node->childs[min_max]->y = y;
	return 0;
}

BotNode* Bot_newNode(Board* toCopy, int depth, bool mode)
{
	BotNode* node = calloc(1, sizeof(BotNode));
	assert(node);

	Board* newBoard = calloc(1, sizeof(Board));
	assert(newBoard);

	SDL_memcpy(newBoard, toCopy, sizeof(Board));
	
	node->actualGame = newBoard;
	node->depth = depth;
	node->max = mode;

	return node;
}

void Bot_freeNode(BotNode* node)
{

	free(node);
	return;
}
