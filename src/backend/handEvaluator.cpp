#include "handEvaluator.hpp"
#include "card.hpp"


HandResult HandEvaluator::evaluateHand()
{
    HandRank winningHand;
    
    // Evaluate in order of payout odds (high to low).
    if (isRoyalFlush()) {winningHand = RoyalFlush;}
    else if (isStraightFlush()) {winningHand = StraightFlush;}
    else if (isFourOfAKind()) {winningHand = FourOfAKind;}
    else if (isFullHouse()) {winningHand = FullHouse;}
    else if (isFlush()) {winningHand = Flush;}
    else if (isStraight()) {winningHand = Straight;}
    else if (isThreeOfAKind()) {winningHand = ThreeOfAKind;}
    else if (isTwoPair()) {winningHand = TwoPair;}
    else if (isJacksOrBetter()) {winningHand = JacksOrBetter;}
    else {winningHand = Loser;}

    HandResult result {winningHand, PayoutOdds[winningHand]};
    return result;
}

void HandEvaluator::sortHand()
{
    // Descending order (high to low)
    std::sort(_sortedCards.begin(), _sortedCards.end(),
                [](const Card& l, const Card& r){return l.value() > r.value();});
}

void HandEvaluator::scanHand()
{
    _hasFlush = true;
    _hasStraight = true;
    int maxCount {1};
    int currentCount {1};
    for (int i = 0; i < Hand::NumCardsInAHand - 1; i++)
    {
        // Check for flush
        if (_hasFlush && _sortedCards[i].suit() != _sortedCards[i + 1].suit())
        {
            _hasFlush = false;
        }

        // Check for straight
        if (_hasStraight && static_cast<int>(_sortedCards[i].value()) != (static_cast<int>(_sortedCards[i + 1].value()) + 1))
        {
            _hasStraight = false;
        }

        // Setup the max number of a kind and determine which suit it is
        if (_sortedCards[i].value() == _sortedCards[i + 1].value())
        {
            currentCount++;
            maxCount = std::max(maxCount, currentCount);
        }
        else
        {
            currentCount = 1;
        }
    }
    _maxNumberOfAKind = maxCount;
}

bool HandEvaluator::isRoyalFlush()
{
    return (
        _hasFlush && // All cards have the same suit
        (_sortedCards[0].value() == CardValue::Ace) &&
        (_sortedCards[1].value() == CardValue::King) && 
        (_sortedCards[2].value() == CardValue::Queen) &&
        (_sortedCards[3].value() == CardValue::Jack) &&
        (_sortedCards[4].value() == CardValue::Ten)
    );
}

bool HandEvaluator::isStraightFlush()
{
    // Do not check for a royal flush since it will already be assumed that there
    // is not a royal flush when this is called in evaluateHand().
    return _hasFlush && _hasStraight;
}

bool HandEvaluator::isFourOfAKind()
{
    return _maxNumberOfAKind == 4;
}

bool HandEvaluator::isFullHouse()
{
    // Check for x, x, x, y, y
    bool const TripleStart {
        // Are 0-2 equivalent?
        _sortedCards[0].value() == _sortedCards[1].value() &&
        _sortedCards[1].value() == _sortedCards[2].value() &&
        // and the last two are a pair?
        _sortedCards[3].value() == _sortedCards[4].value() 
    };

    // Check for x, x, y, y, y
    bool const TripleEnd {
        // Are 2-4 equivalent?
        _sortedCards[2].value() == _sortedCards[3].value() &&
        _sortedCards[3].value() == _sortedCards[4].value() &&
        // and the first two are a pair?
        _sortedCards[0].value() == _sortedCards[1].value() 
    };
    
    return TripleStart || TripleEnd;
}

bool HandEvaluator::isFlush()
{
    // Do not check for a straight flush since it will already be assumed that there
    // is not a straight flush when this is called in evaluateHand().
    return _hasFlush;
}

bool HandEvaluator::isStraight()
{
    // Do not check for a flush since it will already be assumed that there
    // is not a flush when this is called in evaluateHand().
    return _hasStraight;
}

bool HandEvaluator::isThreeOfAKind()
{
    // Do not check for a full house or four of a kind since it will already
    // be assumed that there is not a full house or four of a kind when this is called
    // in evaluateHand().
    return _maxNumberOfAKind == 3;
}

bool HandEvaluator::isTwoPair()
{
    // Check for x, x, y, y, z
    bool const LowPairs {
        _sortedCards[0].value() == _sortedCards[1].value() &&
        _sortedCards[2].value() == _sortedCards[3].value()
    };

    // Check for z, x, x, y, y
    bool const MidPairs {
        _sortedCards[1].value() == _sortedCards[2].value() &&
        _sortedCards[3].value() == _sortedCards[4].value()
    };

    // Check for x, x, z, y, y
    bool const LowAndHighPairs {
        _sortedCards[0].value() == _sortedCards[1].value() &&
        _sortedCards[3].value() == _sortedCards[4].value()
    };

    return LowPairs || MidPairs || LowAndHighPairs;
}

bool HandEvaluator::isJacksOrBetter()
{
    // Do not check for three or four of a kind since it will already
    // be assumed that there is not a three or four of a kind when this is called
    // in evaluateHand().
    bool hasJacksOrBetter {false};
    if (_maxNumberOfAKind == 2)
    {
        for (int i = 0; i < Hand::NumCardsInAHand - 1; i ++)
        {
            if (_sortedCards[i].value() == _sortedCards[i + 1].value())
            {
                // Enum is ordered so >= Jack is valid
                hasJacksOrBetter = _sortedCards[i].value() >= Jack;
                break;
            }
        }
    }
    return hasJacksOrBetter;
}