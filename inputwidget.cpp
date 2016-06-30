#include <cmath>
#include <QGridLayout>

#include "inputwidget.h"
#include "tools.h"
#include "algorithm.h"
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
        float _x = (float) Tools::randomnum(100, 800);
        float _y = (float) Tools::randomnum(100, 600);

        input.nodes.push_back(Node(Vector2f(_x, _y), velocity_max));
        //TODO : check if a node is created with same x and y
    }

    input.setSource(Tools::randomnum(0, input.nodes.size()-1));

    //add algorithms
    input.algos.push_back(new AlgBroadcastDirect);
}

void InputWidget::createUI()
{
    lbl_num = new QLabel("#nodes", this);
    txt_num = new QLineEdit(this);
    lbl_interval = new QLabel("Interval Length", this);
    txt_interval = new QLineEdit(this);
    lbl_velocity = new QLabel("Max Velocity", this);
    txt_velocity = new QLineEdit(this);

    QGridLayout* g_layout = new QGridLayout;
    this->setLayout(g_layout);

    g_layout->addWidget(lbl_num, 0, 0, Qt::AlignLeft);
    g_layout->addWidget(txt_num, 0, 1, Qt::AlignLeft);
    g_layout->addWidget(lbl_interval, 1, 0, Qt::AlignLeft);
    g_layout->addWidget(txt_interval, 1, 1, Qt::AlignLeft);
    g_layout->addWidget(lbl_velocity, 2, 0, Qt::AlignLeft);
    g_layout->addWidget(txt_velocity, 2, 1, Qt::AlignLeft);

}

void InputWidget::appearance(float r, float g, float b, float a)
{
    this->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);

    this->setFixedSize(200, 300);

    QPalette pal(palette());
    pal.setColor(QPalette::Background, QColor(r, g, b, a));
    this->setAutoFillBackground(true);
    this->setPalette(pal);
}

