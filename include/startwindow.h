#ifndef MY_BASKET_STARTWINDOW_H
#define MY_BASKET_STARTWINDOW_H

#include <QPushButton>
#include <QWidget>
#include "recipebook.h"

class StartWindow : public QWidget {
    Q_OBJECT

public:
    StartWindow(QWidget *parent = nullptr);

public slots:
    void go_to_recipe_book();

private:
    //окна для перехода на следующий этап
    RecipeBook *recipe_book;

    //кнопки окна
    QPushButton *start_button;
};

#endif  // MY_BASKET_STARTWINDOW_H
