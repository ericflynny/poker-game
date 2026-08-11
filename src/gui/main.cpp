/*
    DEVELOPED WITH CLAUDE ASSISTANCE
*/
#include <FL/Fl.H>
#include "PokerMachineWindow.h"
#include "game.hpp"

int main(int argc, char** argv)
{
    PokerMachineWindow window;
    Game game;
    game.setBet(1);

    // Initial display state
    window.setHandName(game.handName());
    window.setBet(game.bet());
    window.setPayout(0);
    window.setCoinsRemaining(game.credits());
    // setCardText() only draws a card when given a real label, empty slot is blank
    for (int i = 0; i < PokerMachineWindow::kNumCards; ++i)
    {
        window.setCardText(i, "");
    }

    window.setOnDeal([&]()
    {
        bool wasDrawPhase = game.roundInProgress();

        // Check funds before dealing, handleDeal() will have deducted the bet by the time it returns
        bool insufficientFunds = !wasDrawPhase && game.credits() < game.bet();
        game.handleDeal();

        if (insufficientFunds)
        {
            window.setHandName("Insufficient amount of credits");
            return;
        }

        for (int i = 0; i < PokerMachineWindow::kNumCards; ++i)
        {
            window.setCardText(i, game.cardLabel(i));
        }

        if (!wasDrawPhase)
        {
            // Fresh hand, clear holds and last result.
            window.resetCardHolds();
            window.setHandName("");
            window.setPayout(0);
        }
        else
        {
            // Drew replacements and evaluated the final hand
            window.setHandName(game.handName());
            window.setPayout(game.payout());
        }

        window.setCoinsRemaining(game.credits());
    });

    window.setOnCashOut([&]()
    {
        game.cashOut();

        for (int i = 0; i < PokerMachineWindow::kNumCards; ++i)
        {
            window.setCardText(i, "");
        }
        window.resetCardHolds();
        window.setHandName("");
        window.setPayout(0);
        window.setCoinsRemaining(game.credits());
    });

    window.setOnInsertCoin([&]()
    {
        game.insertCoin();
        window.setCoinsRemaining(game.credits());
    });

    window.setOnBetSelected([&](int bet)
    {
        game.setBet(bet);
        window.setBet(bet);
    });

    window.setOnHoldChanged([&](int cardIndex, bool held)
    {
        game.setHold(cardIndex, held);
    });

    window.setOnDiscard([&](int cardIndex)
    {
        // Card is availavle for redraw next time Deal is pressed
        game.setHold(cardIndex, false);
    });

    window.show(argc, argv);
    return Fl::run();
}
