#include "PokerMachineWindow.h"

namespace {
constexpr int kWinW = 900;
constexpr int kWinH = 650;

constexpr int kCardW = 140;
constexpr int kCardH = 260;
constexpr int kCardGap = 20;
constexpr int kCardY = 110;
constexpr int kCardX0 = 60;
} // namespace

PokerMachineWindow::PokerMachineWindow()
    : Fl_Double_Window(kWinW, kWinH, "Video Poker") {
    // Decorative outer frame, matching the mockup's bounding box.
    auto* frame = new Fl_Box(10, 10, kWinW - 20, kWinH - 20);
    frame->box(FL_BORDER_FRAME);

    payoutBanner_ = new PayoutBanner(40, 25, kWinW - 80, 55);

    for (int i = 0; i < kNumCards; ++i) {
        int x = kCardX0 + i * (kCardW + kCardGap);
        cards_[i] = new CardView(x, kCardY, kCardW, kCardH, i);
    }

    int controlsY = kCardY + kCardH + 30; // 400

    auto* betLabel = new Fl_Box(kCardX0, controlsY, 250, 22, "Place Your Bet");
    betLabel->labelfont(FL_HELVETICA_BOLD);
    betLabel->align(FL_ALIGN_INSIDE | FL_ALIGN_LEFT);

    betSelector_ = new BetSelector(kCardX0, controlsY + 28, 200, 45, 5);

    int dealX = kCardX0 + 2 * (kCardW + kCardGap);
    dealButton_ = new Fl_Button(dealX, controlsY, kCardW, 90, "Deal");
    dealButton_->box(FL_ROUND_UP_BOX);
    dealButton_->labelfont(FL_HELVETICA_BOLD);
    dealButton_->callback(dealCallback, this);

    int cashOutX = kCardX0 + 3 * (kCardW + kCardGap);
    cashOutButton_ = new Fl_Button(cashOutX, controlsY, kCardW, 90, "Cash Out");
    cashOutButton_->box(FL_ROUND_UP_BOX);
    cashOutButton_->labelfont(FL_HELVETICA_BOLD);
    cashOutButton_->callback(cashOutCallback, this);

    int coinSlotX = kCardX0 + 4 * (kCardW + kCardGap);
    coinSlot_ = new CoinSlot(coinSlotX, controlsY, kCardW, 140);

    int coinsRemainingW = (cashOutX + kCardW) - kCardX0; // spans card1..card4
    coinsRemainingBanner_ = new Fl_Box(kCardX0, controlsY + 160, coinsRemainingW, 50);
    coinsRemainingBanner_->box(FL_FLAT_BOX);
    coinsRemainingBanner_->color(FL_LIGHT2);
    coinsRemainingBanner_->copy_label("Coins Remaining: 0");
    coinsRemainingBanner_->labelfont(FL_HELVETICA_BOLD);

    end();
}

// ---- Backend -> GUI ----

void PokerMachineWindow::setHandName(const std::string& name) {
    payoutBanner_->setHandName(name);
}

void PokerMachineWindow::setBet(int bet) {
    payoutBanner_->setBet(bet);
    betSelector_->setSelectedBet(bet);
}

void PokerMachineWindow::setPayout(int payout) {
    payoutBanner_->setPayout(payout);
}

void PokerMachineWindow::setCoinsRemaining(int coins) {
    coinsRemainingBanner_->copy_label(("Coins Remaining: " + std::to_string(coins)).c_str());
    coinsRemainingBanner_->redraw();
}

void PokerMachineWindow::setCardText(int cardIndex, const std::string& text) {
    if (cardIndex < 0 || cardIndex >= kNumCards) return;
    cards_[cardIndex]->setCardText(text);
}

void PokerMachineWindow::setCardHeld(int cardIndex, bool held) {
    if (cardIndex < 0 || cardIndex >= kNumCards) return;
    cards_[cardIndex]->setHeld(held);
}

void PokerMachineWindow::resetCardHolds() {
    for (auto* card : cards_) card->setHeld(false);
}

// ---- GUI -> Backend ----

void PokerMachineWindow::setOnDeal(std::function<void()> cb) {
    onDeal_ = std::move(cb);
}

void PokerMachineWindow::setOnCashOut(std::function<void()> cb) {
    onCashOut_ = std::move(cb);
}

void PokerMachineWindow::setOnInsertCoin(std::function<void()> cb) {
    coinSlot_->setOnInsertCoin(std::move(cb));
}

void PokerMachineWindow::setOnBetSelected(std::function<void(int)> cb) {
    betSelector_->setOnBetSelected(std::move(cb));
}

void PokerMachineWindow::setOnHoldChanged(std::function<void(int, bool)> cb) {
    for (auto* card : cards_) card->setOnHoldChanged(cb);
}

void PokerMachineWindow::setOnDiscard(std::function<void(int)> cb) {
    for (auto* card : cards_) card->setOnDiscard(cb);
}

void PokerMachineWindow::dealCallback(Fl_Widget*, void* data) {
    auto* self = static_cast<PokerMachineWindow*>(data);
    if (self->onDeal_) self->onDeal_();
}

void PokerMachineWindow::cashOutCallback(Fl_Widget*, void* data) {
    auto* self = static_cast<PokerMachineWindow*>(data);
    if (self->onCashOut_) self->onCashOut_();
}
