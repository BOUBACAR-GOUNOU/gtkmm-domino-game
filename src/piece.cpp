// GOUNOU Boubacar
#include "piece.hpp"


Piece::Piece(Board* board, double xb, double yb, double width, double height)
     : m_board(board), m_xb{xb}, m_yb{yb}, m_width{width}, m_height{height}
     {}

double Piece::xb() const { return m_xb; }
double Piece::yb() const { return m_yb; }
double Piece::width() const { return m_width;}
double Piece::height() const { return m_height;}

void Piece::xb(double xb){ m_xb = xb; }
void Piece::yb(double yb){ m_yb = yb; }
void Piece::width( double width ) { m_width = width; }
void Piece::height( double height ) { m_height = height; }

void Piece::draw(const CairoContext& cr){
    cr->save();
    cr->set_source_rgb(0.5, 1.0, 0.5); //vert pâle
    cr->rectangle(m_xb, m_yb, m_width, m_height);
    cr->fill_preserve();

    cr->set_source_rgb(0.5,0.5,0.5); // Gris pour les bords
    cr->set_line_width(1.0);
    cr->stroke();

}

//vérification de click sur la pièce
bool Piece::is_clicked(double ev_x, double ev_y) const {
    return (ev_x >= m_xb && ev_x <= m_xb + m_width && ev_y >= m_yb && ev_y <= m_yb + m_height);
}

// Clic souris
void Piece::on_button_press(double ev_x, double ev_y, int ev_button, bool& raise_on_top){


    raise_on_top = true;


    std::cout << "On_button_press - x: " <<ev_x << ", y:" <<ev_y << ", button:" << ev_button << "\n";
}

//Relâchement de buton de la souris
void Piece::on_button_release(double ev_x, double ev_y, int ev_button){
  std::cout << "Button release - x: " << ev_x << ", y: " << ev_y << ", button: " << ev_button << std::endl;

}

//Mouvement de souris
void Piece::on_motion_notify(double ev_x, double ev_y, double prev_x, double prev_y, int ev_button){

 std::cout << "Motion notify - current x: " << ev_x << ", y: " << ev_y
          << ", previous x: " << prev_x << ", y: " << prev_y
          << ", button: " << ev_button << std::endl;

    // Déplacer la pièce
    double dx = ev_x - prev_x;
    double dy = ev_y - prev_y;
    m_xb += dx;
    m_yb += dy;
}

void Piece::get_closer_magnet(double grid_side, int& x_mag, int& y_mag) {
    x_mag = get_magnet_coord(grid_side, m_xb);
    y_mag = get_magnet_coord(grid_side, m_yb);
}


bool Piece::place_on_magnetic_grid(double grid_side, double dist_threshold) {
    // Obtenir les coordonnées grille du point magnétique le plus proche
    int x_mag, y_mag;
    get_closer_magnet(grid_side, x_mag, y_mag);

    // Convertir ces coordonnées grille en coordonnées écran
    double target_x = x_mag * grid_side;
    double target_y = y_mag * grid_side;

    // Calculer la distance entre la position actuelle et le point cible
    double dx = target_x - m_xb;
    double dy = target_y - m_yb;
    double distance = std::sqrt(dx*dx + dy*dy);

    // Si on est assez proche, on déplace la pièce sur le point cible
    if (distance <= dist_threshold) {
        m_xb = target_x;
        m_yb = target_y;
        return true;
    }

    return false;
}
