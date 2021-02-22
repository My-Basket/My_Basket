//
// Created by nikolya on 22.02.2021.
//

#ifndef MY_BASKET_MAINWINDOW_H
#define MY_BASKET_MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow() override;

private:
    Ui::MainWindow *ui;
};

#endif //MY_BASKET_MAINWINDOW_H
