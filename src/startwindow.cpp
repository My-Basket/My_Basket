#include "startwindow.h"
#include <QBrush>
#include <QGridLayout>
#include <QLabel>
#include <QPalette>
#include <QSizePolicy>
#include <iostream>
#include "algo.h"
#include "style_settings.h"

namespace Ui {

void set_font_color_button(QPushButton *button,
                           std::string const &bg_color,
                           int font_size,
                           int enabled,
                           std::string const &font) {
    std::string s = "QPushButton { background-color : " + bg_color +
                    "; color : white; border-width: 5px; border-radius: 10px; "
                    "padding: 6px; font-size: " +
                    std::to_string(font_size) + "px;";
    if (!font.empty()) {
        s += " font: " + font;
    }
    s += "}";
    button->setStyleSheet(s.c_str());

    if (enabled != -1) {
        button->setEnabled(enabled);
    }
}

void set_font_color_label(QLabel *label,
                          std::string const &word_color,
                          int font_size,
                          std::string const &font,
                          std::string const &bg_color) {
    std::string s = "QLabel { color : " + word_color +
                    "; border-width: "
                    "2px; border-radius: 5px; padding: 2px; font-size: " +
                    std::to_string(font_size) + "px";
    if (!font.empty()) {
        s += "; font: " + font + "; ";
    }
    if (!bg_color.empty()) {
        s += "; background-color : " + bg_color + ";";
    }
    s += "}";
    label->setStyleSheet(s.c_str());
}

StartWindow::StartWindow(QWidget *parent) : QWidget(parent) {
    QBrush image_basket_background(
        QImage(StyleSettings::Titles::path_to_bg_image.c_str()));
    QPalette plt = this->palette();
    plt.setBrush(QPalette::Window, image_basket_background);
    this->setPalette(plt);

    start_shopping_button = new QPushButton(
        StyleSettings::Titles::start_shopping_button_title.c_str());
    set_font_color_button(start_shopping_button, "#FF7699", 30, true);
    start_shopping_button->show();

    my_basket_label = new QLabel(StyleSettings::Titles::windows_title.c_str());
    set_font_color_label(my_basket_label, "black", 130, "bold");
    my_basket_label->setAlignment(/*Qt::AlignTop,*/ Qt::AlignCenter);
    my_basket_label->setMargin(50);

    description_label =
        new QLabel(StyleSettings::Titles::description_label_title
                       .c_str());  //ваш помощник в
                                   //выборе рецептов
    set_font_color_label(description_label, "black", 27);
    description_label->setAlignment(/*Qt::AlignTop,*/ Qt::AlignCenter);

    //добавление картинки
    //    QLabel *image_basket_label = new QLabel;
    //    QPixmap image_basket_pixmap("../data/image_basket.jpeg");
    //    image_basket_pixmap.scaled(50, 50);
    //    image_basket_label->setPixmap(image_basket_pixmap);
    //    image_basket_label->setScaledContents(true);

    QVBoxLayout *label_layout = new QVBoxLayout;
    label_layout->addWidget(my_basket_label, Qt::AlignTop, Qt::AlignVCenter);
    label_layout->addWidget(description_label, Qt::AlignTop, Qt::AlignVCenter);
    label_layout->setSpacing(5);

    QVBoxLayout *main_layout = new QVBoxLayout;
    main_layout->addLayout(label_layout);
    main_layout->addWidget(start_shopping_button, Qt::AlignTop,
                           Qt::AlignVCenter);
    main_layout->setSpacing(5);
    // main_layout->addWidget(image_basket_label);

    //переход к recipe_book
    category_window = new CategoryWindow();
    connect(start_shopping_button, SIGNAL(clicked()), this,
            SLOT(go_to_category_window()));

    setLayout(main_layout);
    setWindowTitle(StyleSettings::Titles::windows_title.c_str());

    // this->setFixedSize(1000, 600);
    // this->setMinimumSize(1000, 600);
    this->setMinimumSize(StyleSettings::WindowSizes::min_width_window,
                         StyleSettings::WindowSizes::min_height_window);
}

void StartWindow::go_to_category_window() {
    set_font_color_button(start_shopping_button, "#FF1099", 30, false);

    category_window->show();
    this->close();
}

CategoryWindow::CategoryWindow(QWidget *parent) : QWidget(parent) {
    QBrush image_basket_background(
        QImage(StyleSettings::Titles::path_to_bg_image.c_str()));
    QPalette plt = this->palette();
    plt.setBrush(QPalette::Window, image_basket_background);
    this->setPalette(plt);

    choose_category_label =
        new QLabel(StyleSettings::Titles::choose_category_label_title.c_str());
    set_font_color_label(choose_category_label, "black", 80);
    choose_category_label->setAlignment(/*Qt::AlignTop,*/ Qt::AlignCenter);
    choose_category_label->setMargin(55);

    economy_button =
        new QPushButton(StyleSettings::Titles::economy_button_title.c_str());
    set_font_color_button(economy_button, "#FF7699", 20);
    economy_button->show();

    base_button =
        new QPushButton(StyleSettings::Titles::base_button_title.c_str());
    set_font_color_button(base_button, "#FF7699", 20);
    base_button->show();

    premium_button =
        new QPushButton(StyleSettings::Titles::premium_button_title.c_str());
    set_font_color_button(premium_button, "#FF7699", 20);
    premium_button->show();

    go_to_searching_button =
        new QPushButton(StyleSettings::Titles::go_to_searching_button.c_str());
    set_font_color_button(go_to_searching_button, "#FF9899", 20, false);
    go_to_searching_button->show();

    QHBoxLayout *button_layout = new QHBoxLayout;
    button_layout->addWidget(economy_button, Qt::AlignTop, Qt::AlignVCenter);
    button_layout->addWidget(base_button, Qt::AlignTop, Qt::AlignVCenter);
    button_layout->addWidget(premium_button, Qt::AlignTop, Qt::AlignVCenter);

    QVBoxLayout *main_layout = new QVBoxLayout;
    main_layout->addWidget(choose_category_label, Qt::AlignTop);
    main_layout->addLayout(button_layout);
    main_layout->addWidget(go_to_searching_button, Qt::AlignTop,
                           Qt::AlignVCenter);
    main_layout->setSpacing(10);
    // main_layout->addWidget(image_basket_label);

    //переход к recipe_book
    recipe_book = new RecipeBook();

    connect(economy_button, SIGNAL(clicked()), this, SLOT(choose_economy()));
    connect(base_button, SIGNAL(clicked()), this, SLOT(choose_base()));
    connect(premium_button, SIGNAL(clicked()), this, SLOT(choose_premium()));
    connect(go_to_searching_button, SIGNAL(clicked()), this,
            SLOT(go_to_recipe_book()));

    setLayout(main_layout);
    setWindowTitle(StyleSettings::Titles::windows_title.c_str());

    // this->setFixedSize(1000, 600);
    // this->setMinimumSize(1000, 600);
    this->setMinimumSize(StyleSettings::WindowSizes::min_width_window,
                         StyleSettings::WindowSizes::min_height_window);
}

void CategoryWindow::choose_economy() {
    chosen_category = "economy";

    //обновить цвет других
    set_font_color_button(base_button, "#FF7699", 20, true);
    set_font_color_button(premium_button, "#FF7699", 20, true);

    //установить свой
    set_font_color_button(economy_button, "#FF1099", 20, false);

    set_font_color_button(go_to_searching_button, "#FF7699", 20, true);
}

void CategoryWindow::choose_base() {
    chosen_category = "base";

    set_font_color_button(economy_button, "#FF7699", 20, true);
    set_font_color_button(premium_button, "#FF7699", 20, true);

    set_font_color_button(base_button, "#FF1099", 20, false);

    set_font_color_button(go_to_searching_button, "#FF7699", 20, true);
}

void CategoryWindow::choose_premium() {
    chosen_category = "premium";

    set_font_color_button(economy_button, "#FF7699", 20, true);
    set_font_color_button(base_button, "#FF7699", 20, true);

    set_font_color_button(premium_button, "#FF1099", 20, false);

    set_font_color_button(go_to_searching_button, "#FF7699", 20, true);
}

void CategoryWindow::go_to_recipe_book() {
    set_font_color_button(go_to_searching_button, "#FF1099", 20, false);
    API::ingredients_to_recipe::choose_category_shop(chosen_category);

    recipe_book->show();
    this->close();
}

}  // namespace Ui
