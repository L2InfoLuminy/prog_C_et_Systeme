#include <assert.h>
#include <string.h>
#include "Card.h"




bool Card_rankIsValid (int rank){
	return ((0<= rank) && (rank < RANK_COUNT) );
}

bool Card_suitIsValid (int suit){
	return ((0<= suit) && (suit < SUIT_COUNT));
}

Card Card_make(int rank, int suit){
	assert(Card_rankIsValid(rank));
	assert(Card_suitIsValid(suit));
	return (Card) {.rank=rank, .suit=suit};
}

bool Card_isPaired (Card card1, Card card2){
	return(card1.rank==card2.rank);
}

bool Card_isSuited (Card card1, Card card2){
	return(card1.suit==card2.suit);
}

bool Card_equals(Card card1, Card card2){
	return(Card_isPaired(card1,card2) && Card_isSuited(card1, card2));
}

int Card_rankFromPip (char rankPip){
	/*for(int i=0;i<RANK_PIPS; i++){
		if(RANK_PIPS[i]==rankPip)
			return i;
	}
	return -1;
	*/
	char * found =strchr(RANK_PIPS, rankPip);
	if(found==NULL)
		return -1;
	return found-RANK_PIPS;
}

int Card_suitFromPip(char suitPip){
	/*for(int i=0;i < SUIT_PIPS; i++){
		if(SUIT_PIPS[i]== suitPip)
			return i;
	}
	return -1;
	*/
	char * found =strchr(SUIT_PIPS, suitPip);
	if(found==NULL)
		return -1;
	return found-SUIT_PIPS;
}

Card Card_makeFromPip(char const pip[]){
	assert(strlen(pip)==2);
	int rank = Card_rankFromPip(pip[0]);
	assert(rank!=-1);
	int suit  = Card_suitFromPip(pip[1]);
	assert (suit!=-1);
	return Card_make(rank,suit);
}

char Card_rankPip (Card card){
	return RANK_PIPS[card.rank];
}

char Card_suitPip (Card card){
	return SUIT_PIPS[card.suit];
}

bool Card_pipEquals(Card card, char const pip[]){
	return((card.rank==pip[0]) && (card.suit==pip[1]));
}

void Card_printPip (Card card, FILE * file){
	fprintf(file,"%c%c", Card_rankPip(card), Card_suitPip(card));
}

int Card_compareByRankOnly( Card card1, Card card2){
	return card1.rank-card2.rank;
}

int Card_compareBySuitonly (Card card1, Card card2){
	return card1.suit-card2.suit;
}

int Card_compareByRankFirst (Card card1, Card card2){
	if(Card_compareByRankOnly(card1, card2)==0)
		return Card_compareBySuitonly(card1,card2);
	return Card_compareByRankOnly(card1, card2);
}

int Card_compareBySuitFirst (Card card1, Card card2){
	if(Card_compareBySuitOnly(card1, card2)==0)
		return Card_compareByRankOnly(card1,card2);
	return Card_compareBySuitOnly(card1, card2);
}

int Card_compareArrayByRankOnly(Card const card1[], Card const card2[], int n){

	for(int i=0; i<n; i++){
		if(Card_compareByRankOnly(card1[i], card2[i]) !=0){
			return Card_compareByRankOnly(card1[i],card2[i]);
		}
	}
	return 0;
}

bool Card_isRegularConnector (Card hiCard, Card loCard){
	return (loCard.rank+1<hiCard.rank);
}

bool Card_isRegularSuitedConnector (Card hiCard, Card loCard){
	return (loCard.suit==hiCard.suit);
}

bool Card_isAce( Card card){
	return card.rank==12;
}

bool Card_isDeuce (Card card){
	return card.rank==0;
}

bool Card_isAceDeuceConnector(Card hiCard, Card loCard){
	return(Card_isDeuce(loCard)&&Card_isAce(hiCard));
}

bool Card_isAceDeuceSuitedConnector( Card hiCard, Card loCard){
	return (Card_isAceDeuceConnector(hiCard,loCard)&&(Card_isRegularSuitedConnector(hiCard,loCard)));
}
