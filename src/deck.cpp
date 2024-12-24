#include "deck.hpp"
#include "board.hpp"

Deck::Deck(Board* board)
    : Piece(board, 0, 0, DOMINO_SIDE * 2, DOMINO_SIDE * 3)
      {}

void Deck::draw(const CairoContext& cr) {
    cr->save();

    // Bordure extérieure vert foncé
    cr->set_source_rgb(0.0, 0.5, 0.0);
    cr->rectangle(xb(), yb(), width(), height());
    cr->set_line_width(10.0);
    cr->stroke();

    // Rectangle intérieur vert pâle
    cr->set_source_rgb(0.5, 1.0, 0.5);
    double margin = 10.0;
    double inner_width = DOMINO_SIDE + margin;
    double inner_height = DOMINO_SIDE * 2 + margin;
    double inner_x = xb() + (width() - inner_width) / 2;
    double inner_y = yb() + (height() - inner_height) / 2;

    cr->rectangle(inner_x, inner_y, inner_width, inner_height);
    cr->fill();

    // Point d'interrogation ou X selon l'état du sabot
    cr->select_font_face("Sans", Cairo::FONT_SLANT_NORMAL, Cairo::FONT_WEIGHT_BOLD);
    cr->set_font_size(50.0);
    cr->set_source_rgb(0.5, 0.5, 0.5);

    Cairo::TextExtents extents;
    const char* symbol = m_board->is_deck_empty() ? "X" : "?";
    cr->get_text_extents(symbol, extents);
    double text_x = xb() + (width() - extents.width) / 2;
    double text_y = yb() + (height() + extents.height) / 2;

    cr->move_to(text_x, text_y);
    cr->show_text(symbol);

    cr->restore();
}
void Deck::on_button_press(double ev_x, double ev_y, int ev_button, bool& raise_on_top) {
    // Test si on est sur la bordure du sabot (bande de 10 pixels)
    if ((ev_x >= xb() && ev_x <= xb() + 12) ||                    // bordure gauche
        (ev_x >= xb() + width() - 12 && ev_x <= xb() + width()) ||// bordure droite
        (ev_y >= yb() && ev_y <= yb() + 12) ||                    // bordure haute
        (ev_y >= yb() + height() - 12 && ev_y <= yb() + height())) // bordure basse
    {
        m_motion_flag = true;
    } else {
        m_motion_flag = false;
    }

    Piece::on_button_press(ev_x, ev_y, ev_button, raise_on_top);
}

void Deck::on_button_release(double x, double y, int button) {
    if (!m_motion_flag) {
        double center_x = xb() + width()/2;
        double center_y = yb() + height()/2;
        m_board->reveal_next_domino(center_x, center_y);
    } else {
        // Placement magnétique avec la grille
        place_on_magnetic_grid(DOMINO_SIDE/2, DOMINO_SIDE/4);
    }
    m_motion_flag = false;
    Piece::on_button_release(x, y, button);
}

void Deck::on_motion_notify(double x, double y, double prev_x, double prev_y, int button) {
    m_motion_flag = true;
    Piece::on_motion_notify(x, y, prev_x, prev_y, button);
}
