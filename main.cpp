#include "mainwindow.h"
#include <QApplication>

#include <iostream>
#include <vector>

#include "tools.h"
#include "voronoicell.h"
#include "algorithm.h"

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}

/*
 *    vector<int> av;
    av.push_back(1);
    av.push_back(2);
    av.push_back(3);

    vector<int> bv;
    av.push_back(8);
    av.push_back(6);
    av.push_back(4);

    vector<int> res = av;
    res.insert(res.begin(),bv.begin(), bv.end());

    for(int i : res)
        cout << i << "-";
    cout << endl;
 */
