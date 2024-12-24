//GOUNOU Boubacar
#pragma once
#include "piece.hpp"
#include "domino.hpp" // Pour accéder à DOMINO_SIDE

class Deck : public Piece {

private:
    bool m_motion_flag = false;


public:
    Deck(Board* board);
    void draw(const CairoContext& cr) override;
    void on_button_press(double ev_x, double ev_y, int ev_button, bool& raise_on_top) override;
    void on_button_release(double x, double y, int button) override;
    void on_motion_notify(double x, double y, double prev_x, double prev_y, int button) override;
};
