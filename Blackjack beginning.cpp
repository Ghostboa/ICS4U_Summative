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
const int MIN_RISK = 2; // This is sort of misleading: The smaller the number the higher the risk level is... :/
const int MAX_RISK = 8;

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
	bool end;
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
	//printf("RULES:\n");
	//printf("Blackjack is the most DANK game on PC! I've learned how to collect SWAG DOLLAS \nfrom Bigley by harnessing the Illuminatis card counters and 360 noscoping the \ndealer! MY review of Blackjack is 8/8, no b8 m8. Hehv fun! Huehuehuehuehuehue.\n");
	//system("PAUSE");
	
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
	
}

int getNumPlayers(){
	printf("Input number of players, including dealer\n");
	return getNum(2, MAX_PLAYERS);
}

void addCard(Profile* player, int tempSuit, int tempValue){
	player->hand[player->numCards].suit = tempSuit;
	player->hand[player->numCards].value = tempValue;
}
//__________________________________________________________________Complex Functions

int sum(Profile* player){
	int numAces = 0;
	player->total = 0;
	for (int i = 0; i < player->numCards; i++){
		if (player->hand[i].value == 1){
			numAces++;
		}
		else if (player->hand[i].value >= 10){
			player->total += 10;
		}
		else{
			player->total += player->hand[i].value;
		}
	}

	for (int i = 0; i < numAces; i++){
		if (player->total <= 10){
			player->total += 11;
		}
		else{
			player->total += 1;
		}
	}
	return player->total;
}





void setPlayed(Cards* deck, int tempValue, int tempSuit){ 		//removal from deck (suits are annoying)
	switch (tempSuit){											// Makes sure there are no duplicate cards dealt.
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
}


void hit(Cards *deck, Profile* player){
	if (player->total < 21){
		int tempSuit;
		int tempValue;

		do {
			tempSuit = rand() % 3;
			tempValue = rb(1, 13);
		} while (cardCheck(deck, tempSuit, tempValue) == true);

		//removal from deck (suits are annoying)
		setPlayed(deck, tempValue, tempSuit);


		// Hadds stuff to hand
		player->hand[player->numCards].suit = tempSuit;
		player->hand[player->numCards].value = tempValue;
		player->numCards++;

	}
	else{
		printf("Miss");
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
		player[i].fucklenuts = rb(MIN_RISK, MAX_RISK);
		player[i].end = false;
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

		if (i == 0){ // Exception case for the dealer (He only gets one card, then at the start of the game, gets another.)
		hit(deck, &player[i]);
		}
		else for (int j = 0; j < 2; j++){
			hit(deck, &player[i]);
		}
}

void dealer(Cards *deck, Profile*dealer){
	if (dealer[0].total < 18)
		hit(deck, dealer);
	else
		dealer[0].end = true;

	return;
}

void AI(Cards *deck, Profile*AI){

	//if (AI[0].money < 1)
	//surrender
	if (AI[0].total + AI[0].fucklenuts > 21){
		AI[0].end = true;
		return;
	}
	else
		hit(deck, AI);

}


void display(Profile* player, int numPlayers){ // Displays the players hand on the screen.

	system("cls");

	for (int i = 0; i < numPlayers; i++){
		if (i == 0)
			printf("Dealer: ");
		else
			printf("Player %i: ", i);

		for (int k = 0; k < player[i].numCards; k++){
			printCard(player[i].hand[k].suit, player[i].hand[k].value);

		}
		printf("\n");
		printf("Count: %i.\n", sum (&player[i]));
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
		return;

	if (fp){
		fprintf(fp, "%i\n", numPlayers); // Number of players is at top of file.
		for (int i = 0; i < numPlayers; i++){
			fprintf(fp, "%i\n", player[i].numCards); // numCards
			for (int k = 0; k < player[i].numCards; k++){
				fprintf(fp, "%i %i %i ", player[i].hand[k].value, player[i].hand[k].suit, player[i].hand[k].counter);
			} // value/suit/counter
			fprintf(fp, "\n");
			fprintf(fp, "%i", player[i].total); //Count
			fprintf(fp, "\n");
			fprintf(fp, "%i", player[i].end);
			fprintf(fp, "\n");
		}

		fclose(fp);
	}

}

bool endGame(Cards *deck, Profile *player, int numPlayers){
	for (int i = 0; i < numPlayers; i++){
		if (player[i].end == false)
			return false;
	}
	return true; // Will only return true if all players are busted.
}

void round(Cards* deck, Profile* player, int numPlayers){
	int userIn;

	while (endGame(deck, player, numPlayers) == false){
		for (int i = 0; i < numPlayers; i++){
			display(player, numPlayers);

			if (i == 0)
				dealer(deck, player);

			else if (i == 1){

				if (player[i].end == false && sum(&player[i])<21){
					userIn = 0;

					do{
						printf("Player %i, would you like to\n1 - stand\n2 - hit?\n3 - Save\n", i);
						userIn = getNum(1, 3);
						if (userIn == 1 || sum (&player[i]) >= 21)
							player[i].end = true;
						else if (userIn == 2)
							hit(deck, &player[i]);
						else if (userIn == 3){
							saveGame(player, numPlayers);
							display(player, numPlayers);
						}
					} while (userIn == 3 );
				}
			}
			else if (i > 1){
				AI(deck, &player[i]);
			}

			if (player[i].total > 21)
				player[i].end = true;
		}

	}
	printf("End of Game.");
	system("PAUSE\n");
}

//__________________________________________________________________Menu and Directories
int startMenu(){
	int user = 100;
	system("cls");
	printf("______________________\n WELCOME TO BLACKJACK\n~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("0. Rules \n");
	printf("1. Start game. \n");
	printf("2. Exit\n");
	printf("3. Test Load game \n");

	user = getNum(0, 3);
	system("cls");
	return user;
}

void mainGame(Cards *deck, Profile* player, int numPlayers){
	deckReset(deck, player, numPlayers);
	deal(deck, player, numPlayers);
	round(deck, player, numPlayers);
}

void loadGame(Cards *deck, Profile *player){
	FILE *fp;
	int numPlayers = 0;

	printf("Which slot would you like to load from? (1-3) \n");
	printf("0. Exit");

	int slot = getNum(0, 3);

	if (slot == 0)
		return;
	else if (slot == 1) // Perhaps this should be changed to allow for file name variation (Constants.)
		fp = fopen("Save1.txt", "r");
	else if (slot == 2)
		fp = fopen("Save2.txt", "r");
	else if (slot == 3)
		fp = fopen("Save3.txt", "r");
	else
		return; // This should not happen.

	if (fp){


		fscanf(fp, "%i ", &numPlayers);

		deckReset(deck, player, numPlayers);

		if (feof(fp)){

			printf("End of File???");
			system("Pause");
			return;
		}

		printf("%i players", numPlayers);
		system("PAUSE");

		for (int i = 0; i < numPlayers; i++){
			fscanf(fp, "%i ", &player[i].numCards);
			printf("Player %i has %i cards. ", i, player[i].numCards);
			system("PAUSE");

			for (int k = 0; k < player[i].numCards; k++){
				fscanf(fp, "%i %i %i ", &player[i].hand[k].value, &player[i].hand[k].suit, &player[i].hand[k].counter); //Value,suit,counter.
				setPlayed(deck, player[i].hand[k].value, player[i].hand[k].suit); // Makes sure that no duplicates can be dealt

			}
			fscanf(fp, "%i ", &player[i].total); //Count
			fscanf(fp, "%i ", &player[i].end); // Checks if player's ended or not.
		}
		fclose(fp);
		round(deck, player, numPlayers);
	}



}

int main(){
	//setup required structs and seeding pre-game
	printf("Enter Number of players (2-4) \n");
	int numPlayers = getNum (2,4);
	Profile player[10]; // The compiler won't stop yelling at me for using an unknown variable :(
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
		case(3) : loadGame(&deck, player);
		}
	}
	system("PAUSE");
	return 0;
}
