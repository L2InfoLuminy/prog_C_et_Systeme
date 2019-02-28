#include <assert.h>
#include <string.h>

#include "Card.h"

char const RANK_PIPS[RANK_COUNT+1] = "23456789TJQKA";
char const SUIT_PIPS[SUIT_COUNT+1] = "cdhs";

bool Card_rankIsValid (int rank) {
  return rank >= 0 && rank <= 12;
}

bool Card_suitIsValid (int suit) {
  return suit >= 0 && suit <= 3;
}

Card Card_make (int rank, int suit) {
  assert(Card_rankIsValid(rank) && Card_suitIsValid(suit));
  return (Card) {
    .rank = rank,
    .suit = suit,
  };
}

bool Card_isPaired (Card card1, Card card2) {
  return card1.rank == card2.rank;
}

bool Card_isSuited (Card card1, Card card2) {
  return card1.suit == card2.suit;
}

bool Card_equals (Card card1, Card card2) {
  return Card_isPaired(card1, card2) &&
    Card_isSuited(card1, card2);
}

int Card_rankFromPip (char rankPip) {
  char *needle = strchr(RANK_PIPS, rankPip);
  return needle != NULL ? needle - RANK_PIPS : -1;
}

int  Card_suitFromPip (char suitPip) {
  char *needle = strchr(SUIT_PIPS, suitPip);
  return needle != NULL ? needle - SUIT_PIPS : -1;
}

Card Card_makeFromPip (char const pip[]) {
  assert(strlen(pip) == 2);
  return Card_make(Card_rankFromPip(pip[0]), Card_suitFromPip(pip[1]));
}

char Card_rankPip (Card card) {
  return RANK_PIPS[card.rank];
}

char Card_suitPip (Card card) {
  return SUIT_PIPS[card.suit];
}

bool Card_pipEquals (Card card, char const pip[]) {
  return RANK_PIPS[card.rank] == pip[0] &&
    SUIT_PIPS[card.suit] == pip[1];
}

void Card_printPip (Card card, FILE * file) {
  fprintf(file, "%c%c", RANK_PIPS[card.rank], SUIT_PIPS[card.suit]);
}

int Card_compareByRankOnly (Card card1, Card card2) {
  return card1.rank - card2.rank;
}

int Card_compareBySuitOnly (Card card1, Card card2) {
  return card1.suit - card2.suit;
}

int Card_compareByRankFirst (Card card1, Card card2) {
  int compareByRank = Card_compareByRankOnly(card1, card2);
  if (compareByRank != 0) return compareByRank;

  return Card_compareBySuitOnly(card1, card2);
}

int Card_compareBySuitFirst (Card card1, Card card2) {
  int compareBySuit = Card_compareBySuitOnly(card1, card2);
  if (compareBySuit != 0) return compareBySuit;

  return Card_compareByRankOnly(card1, card2);
}

int Card_compareArrayByRankOnly (Card const cards1[], Card const cards2[], int n) {
  int compareByRank;
  for (int index = 0; index < n; ++index) {
    compareByRank = Card_compareByRankOnly(cards1[index], cards2[index]);
    if (compareByRank != 0) return compareByRank;
  }
  return 0;
}

bool Card_isAce (Card card) {
  return card.rank == 12;
}

bool Card_isDeuce (Card card) {
  return card.rank == 0;
}

bool Card_isAceDeuceConnector (Card hiCard, Card loCard) {
  return Card_isAce(hiCard) && Card_isDeuce(loCard);
}

bool Card_isRegularConnector (Card hiCard, Card loCard) {
  return Card_compareByRankOnly(hiCard, loCard) == 1;
}

bool Card_isAceDeuceSuitedConnector (Card hiCard, Card loCard) {
  return Card_isAceDeuceConnector(hiCard, loCard) &&
    Card_compareBySuitOnly(hiCard, loCard) == 0;
}

bool Card_isRegularSuitedConnector (Card hiCard, Card loCard) {
  return Card_compareBySuitOnly(hiCard, loCard) == 0 &&
    Card_compareByRankOnly(hiCard, loCard) == 1;
}
