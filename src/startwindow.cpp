#include "startwindow.h"
#include <QBrush>
#include <QGridLayout>
#include <QLabel>
#include <QPalette>
#include <QSizePolicy>

namespace Ui {
StartWindow::StartWindow(QWidget *parent) : QWidget(parent) {
    start_button = new QPushButton(tr("start shopping!"));
    start_button->setStyleSheet(
        "QPushButton { background-color : #FF7699; color : white; "
        "border-width: "
        "5px; border-radius: 10px; padding: 6px;}");
    start_button->show();  // 522030

    //добавление картинки
    //    QLabel *image_basket_label = new QLabel;
    //    QPixmap image_basket_pixmap("../data/image_basket.jpeg");
    //    image_basket_pixmap.scaled(50, 50);
    //    image_basket_label->setPixmap(image_basket_pixmap);
    //    image_basket_label->setScaledContents(true);

    QBrush image_basket_background(QImage("../data/image_basket2.jpg"));
    QPalette plt = this->palette();
    plt.setBrush(QPalette::Window, image_basket_background);
    this->setPalette(plt);

    QHBoxLayout *main_layout = new QHBoxLayout;
    main_layout->addWidget(start_button);
    // main_layout->addWidget(image_basket_label);

    //переход к recipe_book
    category_window = new CategoryWindow();
    connect(start_button, SIGNAL(clicked()), this,
            SLOT(go_to_category_window()));

    setLayout(main_layout);
    setWindowTitle(tr("My_Basket"));

    this->setFixedSize(1000, 600);
}

void StartWindow::go_to_category_window() {
    category_window->show();
    this->close();
}

CategoryWindow::CategoryWindow(QWidget *parent) : QWidget(parent) {
    QBrush image_basket_background(QImage("../data/image_basket2.jpg"));
    QPalette plt = this->palette();
    plt.setBrush(QPalette::Window, image_basket_background);
    this->setPalette(plt);

    economy_button = new QPushButton(tr("economy"));
    economy_button->setStyleSheet(
        "QPushButton { background-color : #FF7699; color : white; "
        "border-width: "
        "5px; border-radius: 10px; padding: 6px;}");
    economy_button->show();  // 522030

    base_button = new QPushButton(tr("base"));
    base_button->setStyleSheet(
        "QPushButton { background-color : #FF7699; color : white; "
        "border-width: "
        "5px; border-radius: 10px; padding: 6px;}");
    base_button->show();  // 522030

    premium_button = new QPushButton(tr("premium"));
    premium_button->setStyleSheet(
        "QPushButton { background-color : #FF7699; color : white; "
        "border-width: "
        "5px; border-radius: 10px; padding: 6px;}");
    premium_button->show();  // 522030

    go_to_searching_button = new QPushButton(tr("go to searching!"));
    go_to_searching_button->setStyleSheet(
        "QPushButton { background-color : #FF7699; color : white; "
        "border-width: "
        "5px; border-radius: 10px; padding: 6px;}");
    go_to_searching_button->show();  // 522030

    QHBoxLayout *main_layout = new QHBoxLayout;
    main_layout->addWidget(economy_button);
    main_layout->addWidget(base_button);
    main_layout->addWidget(premium_button);
    main_layout->addWidget(go_to_searching_button);
    // main_layout->addWidget(image_basket_label);

    //переход к recipe_book
    recipe_book = new RecipeBook();
    connect(go_to_searching_button, SIGNAL(clicked()), this,
            SLOT(go_to_recipe_book()));
    connect(economy_button, SIGNAL(clicked()), this,
            SLOT(set_chosen_category("economy")));
    connect(base_button, SIGNAL(clicked()), this,
            SLOT(set_chosen_category("base")));
    connect(premium_button, SIGNAL(clicked()), this,
            SLOT(set_chosen_category("premium")));

    setLayout(main_layout);
    setWindowTitle(tr("My_Basket"));

    this->setFixedSize(1000, 600);
}

void CategoryWindow::set_chosen_category(std::string &category) {
    chosen_category = category;
}

void CategoryWindow::go_to_recipe_book() {
    recipe_book->show();
    this->close();
}

}  // namespace Ui
