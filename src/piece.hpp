//GOUNOU Boubacar
#pragma once
#include <iostream>
#include <cmath>
#include "utils.hpp"

class Board; // Déclaration forward

class Piece {
protected:
    Board* m_board;

private:
    double m_xb;
    double m_yb;
    double m_width;
    double m_height;

public:

    Piece(Board* board, double xb = 0.0, double yb = 0.0, double width = 0.0, double height = 0.0);
    double xb() const ;
    double yb() const ;
    double width() const;
    double height() const ;

    void xb(double xb);
    void yb(double yb);
    void width( double width );
    void height( double height );

    virtual void draw (const CairoContext& cr);
    virtual bool is_clicked (double ev_x, double ev_y) const;
    virtual void on_button_press (double ev_x, double ev_y, int ev_button, bool& raise_on_top);
    virtual void on_button_release (double ev_x, double ev_y, int ev_button);
    virtual void on_motion_notify (double ev_x, double ev_y, double prev_x, double prev_y, int ev_button);

    void get_closer_magnet(double grid_side, int& x_mag, int& y_mag);

    bool place_on_magnetic_grid(double grid_side, double dist_threshold);

} ;
