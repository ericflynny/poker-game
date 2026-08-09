#pragma once

#include <FL/Fl_Group.H>
#include <FL/Fl_Box.H>
#include <string>

// Gray banner showing the current hand name, bet, and payout,
// matching the "Straight Flush / Bet: 3 / Payout: 150" row in the mockup.
class PayoutBanner : public Fl_Group {
public:
    PayoutBanner(int x, int y, int w, int h);

    void setHandName(const std::string& name);
    void setBet(int bet);
    void setPayout(int payout);

private:
    Fl_Box* background_;
    Fl_Box* handNameLabel_;
    Fl_Box* betLabel_;
    Fl_Box* payoutLabel_;
};
