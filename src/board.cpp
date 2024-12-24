
#include "board.hpp"
#include "domino.hpp"
#include <iomanip>



Board::Board()
    : m_piece_num_clicked(-1),
      m_deck(this){
    populate_dominos();
    populate_pieces();
}


//Pieces
void Board::populate_pieces() {
     m_pieces.clear(); // On vide d'abord le vecteur de pointeurs

    for(size_t i = 0; i < m_dominos_shown_num; ++i) {
        m_pieces.push_back(&m_dominos[i]);
    }

    m_pieces.push_back(&m_deck);
}

void Board::draw_pieces(const CairoContext& cr) {

    // Dessiner les pièces de la dernière à la première.
     for (int i = m_pieces.size() - 1; i >= 0; --i) {
        m_pieces[i]->draw(cr);
    }
}


bool Board::find_piece_clicked(double ev_x, double ev_y) {
    for (size_t i = 0; i < m_pieces.size(); ++i) {
        if (m_pieces[i]->is_clicked(ev_x, ev_y)) {
            m_piece_num_clicked = i;
            return true;
        }
    }
    m_piece_num_clicked = -1;
    return false;
}



void Board::move_piece_to_top(int piece_num){
  if (piece_num >= 0 && static_cast<size_t>(piece_num) < m_pieces.size()) {
    //Déplacment le domino spécifié en première positions
    Piece* moved_piece = m_pieces[piece_num];
    m_pieces.erase(m_pieces.begin() + piece_num);
    m_pieces.insert(m_pieces.begin(), moved_piece);

    m_piece_num_clicked = 0;
  }
}

int Board::piece_num_clicked() const { return m_piece_num_clicked;}
void Board::piece_num_clicked(int piece_num_clicked) { m_piece_num_clicked = piece_num_clicked;}



//Dominos

void Board::populate_dominos() {
    int index = 0;
    double start_x = 500;  // Position de départ pour le premier domino
    double start_y = 100;  // Position verticale du premier domino
    double offset_x = 150;  // Espacement horizontal entre les dominos
    double offset_y = 230;  // Espacement vertical entre les rangées (augmenté pour mieux espacer les rang�es)

    // Remplir m_dominos avec les 28 dominos
    for (int i = 0; i <= 6; ++i) {  // Premier domino (0-0) (6-6)
        for (int j = i; j <= 6; ++j) {  // Les dominos vont de (i-j)
            Domino d(this, i, j);
            d.xc(start_x + (index % 7) * offset_x);  // Calcul de la position x
            d.yc(start_y + (index / 7) * offset_y) ;  // Calcul de la position y
            d.angle(90);  // Angle par défaut
            m_dominos.push_back(d);
            index++;
        }
    }
}


void Board::shuffle_dominos() {
    shuffle_vector(m_dominos);

    // Mettre tous les dominos en position verticale
    for (auto& domino : m_dominos) {
        domino.angle(90);
    }

    // Mettre à jour les pointeurs dans m_pieces
    populate_pieces();
}

void Board::align_dominos_on_grid() {
    const int NB_COLS = 7;
    const double START_X = 500;  // Position de départ en X
    const double START_Y = 100;  // Position de départ en Y
    const double OFFSET_X = 150; // Espacement horizontal
    const double OFFSET_Y = 230; // Espacement vertical

    for (size_t i = 0; i < m_dominos.size(); ++i) {
        double x = START_X + (i % NB_COLS) * OFFSET_X;
        double y = START_Y + (i / NB_COLS) * OFFSET_Y;

        m_dominos[i].xc(x);
        m_dominos[i].yc(y);
        m_dominos[i].angle(90);
    }
}


void Board::reveal_next_domino(double x, double y) {
    if (!is_deck_empty()) {
        Domino* new_domino = &m_dominos[m_dominos_shown_num];
        new_domino->xb(x - new_domino->width()/2);
        new_domino->yb(y - new_domino->height()/2);
        new_domino->validated(false);  // Initialiser validated à false
        m_pieces.insert(m_pieces.begin(), new_domino);
        m_dominos_shown_num++;
    }
}

void Board::restart_game() {
    m_pieces.clear();
    m_pieces.push_back(&m_deck);
    m_dominos_shown_num = 0;
    shuffle_dominos();
}

bool Board::is_deck_empty() const {
    return m_dominos_shown_num >= m_dominos.size();
}

void Board::draw_magnetic_grid(const CairoContext& cr, int width, int height) {
    const double grid_step = DOMINO_SIDE / 2.0;

    // Couleur gris très clair
    cr->set_source_rgba(0.8, 0.8, 0.8, 0.5);
    cr->set_line_width(0.5);

    // Lignes verticales
    for (double x = 0; x <= width; x += grid_step) {
        cr->move_to(x, 0);
        cr->line_to(x, height);
    }

    // Lignes horizontales
    for (double y = 0; y <= height; y += grid_step) {
        cr->move_to(0, y);
        cr->line_to(width, y);
    }

    cr->stroke();
}

bool Board::validate_domino_position(Domino& domino) {
    BoundingBox bbox;
    find_bounding_box(bbox);

    // Élargir la bbox
    bbox.m_xmin -= DOMINO_SIDE;
    bbox.m_ymin -= DOMINO_SIDE;
    bbox.m_xmax += DOMINO_SIDE;
    bbox.m_ymax += DOMINO_SIDE;

    // Conversion en coordonnées grille
    int gxmin = get_magnet_coord(DOMINO_SIDE, bbox.m_xmin);
    int gymin = get_magnet_coord(DOMINO_SIDE, bbox.m_ymin);
    int gxmax = get_magnet_coord(DOMINO_SIDE, bbox.m_xmax);
    int gymax = get_magnet_coord(DOMINO_SIDE, bbox.m_ymax);

    // Dimensions de la grille
    int grid_w = gxmax - gxmin;
    int grid_h = gymax - gymin;

    // Création de la grille
    Grid2D<int> grid(grid_w, grid_h, -1);

    // Remplissage de la grille avec les dominos validés
    fill_marking_pieces(grid, bbox);

    // Affichage de la grille
    std::cout << "\nGrid " << grid_w << "x" << grid_h << ":\n";
    for (int y = 0; y < grid.height(); ++y) {
        for (int x = 0; x < grid.width(); ++x) {
            std::cout << std::setw(3) << grid.data(x, y) << " ";
        }
        std::cout << "\n";
    }
    std::cout << std::endl;

    // Vérifier si l'emplacement est libre
    if (!marking_is_empty(grid, bbox, domino)) {
        return false;
    }

    // Vérifier les voisins
    return check_neighbours(grid, bbox, domino);
}

void Board::find_bounding_box(BoundingBox& bbox) {
    bool first_valid = true;

    for (const auto& domino : m_dominos) {
        if (domino.validated()) {
            if (first_valid) {
                // Pour le premier domino validé, initialiser la bbox
                bbox.init(domino.xb(), domino.xb() + domino.width(),
                         domino.yb(), domino.yb() + domino.height());
                first_valid = false;
            } else {
                // Pour les dominos suivants, mettre à jour la bbox
                bbox.update_min(domino.xb(), domino.yb());
                bbox.update_max(domino.xb() + domino.width(),
                              domino.yb() + domino.height());
            }
        }
    }
}


void Board::fill_marking_pieces(Grid2D<int>& grid, const BoundingBox& bbox) {
    int gxmin = get_magnet_coord(DOMINO_SIDE, bbox.m_xmin);
    int gymin = get_magnet_coord(DOMINO_SIDE, bbox.m_ymin);

    for (size_t i = 0; i < m_dominos.size(); ++i) {
        const Domino& d = m_dominos[i];
        if (d.validated()) {
            // Convertir les coordonnées du domino en coordonnées grille
            int gx1 = get_magnet_coord(DOMINO_SIDE/2, d.xb()) - gxmin;
            int gy1 = get_magnet_coord(DOMINO_SIDE/2, d.yb()) - gymin;

            int angle = d.angle();
            int xa = (angle == 180);
            int ya = (angle == 270);
            int xb = (angle == 0);
            int yb = (angle == 90);

            // Coordonnées des deux carrés 2x2
            int gxa = gx1 + xa * 2;  // Carré pour m_a
            int gya = gy1 + ya * 2;
            int gxb = gx1 + xb * 2;  // Carré pour m_b
            int gyb = gy1 + yb * 2;

            // Marquer le carré 2x2 pour m_a
            for (int dx = 0; dx < 2; ++dx) {
                for (int dy = 0; dy < 2; ++dy) {
                    grid.data(gxa + dx, gya + dy, i);
                }
            }

            // Marquer le carré 2x2 pour m_b
            for (int dx = 0; dx < 2; ++dx) {
                for (int dy = 0; dy < 2; ++dy) {
                    grid.data(gxb + dx, gyb + dy, i);
                }
            }
        }
    }
}

bool Board::marking_is_empty(const Grid2D<int>& grid, const BoundingBox& bbox, const Domino& d) {
    int gxmin = get_magnet_coord(DOMINO_SIDE, bbox.m_xmin);
    int gymin = get_magnet_coord(DOMINO_SIDE, bbox.m_ymin);

    int gx1 = get_magnet_coord(DOMINO_SIDE/2, d.xb()) - gxmin;
    int gy1 = get_magnet_coord(DOMINO_SIDE/2, d.yb()) - gymin;

    int angle = d.angle();
    int xa = (angle == 180);
    int ya = (angle == 270);
    int xb = (angle == 0);
    int yb = (angle == 90);

    // Coordonnées des deux carrés 2x2
    int gxa = gx1 + xa * 2;
    int gya = gy1 + ya * 2;
    int gxb = gx1 + xb * 2;
    int gyb = gy1 + yb * 2;

    // Vérifier les 8 cases (2 carrés 2x2)
    // Premier carré (m_a)
    for (int dx = 0; dx < 2; ++dx) {
        for (int dy = 0; dy < 2; ++dy) {
            if (grid.data(gxa + dx, gya + dy) != -1) {
                return false;
            }
        }
    }

    // Deuxième carré (m_b)
    for (int dx = 0; dx < 2; ++dx) {
        for (int dy = 0; dy < 2; ++dy) {
            if (grid.data(gxb + dx, gyb + dy) != -1) {
                return false;
            }
        }
    }

    return true;
}


bool Board::check_neighbours(const Grid2D<int>& grid, const BoundingBox& bbox, const Domino& d) {
    int gxmin = get_magnet_coord(DOMINO_SIDE, bbox.m_xmin);
    int gymin = get_magnet_coord(DOMINO_SIDE, bbox.m_ymin);

    int gx1 = get_magnet_coord(DOMINO_SIDE/2, d.xb()) - gxmin;
    int gy1 = get_magnet_coord(DOMINO_SIDE/2, d.yb()) - gymin;

    int angle = d.angle();
    int xa = (angle == 180);
    int ya = (angle == 270);
    int xb = (angle == 0);
    int yb = (angle == 90);

    // Position des deux carrés 2x2
    int gxa = gx1 + xa * 2;
    int gya = gy1 + ya * 2;
    int gxb = gx1 + xb * 2;
    int gyb = gy1 + yb * 2;

    int n1 = 0;  // Compteur de voisins valides pour m_a
    int n2 = 0;  // Compteur de voisins valides pour m_b

    // Points m_a du domino d
    for (int x = gxa - 1; x <= gxa + 2; ++x) {
        for (int y = gya - 1; y <= gya + 2; ++y) {
            // Ne pas compter les cases du carré 2x2 lui-même
            if (x >= gxa && x < gxa + 2 && y >= gya && y < gya + 2) {
                continue;
            }

            // Vérifier que les coordonnées sont dans la grille
            if (x >= 0 && x < grid.width() && y >= 0 && y < grid.height()) {
                int val = grid.data(x, y);
                if (val != -1) {
                    if (val == d.a()) {
                        n1++;
                    } else {
                        return false;  // Voisin invalide trouvé
                    }
                }
            }
        }
    }

    // Points m_b du domino d
    for (int x = gxb - 1; x <= gxb + 2; ++x) {
        for (int y = gyb - 1; y <= gyb + 2; ++y) {
            // Ne pas compter les cases du carré 2x2 lui-même
            if (x >= gxb && x < gxb + 2 && y >= gyb && y < gyb + 2) {
                continue;
            }

            // Vérifier que les coordonnées sont dans la grille
            if (x >= 0 && x < grid.width() && y >= 0 && y < grid.height()) {
                int val = grid.data(x, y);
                if (val != -1) {
                    if (val == d.b()) {
                        n2++;
                    } else {
                        return false;  // Voisin invalide trouvé
                    }
                }
            }
        }
    }

    return (n1 + n2) == 2;
}
