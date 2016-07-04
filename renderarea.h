#ifndef RENDERAREA
#define RENDERAREA

#include <iostream>
#include <QWidget>
#include <QPainter>
#include <QBrush>
#include <QPen>
#include <QFont>
#include <vector>

#include "input.h"

class RenderArea : public QWidget
{

public:
    RenderArea(QWidget* parent = 0);

    void render(const Input* input);

private:
    void createUI();
    void appearance(int r, int g, int b, int a);

    void paintNode(QPainter *painter, QPaintEvent *event, Node& node);
    void testPaint(QPainter* painter, QPaintEvent *event);
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;


    vector<Node> nodes;
    const Input* input;
    QBrush* brush;
    QPen* pen;
    QFont* font;
};

#endif // RENDERAREA

