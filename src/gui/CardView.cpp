#include "CardView.h"
#include <FL/Fl_Window.H>

CardView::CardView(int x, int y, int w, int h, int index)
    : Fl_Group(x, y, w, h), index_(index) {
    int cardH = h - 100;

    cardBox_ = new Fl_Box(x, y, w, cardH, "Card");
    cardBox_->box(FL_BORDER_BOX);
    cardBox_->color(FL_BACKGROUND2_COLOR);
    cardBox_->labelsize(16);
    cardBox_->copy_label(("Card " + std::to_string(index_ + 1)).c_str());

    holdButton_ = new Fl_Button(x, y + cardH + 10, w, 40, "Hold");
    holdButton_->type(FL_TOGGLE_BUTTON);
    holdButton_->callback(holdCallback, this);

    discardButton_ = new Fl_Button(x, y + cardH + 60, w, 40, "Discard");
    discardButton_->callback(discardCallback, this);

    end();
}

void CardView::setCardText(const std::string& text) {
    cardBox_->copy_label(text.c_str());
}

void CardView::setHeld(bool held) {
    held_ = held;
    holdButton_->value(held_ ? 1 : 0);
    cardBox_->color(held_ ? FL_YELLOW : FL_BACKGROUND2_COLOR);
    if (window()) window()->redraw();
    else redraw();
}

void CardView::setOnHoldChanged(std::function<void(int, bool)> cb) {
    onHoldChanged_ = std::move(cb);
}

void CardView::setOnDiscard(std::function<void(int)> cb) {
    onDiscard_ = std::move(cb);
}

void CardView::handleHoldClicked() {
    setHeld(holdButton_->value() != 0);
    if (onHoldChanged_) onHoldChanged_(index_, held_);
}

void CardView::handleDiscardClicked() {
    setCardText("");
    setHeld(false);
    if (onDiscard_) onDiscard_(index_);
}

void CardView::holdCallback(Fl_Widget*, void* data) {
    static_cast<CardView*>(data)->handleHoldClicked();
}

void CardView::discardCallback(Fl_Widget*, void* data) {
    static_cast<CardView*>(data)->handleDiscardClicked();
}
