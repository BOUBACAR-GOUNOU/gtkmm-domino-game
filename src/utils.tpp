//GOUNOU Boubacar

#pragma once
#include <vector>
#include <random>

template<typename T>
void shuffle_vector(std::vector<T>& v) {
    // Cr�ation d'un vecteur temporaire avec une copie des �l�ments
    std::vector<T> tmp = v;

    // Vider le vecteur original
    v.clear();

    // G�n�rateur de nombres al�atoires
    std::random_device rd;
    std::mt19937 gen(rd());

    // Tant que le vecteur temporaire n'est pas vide
    while (!tmp.empty()) {
        // G�n�rer un index al�atoire dans la plage valide
        std::uniform_int_distribution<> dis(0, tmp.size() - 1);
        int random_index = dis(gen);

        // Ajouter l'�l�ment choisi au hasard dans v
        v.push_back(tmp[random_index]);

        // Supprimer l'�l�ment choisi de tmp en le rempla�ant par le dernier �l�ment
        // et en r�duisant la taille du vecteur
        tmp[random_index] = tmp.back();
        tmp.pop_back();
    }
}

template<typename T>
class Grid2D {
private:
    std::vector<T> m_data;
    int m_width;
    int m_height;
    T m_empty;

public:
    Grid2D(int width, int height, const T& empty)
        : m_width(width), m_height(height), m_empty(empty) {
        m_data.assign(width * height, empty);
    }

    bool check_coordinates(int x, int y) const {
        return x >= 0 && x < m_width && y >= 0 && y < m_height;
    }

    int width() const { return m_width; }
    int height() const { return m_height; }

    const T& data(int x, int y) const {
        if (check_coordinates(x, y)) {
            return m_data[y * m_width + x];
        }
        return m_empty;
    }

    void data(int x, int y, const T& value) {
        if (check_coordinates(x, y)) {
            m_data[y * m_width + x] = value;
        }
    }
};
