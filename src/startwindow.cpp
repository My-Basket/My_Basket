#include "startwindow.h"
#include <QGridLayout>

StartWindow::StartWindow(QWidget *parent) : QWidget(parent) {
    start_button = new QPushButton(tr("start shopping!"));
    start_button->show();

    QGridLayout *main_layout = new QGridLayout;
    main_layout->addWidget(start_button);

    recipe_book = new RecipeBook();
    connect(start_button, SIGNAL(clicked()), this, SLOT(go_to_recipe_book()));

    setLayout(main_layout);
    setWindowTitle(tr("My_Basket"));
}

void StartWindow::go_to_recipe_book() {
    recipe_book->show();
    this->close();
}
