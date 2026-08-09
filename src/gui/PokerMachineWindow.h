#pragma once

#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <array>
#include <functional>
#include <string>

#include "CardView.h"
#include "PayoutBanner.h"
#include "BetSelector.h"
#include "CoinSlot.h"

// Top-level window: composes the payout banner, 5 card slots, bet selector,
// deal/cash-out buttons, coin slot, and the coins-remaining banner.
//
// This class only knows how to display state and report user actions.
// It owns no game logic -- wire your backend to it via the setOn*()
// callbacks and push state changes to it via the set*() methods.
class PokerMachineWindow : public Fl_Double_Window {
public:
    static constexpr int kNumCards = 5;

    PokerMachineWindow();

    // ---- Backend -> GUI: push state to the display ----
    void setHandName(const std::string& name);
    void setBet(int bet);
    void setPayout(int payout);
    void setCoinsRemaining(int coins);

    void setCardText(int cardIndex, const std::string& text);
    void setCardHeld(int cardIndex, bool held);
    void resetCardHolds();

    // ---- GUI -> Backend: register handlers for user actions ----
    void setOnDeal(std::function<void()> cb);
    void setOnCashOut(std::function<void()> cb);
    void setOnInsertCoin(std::function<void()> cb);
    void setOnBetSelected(std::function<void(int bet)> cb);
    void setOnHoldChanged(std::function<void(int cardIndex, bool held)> cb);
    void setOnDiscard(std::function<void(int cardIndex)> cb);

private:
    static void dealCallback(Fl_Widget* w, void* data);
    static void cashOutCallback(Fl_Widget* w, void* data);

    PayoutBanner* payoutBanner_;
    std::array<CardView*, kNumCards> cards_;
    BetSelector* betSelector_;
    Fl_Button* dealButton_;
    Fl_Button* cashOutButton_;
    CoinSlot* coinSlot_;
    Fl_Box* coinsRemainingBanner_;

    std::function<void()> onDeal_;
    std::function<void()> onCashOut_;
};
