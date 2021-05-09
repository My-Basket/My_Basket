#include "startwindow.h"
#include <QGridLayout>

StartWindow::StartWindow(QWidget *parent) : QWidget(parent) {
    start_button = new QPushButton(tr("start shopping!"));
    start_button->show();

    QGridLayout *main_layout = new QGridLayout;
    main_layout->addWidget(start_button);

    setLayout(main_layout);
    setWindowTitle(tr("My_Basket"));
}
