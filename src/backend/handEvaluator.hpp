#pragma once

#include "hand.hpp"
#include "card.hpp"
#include <algorithm>
#include <unordered_map>


enum HandRank
{
    RoyalFlush,
    StraightFlush,
    FourOfAKind,
    FullHouse,
    Flush,
    Straight,
    ThreeOfAKind,
    TwoPair,
    JacksOrBetter,
    Loser
};

static std::unordered_map<HandRank, int> PayoutOdds
{
    {RoyalFlush, 250},
    {StraightFlush, 50},
    {FourOfAKind, 25},
    {FullHouse, 9},
    {Flush, 6},
    {Straight, 4},
    {ThreeOfAKind, 3},
    {TwoPair, 2},
    {JacksOrBetter, 1},
    {Loser, 0},
};

static std::unordered_map<HandRank, std::string> WinningHandName
{
    {RoyalFlush, "Royal Flush"},
    {StraightFlush, "Straight Flush"},
    {FourOfAKind, "Four of a Kind"},
    {FullHouse, "Full House"},
    {Flush, "Flush"},
    {Straight, "Straight"},
    {ThreeOfAKind, "Three of a Kind"},
    {TwoPair, "Two Pair"},
    {JacksOrBetter, "Jacks or Better"},
    {Loser, "Did not win"}
};

struct HandResult
{
    HandRank hand;
    int odds;
};


class HandEvaluator
{
    public:
        HandEvaluator(const Hand& hand) :
        // Default cards will be immediately overwritten
        _sortedCards
        {
            Card(CardValue::Ace, CardSuit::Hearts),
            Card(CardValue::Ace, CardSuit::Hearts),
            Card(CardValue::Ace, CardSuit::Hearts),
            Card(CardValue::Ace, CardSuit::Hearts),
            Card(CardValue::Ace, CardSuit::Hearts)
        },
        _hasFlush {false},
        _hasStraight {false},
        _maxNumberOfAKind {0}
        {
            // Copy cards for sorting
            for (int i = 0; i <Hand::NumCardsInAHand; i++)
            {
                _sortedCards[i] = hand.card(i);
            }

            // Sort cards to ease future processing
            sortHand();

            // Check for flush and straight, set max number of a kind
            scanHand();
        };

        void sortHand();
        void scanHand();
        HandResult evaluateHand();

        bool isRoyalFlush();
        bool isStraightFlush();
        bool isFourOfAKind();
        bool isFullHouse();
        bool isFlush();
        bool isStraight();
        bool isThreeOfAKind();
        bool isTwoPair();
        bool isJacksOrBetter();

    private:
        std::array<Card, Hand::NumCardsInAHand> _sortedCards;

        bool _hasFlush;
        bool _hasStraight;
        int _maxNumberOfAKind;
};