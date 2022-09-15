#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include <QMessageBox>
#include <QCloseEvent>

#include<chrono>
#include <windows.h>
#include <thread>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {

    ui->setupUi(this);

    closing = false;
    QWidget::setWindowTitle ("Плановая перезагрузка ПК");


    this->setStyleSheet("QMainWindow {background-color: rgba(255, 255, 255, 255);}");
    ui->graphicsView->setStyleSheet("background-color:qlineargradient(spread:pad, x1:0.25, y1:0.267045, x2:1, y2:1, stop:0 rgba(254, 69, 69, 255), stop:1 rgba(225, 4, 4, 255));");
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::closeEvent(QCloseEvent *event)
{
    event->ignore();
}





unsigned long uptime() {
    unsigned long tick = GetTickCount() / 1000;
    int dwD = tick / 86400;
    return dwD;
}





void MainWindow::autoClick() {
    std::this_thread::sleep_for(std::chrono::milliseconds(3600000));
    on_waitButton_clicked(false);
}


void newThread(MainWindow *Main) {
    std::thread t1(&MainWindow::autoClick, Main);
    t1.detach();
    t1.~thread();
}





void MainWindow::checkTime() {

while(1){

    if (uptime() >= 10){
        ui->label_days->setText("более 10 дней");
        ui->label_description->setText("Перезагрузите его сейчас или будет произведена\nавтоматическая перезагрузка через 4 часа");
        ui->waitButton->setText("Перезагрузить\nчерез 4 часа");
        this->show();
        this->check = 2;
        newThread(this);
        break;
        }

    if (uptime() >= 7 && check == 0){
        ui->label_days->setText("более 7 дней");
        ui->label_description->setText("Перезагрузите его сейчас или отложите\nперезагрузку на 3 дня");
        this->show();
        this->check = 1;
        newThread(this);
        break;
        }

    Sleep(5000);
    }
}





void MainWindow::on_restartButton_clicked() {
    system("C:\\Windows\\System32\\shutdown /r /t 0");
}


void MainWindow::on_waitButton_clicked(bool checked) {

    if (this->check == 1) {
        this->hide();
        checked = true;
        checkTime();
    }

    if (this->check == 2 && checked == false) {
        system("C:\\Windows\\System32\\shutdown /r /t 14400");
        this->~MainWindow();
    }
}
