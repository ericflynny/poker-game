#include "game.hpp"



void Game::handleDeal()
{
    // Start new hand if none in progress
    if (_roundInProgress)
    {
        drawAndEvaluate();
    }
    // Otherwise draw replacements and pay out
    else if (_credits >= _bet)
    {
        deal();
    }
}

void Game::setHold(int cardIndex, bool held)
{
    assert(_hand.has_value());
    _hand->setHold(cardIndex, held);
}

void Game::cashOut()
{
    _credits = 0;
    _hand.reset();
    _roundInProgress = false;
    _lastResult = {Loser, 0};
}

std::string Game::cardLabel(int cardIndex) const
{
    assert(_hand.has_value());
    return _hand->card(cardIndex).toString();
}

bool Game::cardIsHeld(int cardIndex) const
{
    assert(_hand.has_value());
    return _hand->cardIsHeld(cardIndex);
}

void Game::deal()
{
    _deck.reset();
    _credits -= _bet;
    _hand.emplace(_deck);
    _roundInProgress = true;
    _lastResult = {Loser, 0};
}

void Game::drawAndEvaluate()
{
    assert(_hand.has_value());
    _hand->drawReplacements();

    HandEvaluator evaluator(*_hand);
    _lastResult = evaluator.evaluateHand();
    _credits += _lastResult.odds * _bet;

    _roundInProgress = false;
}