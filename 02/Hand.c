
#include "Hand.h"

#include <assert.h>

char const *HAND_NAMES[HAND_COUNT] = {
  "Hi-Card", "Pair",      "Two Pairs",
  "Trips",   "Straight",  "Flush",
  "Boat",    "Quads",     "Str-Flush"
};

//------------------------------------------------------------------------------

bool Hand_extractKind (Deck *source, int kindLength, Deck *target) {
  assert(kindLength >=1 && kindLength <= 4);
  assert(Deck_isSortedByRankFirst(source));

  Deck deck;
  int length, index = Deck_startOfHighestKind(source, kindLength);

  if (index == -1) return false;

  length = Deck_lengthOfKindAt(source, index);
  Deck_initEmpty(&deck);
  Deck_copyRangeAt(source, index, length, &deck);
  Deck_killRangeAt(source, index, length);
  Deck_copyRangeAt(&deck, 0, kindLength, target);

  return true;
}

static bool extract (Deck *source, Deck *target, int (*Deck_startOfHighest)(Deck const *source, int length)) {
  Deck deck;
  int index = Deck_startOfHighest(source, 5);

  if (index == -1) return false;

  Deck_initEmpty(&deck);
  Deck_copyRangeAt(source, index, 5, &deck);
  Deck_killRangeAt(source, index, 5);
  Deck_copyRangeAt(&deck, 0, 5, target);

  return true;
}

//static bool extractWhell (Deck *source, Deck *target, int (*lengthOfRegularAt)(Deck const *source, int start), bool (*isAceDeuceConnector)(Card hicard, Card loCard)) {
static bool extractWhell (Deck *source, Deck *target, Deck_lengthOfSlice lengthOfSlice, Card_predicate cardFilter) {
  Deck deck;
  int index = 0, aceIndex = 0, count = 1;

  while (index < source->length && aceIndex < source->length) {
    if (Card_rankPip(source->cards[index]) == '5' && (count = lengthOfSlice(source, index) == 4)) {
      aceIndex = Deck_startOfHighestKind(source, aceIndex);
      if (cardFilter(source->cards[aceIndex], source->cards[index + 3]))
        break;
      else
        aceIndex = index + count;
    }
    index++;
  }

  if (index >= source->length) return false;

  Deck_initEmpty(&deck);
  Deck_copyRangeAt(source, index, 4, &deck);
  Deck_copyRangeAt(source, aceIndex, 1, &deck);
  Deck_killRangeAt(source, index, 4);
  Deck_killRangeAt(source, aceIndex, 1);
  Deck_copyRangeAt(&deck, 0, 5, target);

  return true;
}

bool Hand_extractRegularStraight (Deck *source, Deck *target) {
  assert(Deck_isSortedByRankFirst(source));
  return extract(source, target, Deck_startOfHighestRegularStraight);
}

bool Hand_extractFlush (Deck *source, Deck *target) {
  assert(Deck_isSortedBySuitFirstWithNoEqual(source));
  return extract(source, target, Deck_startOfHighestFlush);
}

bool Hand_extractRegularStrFlush (Deck *source, Deck *target) {
  assert(Deck_isSortedBySuitFirstWithNoEqual(source));
  return extract(source, target, Deck_startOfHighestRegularStrFlush);
}

bool Hand_extractWheelStraight (Deck *source, Deck *target) {
  assert(Deck_isSortedByRankFirst(source));
  return extractWhell(source, target, Deck_lengthOfRegularStraightAt, Card_isAceDeuceConnector);
}

bool Hand_extractWheelStrFlush (Deck *source, Deck *target) {
  assert(Deck_isSortedBySuitFirstWithNoEqual(source));
  return extractWhell(source, target, Deck_lengthOfRegularStrFlushAt, Card_isAceDeuceSuitedConnector);
}

//------------------------------------------------------------------------------

static bool findCards (Deck const *source, Deck *target, int kindLength, int kindCount, int kickers) {
  assert(source->length >= 5);

  bool found = false;
  Deck copy;
  Deck_initEmpty(&copy);
  Deck_initEmpty(target);
  Deck_copyRangeAt(source, 0, source->length, &copy);

  Deck_sortByRankFirst(&copy);

  while (target->length < kindLength * kindCount && (found = Hand_extractKind(&copy, kindLength, target)));
  kindLength = 5 - kindLength * kindCount;
  kindLength = kindLength - kickers ? kindLength : 1;
  if (found)
    while (target->length < 5 && Hand_extractKind(&copy, kindLength, target));

  return target->length == 5;
}

bool Hand_findHiCard (Deck const *source, Deck *target) {
  return findCards(source, target, 1, 5, 0);
}

bool Hand_findPair (Deck const *source, Deck *target) {
  return findCards(source, target, 2, 1, 3);
}

bool Hand_find2Pairs (Deck const *source, Deck *target) {
  return findCards(source, target, 2, 2, 1);
}

bool Hand_findTrips (Deck const *source, Deck *target) {
  return findCards(source, target, 3, 1, 2);
}

bool Hand_findBoat (Deck const *source, Deck *target) {
  return findCards(source, target, 3, 1, 0);
}

bool Hand_findQuads (Deck const *source, Deck *target) {
  return findCards(source, target, 4, 1, 0);
}

//------------------------------------------------------------------------------

// @TODO : factorise
bool Hand_findStraight (Deck const *source, Deck *target) {
  Deck copy;
  Deck_initEmpty(&copy);
  Deck_initEmpty(target);
  Deck_copyRangeAt(source, 0, source->length, &copy);

  Deck_sortByRankFirst(&copy);

  return Hand_extractRegularStraight(&copy, target)
    ? true
    : Hand_extractWheelStraight(&copy, target);
}

bool Hand_findFlush (Deck const *source, Deck *target) {
  Deck copy;
  Deck_initEmpty(&copy);
  Deck_initEmpty(target);
  Deck_copyRangeAt(source, 0, source->length, &copy);

  Deck_sortBySuitFirst(&copy);

  return Hand_extractFlush(&copy, target);
}

bool Hand_findStrFlush (Deck const *source, Deck * target) {
  Deck copy;
  Deck_initEmpty(&copy);
  Deck_initEmpty(target);
  Deck_copyRangeAt(source, 0, source->length, &copy);

  Deck_sortBySuitFirst(&copy);

  return Hand_extractRegularStrFlush(&copy, target)
    ? true
    : Hand_extractWheelStrFlush(&copy, target);
}

//------------------------------------------------------------------------------

// @PYRAMID!
Hand Hand_findBest (Deck const *source, Deck *target) {
  return Hand_findStrFlush(source, target)
    ? HAND_STRFLUSH
    : Hand_findQuads(source, target)
      ? HAND_QUADS
      : Hand_findBoat(source, target)
        ? HAND_BOAT
        : Hand_findFlush(source, target)
          ? HAND_FLUSH
          : Hand_findStraight(source, target)
            ? HAND_STRAIGHT
            : Hand_findTrips(source, target)
              ? HAND_TRIPS
              : Hand_find2Pairs(source, target)
                ? HAND_2PAIRS
                : Hand_findPair(source, target)
                  ? HAND_PAIR
                  : Hand_findHiCard(source, target)
                    ? HAND_HICARD
                    : HAND_UNKNOWN;
}
/*
Hand Hand_findBest (Deck const *source, Deck *target) {
  Deck_initEmpty(target);
  if (Hand_findStrFlush(source, target))
    return HAND_STRFLUSH;
  if (Hand_findQuads(source, target))
    return HAND_QUADS;
  if (Hand_findBoat(source, target))
    return HAND_BOAT;
  if (Hand_findFlush(source, target))
    return  HAND_FLUSH;
  if (Hand_findStraight(source, target))
    return HAND_STRAIGHT;
  if (Hand_findTrips(source, target))
    return HAND_TRIPS;
  if (Hand_find2Pairs(source, target))
    return HAND_2PAIRS;
  if (Hand_findPair(source, target))
    return HAND_PAIR;
  if (Hand_findHiCard(source, target))
    return HAND_HICARD;
  else
    return HAND_UNKNOWN;
}
*/
