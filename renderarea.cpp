#include <QPushButton>

#include "renderarea.h"
#include "algorithm.h"


RenderArea::RenderArea(QWidget* parent)
    : QWidget(parent)
{
    //input = new Input;
    nodes = vector<Node>();

    createUI();
    appearance(125, 200, 190, 180);
}

void RenderArea::createUI()
{
}

void RenderArea::appearance(int r, int g, int b, int a)
{
    QPalette pal(palette());
    pal.setColor(QPalette::Background, QColor(r, g, b, a));
    this->setAutoFillBackground(true);
    this->setPalette(pal);
}

void RenderArea::render(const Input* input)
{
    //input = input;
    nodes = input->nodes;
    update();
}

void RenderArea::paintEvent(QPaintEvent *event)
{
    QPainter* painter = new QPainter;
    painter->begin(this);
    painter->setRenderHint(QPainter::Antialiasing);

    for(Node& node : nodes)
    {
        paintNode(painter, event, node);
    }
    //testPaint(painter, event);    //to test halfplane intersections and voronoi diagrams
    painter->end();
}

void RenderArea::paintNode(QPainter *painter, QPaintEvent *event, Node& node)
{
    painter->setPen(QPen(QBrush(Qt::red), 5));
    painter->setBrush(QBrush(Qt::red));
    painter->drawPoint(node.pos.x, node.pos.y);

    painter->setPen(QPen(QBrush(Qt::green), 2));
    painter->setBrush(Qt::NoBrush);
    int  range = node.getRange();
    //painter->drawEllipse(QPoint(node.pos.x, node.pos.y), range, range); //ToDo : center and radius are not accurate (not in float)

    for(Node* n: node.children)
        painter->drawLine(node.pos.x, node.pos.y, n->pos.x, n->pos.y);

}

void RenderArea::testPaint(QPainter* painter, QPaintEvent *event)
{
    //painter->drawPoint(node.pos.x, node.pos.y);
    //painter->drawLine(node.x, node.y, 200, 200);

    Node node1(Vector2f(200, 200));
    Node node2(Vector2f(300, 300));
    Node node3(Vector2f(600, 400));
    Node node4(Vector2f(950, 500));
    Node node14(Vector2f(150, 670));
    Node node5(Vector2f(50, 50));
    Node node6(Vector2f(300, 200));
    Node node7(Vector2f(150, 550));
    Node node8(Vector2f(250, 50));
    Node node9(Vector2f(850, 150));
    Node node10(Vector2f(900, 550));
    vector<Node> nodes;
    nodes.push_back(node1);
    nodes.push_back(node2);
    nodes.push_back(node3);
    nodes.push_back(node4);
    nodes.push_back(node5);
    nodes.push_back(node6);
    nodes.push_back(node7);
    nodes.push_back(node8);
    nodes.push_back(node9);
    nodes.push_back(node10);
    nodes.push_back(node14);

    Algorithm::voronoiDiagram(nodes);

    painter->setPen(QPen(QBrush(Qt::red), 4));
    painter->setBrush(QBrush(Qt::red));

    for(Node n : nodes)
    {
        painter->drawPoint(n.pos.x, n.pos.y);
        VoronoiCell c1 = n.cell;
        for(auto it = c1.left.begin(); it != c1.left.end()-1; it++)
        {
            painter->drawLine(it->x, it->y, (it+1)->x, (it+1)->y);
        }
        for(auto it = c1.right.begin(); it != c1.right.end()-1; it++)
        {
            painter->drawLine(it->x, it->y, (it+1)->x, (it+1)->y);
        }
    }


}


/////commented out section///
/*
VoronoiCell c1;
c1.left.push_back(Vector2f(220, 100));
c1.left.push_back(Vector2f(120, 200));
c1.left.push_back(Vector2f(250, 300));
c1.right.push_back(Vector2f(220, 100));
c1.right.push_back(Vector2f(300, 240));
c1.right.push_back(Vector2f(250, 300));
VoronoiCell c2;
c2.left.push_back(Vector2f(260, 50));
c2.left.push_back(Vector2f(200, 150));
c2.left.push_back(Vector2f(200, 310));
c2.right.push_back(Vector2f(260, 50));
c2.right.push_back(Vector2f(400, 220));
c2.right.push_back(Vector2f(200, 310));
*/

/*
VoronoiCell c3;
c3.left.push_back(Vector2f(600, 140));
c3.left.push_back(Vector2f(10, 140));
c3.left.push_back(Vector2f(10, 200));
c3.right.push_back(Vector2f(600, 140));
c3.right.push_back(Vector2f(600, 200));
c3.right.push_back(Vector2f(10, 200));
VoronoiCell c4;
c4.left.push_back(Vector2f(600, 140));
c4.left.push_back(Vector2f(150, 140));
c4.left.push_back(Vector2f(100, 200));
c4.right.push_back(Vector2f(600, 140));
c4.right.push_back(Vector2f(600, 200));
c4.right.push_back(Vector2f(100, 200));
*/

//voronoi cell for single node w.r.t two other nodes
/*
painter->setPen(QPen(QBrush(Qt::red), 5));
painter->setBrush(QBrush(Qt::red));

Node node1(Vector2f(100, 300));
Node node2(Vector2f(300, 600));
painter->drawPoint(node1.pos.x, node1.pos.y);

VoronoiCell c1 = Algorithm::getHalfPlane(node1, node2);


painter->drawPoint(node2.pos.x, node2.pos.y);

for(auto it = c1.left.begin(); it != c1.left.end()-1; it++)
{
    painter->drawLine(it->x, it->y, (it+1)->x, (it+1)->y);
}
painter->setPen(QPen(QBrush(Qt::red), 5));
painter->setBrush(QBrush(Qt::red));
for(auto it = c1.right.begin(); it != c1.right.end()-1; it++)
{
    painter->drawLine(it->x, it->y, (it+1)->x, (it+1)->y);
}


Node node3(Vector2f(500, 400));
VoronoiCell c2 = Algorithm::getHalfPlane(node1, node3);

//painter->drawPoint(node1.pos.x, node1.pos.y);
painter->drawPoint(node3.pos.x, node3.pos.y);

painter->setPen(QPen(QBrush(Qt::yellow), 3));
painter->setBrush(QBrush(Qt::yellow));
for(auto it = c2.left.begin(); it != c2.left.end()-1; it++)
{
    painter->drawLine(it->x, it->y, (it+1)->x, (it+1)->y);
}
painter->setPen(QPen(QBrush(Qt::blue), 3));
painter->setBrush(QBrush(Qt::blue));
for(auto it = c2.right.begin(); it != c2.right.end()-1; it++)
{
    painter->drawLine(it->x, it->y, (it+1)->x, (it+1)->y);
}
VoronoiCell* cell;
Algorithm::halfPlaneIntersection(c1, c2, cell);

painter->setPen(QPen(QBrush(Qt::green), 8));
painter->setBrush(QBrush(Qt::green));

for(auto it = cell->left.begin(); it != cell->left.end()-1; it++)
{
    painter->drawLine(it->x, it->y, (it+1)->x, (it+1)->y);
}
for(auto it = cell->right.begin(); it != cell->right.end()-1; it++)
{
    painter->drawLine(it->x, it->y, (it+1)->x, (it+1)->y);
}
*/

/*
painter->setPen(QPen(QBrush(Qt::blue), 3));
painter->setBrush(QBrush(Qt::blue));
for(auto it = c2.left.begin(); it != c2.left.end()-1; it++)
{
    painter->drawLine(it->x, it->y, (it+1)->x, (it+1)->y);
}
for(auto it = c2.right.begin(); it != c2.right.end()-1; it++)
{
    painter->drawLine(it->x, it->y, (it+1)->x, (it+1)->y);
}

VoronoiCell* cell;
Algorithm::halfPlaneIntersection(c1, c2, cell);

painter->setPen(QPen(QBrush(Qt::green), 1));
painter->setBrush(QBrush(Qt::green));

for(auto it = cell->left.begin(); it != cell->left.end()-1; it++)
{
    painter->drawLine(it->x, it->y, (it+1)->x, (it+1)->y);
}
for(auto it = cell->right.begin(); it != cell->right.end()-1; it++)
{
    painter->drawLine(it->x, it->y, (it+1)->x, (it+1)->y);
}
*/

