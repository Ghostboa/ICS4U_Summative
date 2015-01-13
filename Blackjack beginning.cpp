// Blackjack beginning.cpp : Defines the entry point for the console application.

//Requirements: Save output to File, Recursive shuffle, complete actual game with Dealer AI
// Other cool stuff: Variable AI aggressiveness/Number of Players, number of cards, game records or login thing, actual betting, encrypted files, difficulty settings.

/*
The players' objective is to win money by creating card totals that turn out to be higher than the dealer's hand
but do not exceed 21 ("busting"/"breaking"), or alternatively by allowing the dealer to take additional cards until they bust.
On their turn, players must choose whether to
"hit" (take a card)
"stand" (end their turn)
"double" (double wager, take a single card and finish)
"split" (if the two cards have the same value, separate them to make two hands)
"surrender" (give up a half-bet and retire from the game)
*/


//#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include "time.h"

//__________________________________________________________________Structures and Constants
int const maxCards = 52; //#define maxCards 52

enum suits { Spades, Hearts, Diamonds, Clubs };

//Deck Proposition
struct inPlay{
	bool played;
};

struct cards{
	inPlay Spades[12];
	inPlay Hearts[12];
	inPlay Diamonds[12];
	inPlay Clubs[12];
};

cards deck; //two dimensional array, accessed by deck.Spades[1].played  (would return 1 or 0, depending on whether the ace of spades is in play)

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

Profile player[4];//initialization of dealer and hooman, will need to manually initialize later

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

bool cardCheck(int suit, int value){ //returns whether a certain card is in play (1 is in play, 0 is in deck)
	switch (suit){
	case 0:
		return deck.Spades[value].played;
	case 1:
		return deck.Hearts[value].played;
	case 2:
		return deck.Diamonds[value].played;
	case 3:
		return deck.Clubs[value].played;
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

void hit(cards deck, Profile player[], int pNum){
	int tempSuit;
	int tempValue;


	do {
		tempSuit = rand() % 3;
		tempValue = rb(1,13);
	} while (cardCheck(tempSuit, tempValue) == true);

	//removal from deck (suits are annoying)
	switch (tempSuit){
	case 0:
		deck.Spades[tempValue].played = 1;
		break;
	case 1:
		deck.Hearts[tempValue].played = 1;
		break;
	case 2:
		deck.Diamonds[tempValue].played = 1;
		break;
	case 3:
		deck.Clubs[tempValue].played = 1;
		break;
	}

	player[pNum].hand[(player[pNum].numCards)].suit = tempSuit;
	player[pNum].hand[(player[pNum].numCards)].value = tempValue;

	if (tempValue >= 10) // Assigning the count to the players hand.
		player[pNum].hand[(player[pNum].numCards)].counter = 10;
	else if (tempValue == 1){
		if (player[pNum].total >=11) // For Aces!
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

void deckReset(int numPlayers){
	for (int i = 0; i <= 13; i++){ // There's no Spades[13].... How does this not break?
		deck.Spades[i].played = 0;
		deck.Hearts[i].played = 0;
		deck.Diamonds[i].played = 0;
		deck.Clubs[i].played = 0;
	}

	for (int i = 0; i < numPlayers; i++){
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
		printf("%i%c", value, suit+3);
		break;
	}
}

void deal(int numPlayers){
	for (int i = numPlayers-1; i >= 0; i--)
		for (int j = 0; j <= 1; j++)
			hit(deck, player, i);
}

void display(int numPlayers){
	//printf ("%i, %i", player[0].hand[0].suit, player[0].hand[0].value); debug stuff
	printf("Dealer\t");
	for (int i = 1; i < numPlayers; i++){
		printf("player%i\t", i);
	}
	printf("\n");
	for (int i = 0; i < numPlayers; i++){
		for (int j = 0; j < player[i].numCards; j++)
			printCard(player[i].hand[j].suit, player[i].hand[j].value);
		printf(" Count: %i", player[i].total);
		printf("\t");
	}
	printf("\n");
}

void saveGame(int numPlayers){
	FILE *fp;

	printf("Which slot would you like to save in? (1-3) \n");
	int slot = getNum(1, 3);

	if (slot == 1) // Perhaps this should be changed to allow for file name variation (Constants.)
		fp = fopen("Save1.txt","w");
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
			fprintf(fp,"\n");
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

int mainGame(){

	deckReset(2);

	//need function to get number of players (currently set to 2)
	deal(2);

	display(2);

	saveGame(2);

	system("PAUSE");
	return 0;
}

int main(){
	srand(time(NULL)); // Seeding the thing

	while (1){
		switch (startMenu()){
		case (0) :
			rules();
			break;

		case (1) :
			mainGame();
			break;

		case (2) :
			return 0;
		}
	}
	system("PAUSE");
	return 0;
}

//__________________________________________________________________Void Code
/*
struct card{
int value; // Goes from 1 to 13
int count; // Goes from 1 to 10
suits suit;
};
*/

/*
void shuffle(card *cards, int deckRemaining){ // The weird shuffle thing. This will be recursive at some point
//entire shuffling should be unnecessary.  Instead, generate a card and check whether in play.
for (int i = 0; i <= 2*maxCards; i++){
swapCards(&cards[rb(0, maxCards - 1)], &cards[rb(0, maxCards - 1)]);
}
*/
//shuffling deck is n time complexity and uses the single array + temp slot for swapping
/*
int temp = 0;
if (n == 0)
return 1;
else
temp = rand() % n;
swap ()
}
*/

/*
void swapCards(card *card1, card *card2){ // A swap. For cards. this is the hack way that I shuffle the deck.
card tempCard;
tempCard.value = card1[0].value;
tempCard.suit = card1[0].suit;
tempCard.counter = card1[0].counter;
card1[0].value = card2[0].value;
card1[0].suit = card2[0].suit;
card1[0].counter = card2[0].counter;
card2[0].value = tempCard.value;
card2[0].suit = tempCard.suit;
<<<<<<< HEAD
card2[0].counter = tempCard.counter;


=======
>>>>>>> origin/The-Follicle
}
*/

/*
void startCards(card *cards){ // Function that initializes all of the cards.

int num = 0;
for (int i = 0; i <= 13; i++){
cards[num].value = i;
cards[num].suit = Hearts;
num++;
cards[num].value = i;
cards[num].suit = Diamonds;
num++;
cards[num].value = i;
cards[num].suit = Clubs;
num++;
cards[num].value = i;
cards[num].suit = Spades;
num++;
}
for (int i = 0; i < 52; i++)
if (cards[i].value <= 10 )
cards[i].counter = cards[i].value;
else
cards[i].counter = 10;
}
*/

/*
void printCard(card *cards){ // Function that prints cards.
switch (cards[0].value){
case (1) :
printf("A%c ", cards[0].suit + 3);
break;
case (11) :
printf("J%c ", cards[0].suit + 3);
break;
case (12) :
printf("Q%c ", cards[0].suit + 3);
break;
case (13) :
printf("K%c ", cards[0].suit + 3);
break;
default:
printf("%i%c ", cards[0].value, cards[0].suit + 3);
break;
}
<<<<<<< HEAD



}

int startMenu(){ // the menu.
//I made this clear BOTH before AND after, and have a pretty-ish title
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

void shuffle(card *cards){ // The weird shuffle thing. This will be recursive at some point
for (int i = 0; i <= 2 * maxCards; i++){
swapCards(&cards[rb(0, maxCards - 1)], &cards[rb(0, maxCards - 1)]);
}

}

int hit(card *cards, hand *hands, int topDeck,int playerNum){ // Deals the player a card.
int cardNum = hands[playerNum].numCards;

hands[playerNum].playerCard[cardNum].value = cards[topDeck].value;
hands[playerNum].playerCard[cardNum].suit = cards[topDeck].suit;
hands[playerNum].playerCard[cardNum].counter = cards[topDeck].counter;
hands[playerNum].handCounter += hands[playerNum].playerCard[cardNum].counter;

hands[playerNum].numCards++;
topDeck++;

if (hands[playerNum].handCounter > 21) // Checks for the count being over 21.
hands[playerNum].bust = true;

return topDeck;
=======
>>>>>>> origin/The-Follicle
}
*/

//<<<<<<< HEAD


//=======
/*
>>>>>>> origin/The-Follicle
int deal(card *cards, hand *hands, int players, int topDeck){ //Gives cards out to all the players in the game.Topdeck is supposed to be a way of referencing the top of the "stack", or deck.
for (int i = 0; i <= players - 1; i++){				   // The way topDeck is handled is currently pretty bad and should be improved.
topDeck = hit(cards, hands, topDeck, i);
topDeck = hit(cards, hands, topDeck, i);
}

return topDeck;
}
<<<<<<< HEAD

int playerTurn(card *cards, hand *hands, int players, int topDeck){ // TBD

return topDeck;
}

int AITurn(card *cards, hand *hands, int players, int topDeck){ // TBD

return topDeck;
}

void display(card *cards, hand *hands, int players){ // THIS IS IMPORTANT. Wilson sucks at anything requiring any sense of aesthetics. This displays the stuff. -Dorien 2015.
for (int i = 0; i <= players - 1; i++){
printf("Player %i:", i+1);

for (int k = 0; k < hands[i].numCards;k++){
printCard(&hands[i].playerCard[k]);
}
printf("\n");

printf("Player %i count: %i. \n\n", i+1, hands[i].handCounter);
}
}

bool ended(hand *hands, int players){ // Function that checks to see if all hands are busted.
for (int i = 0; i < players; i++){
if (hands[i].bust == false)
return false;
}

return true; // Will only return true if all hands are busted...
}

int turns(card *cards, hand *hands, int players, int topDeck){ // Visual studio is bugging me about not all paths returning...
// This will run turns until the game is done.

for (int i = 0; i <= players - 1; i++){
display(cards,hands,players);

system("PAUSE");

if (i == 0 && hands[i].bust == false)
topDeck = playerTurn(cards,hands,players,topDeck);
else if (i != 0 && hands[i].bust == false)
topDeck = AITurn(cards, hands, players, topDeck);
}

if (ended(hands,players) == true)
return topDeck;
}

int startGame(card *cards){ // Screw non-dealer AI for now, just the dealer and the player...
hand hands[4];
int topDeck = 0;		// The master game thing which calls all the other game functions.
bool end = false;
int players = 2;

shuffle(&cards[0]);
printCard(&cards[0]);

topDeck = deal(cards, &hands[0], players, topDeck);
printf("Player one has ");
printCard(&hands[0].playerCard[0]);
printCard(&hands[0].playerCard[1]);
printf("\n");
printf("\n");

topDeck = turns(cards, &hands[0], players, topDeck);

printf("reached end of startgame\n");
system("PAUSE");
return 0;
}

void rules(){
printf("Example Rules\n");
system("PAUSE");
}

int main()
{
card cards[maxCards];

////////////////////////////////////////
srand(time(NULL)); // Seeding the thing
startCards(&cards[0]);
//we only need this once they start the game? otherwise it's just a waste?
////////////////////////////////////////

while (1){
switch (startMenu()){
case (0) :
rules();
break;

case (1) :
startGame(&cards[0]);
break;

case (2) :
return 0;
}
}
system("PAUSE");
return 0;
}
=======
*/
//>>>>>>> origin/The-Follicle
