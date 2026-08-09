#pragma once

#include <array>
#include "deck.hpp"


class Hand
{
    public:
        static const int NumCardsInAHand {5};

        Hand(Deck& deck) :
        _deck{deck},
        _cards{deck.dealCard(), deck.dealCard(), deck.dealCard(), deck.dealCard(), deck.dealCard()},
        _held{false, false, false, false, false}
        {};

        // Getters
        const Card& card(int index) const {return _cards[index];}
        bool cardIsHeld(int index) const {return _held[index];}

        // Setters
        void setHold(int index, bool state) {_held[index] = state;}

        // Replace cards that are not set to held
        void drawReplacements()
        {
            for (int i = 0; i < NumCardsInAHand; i++)
            {
                if (_held[i] == false)
                {
                    _cards[i] = _deck.dealCard();
                }
            }
        }

    private:
        Deck& _deck;
        std::array<Card, NumCardsInAHand> _cards;
        std::array<bool, NumCardsInAHand> _held;
};