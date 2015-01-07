/*
I'm not sure we actually need to initalize the deck. We can just generate a card when we need one,
and check it against the otehr cards in play to make sure there are no duplicates. Otherwise,
we should have an in-play / not-in-play boolean-esque variable in the card struct to determine
whether or not it's in play.
// Blackjack beginning.cpp : Defines the entry point for the console application.
*/

//#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum suits { Hearts,Diamonds,Clubs,Spades};
struct card{
	int value; // Goes from 1 to 13
	suits suit;
};

void startCards (card *cards){
	int num = 0;
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
}

void printCard(card *cards,int num){
	printf("%i%c\n", cards[num].value, cards[num].suit + 3);
}

int main()
{
	card cards[52];
	startCards(&cards[0]);
	printCard(&cards[0],0);
	system("PAUSE");
	return 0;
}

