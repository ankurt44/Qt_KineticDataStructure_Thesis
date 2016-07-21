#include <cmath>
#include <QGridLayout>
#include <QGroupBox>

#include "inputwidget.h"
#include "tools.h"
#include "algorithm.h"
#include "algbroadcastinterpolate.h"
#include "algbroadcastdirect.h"

InputWidget::InputWidget(QWidget* parent) : QWidget(parent)
{
    createUI();
    appearance(125, 125, 125, 100);
}

void InputWidget::createInput(Input& input)
{
    int num = txt_num->text().toInt();
    float interval_length = txt_interval->text().toInt();
    float velocity_max = txt_velocity->text().toInt();

    vector<Node>* nodes = new vector<Node>;
    nodes->reserve(num);

    //fast calculation which gives same  seed (time(0))
    unsigned long seed = time(0); //TODO : not used

    input.nodes.reserve(num);
    input.interval_length = interval_length;

    for(int i = 0; i < num; i++)
    {
        float _xt = (float) Tools::randomnum(100, 800);
        float _yt = (float) Tools::randomnum(100, 600);

        float _xt1 = (float) Tools::randomnum(100, 800);
        float _yt1 = (float) Tools::randomnum(100, 600);

        input.nodes.push_back(Node(Vector2f(_xt, _yt), Vector2f(_xt1, _yt1), velocity_max));
        //TODO : check if a node is created with same x and y
        //ToDo : randomly assign velocity in the start [0, vmax]
    }

    input.setSource(Tools::randomnum(0, input.nodes.size()-1));

    //add movement model
    input.direction_factor = txt_direction->text().toInt();
    input.nextRandomPosition = Tools::nextAvailablePosition;

    //add algorithms
    input.algos.push_back(new AlgBroadcastInterpolate);
    input.selected_alg = NORMAL_INTERPOLATION;
    input.algos.push_back(new AlgBroadcastDirect);
}

void InputWidget::createUI()
{

    QGridLayout* g_layout = new QGridLayout;
    this->setLayout(g_layout);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QGroupBox* grp_nodes_property = new QGroupBox;
    grp_nodes_property->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    QGridLayout* layout_grid_nodes = new QGridLayout;
    lbl_num = new QLabel("#nodes", this);
    txt_num = new QLineEdit(this);
    lbl_interval = new QLabel("Interval Length", this);
    txt_interval = new QLineEdit(this);
    lbl_velocity = new QLabel("Max Velocity", this);
    txt_velocity = new QLineEdit(this);
    layout_grid_nodes->addWidget(lbl_num, 0,0);
    layout_grid_nodes->addWidget(txt_num, 0,1);
    layout_grid_nodes->addWidget(lbl_interval, 2,0);
    layout_grid_nodes->addWidget(txt_interval, 2,1);
    layout_grid_nodes->addWidget(lbl_velocity, 3,0);
    layout_grid_nodes->addWidget(txt_velocity, 3,1);
    grp_nodes_property->setLayout(layout_grid_nodes);

    /*
    g_layout->addWidget(lbl_num, 0, 0, Qt::AlignLeft);
    g_layout->addWidget(txt_num, 0, 1, Qt::AlignLeft);
    g_layout->addWidget(lbl_interval, 1, 0, Qt::AlignLeft);
    g_layout->addWidget(txt_interval, 1, 1, Qt::AlignLeft);
    g_layout->addWidget(lbl_velocity, 2, 0, Qt::AlignLeft);
    g_layout->addWidget(txt_velocity, 2, 1, Qt::AlignLeft);
    */

    //ToDo : create QValidator for the controls
    QGroupBox* grp_movement_model = new QGroupBox;
    grp_movement_model->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    QGridLayout* layout_grid = new QGridLayout;
    QLabel* lbl_movement_model = new QLabel("Movement model");
    lbl_movement_model->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    QLabel* lbl_direction = new QLabel("Direction factor");
    lbl_direction->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    txt_direction = new QLineEdit;
    QLabel* lbl_speed = new QLabel("Speed factor");
    lbl_speed->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    txt_speed = new QLineEdit;
    layout_grid->addWidget(lbl_movement_model,0,0,1,2,Qt::AlignCenter);
    layout_grid->addWidget(lbl_direction,2,0,1,1,Qt::AlignCenter);
    layout_grid->addWidget(txt_direction,2,1,1,1,Qt::AlignCenter);
    layout_grid->addWidget(lbl_speed,3,0,1,1,Qt::AlignCenter);
    layout_grid->addWidget(txt_speed,3,1,1,1,Qt::AlignCenter);
    grp_movement_model->setLayout(layout_grid);

    g_layout->addWidget(grp_nodes_property, 0, 1,1,10);
    g_layout->addWidget(grp_movement_model, 0,11,1,10);

}

void InputWidget::appearance(float r, float g, float b, float a)
{
    this->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);

    //this->setFixedSize(600, 300);

    QPalette pal(palette());
    pal.setColor(QPalette::Background, QColor(r, g, b, a));
    this->setAutoFillBackground(true);
    this->setPalette(pal);
}

