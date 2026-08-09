#include "CoinSlot.h"

CoinSlot::CoinSlot(int x, int y, int w, int h)
    : Fl_Group(x, y, w, h) {
    int labelH = 25;
    int slotH = h - labelH - 5;

    slotButton_ = new Fl_Button(x + w / 2 - 10, y, 20, slotH, "");
    slotButton_->box(FL_BORDER_BOX);
    slotButton_->callback(slotCallback, this);

    label_ = new Fl_Box(x, y + slotH + 5, w, labelH, "Insert Coins");
    label_->labelfont(FL_HELVETICA_BOLD);

    end();
}

void CoinSlot::setOnInsertCoin(std::function<void()> cb) {
    onInsertCoin_ = std::move(cb);
}

void CoinSlot::handleSlotClicked() {
    if (onInsertCoin_) onInsertCoin_();
}

void CoinSlot::slotCallback(Fl_Widget*, void* data) {
    static_cast<CoinSlot*>(data)->handleSlotClicked();
}
