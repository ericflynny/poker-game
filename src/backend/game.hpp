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

        // Single entry point for the Deal button: starts a new hand if none
        // is in progress, otherwise draws replacements and pays out.
        void handleDeal()
        {
            if (_roundInProgress)
            {
                drawAndEvaluate();
            }
            else
            {
                deal();
            }
        }

        void setHold(int cardIndex, bool held)
        {
            assert(_hand.has_value());
            _hand->setHold(cardIndex, held);
        }

        void cashOut() {_credits = 0;}

        // Read accessors for the GUI
        int credits() const {return _credits;}
        int bet() const {return _bet;}
        bool roundInProgress() const {return _roundInProgress;}

        std::string cardLabel(int cardIndex) const
        {
            assert(_hand.has_value());
            return _hand->card(cardIndex).toString();
        }

        bool cardIsHeld(int cardIndex) const
        {
            assert(_hand.has_value());
            return _hand->cardIsHeld(cardIndex);
        }

        std::string handName() const {return WinningHandName.at(_lastResult.hand);}
        int payout() const {return _lastResult.odds * _bet;}

    private:
        void deal()
        {
            _credits -= _bet;
            _hand.emplace(_deck);
            _roundInProgress = true;
            _lastResult = {Loser, 0};
        }

        void drawAndEvaluate()
        {
            assert(_hand.has_value());
            _hand->drawReplacements();

            HandEvaluator evaluator(*_hand);
            _lastResult = evaluator.evaluateHand();
            _credits += _lastResult.odds * _bet;

            _roundInProgress = false;
        }

        Deck _deck;
        std::optional<Hand> _hand;

        int _credits;
        int _bet;
        bool _roundInProgress;
        HandResult _lastResult;
};
