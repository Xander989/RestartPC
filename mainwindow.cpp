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
#include "iostream"
#include <QFontDatabase>
extern int start;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {

    ui->setupUi(this);

    closing = false;
    QWidget::setWindowTitle ("Плановая перезагрузка ПК");

    QFontDatabase::addApplicationFont(":/fonts/Roboto-Regular.ttf");
    QFontDatabase::addApplicationFont(":/fonts/Roboto-Bold.ttf");
    QFontDatabase::addApplicationFont(":/fonts/Roboto-Medium.ttf");

        QFont Roboto1("Roboto", 12, QFont::Bold);
        QFont Roboto2("Roboto", 18, QFont::Bold);
        QFont Roboto3("Roboto", 28, QFont::Bold);
        QFont Roboto4("Roboto", 12, QFont::Normal);
        QFont Roboto5("Roboto", 12, QFont::Medium);

        ui->label_static_2->setFont(Roboto1);
        ui->label_static->setFont(Roboto2);
        ui->label_days->setFont(Roboto3);
        ui->label_description->setFont(Roboto4);
        ui->waitButton->setFont(Roboto5);
        ui->restartButton->setFont(Roboto5);

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
    std::chrono::system_clock::time_point now = std::chrono::high_resolution_clock::now();
    auto epoch = now.time_since_epoch();
    auto seconds = std::chrono::duration_cast<std::chrono::seconds>(epoch);
    int stop = seconds.count();
    int duration = stop - start;
    int dwD = duration / 86400;
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
