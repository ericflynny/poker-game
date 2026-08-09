#pragma once

#include <string>
#include <unordered_map>

enum CardValue : int
{
    Two,
    Three,
    Four,
    Five,
    Six,
    Seven,
    Eight,
    Nine,
    Ten,
    Jack,
    Queen,
    King,
    Ace,
    ValueCount
};

enum CardSuit : int
{
    Clubs,
    Diamonds,
    Hearts,
    Spades,
    SuitCount
};

static const std::unordered_map<CardValue, std::string> ValueToString
{
    {CardValue::Two, "2"},
    {CardValue::Three, "3"},
    {CardValue::Four, "4"},
    {CardValue::Five, "5"},
    {CardValue::Six, "6"},
    {CardValue::Seven, "7"},
    {CardValue::Eight, "8"},
    {CardValue::Nine, "9"},
    {CardValue::Ten, "10"},
    {CardValue::Jack, "J"},
    {CardValue::Queen, "Q"},
    {CardValue::King, "K"},
    {CardValue::Ace, "A"}
};

static const std::unordered_map<CardSuit, std::string> SuitToString
{
    {CardSuit::Clubs, "Clubs"},
    {CardSuit::Diamonds, "Diamonds"},
    {CardSuit::Hearts, "Hearts"},
    {CardSuit::Spades, "Spades"}
};


class Card
{
    public:
        // Require a value and suit
        Card(CardValue value, CardSuit suit) : 
            _value(value),
            _suit(suit)
            {};

        // Getters
        CardValue value() const {return _value;};
        CardSuit suit() const {return _suit;};

        // Return string names
        std::string valueToString() const {return ValueToString.at(_value);};
        std::string suitToString() const {return SuitToString.at(_suit);};
        std::string toString() const {return (valueToString() + " of " + suitToString());};

        private:
            CardValue _value;
            CardSuit _suit;
};