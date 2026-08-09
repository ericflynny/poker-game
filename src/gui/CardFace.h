#pragma once

#include <FL/Fl_Box.H>
#include <FL/Enumerations.H>
#include <string>

// A single playing card's face: rounded white card with the rank and suit
// symbol printed in the top-left and bottom-right corners, plus a large
// suit symbol in the center. Draws itself; carries no game knowledge.
class CardFace : public Fl_Box {
public:
    CardFace(int x, int y, int w, int h);

    void setCard(const std::string& rank, const std::string& suitSymbol, Fl_Color suitColor);
    void clear();

protected:
    void draw() override;

private:
    std::string rank_;
    std::string suitSymbol_;
    Fl_Color suitColor_ = FL_BLACK;
    bool hasCard_ = false;
};
