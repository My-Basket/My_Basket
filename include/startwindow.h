#ifndef MY_BASKET_STARTWINDOW_H
#define MY_BASKET_STARTWINDOW_H

#include <QWidget>
#include <QPushButton>
//#include "recipebook.h"

class StartWindow : public QWidget {
Q_OBJECT

public:
    StartWindow(QWidget *parent = nullptr);

private:
    //окна для перехода на следующий этап
    //RecipeBook recipe_book;

    //кнопки окна
    QPushButton *start_button;
};

#endif  // MY_BASKET_STARTWINDOW_H
