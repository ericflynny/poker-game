#include <FL/Fl.H>
#include "PokerMachineWindow.h"

int main(int argc, char** argv) {
    PokerMachineWindow window;

    // Initial display state -- replace with values from your backend.
    window.setHandName("");
    window.setBet(1);
    window.setPayout(0);
    window.setCoinsRemaining(0);
    for (int i = 0; i < PokerMachineWindow::kNumCards; ++i) {
        window.setCardText(i, "Card " + std::to_string(i + 1));
    }

    // Wire these up to your game logic. Each callback below is where
    // your backend should react to a user action and then call the
    // window's set*() methods to reflect the new state.
    window.setOnDeal([]() {
        // TODO: backend deals/draws cards, updates payout, etc.
    });
    window.setOnCashOut([]() {
        // TODO: backend cashes out remaining coins.
    });
    window.setOnInsertCoin([]() {
        // TODO: backend increments coins remaining.
    });
    window.setOnBetSelected([](int bet) {
        // TODO: backend records the selected bet amount.
        (void)bet;
    });
    window.setOnHoldChanged([](int cardIndex, bool held) {
        // TODO: backend marks/unmarks the card as held.
        (void)cardIndex;
        (void)held;
    });
    window.setOnDiscard([](int cardIndex) {
        // TODO: backend discards and replaces the given card.
        (void)cardIndex;
    });

    window.show(argc, argv);
    return Fl::run();
}
