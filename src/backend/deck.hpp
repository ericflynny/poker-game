#pragma once

#include <vector>
#include "card.hpp"


class Deck
{
    public:
        Deck()
        {
            setupDeck();
        };

        void shuffle();
        Card dealCard();
        void reset();

    private:
        std::vector<Card> _cards;

        void addAllCards();
        void setupDeck();
};