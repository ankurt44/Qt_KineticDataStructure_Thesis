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
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}

