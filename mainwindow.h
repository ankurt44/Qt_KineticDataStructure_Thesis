#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QThread>
#include <QHBoxLayout>
#include <QGroupBox>

#include "renderarea.h"
#include "inputwidget.h"
#include "input.h"
#include "simulation.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void start();
    void stop();
    void render();
    void openGraphWin();

signals:
    void startDrawing();

private:
    Ui::MainWindow *ui;

    void createUI();
    void appearance();
    void connectSignalSlot();

    RenderArea* render_area;
    InputWidget* input_widget;

    GraphWindow* graph_win;

    QGroupBox* h_group_box;
    QHBoxLayout* controls_layout;
    QPushButton* btn_play;
    QPushButton* btn_open_graph;
    QPushButton* btn_stop;
    QLabel* lbl_status;

    bool is_running;
    Input* input;
    Simulation* simulation;
    QThread* thread;
};

#endif // MAINWINDOW_H
