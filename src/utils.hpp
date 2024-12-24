//GOUNOU Boubacar
#pragma once
#include <gtkmm-3.0/gtkmm.h>
#include <algorithm>
#include "utils.tpp"

// Pour connecter un signal � une fonction
#define CONNECT(signal, func) \
    signal().connect( sigc::mem_fun(*this, &func) )
// Pour les dessins avec Cairo
typedef ::Cairo::RefPtr<::Cairo::Context> CairoContext;


//fonction utilitaire pour calculer la distance entre deux points
double calculate_distance(double x1, double y1, double x2, double y2);

int get_magnet_coord(double grid_side, double t);


struct BoundingBox {
    double m_xmin = 0;
    double m_xmax = 0;
    double m_ymin = 0;
    double m_ymax = 0;

    void init(double xmin, double xmax, double ymin, double ymax);
    void update_min(double x, double y);
    void update_max(double x, double y);
};
