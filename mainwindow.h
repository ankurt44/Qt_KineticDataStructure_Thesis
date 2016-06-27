#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QThread>

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

private:
    Ui::MainWindow *ui;

    void createUI();
    void appearance();
    void connectSignalSlot();

    RenderArea* render_area;
    InputWidget* input_widget;
    QPushButton* btn_play;
    QPushButton* btn_stop;
    QLabel* lbl_status;

    bool is_running;
    Input* input;
    Simulation* simulation;
    QThread* thread;
};

#endif // MAINWINDOW_H
