#include "domino.hpp"
#include "board.hpp"

const double RIVET_RADIUS = 5.0;  // Rayon des rivets (cercles)
const double PI = 3.141592653589793238463;
const int DOMINO_SIDE = 60;  // Taille du petit côté d'un domino


Domino::Domino(Board* board, int a, int b)
    : Piece(board, 0, 0, DOMINO_SIDE, 2 * DOMINO_SIDE),
      m_a(a),
      m_b(b),
      m_validated(false)
      {}


void Domino::draw(const Cairo::RefPtr<Cairo::Context>& cr) {
    double half_width = DOMINO_SIDE / 2.0;
    double full_length = 2 * DOMINO_SIDE;

    cr->save();
    cr->translate(xc(), yc());
    cr->rotate(m_angle * PI / 180.0);

    // Modifier la couleur selon m_validated
    cr->rectangle(-full_length / 2.0, -half_width, full_length, 2 * half_width);
    if (m_validated) {
        cr->set_source_rgb(0.8, 0.8, 1.0);  // Bleu pâle
    } else {
        cr->set_source_rgb(1.0, 1.0, 0.8);  // Jaune paille
    }
    cr->fill_preserve();
    cr->set_source_rgb(0.0, 0.0, 0.0);
    cr->stroke();

    // Le reste de la méthode reste identique
    cr->move_to(0, -half_width);
    cr->line_to(0, half_width);
    cr->stroke();

    draw_rivets(cr, -DOMINO_SIDE / 2.0, 0, m_a);
    draw_rivets(cr, DOMINO_SIDE / 2.0, 0, m_b);

    cr->set_source_rgb(0.0, 0.0, 0.0);
    cr->arc(0, 0, RIVET_RADIUS, 0, 2 * PI);
    cr->fill();

    cr->restore();
}
void Domino::draw_rivets(const Cairo::RefPtr<Cairo::Context>& cr, double cx, double cy, int value) const {
    static const double positions[7][6][2] = {
        {},                                    // 0 points
        {{0, 0}},                              // 1 point
        {{-15, -15}, {15, 15}},               // 2 points
        {{0, 0}, {-15, -15}, {15, 15}},       // 3 points
        {{-15, -15}, {15, 15}, {-15, 15}, {15, -15}}, // 4 points
        {{0, 0}, {-15, -15}, {15, 15}, {-15, 15}, {15, -15}}, // 5 points
        {{-15, -15}, {15, 15}, {-15, 15}, {15, -15}, {0, 15}, {0, -15}} // 6 points
    };

    cr->set_source_rgb(0.0, 0.0, 0.0);  // Noir pour les rivets
    for (int i = 0; i < value; ++i) {
        cr->arc(cx + positions[value][i][0], cy + positions[value][i][1],
                RIVET_RADIUS, 0, 2 * PI);
        cr->fill();
    }
}

bool Domino::rivet_is_clicked(double ev_x, double ev_y) const {
    return calculate_distance(ev_x, ev_y, xc(), yc()) <= RIVET_RADIUS;
}

void Domino::on_button_release(double ev_x, double ev_y, int button) {
    if (rivet_is_clicked(ev_x, ev_y)) {
        double old_xc = xc();
        double old_yc = yc();
        angle((angle() + 90) % 360);
        double temp = width();
        width(height());
        height(temp);
        xc(old_xc);
        yc(old_yc);
    }

    // Placement magnétique avec la grille et validation de la position
    bool placed = place_on_magnetic_grid(DOMINO_SIDE/2, DOMINO_SIDE/4);
    validated(placed && m_board->validate_domino_position(*this));
}

//accesseurs
int Domino::a() const { return m_a;}
int Domino::b() const { return m_b;}
int Domino::angle() const { return m_angle;}

double Domino::xc() const {
    return xb() + width()/2;
}
double Domino::yc() const {
    return yb() + height()/2;
}

//Setters
void Domino::a(int a) { m_a = a; }
void Domino::b(int b) { m_b = b; }
void Domino::angle(int angle) { m_angle = angle; }
void Domino::xc(double xc) {
    xb(xc - width()/2);
}

void Domino::yc(double yc) {
    yb(yc - height()/2);
}

bool Domino::validated() const { return m_validated; }
void Domino::validated(bool val) { m_validated = val; }

