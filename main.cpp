/*
 * Author: Aleksandr Voronkov
 * Designer: Dmitriy Malishev
 */


#include "mainwindow.h"
#include <QFile>
#include <QApplication>
#include <thread>

int start;



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowFlags(Qt::Window
                     |Qt::WindowStaysOnTopHint
                     |Qt::FramelessWindowHint);
    std::chrono::system_clock::time_point now = std::chrono::high_resolution_clock::now();
    auto epoch = now.time_since_epoch();
    auto seconds = std::chrono::duration_cast<std::chrono::seconds>(epoch);
    start = seconds.count();



    w.checkTime();

    return a.exec();
}



