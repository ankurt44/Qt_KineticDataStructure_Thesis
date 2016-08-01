#include "mainwindow.h"
#include <QApplication>

#include <iostream>
#include <vector>

#include "tools.h"
#include "voronoicell.h"
#include "algorithm.h"
#include "constants.h"

int main(int argc, char *argv[])
{

    Vector2f c(5,5);
    Vector2f to(10,10);
    float d = 90;
    float r = 5;
    Vector2f mid = Tools::pointOnLineSegmentInGivenDirection(c, to, r);
    Vector2f a1 = Tools::rotateAbout(c,Tools::toRadian(d/2),mid);
    Vector2f a2 = Tools::rotateAbout(c,-Tools::toRadian(d/2),mid);
    cout << Tools::inArc(c,mid,r,100,a1) << endl;
    cout << Tools::inArc(c,mid,r,100,a2) << endl;
    cout << Tools::inArc(c,mid,r,100,mid) << endl;
    cout << Tools::inArc(c,mid,r,100,Vector2f(7.2,7.2))<<endl;
    cout << Tools::inArc(c,mid,r,100,Vector2f(4,4))<<endl;

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}

