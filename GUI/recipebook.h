#ifndef RECIPEBOOK_H
#define RECIPEBOOK_H

#include <QLabel>
#include <QLineEdit>
#include <QMap>
#include <QPushButton>
#include <QTextEdit>
#include <QWidget>
#include "search_engine.h"

namespace Ui {

// class CategoryWindow;

class SummaryWindow : public QWidget {
    Q_OBJECT

public:
    SummaryWindow(QWidget *parent = nullptr);

public slots:
    static void end_program_func();
    // void start_again_func();

private:
    // CategoryWindow *category_window_; //начать с начала

    // QPushButton *start_again_button;
    QPushButton *end_program_button;

    QLabel *best_total_cost_label;
    QLabel *total_cost_number_label;
    QLabel *in_shop_label;
    QLabel *shop_name_label;

    int total_cost = 1000;
    std::string shop_name = "EuroSpar";
};

class RecipeBook : public QWidget {
    Q_OBJECT

public:
    RecipeBook(QWidget *parent = nullptr);

    enum NextPrevMode { FindProduct_mode, FindRecipe_mode };

public slots:
    void add_product_func();
    void add_recipe_func();
    void find_product_func();
    void put_in_basket_func();
    void find_recipe_func();
    void check_basket_func();
    void choose_recipe_func();

    void next_func();
    void previous_func();

private:
    QLineEdit *product_name_line;
    QLabel *product_name_label;
    QTextEdit *recipe_text;
    QLabel *recipe_label;

    //кнопки правой панели
    QPushButton *add_product_button;
    QPushButton *add_recipe_button;
    QPushButton *find_product_button;
    QPushButton *put_in_basket_button;
    QPushButton *find_recipe_button;
    QPushButton *choose_recipe_button;
    QPushButton *check_basket_button;  //отдельным окошком список всех
                                       //добавленных продуктов

    //кнопки нижней панели
    QPushButton *next_button;
    QPushButton *previous_button;

    //структуры для хранения информации
    std::vector<search::product> basket_of_products;
    std::vector<search::product> res_of_request_products;
    std::vector<search::Recipe> res_of_request_recipes;

    //завершающее окно
    SummaryWindow *summary_window;

    NextPrevMode current_mode;
    long long num_current_object = 0;
    std::string category;

    void clear_fields();
    void clear_fields_and_requests();
    void activate_search_bar();
    void text_field_find_regime(std::string const &s);

    friend void search::put_product_in_basket(
        std::vector<search::product> &basket,
        search::product &prod);
};

// void print_product_by_name(QTextEdit *text_field,
//                           search::product const &product);
// void print_product_by_name_price(QTextEdit *text_field,
//                                 search::product const &product);
// void print_products_vector(QTextEdit *text_field,
//                           std::vector<search::product> const &products_vec);
// void print_recipe(QTextEdit *text_field, search::Recipe const &recipe);

}  // namespace Ui

#endif  // RECIPEBOOK_H