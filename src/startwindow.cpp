#include "startwindow.h"
#include <QBrush>
#include <QGridLayout>
#include <QLabel>
#include <QPalette>
#include <QSizePolicy>

StartWindow::StartWindow(QWidget *parent) : QWidget(parent) {
    start_button = new QPushButton(tr("start shopping!"));
    start_button->show();

    //добавление картинки
    //    QLabel *image_basket_label = new QLabel;
    //    QPixmap image_basket_pixmap("../data/image_basket.jpeg");
    //    image_basket_pixmap.scaled(50, 50);
    //    image_basket_label->setPixmap(image_basket_pixmap);
    //    image_basket_label->setScaledContents(true);

    QBrush image_basket_background(QImage("../data/image_basket.jpeg"));
    QPalette plt = this->palette();
    plt.setBrush(QPalette::Window, image_basket_background);
    this->setPalette(plt);

    QHBoxLayout *main_layout = new QHBoxLayout;
    main_layout->addWidget(start_button);
    // main_layout->addWidget(image_basket_label);

    //переход к recipe_book
    recipe_book = new RecipeBook();
    connect(start_button, SIGNAL(clicked()), this, SLOT(go_to_recipe_book()));

    setLayout(main_layout);
    setWindowTitle(tr("My_Basket"));

    this->setFixedSize(1000, 600);
}

void StartWindow::go_to_recipe_book() {
    recipe_book->show();
    this->close();
}
