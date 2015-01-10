/*
I'm not sure we actually need to initalize the deck. We can just generate a card when we need one,
and check it against the other cards in play to make sure there are no duplicates. Otherwise,
we should have an in-play / not-in-play boolean-esque variable in the card struct to determine
whether or not it's in play.*/

// Blackjack beginning.cpp : Defines the entry point for the console application.

//Requirements: Save output to File, Recursive shuffle, complete actual game with Dealer AI
// Other cool stuff: Variable AI aggressiveness/Number of Players, number of cards, game records or login thing, actual betting, encrypted files, difficulty settings.

// There is currently a lot of test printfs which should maybe be removed?

//#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include "time.h"

//__________________________________________________________________Structures and Constants
int const maxCards = 52; //#define maxCards 52

enum suits {Spades, Hearts, Diamonds, Clubs};

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
};

playerCard hand[80]; //hand[1].suit would return the suit of the first card in hand

//__________________________________________________________________Basic Functions
int rb(int min, int max) { // Magic random number thingy
	return rand() % (max - min + 1) + min;
}

int getNum(int min, int max){ // Thing Wilson likes to have to get a number between a min and max value. Could be useful.
    //good for invalid answer prevention
	int num = 0;

	std::cin >> num;
	while (num < min || num > max){
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

int cardCheck (int suit, int value){ //returns whether a certain card is in play (1 is in play, 0 is in deck)
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

void hit(int player, int* hand){
int tempSuit;
int tempValue;
    do {
        tempSuit = rand () % 3;
        tempValue = rand () % 12;
    }while (!cardCheck(tempSuit, tempValue));
    //need to remove card from deck, place in player's hand
}

//__________________________________________________________________Complex Functions
void deckReset (){
	for (int i = 0; i <= 13; i++){
	    deck.Spades[i].played = 0;
	    deck.Hearts[i].played = 0;
        deck.Diamonds[i].played = 0;
	    deck.Clubs[i].played = 0;
	}
}

void printCard(int suit, int value){
    switch (value){
    case 1:
        printf("A%c\n", suit + 3);
        break;
    case 11:
        printf("J%c\n", suit + 3);
        break;
    case 12:
        printf("Q%c\n", suit + 3);
        break;
    case 13:
        printf("K%c\n", suit + 3);
        break;
    default:
        printf("%i%c\n", value, suit);
        break;
    }
}

void rules(){
	printf("Example Rules\n");
    system ("PAUSE");
}

int deal(card *cards, hand *hands, int players, int topDeck){ //Gives cards out to all the players in the game.Topdeck is supposed to be a way of referencing the top of the "stack", or deck.
	for (int i = 0; i <= players - 1; i++){				   // The way topDeck is handled is currently pretty bad and should be improved.
		hands[i].playerCard[0].value = cards[topDeck].value;
		hands[i].playerCard[0].suit = cards[topDeck].suit;
		topDeck++;
		hands[i].playerCard[1].value = cards[topDeck].value;
		hands[i].playerCard[1].suit = cards[topDeck].suit;
		topDeck++;
	}

	return topDeck;
}

//__________________________________________________________________Menu and Directories
int startMenu(){ // the menu.
    //Made this clear both before AND after, and have a pretty (subjective) title
	int user = 100;
    system("cls");
    printf ("______________________\n WELCOME TO BLACKJACK\n~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("0. Rules \n");
	printf("1. Start game. \n");
	printf ("2. Exit\n");

	user = getNum(0, 2);
	system("cls");
	return user;
}

int startGame(card *cards){ // Screw non-dealer AI for now, just the dealer and the player...
	hand hands[4];
	int topDeck = 0;		// The master game thing which calls all the other game functions.

//	shuffle(&cards[0]);
	printCard(&cards[0]);

	topDeck = deal(cards, &hands[0], 2, topDeck);
	printf("Player one has ");
	printCard(&hands[0].playerCard[0]);
	printCard(&hands[0].playerCard[1]);

    printf ("reached end of startgame\n");
    system ("PAUSE");
	return 0;
}

int main()
{
	card cards[maxCards];

    ////////////////////////////////////////
	srand(time(NULL)); // Seeding the thing
	startCards(&cards[0]);
	printCard(&cards[0]);
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
	card1[0].value = card2[0].value;
	card1[0].suit = card2[0].suit;
	card2[0].value = tempCard.value;
	card2[0].suit = tempCard.suit;
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
		if (cards[i].value <= 10)
			cards[i].count = cards[i].value;
		else
			cards[i].count = 10;
}
*/

/*
void printCard(card *cards){ // Function that prints cards.
	switch (cards[0].value){
	case (1):
		printf("A%c\n", cards[0].suit + 3);
		break;
	case (11) :
		printf("J%c\n", cards[0].suit + 3);
		break;
	case (12) :
		printf("Q%c\n", cards[0].suit + 3);
		break;
	case (13) :
		printf("K%c\n", cards[0].suit + 3);
		break;
	default:
		printf("%i%c\n", cards[0].value, cards[0].suit + 3);
		break;
	}
}
*/
