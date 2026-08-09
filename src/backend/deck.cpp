#include <algorithm> // For shuffling
#include <random> // For shuffling
#include <cassert>
#include "deck.hpp"
#include "card.hpp"


void Deck::shuffle()
{
    // Retrieve random number from OS
    static std::mt19937 rng(std::random_device{}());

    // Shuffle all cards in deck
    std::shuffle(_cards.begin(), _cards.end(), rng);
}

Card Deck::dealCard()
{
    // Ensure the deck is not empty
    assert(!_cards.empty());

    // Pop card out of the deck and return it
    Card top = _cards.back();
    _cards.pop_back();
    return top;
}

void Deck::addAllCards()
{
    const int CardSuitCount {static_cast<int>(CardSuit::SuitCount)};
    const int CardValueCount {static_cast<int>(CardValue::ValueCount)};

    for (int i = 0; i < CardSuitCount; i++)
    {
        for (int j = 0; j < CardValueCount; j++)
        {
            Card card {static_cast<CardValue>(j), static_cast<CardSuit>(i)};
            _cards.push_back(card);
        }
    }
}

void Deck::setupDeck()
{
    addAllCards();
    shuffle();
}

void Deck::reset()
{
    // Remove all cards
    _cards.clear();

    // Add all cards back and shuffle
    setupDeck();
}