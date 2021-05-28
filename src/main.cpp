#include <QApplication>
#include <QtGui>
#include "additional_windows.h"
#include "for_static.h"


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    Ui::StartWindow start_window;
    start_window.show();

    return app.exec();
}