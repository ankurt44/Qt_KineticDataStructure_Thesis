#include <QGridLayout>

#include "mainwindow.h"
#include "constants.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    srand(time(0));

    createUI();
    appearance();

    connect(btn_play, SIGNAL(clicked(bool)), this, SLOT(start()));
}

//starting point of the simulation
//  create input from input widget
//  start simulation in different thread and pass pointer to the create input
void MainWindow::start()
{
    if(is_running)
    {
        lbl_status->setText("Already running. Press stop to stop");
        return;
    }
    lbl_status->setText("Running");
    is_running = true;

    //create input from input widget
    input = new Input();
    input_widget->createInput(*input);

    //start simulation
    //pass input to the simulation thread
    cout << "thread 1" << endl;
    simulation = new Simulation(input);
    thread = new QThread();
    simulation->moveToThread(thread);

    cout << "thread 2" << endl;

    connectSignalSlot();

    thread->start();
    cout << "thread 3" << endl;

}

//connect logics for simulation thread and main thread
void MainWindow::connectSignalSlot()
{
    connect(thread, SIGNAL(started()), simulation, SLOT(start()));
    connect(simulation, SIGNAL(finished()), thread, SLOT(quit()));
    connect(simulation, SIGNAL(finished()), thread, SLOT(deleteLater()));
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    connect(btn_stop, SIGNAL(clicked(bool)), simulation, SLOT(stop()));
    connect(simulation, SIGNAL(finished()), this, SLOT(stop()));
    //simulation should wait until rendering is completed : Qt::BlockingQueuedConnection
    connect(simulation, SIGNAL(render()), this, SLOT(render()), Qt::BlockingQueuedConnection);
}

//ask render widget to render simulation state
void MainWindow::render()
{
    render_area->render(input);
}

//set running flag to false
void MainWindow::stop()
{
    //thread->terminate();

    is_running = false;

    lbl_status->setText("Stopped. Click Play to start simulation.");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createUI()
{
    QWidget* central_widget = new QWidget;
    QGridLayout* g_layout = new QGridLayout;
    central_widget->setLayout(g_layout);

    //initialize component components
    render_area = new RenderArea(this);
    render_area->setFixedSize(WIDTH - 2 * MARGIN, HEIGHT - 2 * MARGIN);
    input_widget = new InputWidget();
    btn_play = new QPushButton("Play");
    btn_stop = new QPushButton("Stop");
    lbl_status = new QLabel("Click Play to run");
    //add components to layout
    g_layout->addWidget(render_area, 0, 0, Qt::AlignCenter);
    g_layout->addWidget(input_widget, 1, 0, Qt::AlignLeft);
    g_layout->addWidget(btn_play, 2, 0, Qt::AlignLeft);
    g_layout->addWidget(btn_stop, 2, 0, Qt::AlignRight);
    g_layout->addWidget(lbl_status, 2, 0, Qt::AlignCenter);


    this->setCentralWidget(central_widget);
}

void MainWindow::appearance()
{
    setFixedSize(WIDTH, HEIGHT);
}