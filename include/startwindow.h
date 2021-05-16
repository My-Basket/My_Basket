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
};

class CategoryWindow : public QWidget {
    Q_OBJECT

public:
    CategoryWindow(QWidget *parent = nullptr);

public slots:
    void go_to_recipe_book();
    void set_chosen_category(/*std::string &category*/);

private:
    RecipeBook *recipe_book;

    QPushButton *economy_button;
    QPushButton *base_button;
    QPushButton *premium_button;
    QPushButton *go_to_searching_button;
};
}  // namespace Ui

#endif  // MY_BASKET_STARTWINDOW_H
