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
const int maxCards = 52; //#define maxCards 52

enum suits { Spades, Hearts, Diamonds, Clubs };

struct Cards{
	bool Spades[13]; // This array actually goes 0-12. The previous one only had 12 elements, or 48 cards. Oops.
	bool Hearts[13];
	bool Diamonds[13];
	bool Clubs[13];
};

struct PlayerCard {
	int suit;
	int value;
	int counter; // what is this for?
};

struct Profile {
	int numCards;
	PlayerCard hand[11];
	int money;
	int total;
	int fucklenuts;
};

//making space for 2 AIs

//__________________________________________________________________Basic Functions
int rb(const int min, const int max) { // Magic random number thingy
	return rand() % (max - min + 1) + min;
}

int getNum(const int lo, const int hi){ // Thing Wilson likes to have to get a number between a min and max value. Could be useful.
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
		return deck[0].Spades[value];
	case 1:
		return deck[0].Hearts[value];
	case 2:
		return deck[0].Diamonds[value];
	case 3:
		return deck[0].Clubs[value];
	}
}

void rules(){
    printf("RULES:\n");
	printf("Blackjack is the most DANK game on PC! I've learned how to collect SWAG DOLLAS \nfrom Bigley by harnessing the Illuminatis card counters and 360 noscoping the \ndealer! MY review of Blackjack is 8/8, no b8 m8. Hehv fun! Huehuehuehuehuehue.\n");
	system("PAUSE");
    /*
	printf("RULES:\n");
	printf("The goal of Blackjack is to have the highest hand without exceeding a total value of 21.\n");
	printf("Every player is dealt two cards.\n");
	printf("Every player can do two things: hit and stand.\n");
	printf("If you 'hit', you get another card.\n");
	printf("If you 'stand' then you are doing taking cards.\n");
	printf("If you hit and it ushes the value of your hand over 21, then you are out for that round.\n");
	printf("The dealer goes first, and hits himself until he has a hand of 18 or over.\n");
	printf("Everybody else can choose to hit or stand as they wish.\n");
	system("PAUSE");
	*/
}

int getNumPlayers (){
	printf("Input number of players, including dealer\n");
	return getNum(2, MAX_PLAYERS);
}

void addCard (Profile* player, int tempSuit, int tempValue){
	player -> hand[player -> numCards].suit = tempSuit;
	player -> hand[player -> numCards].value = tempValue;
}
//__________________________________________________________________Complex Functions
/*
void AI (Cards *deck, Profile*AI){
    int stand = 0;

    if (*AI.money < 1)
        //surrender
    while (!stand){
        if(*AI.total + *AI.fucklenuts > 21)
            stand = 1;
        else
            hit(*deck, *AI);
}
}


void dealer (Profile*dealer){
    while (dealer.total < 18)
       hit(*deck, *dealer);
}
*/


void hit(Cards *deck, Profile* player){
    if (player -> total < 21){
	int tempSuit;
	int tempValue;

	do {
		tempSuit = rand() % 3;
		tempValue = rb(1, 13);
	} while (cardCheck(deck, tempSuit, tempValue) == true);

	//removal from deck (suits are annoying)
	switch (tempSuit){
	case 0:
		deck[0].Spades[tempValue] = 1;
		break;
	case 1:
		deck[0].Hearts[tempValue] = 1;
		break;
	case 2:
		deck[0].Diamonds[tempValue] = 1;
		break;
	case 3:
		deck[0].Clubs[tempValue] = 1;
		break;
	}

    switch (tempValue){
        case 1:
            if ((player -> total) <= 10)
                player -> hand[player -> numCards].counter = 11;
            else
                player -> hand[player -> numCards].counter = 1;
            break;
//        case 11,12,13:
//            player -> hand[player -> numCards.counter = 10;
//            break;
        default:
            player -> hand[player -> numCards].counter = tempValue;
            break;
    }
	player -> total += player -> hand[(player -> numCards)].counter;

	player -> hand[player -> numCards].suit = tempSuit;
	player -> hand[player -> numCards].value = temhit(*deck, *AI);pValue;

	player -> numCards++;
	//need to remove card from deck, place in player's hand
    }
    else{
        printf ("Miss");
    }
}

void deckReset(Cards *deck, Profile* player, int numPlayers){
	for (int i = 0; i <= 12; i++){
		deck[0].Spades[i] = 0;
		deck[0].Hearts[i] = 0;
		deck[0].Diamonds[i] = 0;
		deck[0].Clubs[i] = 0;
	}

	for (int i = 0; i <= numPlayers; i++){
		player[i].numCards = 0;
		player[i].total = 0;
	}
}

void printCard(const int suit, const int value){
	switch (value){
	case 1:
		printf("A%c ", suit + 3);
		break;
	case 11:
		printf("J%c ", suit + 3);
		break;
	case 12:
		printf("Q%c ", suit + 3);
		break;
	case 13:
		printf("K%c ", suit + 3);
		break;
	default:
		printf("%i%c ", value, suit + 3);
		break;
	}
}

void deal(Cards *deck, Profile* player, int numPlayers){
	for (int i = 0; i < numPlayers; i++)
		for (int j = 0; j < 2; j++){
            hit(deck, &player[j]);
		}
}

void display(Profile* player, int numPlayers){

    system("cls");
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

void round (Cards* deck, Profile* player, int numPlayers){
    int userIn;
    for (int i = 0; i < numPlayers;){
            display(player, numPlayers);
            printf ("Player %i, would you like to\n1 - stand\n2 - hit?\n", i);
            userIn = getNum(1,2);
            switch (userIn){
                case 1:
                    i++;
                    break;
                case 2:
                    hit (deck, &player[i]);
                    break;
            }
    }
}
*/
//__________________________________________________________________Menu and Directories
int startMenu(){
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

void mainGame(Cards *deck, Profile* player, int numPlayers){
	deckReset(deck, player, numPlayers);
	deal(deck, player, numPlayers);
    round (deck, player, numPlayers);
	saveGame(player, numPlayers);
}

int main(){
    //setup required structs and seeding pre-game
	int numPlayers = getNumPlayers();
    Profile player[numPlayers];
    Cards deck;
    srand(time(NULL)); // Seeding the thing


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
