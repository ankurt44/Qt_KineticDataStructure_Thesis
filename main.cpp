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

    /*
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

    cout << Tools::angleBetweenVectorsInDegree(Vector2f(4,2), Vector2f(3,3));


    Vector2f res = Tools::rotateAbout(Vector2f(0,0), 45*PI/180, Vector2f(3,3));
    cout << res << endl;
     res = Tools::rotateAbout(Vector2f(0,0), -45*PI/180, Vector2f(3,3)) ;
    cout << res << endl;
    res = Tools::rotateAbout(Vector2f(1,1), -45*PI/180, Vector2f(2,1));
   cout << res << endl;
   res = Tools::rotateAbout(Vector2f(1,1), 45*PI/180, Vector2f(2,1));
  cout << res << endl;
  res = Tools::rotateAbout(Vector2f(1,1), -180*PI/180, Vector2f(2,1));
 cout << res << endl;
 res = Tools::rotateAbout(Vector2f(1,1), 180*PI/180, Vector2f(2,1));
cout << res << endl;

    cout << Tools::angleBetweenVectorsInDegree(Vector2f(2,3), Vector2f(4,4));
    */

    /*
    vector<Vector2f> hull;
    hull.push_back(Vector2f(5000, 85.8009));
    hull.push_back(Vector2f(869.824, 198.063));
    hull.push_back(Vector2f(-5000, 2540.76));
    hull.push_back(Vector2f(-5000, 5000));
    hull.push_back(Vector2f(5000, 5000));
    hull.push_back(Vector2f(5000, 85.8009));

    cout << Tools::ifPointInsideConvexHull(hull, Vector2f(495.704, 439.816));

    vector<Vector2f> hull1;
    hull1.push_back(Vector2f(869.824, 198.063));
    hull1.push_back(Vector2f(-5000, 357.61));
    hull1.push_back(Vector2f(-5000, 5000));
    hull1.push_back(Vector2f(5000, 5000));
    hull1.push_back(Vector2f(5000, 2259.33));
    hull1.push_back(Vector2f(869.824, 198.063));

    cout << Tools::ifPointInsideConvexHull(hull1, Vector2f(495.704, 439.816));
    */

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}

