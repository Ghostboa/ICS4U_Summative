// Blackjack beginning.cpp : Defines the entry point for the console application.

//Requirements: Save output to File, Recursive shuffle, complete actual game with Dealer AI
// Other cool stuff: Variable AI aggressiveness/Number of Players, number of Cards, game records or login thing, actual betting, encrypted files, difficulty settings.

/*
The players' objective is to win money by creating card totals that turn out to be higher than the dealer's hand
but do not exceed 21 ("busting"/"breaking"), or alternatively by allowing the dealer to take additional Cards until they bust.
On their turn, players must choose whether to
"hit" (take a card)
"stand" (end their turn)
"double" (double wager, take a single card and finish)
"split" (if the two Cards have the same value, separate them to make two hands)
"surrender" (give up a half-bet and retire from the game)
*/

//#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include "time.h"
#define MAX_PLAYERS 2

//__________________________________________________________________Structures and Constants
int const maxCards = 52; //#define maxCards 52

enum suits { Spades, Hearts, Diamonds, Clubs };

//Deck Proposition
struct inPlay{
	bool played;
};

struct Cards{
	inPlay Spades[13]; // This array actually goes 0-12. The previous one only had 12 elements, or 48 cards. Oops.
	inPlay Hearts[13];
	inPlay Diamonds[13];
	inPlay Clubs[13];
};

struct playerCard {
	int suit;
	int value;
	int counter; // what is this for?
};

struct Profile {
	int numCards;
	playerCard hand[11];
	int money;
	int total;
	int fucklenuts;
};

//making space for 2 AIs

//__________________________________________________________________Basic Functions
int rb(int min, int max) { // Magic random number thingy
	return rand() % (max - min + 1) + min;
}

int getNum(int lo, int hi){ // Thing Wilson likes to have to get a number between a min and max value. Could be useful.
	//good for invalid answer prevention
	int num = 0;

	std::cin >> num;
	while (num < lo || num > hi){
		std::cin >> num;
	}
	return num;
}

void swap(int a, int b){ //swaps two elements
	int temp;

	temp = a;
	a = b;
	b = temp;
}

bool cardCheck(Cards *deck, int suit, int value){ //returns whether a certain card is in play (1 is in play, 0 is in deck)
	switch (suit){
	case 0:
		return deck[0].Spades[value].played;
	case 1:
		return deck[0].Hearts[value].played;
	case 2:
		return deck[0].Diamonds[value].played;
	case 3:
		return deck[0].Clubs[value].played;
	}
}

void rules(){
	printf("Example Rules\n");
	system("PAUSE");
}

//__________________________________________________________________Complex Functions
/*
void AI (Profile*AI){
int stand = 0;

if (*AI.money < 1)
//surrender
while (!stand){
if(*AI.total + *AI.fucklenuts > 21)
stand = 1;
else
//hit
}
}


void dealer (Profile*dealer){
while (dealer.total < 18)
//hit
}
*/

void hit(Cards *deck, Profile* player, int pNum){
	int tempSuit;
	int tempValue;

	do {
		tempSuit = rand() % 3;
		tempValue = rb(1, 13);
	} while (cardCheck(deck, tempSuit, tempValue) == true);

	//removal from deck (suits are annoying)
	switch (tempSuit){
	case 0:
		deck[0].Spades[tempValue].played = 1;
		break;
	case 1:
		deck[0].Hearts[tempValue].played = 1;
		break;
	case 2:
		deck[0].Diamonds[tempValue].played = 1;
		break;
	case 3:
		deck[0].Clubs[tempValue].played = 1;
		break;
	}

	player[pNum].hand[(player[pNum].numCards)].suit = tempSuit;
	player[pNum].hand[(player[pNum].numCards)].value = tempValue;

	if (tempValue >= 10) // Assigning the count to the players hand.
		player[pNum].hand[(player[pNum].numCards)].counter = 10;
	else if (tempValue == 1){
		if (player[pNum].total >= 11) // For Aces!
			player[pNum].hand[(player[pNum].numCards)].counter = 1;
		else
			player[pNum].hand[(player[pNum].numCards)].counter = 11;
	}
	else{
		player[pNum].hand[(player[pNum].numCards)].counter = tempValue;
	}

	player[pNum].total += player[pNum].hand[(player[pNum].numCards)].counter;
	player[pNum].numCards++;
	//need to remove card from deck, place in player's hand
}

void deckReset(Cards *deck, Profile* player, int numPlayers){
	for (int i = 0; i <= 12; i++){
		deck[0].Spades[i].played = 0;
		deck[0].Hearts[i].played = 0;
		deck[0].Diamonds[i].played = 0;
		deck[0].Clubs[i].played = 0;
	}

	for (int i = 0; i <= numPlayers; i++){
		player[i].numCards = 0;
		player[i].total = 0;
	}
}

void printCard(int suit, int value){
	switch (value){
	case 1:
		printf("A%c", suit + 3);
		break;
	case 11:
		printf("J%c", suit + 3);
		break;
	case 12:
		printf("Q%c", suit + 3);
		break;
	case 13:
		printf("K%c", suit + 3);
		break;
	default:
		printf("%i%c", value, suit + 3);
		break;
	}
}

void deal(Cards *deck, Profile* player, int numPlayers){
	for (int i = 0; i < numPlayers; i++)
		for (int j = 0; j < 2; j++){
		hit(deck, player, i);
		}
}

void display(Profile* player, int numPlayers){
	printf("Dealer\t\t");
	for (int i = 1; i < numPlayers; i++){
		printf("player%i\t\t", i);
	}
	printf("\n");
	for (int i = 0; i < numPlayers; i++){
		for (int j = 0; j < player[i].numCards; j++)
			printCard(player[i].hand[j].suit, player[i].hand[j].value);
		printf("\t\t");
	}
	printf("\n");
	for (int i = 0; i < numPlayers; i++){
		printf("Total: %i\t", player[i].total);
	}
	printf("\n");


}

void saveGame(Profile* player, int numPlayers){
	FILE *fp;

	printf("Which slot would you like to save in? (1-3) \n");
	int slot = getNum(1, 3);

	if (slot == 1) // Perhaps this should be changed to allow for file name variation (Constants.)
		fp = fopen("Save1.txt", "w");
	else if (slot == 2)
		fp = fopen("Save2.txt", "w");
	else if (slot == 3)
		fp = fopen("Save3.txt", "w");
	else //This really should not happen
		fp = fopen("Save1.txt", "w");

	if (fp){
		for (int i = 0; i < numPlayers; i++){
			fprintf(fp, "Player %i: \n", i + 1);
			for (int k = 0; k < player[i].numCards; k++){
				fprintf(fp, "%i/%i ", player[i].hand[k].value, player[i].hand[k].suit);
			}
			fprintf(fp, "\n");
			fprintf(fp, "Count: %i", player[i].total);
			fprintf(fp, "\n\n");
		}

		fclose(fp);
	}

}

//__________________________________________________________________Menu and Directories
int startMenu(){ // the menu.
	//Made this clear both before AND after, and have a pretty (subjective) title
	int user = 100;
	system("cls");
	printf("______________________\n WELCOME TO BLACKJACK\n~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("0. Rules \n");
	printf("1. Start game. \n");
	printf("2. Exit\n");

	user = getNum(0, 2);
	system("cls");
	return user;
}

int mainGame(Cards *deck, Profile* player, int numPlayers){

	deckReset(deck, player, numPlayers);

	//need function to get number of players (currently set to 2)
	deal(deck, player, numPlayers);
	display(player, numPlayers);
	saveGame(player, numPlayers);
	system("PAUSE");
	return 0;
}

int main(){
	srand(time(NULL)); // Seeding the thing
	Cards deck; //two dimensional array, accessed by deck.Spades[1].played  (would return 1 or 0, depending on whether the ace of spades is in play)
	Profile player[4];//initialization of dealer and hooman, will need to manually initialize later
	printf("Input number of players");
	int numPlayers = getNum(2, MAX_PLAYERS);

	while (1){
		switch (startMenu()){
		case (0) :
			rules();
			break;

		case (1) :
			mainGame(&deck, player, numPlayers);
			break;

		case (2) :
			return 0;
		}
	}
	system("PAUSE");
	return 0;
}
