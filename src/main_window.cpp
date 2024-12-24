#include "main_window.hpp"
#include  <iostream>

MainWindow::MainWindow(MyData& my) {
    m_my = &my;

    // Fenêtre
    m_window.set_title("Domino");
    m_window.set_size_request(my.win_width, my.win_height);
    m_window.add(m_vbox1);
    m_vbox1.pack_start(m_hbox1, false, false, 5);

    // Ajout du bouton shuffle dans la hbox
    m_hbox1.pack_start(m_button_shuffle, false, false, 5);
    m_button_shuffle.signal_clicked().connect(
        sigc::mem_fun(*this, &MainWindow::on_shuffle_clicked)
    );

     // Ajout du bouton New game dans la hbox
    m_hbox1.pack_start(m_button_new_game, false, false, 5);
    m_button_new_game.signal_clicked().connect(
        sigc::mem_fun(*this, &MainWindow::on_new_game_clicked)
    );
    // Zone de dessin m_darea
    m_vbox1.pack_start(m_frame1, true, true, 2);
    m_frame1.set_border_width(2);
    m_frame1.add(m_darea);
    CONNECT(m_darea.signal_draw, MainWindow::darea_on_draw);

    m_darea.set_events(Gdk::BUTTON_PRESS_MASK |
                       Gdk::BUTTON_RELEASE_MASK |
                       Gdk::POINTER_MOTION_MASK);

    CONNECT(m_darea.signal_button_press_event,
            MainWindow::darea_on_button_press);
    CONNECT(m_darea.signal_button_release_event,
            MainWindow::darea_on_button_release);
    CONNECT(m_darea.signal_motion_notify_event,
            MainWindow::darea_on_motion_notify);
     CONNECT(m_darea.signal_size_allocate,
             MainWindow::darea_on_size_allocate);

    m_window.show_all();
}

bool MainWindow::darea_on_draw(const CairoContext& cr) {
    // Dessiner d'abord la grille magnétique
    m_my->m_board.draw_magnetic_grid(cr, m_darea_width, m_darea_height);

    // Puis dessiner les pièces
    m_my->m_board.draw_pieces(cr);

    return true;
}

void MainWindow::repaint_darea() {
    m_darea.queue_draw();   // force darea à se redessiner
}

//Méthode bouton pressé
bool MainWindow::darea_on_button_press(GdkEventButton* event) {
    m_my->mouse_button_pressed = true;
    // Vérifie si une pièce est cliquée
    if (m_my->m_board.find_piece_clicked(event->x, event->y)) {
        bool raise_on_top = false;
        int clicked_piece_num = m_my->m_board.piece_num_clicked();

        m_my->m_board.m_pieces[clicked_piece_num]->on_button_press(event->x, event->y, event->button, raise_on_top);

        if (raise_on_top) {
            m_my->m_board.move_piece_to_top(clicked_piece_num);
        }

        repaint_darea();
        m_my->prev_mouse_x = event->x;
        m_my->prev_mouse_y = event->y;

        return true;

    }

    return true; // Événement capté
}

// Méthode pour le deplacement
bool MainWindow::darea_on_motion_notify(GdkEventMotion* event) {

    if (!m_my->mouse_button_pressed) {
        return true;
    }
    int clicked_piece_num = m_my->m_board.piece_num_clicked();

    if ( clicked_piece_num != -1) {
        m_my->m_board.m_pieces[clicked_piece_num]->on_motion_notify(event->x, event->y, m_my->prev_mouse_x, m_my->prev_mouse_y, event->state);
        repaint_darea();
    }

    // Mettre à jour les coordonnées précédentes
    m_my->prev_mouse_x = event->x;
    m_my->prev_mouse_y = event->y;

    return true;
}

// Méthode bouton relâché
bool MainWindow::darea_on_button_release(GdkEventButton* event) {
    m_my->mouse_button_pressed = false;

    int piece_num =  m_my->m_board.piece_num_clicked();

    // Vérifie si une pièce était cliquée
    if (piece_num != -1) {

        m_my->m_board.m_pieces[piece_num]->on_button_release(event->x, event->y, event->button);

        repaint_darea();

    }
    return true;
}

void MainWindow::on_shuffle_clicked() {
    m_my->m_board.shuffle_dominos();
    m_my->m_board.align_dominos_on_grid();
    repaint_darea();
}

void MainWindow::on_new_game_clicked() {
    m_my->m_board.restart_game();
    repaint_darea();
}

void MainWindow::darea_on_size_allocate(Gtk::Allocation& allocation) {
    m_darea_width = allocation.get_width();
    m_darea_height = allocation.get_height();
}
