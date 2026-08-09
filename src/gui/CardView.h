#pragma once

#include <FL/Fl_Group.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <functional>
#include <string>

// One card slot: the card face plus its Hold/Discard buttons.
class CardView : public Fl_Group {
public:
    CardView(int x, int y, int w, int h, int index);

    void setCardText(const std::string& text);
    void setHeld(bool held);
    bool isHeld() const { return held_; }

    void setOnHoldChanged(std::function<void(int index, bool held)> cb);
    void setOnDiscard(std::function<void(int index)> cb);

    int index() const { return index_; }

private:
    static void holdCallback(Fl_Widget* w, void* data);
    static void discardCallback(Fl_Widget* w, void* data);

    void handleHoldClicked();
    void handleDiscardClicked();

    int index_;
    bool held_ = false;

    Fl_Box* cardBox_;
    Fl_Button* holdButton_;
    Fl_Button* discardButton_;

    std::function<void(int, bool)> onHoldChanged_;
    std::function<void(int)> onDiscard_;
};
