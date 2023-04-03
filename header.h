#pragma once

// ERROR CODES: name - <1 - deck error; 2 - card error> <error_number>
// DECK_INDEX_OUT_OF_BOUNDS 10;
// CARD_INDEX_OUT_OF_BOUNDS 20;
// INVALID_CARD 21;
// INVALID_COMMAND 1;
// NOT_IMPLEMENTED 2;

typedef unsigned int uint;

struct CARD
{
	uint value;
	char symbol[7];
	CARD* next, * prev;
};

struct DECK {
	CARD* cardList, * lastCard;
	DECK* next, * prev, * last;
};
// READ_COMMAND : reads input from cmdline and parses the string to process commands. Returns success code.
// Parameter: deck list to save in main.
int READ_COMMAND(DECK*& decklist);
// PROCESS_COMMAND : cmdline interpreter to call functions while program is running.
// Returns a success message. Parameter: deck list to save in main.
// Examples: EXIT, HELP, ABOUT, SPLIT_DECK 0 2
int PROCESS_COMMAND(char* command, uint param1, uint param2, DECK*& deckList);
// ADD_DECK : adds a new deck of cardNum cards at the end of deck list. Returns the last deck in deck list.
// If deck reaches cardNum cards it will add it to deck list, then print a success message.
// If the card is invalid it will throw INVALID_CARD error.
DECK* ADD_DECK(uint cardNum, DECK*& deckList);
// DEL_DECK : deletes deck at dIndex, then prints a success message.
void DEL_DECK(uint dIndex, DECK*& deckList);
// DEL_CARD : deletes card at cIndex from pack at dIndex, then prints a success message.
// If pack becomes empty, it is deleted from the list.
void DEL_CARD(uint cIndex, uint dIndex, DECK*& deckList);
// ADD_CARDS : adds in pack at dIndex a number of cardNum cards, then prints a success message.
CARD* ADD_CARDS(uint dIndex, uint cardNum, DECK*& deckList);
// DECK_NUMBER: prints the number of decks in the deck list. Returns the last card in deck.
void DECK_NUMBER(DECK* deckList);
// DECK_LEN: prints the number of cards (length) contained in the deck list.
void DECK_LEN(uint dIndex, DECK* deckList);
// SHUFFLE_DECK : interpolates the first and the second half of the deck at dIndex, then prints a success message.
// First half is n/2, the second is n/2 if n is even, or n/2+1 if n odd.
void SHUFFLE_DECK(uint dIndex, DECK*& decklist);
// MERGE_DECKS : merges deck at dIndex1 with deck ad dIndex2 via interpolation, then prints a success message.
// The two packs will be deleted, with the resulting pack added at the end of the deck list.
void MERGE_DECKS(uint dIndex1, uint dIndex2, DECK*& decklist);
// SPLIT_DECK : splits deck at dIndex by card at cIndex. First pack will stay at dIndex, and the second will be inserted at dIndex + 1.
// If after splitting the result is an empty deck and one that contains all of them, only the one with cards will be kept.
// Prints a success message.
void SPLIT_DECK(uint dIndex, uint cIndex, DECK*& deckList);
// REVERSE_DECK : reverses the order of cards in deck at dIndex, then prints a success message.
void REVERSE_DECK(uint dIndex, DECK* deckList);
// SHOW_DECK : prints the cards in deck at dIndex.
void SHOW_DECK(uint dIndex, DECK* deckList);
// SHOW_ALL : prints all the cards in all the decks in deck list.
void SHOW_ALL(DECK* deckList);
// SORT_DECK : sorts the deck at dIndex by the values of the cards.
// If the cards have same value, priority is: PICA, CUPA, CARO, TREFLA.
// Prints a success message.
void SORT_DECK(uint dIndex, DECK*& deckList);
// EXIT : exits the program.
void EXIT(void);
// CATCH_ERR : catches errors and prints certain messages.
void CATCH_ERR(uint ERR);

// AUXILIARY FUNCTIONS

void RECURSIVE_SHOW_CARDS(CARD* cardList);
void HELP(void);
