/*
I'm not sure we actually need to initalize the deck. We can just generate a card when we need one,
and check it against the otehr cards in play to make sure there are no duplicates. Otherwise,
we should have an in-play / not-in-play boolean-esque variable in the card struct to determine
whether or not it's in play.*/

// Blackjack beginning.cpp : Defines the entry point for the console application.


//Requirements: Save output to File, Recursive shuffle, complete actual game with Dealer AI
// Other cool stuff: Variable AI aggressiveness/Number of Players, number of cards, game records or login thing, actual betting. 

// There is currently a lot of test printfs which should maybe be removed?

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include "time.h"

int const maxCards = 52;

enum suits { Hearts, Diamonds, Clubs, Spades };
struct card{
	int value; // Goes from 1 to 13
	int count; // Goes from 1 to 10
	suits suit;
};

struct hand { // Place where the players keep their cards. The count is the thing going up to 21.
	card playerCard[10];
	int count = 0;
	int numCards = 0;
};



int rb(int min, int max) { // Magic random number thingy
	return rand() % (max - min + 1) + min;
}

int getNum(int min, int max){ // Thing Wilson likes to have to get a number between a min and max value. Could be useful.
	int num = 0;

	std::cin >> num;
	while (num < min || num > max){
		std::cin >> num;
	}
	return num;
}

void swap(int a, int b){
	int temp;

	temp = a;
	a = b;
	b = temp;
}

void swapCards(card *card1, card *card2){ // A swap. For cards. this is the hack way that I shuffle the deck.
	card tempCard;
	tempCard.value = card1[0].value;
	tempCard.suit = card1[0].suit;
	card1[0].value = card2[0].value;
	card1[0].suit = card2[0].suit;
	card2[0].value = tempCard.value;
	card2[0].suit = tempCard.suit;


}

void startCards(card *cards){ // Function that initializes all of the cards.

	// It is entirely possible that the cards could be implemented as a linked list. 
	int num = 0;			   // I don't know how to do that. -Wilson
	for (int i = 1; i <= 13; i++){
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

void printCard(card *cards){ // Function that prints cards. It doesn't quite do jack/queen/king yet. Oh well.
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

int startMenu(){ // the menu.
	int user = 100;
	printf("0. Rules \n");
	printf("1. Start game. \n");

	user = getNum(0, 1);
	system("cls");
	return user;
}

void shuffle(card *cards){ // The weird shuffle thing. This will be recursive at some point
	for (int i = 0; i <= 2*maxCards; i++){
		swapCards(&cards[rb(0, maxCards - 1)], &cards[rb(0, maxCards - 1)]);
	}

}

void hit(card *cards, hand *hands, int players, int topDeck){

	
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

int startGame(card *cards){ // Screw non-dealer AI for now, just the dealer and the player...
	hand hands[4];
	int topDeck = 0;		// The master game thing which calls all the other game functions.

	shuffle(&cards[0]);    
	printCard(&cards[0]);

	topDeck = deal(cards, &hands[0], 2, topDeck);
	printf("Player one has ");
	printCard(&hands[0].playerCard[0]);
	printCard(&hands[0].playerCard[1]);

	return 0;
}

void rules(){
	printf("Example Rules\n");
}

int main()
{
	card cards[maxCards];


	srand(time(NULL)); // Seeding the thing
	startCards(&cards[0]);
	printCard(&cards[0]);
	switch (startMenu()){
	case (0) : rules();

	case (1) : startGame(&cards[0]);
	}
	system("PAUSE");
	return 0;
}

