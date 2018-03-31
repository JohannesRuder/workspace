//
// Created by hannes on 03.02.18.
//

#include <qapplication.h>  // for QApplication

#include "mainwindow.h"  // for MainWindow

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
