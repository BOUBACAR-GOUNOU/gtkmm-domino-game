#include "utils.hpp"
#include <cmath>

// Implémentation de la fonction pour calculer la distance entre deux points (x1, y1) et (x2, y2)
double calculate_distance(double x1, double y1, double x2, double y2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));  // Calcul de la distance Euclidienne
}

//Placement magnétique
int get_magnet_coord(double grid_side, double t) {
    return t / grid_side + (t >= 0 ? 0.5 : -0.5);
}

void BoundingBox::init(double xmin, double xmax, double ymin, double ymax) {
    m_xmin = xmin;
    m_xmax = xmax;
    m_ymin = ymin;
    m_ymax = ymax;
}

void BoundingBox::update_min(double x, double y) {
    m_xmin = std::min(m_xmin, x);
    m_ymin = std::min(m_ymin, y);
}

void BoundingBox::update_max(double x, double y) {
    m_xmax = std::max(m_xmax, x);
    m_ymax = std::max(m_ymax, y);
}
