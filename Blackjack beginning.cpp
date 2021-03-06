// Blackjack beginning.cpp : Defines the entry point for the console application.

// Other cool stuff: number of Cards, actual betting, encrypted files, difficulty settings.

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
#include <string.h>
#include "time.h"
#define MAX_PLAYERS 2
const int MIN_RISK = 2; // This is sort of misleading: The smaller the number the higher the risk level is... :/
const int MAX_RISK = 8;

//__________________________________________________________________Structures and Constants
const int maxCards = 52; //#define maxCards 52


struct Cards{
	bool Spades[13]; // Array of booleans meant to signal if the card has already been played
	bool Hearts[13];
	bool Diamonds[13];
	bool Clubs[13];
};

struct PlayerCard { // Individual card struct that holds a value (1-13, or Ace to King), and a suit number.
	int suit;
	int value;
};

struct Profile { // Player struct that holds the individual player's
	int numCards;
	PlayerCard hand[11];
	int risk; // This defines the risk of the computer player, or the amount of points from 21 that they will stand on. (Lower number = higher points.)
	bool end; // Determines whether the player has busted.
	char name[80];
};



//__________________________________________________________________Basic Functions
int rb(const int min, const int max) { // Simple function to obtain a random number between min and max
	return rand() % (max - min + 1) + min;
}

int getNum(const int lo, const int hi){ // Thing Wilson likes to have to get a number between a min and max value. Could be useful.
	//good for input validation
	int num = 0;

	std::cin >> num;
	while (num < lo || num > hi){
		std::cin >> num;
	}
	return num;
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

void rules(){ // Prints the rules...
	printf("RULES:\n");
	printf("Blackjack is the most DANK game on PC! I've learned how to collect SWAG DOLLAS \nfrom Bigley by harnessing the Illuminatis card counters and 360 noscoping the \ndealer! My review of Blackjack is 8/8, no b8 m8. Hehv fun! Huehuehuehuehuehue.\n");
	system("PAUSE");
	system("cls");
	printf("RULES:\n");
	printf("The goal of Blackjack is to have the highest hand without exceeding a total\nvalue of 21.\n");
	printf("Every player is dealt two cards.\n");
	printf("Every player can do two things: hit and stand.\n");
	printf("If you 'hit', you get another card.\n");
	printf("If you 'stand' then you are doing taking cards.\n");
	printf("If you hit and it pushes the value of your hand over 21, then you are out for\nthat round.\n");
	printf("The dealer goes first, and hits himself until he has a hand of 18 or over.\n");
	printf("Everybody else can choose to hit or stand as they wish.\n");
	system("PAUSE");

}

int playerInit(Profile* player){//obtains user's name and number of ai they wish to play against
	printf("Please enter your name\n");
	fflush(stdin);
	gets(player[1].name);
	printf("Enter Number of players (2-6) \n");
	return getNum(2, 6);
}

int sum(Profile* player){ // returns a player's total hand worth
	int numAces = 0;
	int total = 0;
	for (int i = 0; i < player->numCards; i++){
		if (player->hand[i].value == 1){
			numAces++;
		}
		else if (player->hand[i].value >= 10){
			total += 10;
		}
		else{
			total += player->hand[i].value;
		}
	}

	for (int i = 0; i < numAces; i++){ // This handles the ace values swapping between 11 and 1.
		if (total <= 10){
			total += 11;
		}
		else{
			total ++;
		}
	}
	return total;
}





void setPlayed(Cards* deck, int tempValue, int tempSuit){ 		//removal from deck (Suits are annoying)
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


void hit(Cards *deck, Profile* player){ // Deals a player a random card.
	if (sum(player) < 21){
		int tempSuit;
		int tempValue;

		do {
			tempSuit = rand() % 3;
			tempValue = rb(1, 13);
		} while (cardCheck(deck, tempSuit, tempValue) == true);

		//removal from deck (Suits are annoying)
		setPlayed(deck, tempValue, tempSuit);


		// Adds stuff to hand
		player->hand[player->numCards].suit = tempSuit;
		player->hand[player->numCards].value = tempValue;
		player->numCards++;

	}
	else{
		printf("Miss.  You should not be here\n");
	}
}

void deckReset(Cards *deck, Profile* player, int numPlayers){// Initializes all structs
    //Apparently you can't initialize them in the struct declaration or the compiler yells at you.
	for (int i = 0; i <= 12; i++){
		deck[0].Spades[i] = 0;
		deck[0].Hearts[i] = 0;
		deck[0].Diamonds[i] = 0;
		deck[0].Clubs[i] = 0;
	}

	for (int i = 0; i <= numPlayers; i++){
		player[i].numCards = 0;
		player[i].risk = rb(MIN_RISK, MAX_RISK);
		player[i].end = false;
	}
}

void printCard(const int suit, const int value){ // Prints a card on the screen.
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

void deal(Cards *deck, Profile* player, int numPlayers){ // Does the initial dealing (Hits dealer once, each player twice)
	hit(deck, &player[0]);
	for (int i = 1; i < numPlayers; i++)
		for (int j = 0; j < 2; j++){
		hit(deck, &player[i]);
		}
}

void dealer(Cards *deck, Profile*dealer){ // Dealer AI
	if (sum(dealer) < 18)
		hit(deck, dealer);
	else
		dealer[0].end = true;

	return;
}

void AI(Cards *deck, Profile*AI){ // Non dealer AI

	//if (AI[0].money < 1)
	//surrender
	if (sum(AI) + AI[0].risk > 21){
		AI[0].end = true;
		return;
	}
	else
		hit(deck, AI);

}


void display(Profile* player, int numPlayers){ // Displays the players hands on the screen.

	system("cls");

	for (int i = 0; i < numPlayers; i++){

		printf("%s\n", player[i].name);

		for (int k = 0; k < player[i].numCards; k++){
			printCard(player[i].hand[k].suit, player[i].hand[k].value);

		}
		printf(": %i.\n\n", sum(&player[i]));
	}
	printf("\n");

}

void saveGame(Profile* player, int numPlayers){ // Writes things to a file to be read later.
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
        printf ("Error in saveGame");
		return;

	if (fp){
		fprintf(fp, "%i\n", numPlayers); // Number of players is at top of file.

		for (int i = 0; i < numPlayers; i++){
			fprintf(fp, "%s\n", player[i].name); // name....
		}
		for (int i = 0; i < numPlayers; i++){
			fprintf(fp, "%i\n", player[i].numCards); // numCards
			for (int k = 0; k < player[i].numCards; k++){
				fprintf(fp, "%i %i ", player[i].hand[k].value, player[i].hand[k].suit);
			} // value/suit/counter
			fprintf(fp, "\n");
			fprintf(fp, "%i", player[i].end);
			fprintf(fp, "\n");
		}

		fclose(fp);
	}

}

bool endGame(Cards *deck, Profile *player, int numPlayers){ // Function that checks if everyone is done playing the game.
	for (int i = 0; i < numPlayers; i++){
		if (player[i].end == false)
			return false;
	}
	return true; // Will only return true if all players are busted.
}

void round(Cards* deck, Profile* player, int numPlayers){ // Does a round of play
	int userIn;

	while (endGame(deck, player, numPlayers) == false){ // Checks for the end of the game
		for (int i = 0; i < numPlayers + 1; i++){

			display(player, numPlayers); // Displays

			if (i == numPlayers)
				dealer(deck, player); // Dealer turn

			else if (i == 1){ // Player Turn

				if (player[i].end == false && sum(&player[i])<21){
					userIn = 0;

					do{ // Player input menu
						printf("Player %i, would you like to\n1 - Stand\n2 - Hit?\n3 - Save\n", i);
						userIn = getNum(1, 3);
						if (userIn == 1 || sum(&player[i]) >= 21)
							player[i].end = true;
						else if (userIn == 2)
							hit(deck, &player[i]);
						else if (userIn == 3){
							saveGame(player, numPlayers);
							display(player, numPlayers);
						}
					} while (userIn == 3); // Lets you go again if you save the game... That was a bug.
				}
			}
			else if (i > 1){ // AI turn
				AI(deck, &player[i]);
			}

			if (sum(&player[i])>= 21) // Checks whether the player is busted...
				player[i].end = true;
		}

	}
	printf("End of Game.\n\n\n");
}

void roundEnd(Profile* player, int numPlayers){
	Profile temp;

	//bubblesort due to very small array
	for (int i = 0; i < numPlayers; i++){
		for (int j = i; j < numPlayers; j++){
			if (sum(&player[i]) < sum(&player[j])){
				temp = player[j];
				player[j] = player[i];
				player[i] = temp;
			}
		}
	}

    if (sum (&player[numPlayers-1]) <= 21){
        printf("%40s Scores\n","");
        for (int i = 0; i < numPlayers; i++){
            if (sum(&player[i]) <= 21)
                printf("%32s: %i\n", player[i].name, sum(&player[i]));
        }
    }
    else{
        printf ("Everyone Busted!\n\n");
    }
}

int nameCheck(int*whichName, int * takenNames, int i){
	if (i == 8)
		return 1;
	if (*whichName == takenNames[i])
		return 0;
	else
		return nameCheck(whichName, takenNames, i + 1);
}

void nameGen(Profile * players, int numPlayers){//We chose not to use random letters
	int whichName;
	int takenNames[8] = { -1, -1, -1, -1, -1, -1, -1, -1 };
	int go = 1;

	for (int i = 2; i < numPlayers; i++){

		do {
			whichName = rb(1, 8);
			go = nameCheck(&whichName, takenNames, 0);
		} while (go == 0);

		switch (whichName){
		case (1) :
			strcpy(players[i].name, "DANK!");
			break;
		case (2) :
			strcpy(players[i].name, "Jon Devlin");
			break;
		case (3) :
			strcpy(players[i].name, "Brooker Brooks");
			break;
		case (4) :
			strcpy(players[i].name, "Ross Reid");
			break;
		case (5) :
			strcpy(players[i].name, "Big Tyrone");
			break;
		case (6) :
			strcpy(players[i].name, "Cameron 'Lebron' Mussar");
			break;
		case (7) :
			strcpy(players[i].name, "The Glorious Leader Rem-Jong-Un");
			break;
		case (8) :
			strcpy(players[i].name, "Neil DeGrasse Tyson");
			break;
		}
		takenNames[i] = whichName;
	}
	strcpy(players[0].name, "Dealer");
}


//__________________________________________________________________Menu and Directories
int startMenu(){//obatins what system action the user would like to perform
	int user = 100;
	system("cls");
	printf("______________________\n WELCOME TO BLACKJACK\n~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("0. Rules \n");
	printf("1. Start game. \n");
	printf("2. Load game \n");
	printf("3. Exit\n");

	user = getNum(0, 3);
	system("cls");
	return user;
}

void mainGame(Cards *deck, Profile* player){//performs a single round of play
	int numPlayers = playerInit(player);
	deckReset(deck, player, numPlayers);
	nameGen(player, numPlayers);
	deal(deck, player, numPlayers);
	round(deck, player, numPlayers);
	roundEnd(player, numPlayers);
	system("PAUSE");
}

void loadGame(Cards *deck, Profile *player){//loads game state from save file
	FILE *fp;
	int numPlayers = 0;
	int temp = 0;

	printf("Which slot would you like to load from? (1-3) \n");
	printf("0. Exit \n");

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

			printf("End of File??? Something bad happened.");
			system("Pause");
			return;
		}

		for (int i = 0; i < numPlayers; i++){
			fgets(player[i].name, 80, fp);
			player[i].name[strlen(player[i].name) - 1] = NULL;
		}
		for (int i = 0; i < numPlayers; i++){
			fscanf(fp, "%i ", &player[i].numCards);


			for (int k = 0; k < player[i].numCards; k++){
				fscanf(fp, "%i %i ", &player[i].hand[k].value, &player[i].hand[k].suit); //Value,suit
				setPlayed(deck, player[i].hand[k].value, player[i].hand[k].suit); // Makes sure that no duplicates can be dealt

			}
			fscanf(fp, "%i ", &temp); // Checks if player's ended or not.
			player[i].end = temp;
		}
		fclose(fp);
		round(deck, player, numPlayers);
		roundEnd(player, numPlayers);
		system("PAUSE");
	}



}

int main(){
	//setup required structs and seeding pre-game

	Profile player[10];
	Cards deck;
	srand((unsigned int)time(NULL)); // Seeding the thing

	while (1){
		switch (startMenu()){
		case (0) :
			rules();
			break;

		case (1) :
			mainGame(&deck, player);
			break;
		case(2) :
			loadGame(&deck, &player[0]);
			break;
		case (3) :
			return 0;
		default:
			printf("UrBadKid (Error in main)");
			break;
		}
	}
	system("PAUSE");
	return 0;
}
