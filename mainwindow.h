#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
//int start;
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void checkTime();
    void autoClick();
    int check = 0;


private:
    Ui::MainWindow *ui;
    bool closing;


protected:
    void closeEvent(QCloseEvent *event) override;
private slots:
    void on_restartButton_clicked();
    void on_waitButton_clicked(bool checked);
};
#endif // MAINWINDOW_H

