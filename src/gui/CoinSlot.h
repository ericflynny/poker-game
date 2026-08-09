#pragma once

#include <FL/Fl_Group.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Box.H>
#include <functional>

// The tall "Insert Coins" slot button on the right side of the machine.
class CoinSlot : public Fl_Group {
public:
    CoinSlot(int x, int y, int w, int h);

    void setOnInsertCoin(std::function<void()> cb);

private:
    static void slotCallback(Fl_Widget* w, void* data);
    void handleSlotClicked();

    Fl_Button* slotButton_;
    Fl_Box* label_;
    std::function<void()> onInsertCoin_;
};
