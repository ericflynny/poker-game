#pragma once

#include <cassert>
#include <optional>
#include <string>

#include "card.hpp"
#include "deck.hpp"
#include "hand.hpp"
#include "handEvaluator.hpp"


class Game
{
    public:
        Game() :
        _credits{0},
        _bet{0},
        _roundInProgress{false},
        _lastResult{Loser, 0}
        {};

        // Coin/bet
        void insertCoin() {_credits++;}
        void setBet(int bet) {_bet = bet;}

        // Read accessors for the GUI
        int credits() const {return _credits;}
        int bet() const {return _bet;}
        bool roundInProgress() const {return _roundInProgress;}
        std::string handName() const {return WinningHandName.at(_lastResult.hand);}
        int payout() const {return _lastResult.odds * _bet;}

        void handleDeal();
        void setHold(int cardIndex, bool held);
        void cashOut();
        std::string cardLabel(int cardIndex) const;
        bool cardIsHeld(int cardIndex) const;

    private:
        void deal();
        void drawAndEvaluate();
        Deck _deck;
        std::optional<Hand> _hand;

        int _credits;
        int _bet;
        bool _roundInProgress;
        HandResult _lastResult;
};
