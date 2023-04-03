#include <iostream>
#include <cstring>
#include "header.h"

using std::cin;
using std::cout;

//**********************************************
//               CLI FUNCTIONS
//**********************************************

int READ_COMMAND(DECK*& deckList)
{
	char buffer[20];
	char command[20];
	char* token;
	uint param1 = 0, param2 = 0;
	int arg = 0;

	cin.getline(buffer, 20);
	if (buffer[0] == '\0')
	{
		return -1;
	}


	token = strtok(buffer, " ");
	while (token != NULL)
	{
		if (arg == 0)
		{
			strcpy(command, token);
		}
		else if (arg == 1)
		{
			param1 = 0;
			for (int i = 0; i < strlen(token); ++i)
			{
				if (strchr("0123456789", token[i]) != 0)
				{
					param1 = param1 * 10 + (token[i] - '0');
				}
			}
		}
		else if (arg == 2) 
		{
			param2 = 0;
			for (int i = 0; i < strlen(token); ++i)
			{
				if (strchr("0123456789", token[i]) != 0)
				{
					param2 = param2 * 10 + (token[i] - '0');
				}
			}
		}
		else break;

		++arg;
		token = strtok(NULL, " ");
	}
	//cout <<"COMMAND: "<<command<< "\n"<<"PARAMS: "<< param1 << " " << param2 << '\n';
	PROCESS_COMMAND(command, param1, param2, deckList);
	return 1;
}

int PROCESS_COMMAND(char* command, uint param1, uint param2, DECK*& deckList)
{
	if (strcmp(command, "ADD_DECK") == 0)
	{
		//cout << "\nAdding cards to deck...\n";
		if (deckList == 0)
			ADD_DECK(param1, deckList);
		else
		{
			DECK* newLDeck = ADD_DECK(param1, deckList->last);
			deckList->last = newLDeck;
		}
	}
	else if (strcmp(command, "SHOW_DECK") == 0)
	{
		SHOW_DECK(param1, deckList);
	}
	else if (strcmp(command, "ADD_CARDS") == 0)
	{
		ADD_CARDS(param1, param2, deckList);
	}
	else if (strcmp(command, "SHOW_ALL") == 0)
	{
		SHOW_ALL(deckList);
	}
	else if (strcmp(command, "DECK_NUMBER") == 0)
	{
		DECK_NUMBER(deckList);
	}
	else if (strcmp(command, "DECK_LEN") == 0)
	{
		DECK_LEN(param1, deckList);
	}
	else if (strcmp(command, "DEL_DECK") == 0)
	{
		DEL_DECK(param1, deckList);
	}
	else if (strcmp(command, "DEL_CARD") == 0)
	{
		DEL_CARD(param1, param2, deckList);
	}
	else if (strcmp(command, "HELP") == 0)
	{
		HELP();
	}
	else if (strcmp(command, "EXIT") == 0)
	{
		EXIT();
		return 0;
	}
	else if (strcmp(command, "SHUFFLE_DECK") == 0)
	{
		CATCH_ERR(2);
		return 0;
	}
	else if (strcmp(command, "MERGE_DECKS") == 0)
	{
		CATCH_ERR(2);
		return 0;
	}
	else if (strcmp(command, "SPLIT_DECK") == 0)
	{
		CATCH_ERR(2);
		return 0;
	}
	else if (strcmp(command, "REVERSE_DECK") == 0)
	{
		CATCH_ERR(2);
		return 0;
	}
	else if (strcmp(command, "SORT_DECK") == 0)
	{
		CATCH_ERR(2);
		return 0;
	}
	else
	{
		//cout << "ERR : INVALID_COMMAND. Please try again.\n";
		CATCH_ERR(1);
	}
	return 1;
}

//**********************************************
//        ADD TO LISTS FUNCTIONS
//**********************************************

DECK* ADD_DECK(uint cardNum, DECK*& deckList)
{
	DECK* deck = new DECK;
	CARD* aux = 0;
	deck->next = 0;
	deck->prev = deckList;
	deck->last = deck;
	if (deckList == 0)
	{
		deck->cardList = 0;
		aux = ADD_CARDS(0, cardNum, deck);
		if(aux)
			deckList = deck;
	}
	else
	{	
		deck->cardList = 0;
		aux = ADD_CARDS(0, cardNum, deck);
		if (aux)
		{
			deckList->last->next = deck;
			deckList = deckList->last;
		}
	}
	if (aux)
	{
		cout << "The deck was successfully created with " << cardNum << " cards.\n\n";
		return deck;
	}
	else
	{
		delete deck;
		return 0;
	}
}

CARD* ADD_CARDS(uint dIndex, uint cardNum, DECK*& deckList)
{
	if (cardNum <= 0)
	{
		CATCH_ERR(3);
		return 0;
	}
	DECK* deckPtr = deckList;
	CARD* lastCard = 0;
	for (uint j = 0; j < dIndex; ++j)
	{
		deckPtr = deckPtr->next;
		//deckPtr->prev = deckPtr;
	}
	if (deckPtr->cardList == 0 || deckPtr->prev == 0)
		deckList = deckPtr;
	else
		deckList->next = deckPtr;
	for (uint i = 1; i <= cardNum; ++i)
	{
		CARD* currCard = new CARD;
		cout << "Card " << i << " in deck " << dIndex << " : ";
		cin >> currCard->value;
		if (currCard->value > 14 || currCard->value < 0)
		{
			CATCH_ERR(21);
			return 0;
		}
		cin >> currCard->symbol;
		if (strcmp(currCard->symbol, "PICA") != 0 && strcmp(currCard->symbol, "CUPA") != 0
			&& strcmp(currCard->symbol, "CARO") != 0 && strcmp(currCard->symbol, "TREFLA") != 0)
		{
			CATCH_ERR(21);
			return 0;
		}
		if (deckPtr->cardList == 0)
		{
			currCard->prev = deckPtr->cardList;
			currCard->next = 0;
			deckPtr->cardList = currCard;
		}
		else
		{

			currCard->prev = deckPtr->cardList;
			currCard->next = 0;
			deckPtr->cardList->next = currCard;
			//deckPtr->cardList->prev = currCard;
			deckPtr->cardList = currCard;
		}
		lastCard = currCard;
	}
	cout << "The cards were successfully added to deck " << dIndex << ".\n";
	deckPtr->lastCard = lastCard;
	return lastCard;
}

//**********************************************
//           DELETION FUNCTIONS
//**********************************************

void DEL_DECK(uint dIndex, DECK*& deckList)
{
	if (dIndex == 0)
	{
		DECK* deckPtr = deckList;
		if (deckPtr->next == 0)
		{
			delete deckList->cardList;
			deckList->cardList = 0;
			delete deckList;
			deckList = 0;
		}
		else
		{
			deckList = deckList->next;
			deckList->prev = 0;
			delete deckPtr->cardList;
			deckPtr->cardList = 0;
			delete deckPtr;
		}
		cout << "The deck " << dIndex << " was successfully deleted.\n";
	}
	else
	{
		DECK* deckPtr = deckList;
		if (deckPtr == 0)
		{
			CATCH_ERR(10);
			return;
		}
		for (uint i = 0; i < dIndex; ++i)
		{
			deckPtr = deckPtr->next;
			if (deckPtr == 0)
			{
				CATCH_ERR(10);
				return;
			}
		}
		deckPtr->prev->next = deckPtr->next;
		if(deckPtr->next)
			deckPtr->next->prev = deckPtr->prev;
		delete deckPtr->cardList;
		deckPtr->cardList = 0;
		delete deckPtr;
		deckPtr = 0;
		cout << "The deck " << dIndex << " was successfully deleted.\n";
	}
}
// !!!!! this is not fully implemented, doesn't work for all cases yet (time ran out)
void DEL_CARD(uint dIndex, uint cIndex, DECK*& deckList)
{
	if(cIndex <= 0)
		CATCH_ERR(20);
	DECK* deckPtr = deckList;
	if (deckPtr == 0)
	{
		CATCH_ERR(10);
		return;
	}
	for (uint i = 0; i < dIndex; ++i)
	{
		deckPtr = deckPtr->next;
		if (deckPtr == 0)
		{
			CATCH_ERR(10);
			return;
		}
	}
	CARD* cardPtr = deckList->cardList;
	if (cardPtr == 0)
	{
		CATCH_ERR(20);
		return;
	}
	for (uint i = 0; i < cIndex; ++i)
	{
		cardPtr = cardPtr->prev;
		if (cardPtr == 0)
		{
			CATCH_ERR(20);
			return;
		}
	}
	if (cIndex == 1)
	{
		if (cardPtr->prev == 0 && cardPtr->next == 0)
		{
			cout << "The card was successfully deleted from deck " << dIndex << ".\n";
			DEL_DECK(dIndex, deckPtr);
		}
		else
		{
			deckPtr->cardList = deckPtr->cardList->prev;
			deckPtr->cardList->next = 0;
			delete cardPtr;
		}
	}
	else
	{
		cardPtr->next->prev = cardPtr->prev;
		if (cardPtr->prev)
			cardPtr->prev->next = cardPtr->next;
		delete cardPtr;
		cardPtr = 0;
		cout << "The card was successfully deleted from deck " << dIndex << ".\n";
		if (deckList->cardList == 0)
		{
			DEL_DECK(dIndex, deckPtr);
			deckPtr = 0;
		}
	}

}

//**********************************************
//        PRINT LISTS FUNCTIONS
//**********************************************

void SHOW_DECK(uint dIndex, DECK* deckList)
{
	DECK* deckPtr = deckList;
	if (deckPtr == 0)
	{
		CATCH_ERR(10);
		return;
	}
	for (uint j = 0; j < dIndex; ++j)
	{
		deckPtr = deckPtr->next;
		if (deckPtr == 0)
		{
			CATCH_ERR(10);
			return;
		}
	}
	cout << "Deck " << dIndex << " : \n";
	CARD* cardPtr = deckPtr->cardList;
	RECURSIVE_SHOW_CARDS(cardPtr);
}

void RECURSIVE_SHOW_CARDS(CARD* cardList)
{
	if (cardList->prev != 0)
		RECURSIVE_SHOW_CARDS(cardList->prev);
		cout << '\t' << cardList->value << " " << cardList->symbol << '\n';
		cardList = cardList->next;
}


void SHOW_ALL(DECK* deckList)
{
	DECK* deckPtr = deckList;
	int i = 0;
	while (deckPtr != 0)
	{
		cout << "Deck " << i++ << " : \n";
		CARD* cardPtr = deckPtr->cardList;
		RECURSIVE_SHOW_CARDS(cardPtr);
		deckPtr = deckPtr->next;

	}
}

//**********************************************
//           NUMBER FUNCTIONS
//**********************************************

void DECK_NUMBER(DECK* deckList)
{
	uint num = 0;
	while (deckList)
	{
		++num;
		deckList = deckList->next;
	}
	cout << "The number of decks is " << num << ".\n";
}

void DECK_LEN(uint dIndex, DECK* deckList)
{
	DECK* deckPtr = deckList;
	if (deckPtr == 0)
	{
		CATCH_ERR(10);
		return;
	}
	for (uint i = 0; i < dIndex; ++i)
	{
		deckPtr = deckPtr->next;
		if (deckPtr == 0)
		{
			CATCH_ERR(10);
			return;
		}

	}
	CARD* cardPtr = deckPtr->cardList;
	uint num = 0;
	while (cardPtr)
	{
		++num;
		cardPtr = cardPtr->prev;
	}
	cout << "The length of deck " << dIndex << " is " << num << ".\n";
}

//**********************************************
//        ERRORS AND EXIT FUNCTIONS
//**********************************************

void CATCH_ERR(uint ERR)
{
	switch (ERR)
	{
	case 1:
		cout << "Invalid command. Please try again.\n";
		break;
	case 2:
		cout << "This function has not been implemented yet.\n";
		break;
	case 3:
		cout << "The number of cards to be inserted is invalid.\n";
		break;
	case 10:
		cout << "The provided deck index is out of bounds for the deck list.\n";
		break;
	case 20:
		cout << "The provided card index is out of bounds for the selected deck.\n";
		break;
	case 21:
		cout << "The provided card is not a valid one. Add to deck is cancelled.\n";
		break;
	default:
		cout << "An unknown error has occured. Please try again or contact the developer.\n";
		break;
	}
}

void HELP(void)
{
	cout << "Welcome! The available commands and their syntax is:\n";
	cout << "      FOR DECKS          |                FOR CARDS              | GENERAL\n";
	cout << "ADD_DECK <NumberOfCards> | ADD_CARDS <deckIndex> <NumberOfCards> |  EXIT\n";
	cout << "DEL_DECK <deckIndex>     | DEL_CARD <deckIndex> <cardIndex>      |  HELP\n";
	cout << "DECK_NUMBER\n";
	cout << "DECK_LEN <deckIndex>\n";
	cout << "SHOW_DECK <deckIndex>\n";
	cout << "SHOW_ALL\n";
	cout << "Not implemented: SHUFFLE_DECK, MERGE_DECKS, SPLIT_DECK, REVERSE_DECK, SORT_DECK.\n";
	cout << "Not working properly: DEL_CARD.\n";
	cout << "The updated version will be available on github.com/evomh.\n";
}

void EXIT(void)
{
	cout << "Quitting game...\n";
	exit(0);
}