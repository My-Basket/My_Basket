//
// Created by Евгения Федотова
//

#ifndef RECIPEBOOK_H
#define RECIPEBOOK_H

#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QTextEdit>
#include <QPushButton>
#include <QMap>
#include "search_engine.h"

class RecipeBook : public QWidget{
Q_OBJECT

public:
    RecipeBook(QWidget *parent = 0);

    enum NextPrevMode {
        FindProduct_mode,
        FindRecipe_mode
    };

public slots:
    void add_product_func();
    void find_product_func();
    void put_in_basket_func();
    void find_recipe_func();
    void check_basket_func();

    void next_func();
    void previous_func();

private:
    QLineEdit *product_name_line;
    QLabel *product_name_label;
    QTextEdit *recipe_text;
    QLabel *recipe_label;

    //кнопки правой панели
    QPushButton *add_product_button;
    QPushButton *find_product_button;
    QPushButton *put_in_basket_button;
    QPushButton *find_recipe_button;
    QPushButton *check_basket_button; //отдельным окошком список всех добавленных продуктов

    //кнопки нижней панели
    QPushButton *next_button;
    QPushButton *previous_button;

    //структуры для хранения информации
    std::vector<search::product> basket_of_products;
    std::vector<search::product> res_of_request_products;
    QMap<QString, QString> map_recipes;

    NextPrevMode current_mode;
    long long num_current_object = 0;

    friend void search::put_product_in_basket(std::vector<search::product> &basket, search::product &prod);
};

#endif // RECIPEBOOK_H