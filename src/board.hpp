//GOUNOU Boubacar
#pragma once
#include "utils.hpp"
#include "domino.hpp"
#include <vector>
#include "piece.hpp"
#include "deck.hpp"
#include "utils.tpp"


class Board {
private:

    int m_piece_num_clicked = -1;
    size_t m_dominos_shown_num = 0;


public:

    Board();

    //dominos
    void populate_dominos();
    void draw_dominos(const CairoContext& cr);
    void align_dominos_on_grid();
    void shuffle_dominos();
    void restart_game();

    //pieces
    void populate_pieces();
    void draw_pieces(const CairoContext& cr);
    bool find_piece_clicked(double mouse_x, double mouse_y);
    void move_piece_to_top(int piece_num);

    int piece_num_clicked() const;
    void piece_num_clicked(int piece_num_clicked);

    bool is_deck_empty() const;

    std::vector<Domino> m_dominos;
    std::vector<Piece*> m_pieces;

    Deck m_deck;
    void reveal_next_domino(double x, double y);

    void draw_magnetic_grid(const CairoContext& cr, int width, int height);

    bool validate_domino_position(Domino& domino);

    void find_bounding_box(BoundingBox& bbox);

    void fill_marking_pieces(Grid2D<int>& grid, const BoundingBox& bbox);

    bool marking_is_empty(const Grid2D<int>& grid, const BoundingBox& bbox, const Domino& d);

    bool check_neighbours(const Grid2D<int>& grid, const BoundingBox& bbox, const Domino& d);
};
