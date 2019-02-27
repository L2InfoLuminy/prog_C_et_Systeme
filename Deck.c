#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "Deck.h"
#include "Card.h"


bool Deck_isEmpty(Deck * deck){
	return deck->length==0;
}

bool Deck_isFull( Deck * deck){
	return deck->length==DECK_CAPACITY;
}

void Deck_appendCard(Deck * deck, Card card){
	if(!Deck_isFull(deck)){
		deck->cards[deck->length]=card;
		deck->length++;
	}
}

Card Deck_popCard (Deck * deck){
	Card save = deck->cards[deck->length-1];
	if(!Deck_isEmpty(deck)){
		deck->cards[deck->length]=Card_make(-1,-1);
		deck->length--;
	}
	return save;
}


void Deck_initEmpty(Deck * deck){
	deck->length=0;
	for(int i=0;i<DECK_CAPACITY; i++){
		deck->cards[i]=Card_make(-1,-1);
	}
}

void Deck_initComplete (Deck * deck){
	Deck_initEmpty(deck);
	for(int i = 0; i<RANK_COUNT; i++){
		for(int j=0; j<SUIT_COUNT;j++){
			deck->cards[deck->length]=Card_make(RANK_PIPS[i],SUIT_PIPS[j]);
			deck->length++;
		}
	}

}

bool Deck_pipsEqual(Deck const * deck, char const pips[]){
	int nbEqual=0;
	int pips_length=strlen(pips);
	for(int i=0; i<deck->length; i++){
		for(int j=0; j<pips_length-1;j+=3){
			if(deck->cards[i].rank==pips[j] && deck->cards[i].suit==pips[j+1])
				nbEqual++;
		}
		if(nbEqual!=i-1)			//ici on ne fait pas de return nbEqual!=i-1 pour avoir un early exit
			return	false;	
	}
	return true;
}


void Deck_printPips (Deck const * deck, FILE * file){

	for(int i=0;i<deck->length;i++){
		fprintf(file, "%c%c ",deck->cards[i].rank, deck->cards[i].suit );
	}
}

void Deck_appendPips (Deck * deck, char const pips[]){
	int pips_length=strlen(pips);
	for(int i=0; i<pips_length-1;i+=3){
		deck->length++;
		deck->cards[deck->length].rank=pips[i];
		deck->cards[deck->length].suit=pips[i+1];
	}
}

void Deck_initFromPips(Deck * deck, char const pips[]){
	Deck_initEmpty(deck);
	Deck_appendPips(deck, pips);
}


bool Deck_indexIsValid(Deck const * deck, int index){
	return(index>=0 && index<=deck->length);
}

bool Deck_rangeIsValide (Deck const * deck, int start, int length){
	return (Deck_indexIsValid(deck, start) && Deck_indexIsValid(deck,start+length));
}


static int Random_IntBetween( int left, int rigth){
	return rand()%(rigth-left)+left;
}

void Deck_swapCardAt (Deck * deck , int index1, int index2){
	Card Sauvcard=deck->cards[index1];
	deck->cards[index1]=deck->cards[index2];
	deck->cards[index2]=Sauvcard;
}

void Deck_shuffle (Deck * deck){
	for(int i=0; i< deck-> length; i++){
		Deck_swapCardAt(deck, i, Random_IntBetween(i,deck->length));
	}
}


void Deck_dealCardsTo (Deck * deck, int cardCount, Deck * target){

	for(int i=0; i< cardCount; i++){
		Deck_appendCard(target, deck->cards[deck->length]);
		Deck_popCard(deck);
	}
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//les fonctions qsort bas de la page 4 et les prédicats associés


static int reverseCompareCardByRankFirst (void const * data1, void const * data2){
	
}

static int reverseCompareCardBySuitFirst (void const * data1, void const * data2){

}

void Deck_sortByRankFirst (Deck * deck){
	
}

void Deck_sortBySuitFirst (Deck * deck){
	
}


bool Deck_isSortedByRankFirst (Deck const * deck){
	return 	;
}

bool Deck_isSortedBySuitFirst (Deck const * deck){
	return	;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/*
int Deck_lengthOfKindAt (Deck const * deck, int start){

}

int Deck_lengthOfFlushAt (Deck const * deck, int start){
	
}

int Deck_lengthOf ReguliarStraightAt(Deck const * deck, int start){
	
}

int Deck_lengthOfRegularStrFlushAt( Deck const * deck , int start){
	
}

int Deck_lengthOfEqualsAt( Deck const * deck , int start){
	
}

int Deck_startOfHighestKind( Deck const * deck, int kindLength){
	
}

int Deck_startOfhighestFlush (Deck const * deck, int flushLength){
	
}

int Deck_startOfHighestRegularStraight (Deck const * deck, int flushLength ){
	
}

int Deck_startOfHighestRegularStraight (Deck const * deck, int straightLength){
	
}

int Deck_startOfHighestRegularStrFlush (Deck const * deck, int strFlushLength){
	
}

void Deck_killRangeAt(Deck * deck, int start, int length){
	
}

void Deck_copyRangeAt (Deck const *deck, int start, int length, Deck *copy){
	
}

void Deck_keepOnlyOneCardPerKind  (Deck * deck){
	
}

void Deck_keepOnlyOneCardPerEqual (Deck * deck){
	
}

bool Deck_isSortedByRankWithNoKind (Deck const * deck){
	
}

bool Deck_isSortedBySuitFirstWithNoEqual (Deck const * deck){
	

}

*/