#include "main_window.hpp"


int main(int argc, char** argv) {
    // Initialiser GTK
    Gtk::Main app(argc, argv);

    // Créer les données de l'application
    MyData my;

    // Créer la fenêtre principale
    MainWindow main_window(my);

    // Lancer l'application GTK
    app.run(main_window.m_window);

    return 0;
}
