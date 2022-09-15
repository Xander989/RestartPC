/*
 * Author: Aleksandr Voronkov
 * Designer: Dmitriy Malishev
 */


#include "mainwindow.h"

#include <QApplication>
#include <thread>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowFlags(Qt::Window
                     |Qt::WindowStaysOnTopHint
                     |Qt::FramelessWindowHint);
    w.checkTime();

    return a.exec();
}



