//GOUNOU Boubacar
#pragma once
#include "my_data.hpp"
#include "domino.hpp"
#include "board.hpp"

class MainWindow {
public:
    Gtk::Window m_window;
    Gtk::VBox m_vbox1;
    Gtk::HBox m_hbox1;
    Gtk::Button m_button_quit {"Quit"};
    Gtk::Button m_button_shuffle {"Shuffle"};
    Gtk::Button m_button_new_game {"New game"};
    Gtk::Frame m_frame1;
    Gtk::DrawingArea m_darea;
    MyData *m_my = nullptr;

    int m_darea_width = 0;
    int m_darea_height = 0;

    MainWindow(MyData& my);

    bool darea_on_draw(const CairoContext& cr);
    void repaint_darea();
    bool darea_on_button_press(GdkEventButton* event);
    bool darea_on_motion_notify(GdkEventMotion* event);
    bool darea_on_button_release(GdkEventButton* event);
    void on_shuffle_clicked();
    void on_new_game_clicked();
    void darea_on_size_allocate(Gtk::Allocation& allocation);
};
