#include "PayoutBanner.h"

PayoutBanner::PayoutBanner(int x, int y, int w, int h)
    : Fl_Group(x, y, w, h) {
    background_ = new Fl_Box(x, y, w, h);
    background_->box(FL_FLAT_BOX);
    background_->color(FL_LIGHT2);

    int thirdW = w / 3;

    handNameLabel_ = new Fl_Box(x + 15, y, thirdW, h, "Hand Name");
    handNameLabel_->align(FL_ALIGN_INSIDE | FL_ALIGN_LEFT);
    handNameLabel_->labelfont(FL_HELVETICA_BOLD);

    betLabel_ = new Fl_Box(x + thirdW, y, thirdW, h, "Bet: 0");
    betLabel_->align(FL_ALIGN_INSIDE | FL_ALIGN_CENTER);
    betLabel_->labelfont(FL_HELVETICA_BOLD);

    payoutLabel_ = new Fl_Box(x + 2 * thirdW, y, thirdW - 15, h, "Payout: 0");
    payoutLabel_->align(FL_ALIGN_INSIDE | FL_ALIGN_RIGHT);
    payoutLabel_->labelfont(FL_HELVETICA_BOLD);

    end();
}

void PayoutBanner::setHandName(const std::string& name) {
    handNameLabel_->copy_label(name.c_str());
}

void PayoutBanner::setBet(int bet) {
    betLabel_->copy_label(("Bet: " + std::to_string(bet)).c_str());
}

void PayoutBanner::setPayout(int payout) {
    payoutLabel_->copy_label(("Payout: " + std::to_string(payout)).c_str());
}
