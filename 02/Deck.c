#include "Deck.h"

#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>

//------------------------------------------------------------------------------

bool Deck_isFull (Deck *deck) {
  return deck->length == DECK_CAPACITY;
}

bool Deck_isEmpty (Deck *deck) {
  return deck->length == 0;
}

void Deck_appendCard (Deck *deck, Card card) {
  assert(!Deck_isFull(deck));
  deck->cards[deck->length++] = card;
}

Card Deck_popCard (Deck *deck) {
  assert(!Deck_isEmpty(deck));
  return deck->cards[--deck->length];
}

void Deck_initEmpty (Deck *deck) {
  deck->length = 0;
}

void Deck_initComplete (Deck *deck) {
  int index = DECK_CAPACITY - 1;
  int suit = SUIT_COUNT - 1;
  Deck_initEmpty(deck);

  while (index >= 0) {
    Deck_appendCard(deck, (Card) {.rank = index % RANK_COUNT, .suit = suit});
    if (!(index-- % RANK_COUNT)) suit--;
  }
}


bool Deck_pipsEqual (Deck const *deck, char const pips[]) {
  int pipCount = 0;
  char * const copy = strdup(pips);
  char *pip = NULL;
  char *next;

  pip = strtok_r(copy, " ", &next);

  while (pip) {
    pipCount++;
    if (pipCount > deck->length || !Card_pipEquals(deck->cards[pipCount -1], pip)) {
      free(copy);
      return false;
    }
    pip = strtok_r(NULL, " ", &next);
  }
  free(copy);
  return pipCount == deck->length;
}

void Deck_appendPips (Deck *deck, char const pips []) {
  char * const copy = strdup(pips);
  char *pip = NULL;
  char *next = NULL;

  pip = strtok_r(copy, " ", &next);

  while (pip) {
    Deck_appendCard(deck, Card_makeFromPip(pip));
    pip = strtok_r(NULL, " ", &next);
  }
  free(copy);
}

void Deck_initFromPips (Deck *deck, char const pips []) {
  Deck_initEmpty(deck);
  Deck_appendPips(deck, pips);
}

//------------------------------------------------------------------------------

bool Deck_indexIsValid (Deck const *deck, int index) {
  return index >= 0 && index < deck->length;
}

bool Deck_rangeIsValid (Deck const *deck, int start, int length) {
  return Deck_indexIsValid(deck, start) && start + length <= deck->length;
}

//------------------------------------------------------------------------------

static int Random_IntBetween (int left, int right) {
  return left + rand() % (right - left + 1);
}

void Deck_swapCardsAt (Deck *deck, int index1, int index2) {
  assert(Deck_indexIsValid(deck, index1) && Deck_indexIsValid(deck, index2));
  Card card = deck->cards[index1];
  deck->cards[index1] = deck->cards[index2];
  deck->cards[index2] = card;
}

void Deck_shuffle (Deck *deck) {
  for (int index = 0; index < deck->length; ++index)
    Deck_swapCardsAt(deck, index, Random_IntBetween(index, deck->length -1));
}

static int reverseCompareCardBySuitFirst (void const *data1, void const *data2) {
  return -Card_compareBySuitFirst(*((Card *) data1), *((Card *) data2));
}

static int reverseCompareCardByRankFirst (void const *data1, void const *data2) {
  return -Card_compareByRankFirst(*((Card *) data1), *((Card *) data2));
}

void Deck_sortBySuitFirst (Deck *deck) {
  qsort(deck->cards, deck->length, sizeof(Card), reverseCompareCardBySuitFirst);
}

void Deck_sortByRankFirst (Deck *deck) {
  qsort(deck->cards, deck->length, sizeof(Card), reverseCompareCardByRankFirst);
}

//------------------------------------------------------------------------------

static bool isSortedBy (Deck const *deck, Card_comparator cardCompare, Card_predicate cardFilter) {
  for (int index = 1; index < deck->length; ++index)
    if (cardCompare(deck->cards[index -1], deck->cards[index]) < 0
        || (cardFilter && cardFilter(deck->cards[index -1], deck->cards[index])))
      return false;

  return true;
}

bool Deck_isSortedByRankFirst (Deck const *deck) {
  return isSortedBy(deck, Card_compareByRankFirst, NULL);
}

bool Deck_isSortedBySuitFirst (Deck const *deck) {
  return isSortedBy(deck, Card_compareBySuitFirst, NULL);
}

bool Deck_isSortedBySuitFirstWithNoEqual (Deck const * deck) {
  return isSortedBy(deck, Card_compareBySuitFirst, Card_equals);
}

bool Deck_isSortedByRankWithNoKind (Deck const * deck) {
  return isSortedBy(deck, Card_compareByRankOnly, Card_isPaired);
}

//------------------------------------------------------------------------------

void Deck_printPips (Deck const *deck, FILE * file) {
  if (Deck_isEmpty((Deck *) deck)) return;

  int index = 0;

  Card_printPip(deck->cards[index++], file);
  while (index < deck->length) {
    fprintf(file, " ");
    Card_printPip(deck->cards[index++], file);
  }
}

//------------------------------------------------------------------------------

static int min (int a, int b) {
  return a < b ? a : b;
}

void Deck_dealCardsTo (Deck *deck, int cardCount, Deck *dealed) {
  if (Deck_isEmpty(deck) || Deck_isFull(dealed)) return;

  cardCount = min(min(cardCount, deck->length), DECK_CAPACITY - dealed->length);

  while (cardCount--)
    Deck_appendCard(dealed, Deck_popCard(deck));
}

//------------------------------------------------------------------------------

static int lengthOf_At (Deck const *deck, int start, Card_predicate cardFilter) {
  assert(Deck_indexIsValid(deck, start));
  int count = 1;
  Card card = deck->cards[start++];

  while (start < deck->length && cardFilter(card, deck->cards[start])) {
    card = deck->cards[start++];
    count++;
  }

  return count;
}

int Deck_lengthOfKindAt (Deck const *deck, int start) {
  return lengthOf_At(deck, start, Card_isPaired);
}

int Deck_lengthOfFlushAt (Deck const *deck, int start) {
  return lengthOf_At(deck, start, Card_isSuited);
}

int Deck_lengthOfRegularStraightAt (Deck const *deck, int start) {
  return lengthOf_At(deck, start, Card_isRegularConnector);
}

int Deck_lengthOfRegularStrFlushAt (Deck const *deck, int start) {
  return lengthOf_At(deck, start, Card_isRegularSuitedConnector);
}

int Deck_lengthOfEqualsAt (Deck const *deck, int start) {
  return lengthOf_At(deck, start, Card_equals);
}

//------------------------------------------------------------------------------

// @TODO : ugly --> rework
static int startOfHighest (Deck const *deck, int minLength, int (*lengthOfAt)(Deck const *deck, int start)) {
  int count = 1, maxCount = 1, indexOfHighest = 0;
  bool compare; // @TODO rename
  Card cards1[DECK_CAPACITY];
  Card cards2[DECK_CAPACITY];

  while (count < minLength && indexOfHighest < deck->length) {
    count = lengthOfAt(deck, indexOfHighest);
    if (count >= minLength) {
      maxCount = count;
      break;
    }
    indexOfHighest++;
  }

  if (indexOfHighest == deck->length) return -1;

  memcpy(cards1, &deck->cards[indexOfHighest], sizeof(Card));

  for (int index = indexOfHighest; index < deck->length; ++index) {
    count = lengthOfAt(deck, index);
    if (count < minLength) continue;

    memcpy(cards2, &deck->cards[index], count * sizeof(Card));

    if (count < maxCount)
      compare = Card_compareByRankOnly(cards1[0], cards2[0]) < 0;
    else
      compare = Card_compareArrayByRankOnly(cards1, cards2, count) < 0;

    if (compare) {
      maxCount = count;
      indexOfHighest = index;
      memcpy(cards1, cards2, count * sizeof(Card));
    }
  }

  return indexOfHighest;
}

int Deck_startOfHighestKind  (Deck const *deck, int kindLength) {
  return startOfHighest(deck, kindLength, Deck_lengthOfKindAt);
}

int Deck_startOfHighestFlush (Deck const *deck, int flushLength) {
  return startOfHighest(deck, flushLength, Deck_lengthOfFlushAt);
}

int Deck_startOfHighestRegularStraight (Deck const *deck, int straightLength) {
  return startOfHighest(deck, straightLength, Deck_lengthOfRegularStraightAt);
}

int Deck_startOfHighestRegularStrFlush (Deck const *deck, int strFlushLength) {
  return startOfHighest(deck, strFlushLength, Deck_lengthOfRegularStrFlushAt);
}

//------------------------------------------------------------------------------

void Deck_killRangeAt (Deck *deck, int start, int length) {
  assert(Deck_rangeIsValid(deck, start, length));

  int index = start + length;
  int blocks = &deck->cards[deck->length -1] - &deck->cards[index] + 1;

  if (blocks > 0)
    memcpy(&deck->cards[start], &deck->cards[index], blocks * sizeof(Card));

  deck->length -= length;
}

void Deck_copyRangeAt (Deck const *deck, int start, int length, Deck *copy) {
  assert( Deck_rangeIsValid(deck, start, length));
  assert(!Deck_isFull(copy)  && copy->length + length <= DECK_CAPACITY);

  length = start + length;
  while (start < length)
    Deck_appendCard(copy, deck->cards[start++]);
}

//------------------------------------------------------------------------------

// @FIXME : unused for now
static void keepOnlyOneCardPer (Deck *deck, bool (*Card_predicate) (Card hiCard, Card loCard)) {
  int count;
  for (int index = 0; index < deck->length; ++index) {
    count = lengthOf_At(deck, index, Card_predicate);
    if (count == 1) continue;

    Deck_killRangeAt(deck, index + 1, count - 1);
  }
}

void Deck_keepOnlyOneCardPerKind (Deck *deck) {
  keepOnlyOneCardPer(deck, Card_isPaired);
}

void Deck_keepOnlyOneCardPerEqual (Deck *deck) {
  keepOnlyOneCardPer(deck, Card_equals);
}
