//GOUNOU Boubacar
#pragma once
#include <cmath>
#include "utils.hpp"
#include "piece.hpp"

extern const double RIVET_RADIUS;  // Rayon des rivets (cercles)
extern const double PI;
extern const int DOMINO_SIDE;

class Domino : public Piece {
private:
  int m_a = 0;  // Nombre de points sur la face 1
  int m_b = 0;  // Nombre de points sur la face 2
  int m_angle = 0;  // Angle de rotation (0, 90, 180, 270)
  bool m_validated = false;

public:

     // Constructeur avec paramètres optionnels pour les points
    Domino(Board* board, int a = 0, int b = 0);

    //accesseurs
    int a() const;
    int b() const;
    int angle() const;
    double xc() const;
    double yc() const;

    //Setters
    void a(int a);
    void b(int b);
    void angle(int angle);
    void xc(double xc);
    void yc(double yc);

    bool validated() const;
    void validated(bool val);



    // Méthode pour dessiner un domino
    void draw(const CairoContext& cr) override ;

    // Méthode pour vérifier si le clic est sur le rivet
    bool rivet_is_clicked(double ev_x, double ev_y) const;

    // Méthode utilitaire pour dessiner les rivets sur une face
    void draw_rivets(const CairoContext& cr, double cx, double cy, int value) const;

    void on_button_release(double ev_x, double ev_y, int button) override;

};

