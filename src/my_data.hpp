//GOUNOU Boubacar
#pragma once
#include "board.hpp"
#include "my_data.hpp"

class MyData {
public:
    int win_width;
    int win_height;

    Board m_board;  // Le domino à dessiner


    double prev_mouse_x;
    double prev_mouse_y;
    bool mouse_button_pressed;

    MyData();
};
