#include "bot.h"
//#include "vld.h"

const int WEIGHTS[8][8] = {
{4, -3, 2, 2, 2, 2, -3, 4},
{-3, -4, -1, -1, -1, -1, -4, -3},
{2, -1, 1, 0, 0, 1, -1, 2},
{2, -1, 0, 1, 1, 0, -1, 2},
{2, -1, 0, 1, 1, 0, -1, 2},
{2, -1, 1, 0, 0, 1, -1, 2},
{-3, -4, -1, -1, -1, -1, -4, -3},
{4, -3, 2, 2, 2, 2, -3, 4}
};

int Bot_doAFlip(Board* original, Pawn playedColor, int depth)
{
	int endFlag = 0;
	BotNode* root = Bot_newNode(original, depth-1, true);
	root->childTabSize = Board_getCountPlays(original);

	if (!root->childTabSize)
	{
		free(root->actualGame);
		Bot_freeNode(root);
		return 1;
	}

	root->playedColor = playedColor;

	root->childs = calloc(root->childTabSize, sizeof(BotNode*));
	assert(root->childs);

	int i = 0;
	for (int x = 0; x < 8; ++x)
		for (int y = 0; y < 8; y++)
			if (original->gain[x][y])
			{
				Bot_addChild(root, x, y, i++);
			}

	int max = 0;
	for (int j = 0; j < root->childTabSize; j++)
	{
		if (root->childs[j]->value > root->childs[max]->value)
		{
			max = j;
		}
	}
	if (!Board_addPawn(original, root->childs[max]->x, root->childs[max]->y, playedColor))
		endFlag = 1;

	Bot_freeNode(root);
	
	return endFlag;
}

int Bot_addChild(BotNode* parent, int x, int y, int tabPos) 
{

	int mode = (1 + -2 * (parent->max));//l'inverse du parent
	int gain = (parent->actualGame->gain[x][y] + WEIGHTS[x][y]) * mode * -1;// -1 = min et 1 = max
	if (!parent->depth) // si pas de profondeur
	{
		BotNode* node = calloc(1, sizeof(BotNode));
		assert(node);
		parent->childs[tabPos] = node;
		node->x = x;
		node->y = y;
		node->value = gain ;
		return 0;
	}

	BotNode* node = Bot_newNode(parent->actualGame, parent->depth-1, !parent->max);
	parent->childs[tabPos] = node;
	node->playedColor = Board_addPawn(node->actualGame, x, y, parent->playedColor);
	
	if (node->playedColor == parent->playedColor)//si ne peu pas jouer 1 fois
	{
		node->max = !node->max;
	}
	
	if (!node->playedColor)// si partie terminer
	{
		node->x = x;
		node->y = y;
		node->value = gain;
		return 0;
	}

	node->childTabSize = Board_getCountPlays(node->actualGame);

	node->childs = calloc(node->childTabSize, sizeof(BotNode*));
	assert(node->childs);

  	int i = 0;
	for (int y = 0; y < 8; ++y)

		for (int x = 0; x < 8; x++)
			if (node->actualGame->gain[x][y])
			{
				Bot_addChild(node, x, y, i++);
				
			}
	int min_max = 0;
	for (int j = 0; j < node->childTabSize; j++)
	{
		if (node->childs[j]->value * mode > node->childs[min_max]->value * mode)
		{
			min_max = j;
		}
	}
	node->value = node->childs[min_max]->value + gain;
	for (int j = 0; j < node->childTabSize; j++)
	{
		Bot_freeNode(node->childs[j]);
	}
	free(node->childs);
	free(node->actualGame);
	node->childTabSize = 0;
	

	node->x = x;
	node->y = y;
	
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
	int nbchild = 0;
	if (node) {
		nbchild = node->childTabSize;
		if (nbchild)
		{
			free(node->actualGame);
			for (int i = 0; i < nbchild; i++)
			{
				Bot_freeNode(node->childs[i]);
			}
			free(node->childs);
		}
	}
	
	free(node);
	return;
}
