#include "mainwindow.h"
#include <QApplication>

#include <iostream>

#include "tools.h"
#include "voronoicell.h"
#include "algorithm.h"

void test();

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}


void test()
{
    vector<Vector2f> vec;
    vec.push_back(Vector2f(5000, -4700));
    vec.push_back(Vector2f(-4700, 5000));
    vec.push_back(Vector2f(5000, 5000));

    sort(vec.begin(), vec.end());

    Node node1(Vector2f(20,20));
    Node node2(Vector2f(10,10));
    Node node3(Vector2f(-10,-10));
    Node node4(Vector2f(20,30));

    vector<Node> nodes;
    nodes.reserve(4);
    nodes.push_back(node1);
    nodes.push_back(node2);
    nodes.push_back(node3);
    nodes.push_back(node4);

    //Algorithm::broadcastTree(nodes, 1);
}
