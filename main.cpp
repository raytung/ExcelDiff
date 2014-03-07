#include "mainwindow.h"
#include <QApplication>
#include <iostream>
#include "ExcelDiff.hpp"

int main(int argc, char *argv[])
{

    const char *dir_one = "C:\\Users\\rt23389\\Desktop\\10gnew\\";
    const char *dir_two = "C:\\Users\\rt23389\\Desktop\\11gnew\\";

   // ExcelDiff xD (dir_one, dir_two);
    //xD.run();

    QApplication a(argc, argv);
    MainWindow w;

    w.mainWindow->show();

    return a.exec();
}

