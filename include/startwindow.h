#ifndef MY_BASKET_STARTWINDOW_H
#define MY_BASKET_STARTWINDOW_H

#include "recipebook.h"

namespace Ui {

class CategoryWindow;

class StartWindow : public QWidget {
    Q_OBJECT

public:
    StartWindow(QWidget *parent = nullptr);

public slots:
    void go_to_category_window();

private:
    //окна для перехода на следующий этап
    CategoryWindow *category_window;

    //кнопки окна
    QPushButton *start_button;
    QLabel *my_basket_label;
    QLabel *description_label;
};

class CategoryWindow : public QWidget {
    Q_OBJECT

public:
    CategoryWindow(QWidget *parent = nullptr);

public slots:
    void go_to_recipe_book();
    // void set_chosen_category(/*std::string &category*/);
    void choose_economy();
    void choose_base();
    void choose_premium();

private:
    RecipeBook *recipe_book;

    QPushButton *economy_button;
    QPushButton *base_button;
    QPushButton *premium_button;
    QPushButton *go_to_searching_button;
    QLabel *choose_category_label;

    std::string chosen_category;
};

void set_font_color_button(QPushButton *button,
                           std::string const &bg_color,
                           int font_size = 20,
                           int enabled = -1,
                           std::string const &font = "");
}  // namespace Ui

#endif  // MY_BASKET_STARTWINDOW_H
