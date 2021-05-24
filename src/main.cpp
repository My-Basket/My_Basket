
#include "startwindow.h"
#include <QApplication>
#include <QtGui>
#include <iostream>
#include "algo.h"
#include "for_static.h"
#include "search_engine.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    Ui::StartWindow start_window;
    start_window.show();

    return app.exec();
}