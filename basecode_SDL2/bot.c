#include "bot.h"

int Bot_doAFlip(Board* original, Pawn playedColor, int depth)
{
	BotNode* root = Bot_newNode(original, depth, true);
	Board_checkGain(original, playedColor);

	return 0;
}

BotNode* Bot_addChild(BotNode* parent, int x, int y) 
{

}

BotNode* Bot_newNode(Board* toCopy, int depth, bool mode)
{
	BotNode* node = calloc(1, sizeof(BotNode));
	assert(node);

	node->depth = depth;
	node->max = mode;

	return node;
}
void Bot_freeNode(BotNode* node)
{

	free(node);
	return;
}
