#ifndef INPUTWIDGET
#define INPUTWIDGET

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>

#include "input.h"

class InputWidget : public QWidget
{
public:
    Q_OBJECT

public:
    InputWidget(QWidget* parent = 0);
public slots:
    void createInput(Input& input);

private:

    void createNodes(Input* input, int num, float velocity_max);
    void createUI();
    void appearance(float r, float g, float b, float a);

    //CONTROLS
    //number of nodes
    QLabel* lbl_num;
    QLineEdit* txt_num;
    //time interval
    QLabel* lbl_interval;
    QLineEdit* txt_interval;
    //max velocity
    QLabel* lbl_velocity;
    QLineEdit* txt_velocity;

    //movement model
    QLineEdit* txt_direction;
    QLineEdit* txt_speed;

};

#endif // INPUTWIDGET

