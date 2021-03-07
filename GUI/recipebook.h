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

class RecipeBook : public QWidget{
Q_OBJECT

public:
    RecipeBook(QWidget *parent = 0);

public slots:
    void add_product_func();
    void find_product_func();
    void put_in_basket_func();
    void find_recipe_func();
    void check_basket_func();

    void next_recipe_func();
    void previous_recipe_func();

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
    QPushButton *next_recipe_button;
    QPushButton *previous_recipe_button;

    QMap<QString, QString> map_product_recipes_vector; //TODO: синхронизировать нужную DS
    QMap<QString, QString> map_recipes;
    QString old_product;
    QString old_recipe;
};

#endif // RECIPEBOOK_H