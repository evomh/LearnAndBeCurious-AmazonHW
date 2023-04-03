#include <iostream>
#include "header.h"

using std::cout;

int main(void)
{
	cout << "=========================================================\n";
	cout << "|            CRACIUN MIHAI'S CARD GAME                  |\n";
	cout << "=========================================================\n";
	cout << "\nCommandline started. Type HELP for details.\n\n";
	cout << "[player @ game] ~ ";
	DECK* deckList = 0;
	DECK* lastDeck = deckList;
	int run = READ_COMMAND(deckList);
	while (run)
	{
		if(run != -1)
			cout << "[player @ game] ~ ";
		run = READ_COMMAND(deckList);
	}
}